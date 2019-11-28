/*
 * agent.cc
 *
 *  Created on: 25 set 2017
 *      Author: peppe
 */

#include "../headers/agent.h"
#include "../headers/ag_scheduler.h"
#include "../headers/writer.h"

using namespace omnetpp;
using namespace std;

agent::agent() {
    //   event = tictocMsg = nullptr;
}

agent::~agent() {
//    if (df_Service_Handler != nullptr) {
//        delete df_Service_Handler;
//    }
//    if (ag_Needs_Handler != nullptr) {
//        delete ag_Needs_Handler;
//    }
//    if (ag_Sched != nullptr) {
//        delete ag_Sched;
//    }
//    if (ag_Heuristic_Handler  != nullptr) {
//        delete ag_Heuristic_Handler;
//    }
//    if (ag_Server_Handler != nullptr) {
//        delete ag_Server_Handler;
//    }
//    if (ag_Neg_Handler != nullptr) {
//        delete ag_Neg_Handler;
//    }
//    if (tGen != nullptr) {
//        delete tGen;
//    }
//    if (ag_settings != nullptr) {
//        delete ag_settings;
//    }
//
//    if (!ag_tasks_vector.empty()) {
//        for (auto item : ag_tasks_vector) {
//            delete item;
//        }
//        ag_tasks_vector.clear();
//    }
//
//    if (!ag_specific_tasks_vector.empty()) {
//        for (auto item : ag_specific_tasks_vector) {
//            delete item;
//        }
//        ag_specific_tasks_vector.clear();
//    }
//
//    if (!df_tasks_vector.empty()) {
//        for (auto item : df_tasks_vector) {
//            delete item;
//        }
//        df_tasks_vector.clear();
//    }
//
//    if (!df_specific_tasks_vector.empty()) {
//        for (auto item : df_specific_tasks_vector) {
//            delete item;
//        }
//        df_specific_tasks_vector.clear();
//    }
}

void agent::initialize() {
    //get directory params
    string date = getParentModule()->par("timestamp");
    string user = getParentModule()->par("user");
    string path = "../simulations/" + user + "/" + date + "/inputs/";

    // initialize negotiation window
//    NEG_TIMEOUT = par("neg_timeout");

    //generate private_ag_settings
    ag_settings = new Ag_settings;

    //generate task set
    tGen = new TaskHandler;

    //generate needs handler
    //NOTE could me moved into agent because df doesn't have needs...(for now?)
    ag_Needs_Handler = new NeedsHandler;

    //initialize server handler (for EDF)
    if((int) par("sched_type") == EDF){
        bool msg_server_mode = (bool) par("msg_server_mode");
        //to handle msg server
        ag_Server_Handler = new ServerHandler;
        if (msg_server_mode) {
            int server_type = (int) par("server_type");
            double bandwidth = 0.1;
            double budget = 1;
            ag_Server_Handler->add_server(new Server(100, bandwidth, budget, (ServerType) server_type));
            ag_Server_Handler->add_server(new Server(200, bandwidth, budget, (ServerType) server_type));
        }
    }

    //if I'm the DF
    if (strcmp("DF", getName()) == 0) {
        //we use empty df for now
//        agentMSG *get_df_tasks_msg = set_df_tasks();
//        scheduleAt(0.0, get_df_tasks_msg);
        df_Service_Handler = new ServiceHandler;

        int type = par("sched_type");
        ag_Sched = new Ag_Scheduler((SchedType) type);
        ag_settings->set_ag_has_scheduler(true);
    }

    //if I'm an AGENT
    else {
        if((int) par("sched_type") == EDF) {
//          int server_type = (int) par("server_type");
            //note: inizializzazione server: solo per test sporadici!!! (impostazione temporanea)
            int ag_id = getIndex();
            //impostazione del server per ciascun agente in base all'id
            ag_Server_Handler->read_servers_from_json(path + "servers.json", ag_id);
        }

        // generating connection gate$0 -> agent
        ag_settings->set_ag_conn_table(getIndex(), getVectorSize());

        //generate heuristic_handler
        ag_Heuristic_Handler = new Hhandler;

        //generate negotiation session handler
        ag_Neg_Handler = new NegSessionHandler;

        //initialize statistics signal
        ddl_miss_signal = registerSignal("ddl_miss");

        agentMSG *get_ag_tasks_msg = set_ag_tasks();
        scheduleAt(0.0, get_ag_tasks_msg);

        agentMSG *get_ag_sched_msg = set_ag_scheduler();
        scheduleAt(0.0, get_ag_sched_msg);

        agentMSG *set_ag_services_msg = set_ag_services();
        scheduleAt(0.0, set_ag_services_msg);

        agentMSG *set_ag_needs_msg = set_ag_needs();
        scheduleAt(0.0, set_ag_needs_msg);
    }
// close initialize
}

void agent::handleMessage(cMessage *msg) {
    int sched_type = par("sched_type");
    SchedType scheduler = (SchedType) sched_type;
    if (scheduler == FCFS || scheduler == RR || scheduler == SJF)
        handleMessageGP(msg);
    else
        handleMessageRT(msg);
}

void agent::handleMessageGP(cMessage *msg){
    agentMSG *agMsg = check_and_cast<agentMSG *>(msg);
    //Handle messages sent to self
    if (agMsg->isSelfMessage() && agMsg->getNeg_step() != INIT) {
        switch (agMsg->getInformative()) {
        case SET_AG_TASKSET: {
            set_ag_taskset(agMsg);
            break;
        }
        case SCHEDULE: {
            schedule_taskset(agMsg);
            break;
        }
        case SET_DF_TASKSET: {
            set_df_taskset(agMsg);
            break;
        }
        case ACTIVATE_TASK: {
            activate_task(agMsg);
            break;
        }
        case CHECK_TASK_TERMINATED: {
            check_task_completion(agMsg);
            break;
        }
        case CHECK_DDL_MISS: {
            check_ddl_miss(agMsg);
            break;
        }
        case PUBLISH_SERVICES_DF: {
            publish_services(agMsg);
            break;
        }
        case GENERATE_AG_NEEDS: {
            generate_ag_needs(agMsg);
            break;
        }
        case RELEASE_NEED: {
            release_need(agMsg);
            break;
        }
        case ACKNOWLEDGE: {
            acknowledge_job(agMsg);
            break;
        }
        default:
            EV << "Event with informative: " << agMsg->getInformative()
                      << " not supported";
            break;
        }
    } // chiude isSelfMessage

    //Handle messages sent from other agents
    else {
        if (strcmp("DF", getName()) != 0) {
            handle_ag_msg(agMsg);
        }

        if (strcmp("DF", getName()) == 0) {
            handle_df_msg(agMsg);
        }
    }
}

void agent::handleMessageRT(cMessage *msg) {
    agentMSG *agMsg = check_and_cast<agentMSG *>(msg);
    //Handle messages sent to self
    if (agMsg->isSelfMessage() && agMsg->getNeg_step() != INIT) {
        switch (agMsg->getInformative()) {
        case SET_AG_TASKSET: {
            set_ag_taskset(agMsg);
            break;
        }
        case SCHEDULE: {
            schedule_taskset_rt(agMsg);
            break;
        }
        case SET_DF_TASKSET: {
            set_df_taskset(agMsg);
            break;
        }
        case ACTIVATE_TASK: {
            activate_task(agMsg);
            break;
        }
        case PREEMPT: {
            preempt(agMsg);
            break;
        }
        case CHECK_TASK_TERMINATED: {
            check_task_completion_rt(agMsg);
            break;
        }
        case CHECK_DDL_MISS: {
            check_ddl_miss(agMsg);
            break;
        }
        case PUBLISH_SERVICES_DF: {
            publish_services(agMsg);
            break;
        }
        case GENERATE_AG_NEEDS: {
            generate_ag_needs(agMsg);
            break;
        }
        case RELEASE_NEED: {
            release_need(agMsg);
            break;
        }
        case ACKNOWLEDGE: {
            acknowledge_job(agMsg);
            break;
        }
        case REPLENISH: {
            replenish(agMsg);
            break;
        }
        case -1:{
            //NOTE: solo per test (gantt)
            break;
        }
        default:
            EV << "Event with informative: " << agMsg->getInformative()
                      << " not supported";
            break;
        }
    } // chiude isSelfMessage

    //Handle messages sent from other agents
    else {
        if ((bool) par("msg_server_mode") == true && agMsg->getProcessed() == false) {
            create_msg_task(agMsg, "read");
        } else {
            if (strcmp("DF", getName()) != 0) {
                handle_ag_msg(agMsg);
            }
            if (strcmp("DF", getName()) == 0) {
                handle_df_msg(agMsg);
            }
        }
    }
}

void agent::handle_ag_msg(agentMSG *agMsg) {
    // Messages received FROM DF

    if ((strcmp("DF", agMsg->getSenderModule()->getName()) == 0)) {
        switch (agMsg->getContent()) {
        case PUBLISH: {
            break;
        }
        case REQUEST: {
            break;
        }
        case PROCESS_LIST: {
            process_list(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        } // close the switch
    }

    // Messages received FROM AGs
    //Negotiation phase
    else {
        switch (agMsg->getNeg_step()) {
        case INIT: {
            begin_neg(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case BID: {
            receive_bid(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case REJECTED: {
            reject(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case CLOSE: {
            close(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case REFUSED: {
            refuse(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case CONF_REQ: {
            confirm(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case CONFIRMED: {
            on_confirm(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        case BID_BROADCAST: {
            on_bid_broadcast(agMsg);
            cancelAndDelete(agMsg);
            break;
        }
        } // close the switch
    }
}

void agent::handle_df_msg(agentMSG *agMsg) {
    switch (agMsg->getContent()) {
    case PUBLISH: {
        df_publish(agMsg);
        cancelAndDelete(agMsg);
        break;
    }
    case REQUEST: {
        df_request(agMsg);
        cancelAndDelete(agMsg);
        break;
    }
    } // close the switch
}

void agent::finish() {
    if (strcmp("DF", getName()) != 0) {
        string timestamp = getParentModule()->par("timestamp");
        string user = getParentModule()->par("user");
        write_stats_json_report(getIndex(), ag_settings->get_ddl_check(),
                ag_settings->get_ddl_miss(), timestamp, user);
        write_acceptance_ratio(getIndex(), get_accept_ratio(), timestamp, user);

        //save_reports();
        save_ddl_json(timestamp, user);
        save_resp_per_task_json(timestamp, user);
        save_response_json(timestamp, user);
        save_lateness_json(timestamp, user);
        save_util_json(timestamp, user);
        save_pot_util_json(timestamp, user);
    }
    //
    while(!cSimulation::getActiveSimulation()->getFES()->isEmpty()){
        cEvent* evt = cSimulation::getActiveSimulation()->getFES()->removeFirst();
        agentMSG* msg = check_and_cast<agentMSG *>(evt);
        cancelAndDelete(msg);
    }
}

// *****************************************************************************
// *******                        BEHAVIOURS-GP                          *******
// *****************************************************************************

void agent::set_ag_taskset(agentMSG *msg) {
    //get directory params
    string date = getParentModule()->par("timestamp");
    string user = getParentModule()->par("user");
    string path = "../simulations/" + user + "/" + date + "/inputs/";

    EV << "SETTING_AG_TASKSET\n";
    //associate common tasks
//    ag_tasks_vector = tGen->create_common_tasks(getName(), getIndex());

//    //associate specific tasks (not to the DF for now)
//        ag_tasks_vector = tGen->create_specific_tasks(getName(), getIndex());

    //load tasks from file (knowledge)
    try {
        ag_tasks_vector = tGen->read_tasks_from_json(path + "knowledge.json", getIndex());
    } catch (exception const& ex) {
        cerr << "Error loading the taskset file\n";
        exit(EXIT_FAILURE);
    }
    cancelAndDelete(msg);
}

void agent::schedule_taskset(agentMSG *msg) {
    //get directory params
    string date = getParentModule()->par("timestamp");
    string user = getParentModule()->par("user");
   string path = "../simulations/" + user + "/" + date + "/inputs/";

    //get scheduler type from agent module parameter
    int type = par("sched_type");
    string scheduler_name;
    switch (type){
    case FCFS: scheduler_name = "FCFS"; break;
    case RR: scheduler_name = "RR"; break;
    case SJF: scheduler_name = "SJF"; break;
    default: scheduler_name = "UNKNOWN"; break;
    }

    if (!ag_settings->get_ag_has_scheduler()) {
        EV << "SETTING " << scheduler_name << " SCHEDULER\n";
        //associate scheduler
        ag_Sched = new Ag_Scheduler((SchedType) type);
        ag_settings->set_ag_has_scheduler(
                ag_Sched->ag_create_scheduler(tGen->read_tasks_from_json(path + "taskset.json", getIndex())));
        if (!ag_settings->get_ag_has_scheduler()) {
            //TODO: TO DECIDE WITH [MM] WHAT TO DO IN THIS CASE.
            //      TO STOP THE SIMULATION?
            EV << "Taskset not schedulable\n";
        }
    }

    if (!ag_Sched->get_tasks_vector_to_release().empty()) {
        //schedula gli arrivi dei task (carico il vett dei ready)
        ag_Sched->ag_sort_tasks_arrival();
        ag_Sched->ev_ag_tasks_vector_to_release();
        Task *p_task = ag_Sched->get_tasks_vector_to_release()[0];

        //Se il tempo di arrivo del task è maggiore dell'istante attuale,
        //rimanda il messaggio all'arrival time del task in considerazione
        //(in poche parole si mette in attesa)

        //write utilization report (non real-time)
        write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "release");

        if (fabs(p_task->getTaskArrivalTime() - simTime().dbl()) > ag_Sched->EPSILON) {
            agentMSG *task_activation_msg = set_next_task_arrival();
            scheduleAt(p_task->getTaskArrivalTime(), task_activation_msg);
            EV << "t: " << simTime().dbl() << ", task [" << p_task->getTaskId()
                      << "] arrival is scheduled at t: "
                      << p_task->getTaskArrivalTime() << "\n";

            //L'else si "attiva" quando si è arrivati al tempo di arrivo del task
            //(in poche parole, dopo l'attesa)
        } else if (fabs(p_task->getTaskArrivalTime() - simTime().dbl()) < ag_Sched->EPSILON) {

            //if the task's number of execution is set, decrease it
            int n_exec = p_task->getTaskNExec();
            if(n_exec > 0){
                p_task->setTaskNExec(n_exec - 1);
            }

            //if the task has not been activated, set the release time at t_now
            if (p_task->getTaskFirstActivation() == -1)
                p_task->setTaskReleaseTime(simTime().dbl());

            EV << "t: " << simTime().dbl() << ", ARRIVED task:["
                      << p_task->getTaskId() << "]\n";

            // task's number of executions
            EV << "Executions left: " << n_exec << endl;

            bool single_ready_task = ag_Sched->ag_task_arrived();

            //task ddl_miss check at arrival time
            double t_ddl_miss = p_task->getTaskArrivalTime()
                    + p_task->getTaskDeadLine();

            //EV <<"AG: " << getIndex() << " T: "<< p_task->getTaskId() << " TD: " << p_task->getTaskDemander() << "\n";


            agentMSG *check_task_ddl_miss_msg = set_check_task_ddl_miss(p_task);
            scheduleAt(t_ddl_miss, check_task_ddl_miss_msg);
            EV << "t: " << simTime().dbl() << ", DDL check for task:["
                      << p_task->getTaskId() << "] scheduled at t: "
                      << t_ddl_miss << "\n";
            if (single_ready_task) {
                // only one task in the ready queue so it gets the cpu
                // scheduling the task execution
                agentMSG *task_activation_msg = set_task_activation();
                scheduleAt(simTime().dbl(), task_activation_msg);
            } else {
                if (type == SJF) {
                    ag_Sched->ag_sort_tasks_arrival();
                    ag_Sched->ag_sort_tasks_ready();
                } else {
                    ag_Sched->ag_sort_tasks_arrival();
                }
            }

            //  -------------------------------------------------------------------------------  //

            //check if t is periodic
            if (p_task->getTaskPeriod() > 0) {
                EV << "Task:[" << p_task->getTaskId()
                          << "] is periodic, copied back into the -to-be-released-queue!\n";
                double n_arrival_time = simTime().dbl() + p_task->getTaskPeriod();
                Task* np_task;
                np_task = tGen->cloneTask(p_task);
                np_task->setTaskLastActivation(-1);
                np_task->setTaskFirstActivation(-1);
                np_task->setTaskCompTimeRes(p_task->getTaskCompTime());
                np_task->setTaskArrivalTime(n_arrival_time);
                n_exec = p_task->getTaskNExec();
                if (n_exec > 0 || n_exec == -1) {
                    ag_Sched->ag_add_task_in_vector_to_release(np_task);
                    ag_Sched->ag_sort_tasks_arrival();
                }
            }
            if (!ag_Sched->get_tasks_vector_to_release().empty()) {
                ag_Sched->ag_sort_tasks_arrival();
                agentMSG *task_arrival_msg = set_next_task_arrival();
                scheduleAt(
                        ag_Sched->get_tasks_vector_to_release()[0]->getTaskArrivalTime(),
                        task_arrival_msg);
                EV
                          << "More Task(s) to release in the vector, scheduling next check for arrival\n";
            }
        }

        else if ((simTime().dbl()
                > ag_Sched->get_tasks_vector_to_release()[0]->getTaskArrivalTime())
                && (ag_Sched->get_tasks_vector_to_release()[0]->getTaskCompTimeRes()
                        > 0)) {
            EV << "SONO FINITO QUI-------COSA---DEVO---FARE???";
        }
    }
    cancelAndDelete(msg);
}

void agent::set_df_taskset(agentMSG *msg) {
    EV << "SETTING_DF_TASKSET\n";
    //associate tasks to DF
    df_tasks_vector = tGen->create_df_tasks(getName(), getIndex());
    cancelAndDelete(msg);
}

void agent::activate_task(agentMSG *msg) {
    // --ACTIVATE TASK--
    if (!ag_Sched->get_tasks_vector_ready().empty()) {
        Task *new_task;
        Task *p_server = nullptr;
        new_task = ag_Sched->get_tasks_vector_ready()[0];

        // server
        if (new_task->is_server()) {
            p_server = new_task;
            new_task = p_server->get_head();
            if (p_server->get_server_type() == DSS)
                p_server->reset(simTime().dbl());
            EV << "t: " << simTime().dbl() << ", SERVER "
                      << p_server->getTaskServer() << " ACTIVATED tskId:["
                      << new_task->getTaskId() << "] tskDm: ag["
                      << new_task->getTaskDemander() << "] tskEx: ag["
                      << new_task->getTaskExecuter() << "] tskRt: "
                      << new_task->getTaskReleaseTime() << " currDdl: "
                      << p_server->get_curr_ddl() << " budget: "
                      << p_server->get_curr_budget() << endl;
        } else {
            EV << "t: " << simTime().dbl() << ", ACTIVATED tskId:["
                      << new_task->getTaskId() << "] tskDm: ag["
                      << new_task->getTaskDemander() << "] tskEx: ag["
                      << new_task->getTaskExecuter() << "] tskRt: "
                      << new_task->getTaskReleaseTime() << endl;
        }


        EV << "Task:[" << new_task->getTaskId() << "], C_Res: "
                  << new_task->getTaskCompTimeRes() << "\n";

        /* t_comp is assigned according to the scheduling algorithm */
        double t_comp;
        if (ag_Sched->get_sched_type() == RR) {
            const double QUANTUM = par("quantum");
            t_comp = min(QUANTUM + simTime().dbl(),
                    new_task->getTaskCompTimeRes() + simTime().dbl());
        }

        // CBS
        else if(p_server != nullptr) {
            t_comp = min(p_server->get_curr_budget() + simTime().dbl(),
                    new_task->getTaskCompTimeRes() + simTime().dbl());
        }

        else {
            t_comp = simTime().dbl() + new_task->getTaskCompTimeRes();
        }

        //note: test per il gantt
//        char msgname[30];
//        sprintf(msgname, "Active task: %d", new_task->getTaskId());
//        agentMSG *msg = new agentMSG(msgname);
//        msg->setInformative(-1);
//        scheduleAt(simTime().dbl(), msg);

        // scheduling task completion check
        agentMSG *check_task_complete_msg = set_check_task_complete(new_task,
                t_comp);
        scheduleAt(t_comp, check_task_complete_msg);
        EV << "t: " << simTime().dbl() << ", scheduled check for completion task:["
                  << new_task->getTaskId() << "] at t: " << t_comp << "\n";

        //if task's first activation
        if (new_task->getTaskFirstActivation() == -1) {
            new_task->setTaskFirstActivation(simTime().dbl());
            new_task->setTaskCompTimeRes(new_task->getTaskCompTime());
            if(p_server != nullptr){
                p_server->setTaskFirstActivation(simTime().dbl());
            }
        }
        if (p_server != nullptr) {
            p_server->setTaskLastActivation(simTime().dbl());
            new_task->setTaskLastActivation(simTime().dbl());
            ag_Sched->update_active_task_in_sorted_tasks_vector(p_server);
        } else {
            new_task->setTaskLastActivation(simTime().dbl());
            ag_Sched->update_active_task_in_sorted_tasks_vector(new_task);
        }
    }
    cancelAndDelete(msg);
}

void agent::check_task_completion(agentMSG *agMsg) {
    //--CHECK TASK FINITO--
    if (!ag_Sched->get_tasks_vector_ready().empty()) {
        Task *p_task;
        p_task = ag_Sched->get_tasks_vector_ready()[0];
        EV << "t: " << simTime().dbl() << ", checking COMPLETION for task ["
                  << agMsg->getAg_task_id() << "]\n";
        /*  it might have been killed due to ddl_miss so we need the following check
         *  or it can be preempted so it didn't finish and we need to check in a second time
         */
        if ((agMsg->getAg_task_id() == p_task->getTaskId())
                && (p_task->getTaskDemander() == agMsg->getAg_task_demander())
                && (p_task->getTaskReleaseTime() == agMsg->getAg_task_release_time())
                && (p_task->getTaskLastActivation() != -1)
                && (p_task->getTaskLastActivation() < simTime().dbl())) {
            // EV<<"t: " << simTime().dbl() << ", check task: "<< p_task->getTaskId() << " completion\n";
            double t_CRes = p_task->getTaskCompTimeRes();
            double last_computation = simTime().dbl()
                    - p_task->getTaskLastActivation();
            p_task->setTaskCompTimeRes(t_CRes - last_computation);
            if (fabs(p_task->getTaskCompTimeRes()) < ag_Sched->EPSILON) {
                EV << "t: " << simTime().dbl() << ", COMPLETED tskId:["
                          << p_task->getTaskId() << "] tskDm: ag["
                          << p_task->getTaskDemander() <<"] tskEx: ag["
                          << p_task->getTaskExecuter() << "] tskRt: "
                          << p_task->getTaskReleaseTime() << endl;
                //remove head on the ordered vector
                ag_Sched->ag_remove_head_in_ready_tasks_vector();

                //write lateness report
                double ddl = p_task->getTaskReleaseTime()
                        + p_task->getTaskDeadLine();
                double lateness = simTime().dbl() - ddl;
                if (lateness > 0) {
                    int agent_id = getIndex();
                    write_lateness_json_report(p_task, agent_id, lateness, simTime().dbl());
                }

//                //write response time report
                double resp_time = simTime().dbl() - p_task->getTaskReleaseTime();
                write_response_json_report(p_task, getIndex(), simTime().dbl(),
                        resp_time);

                //write response time per task report
                write_json_resp_per_task(p_task, getIndex(), simTime().dbl(), resp_time);

                //write utilization report
                write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "task completed");

                //schedule next activation
                if (!ag_Sched->get_tasks_vector_ready().empty()) {
                    p_task = ag_Sched->get_tasks_vector_ready()[0];
                    agentMSG *task_activation_msg = set_task_activation();
                    scheduleAt(simTime().dbl(), task_activation_msg);
                }

                /**
                 * RR scheduling is (almost) all here!
                 */

            } else if (p_task->getTaskCompTimeRes() > 0) {
                if (ag_Sched->get_sched_type() == RR) {
                    ag_Sched->ag_remove_head_in_ready_tasks_vector();
                    double next_arrival_time = simTime().dbl();
                    if (!ag_Sched->get_tasks_vector_ready().empty()) {
                        Task *next_task = ag_Sched->get_tasks_vector_ready()[0];
                        if (next_task->getTaskCompTimeRes()
                                > ag_Sched->get_quantum()) {
                            next_arrival_time += ag_Sched->get_quantum();
                        } else
                            next_arrival_time +=
                                    next_task->getTaskCompTimeRes();
                    }
                    p_task->setTaskArrivalTime(next_arrival_time);
                    p_task->setTaskLastActivation(simTime().dbl());
                    ag_Sched->ag_add_task_in_ready_tasks_vector(p_task);
                    EV << "t: " << simTime().dbl() << ", EXPIRED tskId:["
                              << p_task->getTaskId() << "] tskDm: ag["
                              << p_task->getTaskDemander() << "] tskEx: ag["
                              << p_task->getTaskExecuter() << "] tskRt: "
                              << p_task->getTaskReleaseTime() << endl;
                    agentMSG *task_activation_msg = set_task_activation();
                    scheduleAt(simTime().dbl(), task_activation_msg);
                }
//                else if (ag_Sched->get_sched_type() == FCFS){
//                    agentMSG *check_task_ddl_miss_msg = set_check_task_ddl_miss(
//                            p_task);
//                    scheduleAt(simTime().dbl(), check_task_ddl_miss_msg);
//                    EV << "t: " << simTime().dbl() << ", DDL check for task:["
//                              << p_task->getTaskId() << "] scheduled at t: "
//                              << simTime().dbl() << "\n";
//                }
            }

            /******************************/

        } else {
            //Task *nc_t;
            //nc_t = ag_CBS_Sched->get_single_task_by_id_from_vector_sorted_by_ddl(agMsg->getAg_task_id());
            //EV<<"t: " << simTime().dbl() << ", task:["<< agMsg->getAg_task_id() << "] NOT completed, C_R: " << nc_t->getTaskCompTimeRes() << "\n";
        }
    }
    cancelAndDelete(agMsg);
}

void agent::check_ddl_miss(agentMSG *agMsg) {
    // --- CHECK DDL_MISS
    ag_settings->add_ddl_check();
    EV << "t: " << simTime().dbl() << ", checking DDL_MISS for task:["
              << agMsg->getAg_task_id() << "]\n";

    if (!ag_Sched->get_tasks_vector_ready().empty()) {
//        Task *p_task;
//        p_task = ag_Sched->get_tasks_vector_ready()[0];
        Task *p_task = ag_Sched->get_ready_task_by_id(agMsg->getAg_task_id(),
                agMsg->getSource(),
                agMsg->getAg_task_release_time());

        int first_task_id = ag_Sched->get_tasks_vector_ready()[0]->getTaskId();

        //Condizione di ddl miss
        //c_res contiene il tempo residuo che serve al task per completare,
        //calcolato nel momento in cui perde la deadline
        double c_res;
        c_res = ag_Sched->get_ddl_miss(p_task, first_task_id);
        if (fabs(c_res) > ag_Sched->EPSILON && c_res != -1) {

//          //remove head on the ordered vector
//            ag_Sched->ag_remove_head_in_ready_tasks_vector();

            //remove task on the ordered vector
//            ag_Sched->ag_remove_task_in_ready(agMsg->getAg_task_id());

            //calculate the utilization factor when a ddl_miss occurs
            double ag_utilization = ag_Sched->ag_sched_test(ag_Sched->get_tasks_vector_to_release());

            //calculate the number of tasks when a ddl_miss occurs (changed to ready)
            int num_tasks = ag_Sched->get_tasks_vector_ready().size();

            //writing ddl_miss xml file note: commented for faster test
            write_ddl_json_report(p_task, simTime().dbl(), c_res, ag_utilization, num_tasks);
            ag_settings->add_ddl_miss();
//
//            //emitting ddl miss statistic signal
//            int ddl_miss_count = ag_settings->get_ddl_miss();
//            emit(ddl_miss_signal, ddl_miss_count);

            EV << "t: " << simTime().dbl() << ", task:[" << agMsg->getAg_task_id()
                      << "] MISSED the DDL\n";
//            EV << ", task:[" << agMsg->getAg_task_id()
//                      << "] removed from the list and scheduled next activation\n";
//
//            //scheduling next task activation
//            if (!ag_Sched->get_tasks_vector_ready().empty()) {
//                p_task = ag_Sched->get_tasks_vector_ready()[0];
//                agentMSG *task_activation_msg = set_task_activation();
//                scheduleAt(simTime().dbl(), task_activation_msg);
//            }
        }
    }
    EV << "Ag_DDL_miss: " << ag_settings->get_ddl_miss() << "\n";
    cancelAndDelete(agMsg);
}

void agent::publish_services(agentMSG *msg) {
    EV << "Publish services on DF table\n";
    bubble("Publishing Services");

    // If at least one task is public (service) it is published on
    // the DF table
    int i = 0;
    bool pub = false;
    while (!pub && i < ag_tasks_vector.size()) {
        if (ag_tasks_vector[i]->get_t_is_public()) {
            agentMSG *pub_services_msg = publish_services_to_DF();
            if ((bool) par("msg_server_mode") == true) {
                create_msg_task(pub_services_msg, "write");
                pub = true;
            } else {
                forwardMessage(pub_services_msg);
                pub = true;
            }
        }
        i++;
    }
    cancelAndDelete(msg);
}

void agent::generate_ag_needs(agentMSG *msg) {
    //get directory params
    string date = getParentModule()->par("timestamp");
    string user = getParentModule()->par("user");
   string path = "../simulations/" + user + "/" + date + "/inputs/";

    EV << "Generating Ag needs\n";
    bubble("let me think... what do I need?");

    //ag_Needs_Handler->create_rnd_needs_vector();

    //the DF doesn't have needs (for now?)
//    if (strcmp("DF", getName()) != 0) {
//        ag_Needs_Handler->create_static_needs_vector(getName(), getIndex());
//    }

    //read needs
    if (strcmp("DF", getName()) != 0) {
          ag_Needs_Handler->read_needs_from_json(path + "needs.json", getIndex());
      }

    // scheduling the needs release
    vector<Need*> p_ag_needs_vector;
    p_ag_needs_vector = ag_Needs_Handler->get_needs_vector();
    for (int i = 0; i < p_ag_needs_vector.size(); i++) {
        agentMSG *rel_need_msg = set_release_need(p_ag_needs_vector[i]);
        scheduleAt(rel_need_msg->getNeed()->get_need_release(), rel_need_msg);
    }
    cancelAndDelete(msg);
}

void agent::release_need(agentMSG *agMsg) {
    bubble("uhm.. it seems I need something, let me ask for it!");
//    Need *need = ag_Needs_Handler->get_need_by_id(agMsg->getAg_need_id());
    Need *need = agMsg->getNeed();
    //note more than 1 task per need
    if (need->get_needed_t_ids().size() > 1) {
        EV << "Needed tasks for agent[" << getIndex() << "]:\n";
        for (int i = 0; i < need->get_needed_t_ids().size(); i++) {
            EV << " - task[" << need->get_needed_t_ids()[i] << "]\n";
        }
    }
    //note only one task per need
//    vector<int> p_needed_task_ids = need->get_needed_t_ids();
//    double p_needed_t_R = need->get_needed_t_R();
//    double p_needed_t_E = need->get_needed_t_E();
//    int p_needed_n_exec = need->get_needed_t_n_exec();
//    int need_id = need->get_need_id();
    EV << "ARRIVED NEED: " << need->get_need_id() << " TASK REQ ID: "
              << need->get_needed_t_ids()[0] << "\n";
    // Request to the DF the list of agents available for a certain task
    agentMSG *get_service_ag_list_msg = get_service_ag_list_from_DF(need);
    if ((bool) par("msg_server_mode") == true){
        create_msg_task(get_service_ag_list_msg, "write");
    } else {
        forwardMessage(get_service_ag_list_msg);
    }
    cancelAndDelete(agMsg);
}

void agent::acknowledge_job(agentMSG *agMsg) {
    int neg_type = par("neg_type");
    Need* p_need = agMsg->getNeed();
    // Retrieve open session
    NegSession* open_session = ag_Neg_Handler->get_neg_session(p_need);
    vector<Bid*> bids = open_session->get_bids();
    if (!bids.empty()) {
        //selects first bidder
        int heuristic = par("bidder_heuristic");
        int p_executor = ag_Heuristic_Handler->select_bidder(heuristic, bids, neg_type);
        if (neg_type == CNCP) {
            agentMSG *set_req_conf_msg = req_conf_msg(p_need, p_executor);
            if ((bool) par("msg_server_mode") == true) {
                create_msg_task(set_req_conf_msg, "write");
            } else {
                forwardMessage(set_req_conf_msg);
            }
        } else if (neg_type == EN) {
           double tmp_best = open_session->get_tmp_best();
           double curr_best = open_session->get_curr_best(neg_type);
           int round = open_session->get_round();
           open_session->increase_round();
            if (tmp_best != curr_best && bids.size() > 1) {
                open_session->set_best_bid(curr_best);
                // broadcast new offer
                for (int i = 0; i < bids.size(); i++) {
                    if (bids[i]->getContractor() != p_executor) {
                        agentMSG *broadcast_msg = bid_broadcast_msg(p_need,
                                bids[i]->getContractor(), round, curr_best);
                        if ((bool) par("msg_server_mode") == true) {
                            create_msg_task(broadcast_msg, "write");
                        } else {
                            forwardMessage(broadcast_msg);
                        }
                    }
                }
               // re-schedule acknowledge
                agentMSG *ack_neg_msg = ack_msg(p_need);
//                scheduleAt(simTime().dbl() + NEG_TIMEOUT, ack_neg_msg);
                scheduleAt(simTime().dbl() + p_need->get_timeout(), ack_neg_msg);

           } else {
               // do what's below (close with best and refuse the others)
               //note: optimize code repetition...
                agentMSG *close_neg_msg = close_msg(p_need, p_executor);
                if ((bool) par("msg_server_mode") == true) {
                    create_msg_task(close_neg_msg, "write");
                } else {
                    forwardMessage(close_neg_msg);
                }
                //refuse all the remaining proposals
                if (!bids.empty()) {
                    for (int i = 0; i < bids.size(); i++) {
                        if (bids[i]->getContractor() != p_executor) {
                            agentMSG *refuse_neg_msg = refuse_msg(p_need,
                                    bids[i]->getContractor());
                            if ((bool) par("msg_server_mode") == true) {
                                create_msg_task(refuse_neg_msg, "write");
                            } else {
                                forwardMessage(refuse_neg_msg);
                            }
                        }
                    }
                }
                bids.clear();
                ag_Neg_Handler->remove_neg_session(p_need);
           }
        } else {
            agentMSG *close_neg_msg = close_msg(p_need, p_executor);
            if ((bool) par("msg_server_mode") == true) {
                create_msg_task(close_neg_msg, "write");
            } else {
                forwardMessage(close_neg_msg);
            }
            //refuse all the remaining proposals
            if (!bids.empty()) {
                for (int i = 0; i < bids.size(); i++) {
                    if (bids[i]->getContractor() != p_executor) {
                        agentMSG *refuse_neg_msg = refuse_msg(p_need,
                                bids[i]->getContractor());
                        if ((bool) par("msg_server_mode") == true) {
                            create_msg_task(refuse_neg_msg, "write");
                        } else {
                            forwardMessage(refuse_neg_msg);
                        }
                    }
                }
            }
            bids.clear();
            ag_Neg_Handler->remove_neg_session(p_need);
        }
    } else {
        double bid = open_session->get_tmp_best() - 100; //note set decreasing step as constant
        if (neg_type == DU && (bid > 0)) {
            vector<int> contractors = agMsg->getAgents_per_need();
            int round = open_session->get_round();
            open_session->increase_round();
            open_session->set_best_bid(bid);
            // broadcast new offer
            for (int i = 0; i < contractors.size(); i++) {
                agentMSG *broadcast_msg = bid_broadcast_msg(p_need, contractors[i], round, bid);
                if ((bool) par("msg_server_mode") == true) {
                    create_msg_task(broadcast_msg, "write");
                } else {
                    forwardMessage(broadcast_msg);
                }
            }
            agentMSG *ack_neg_msg = ack_msg(p_need);
            ack_neg_msg->setAgents_per_need(contractors);
//            scheduleAt(simTime().dbl() + NEG_TIMEOUT, ack_neg_msg);
            scheduleAt(simTime().dbl() + p_need->get_timeout(), ack_neg_msg);
        }
        EV << "Nobody wants to help me :(\n";
    }
    cancelAndDelete(agMsg);
}

// *****************************************************************************
// *******                        BEHAVIOURS-RT                          *******
// *****************************************************************************

void agent::schedule_taskset_rt(agentMSG *msg) {
    //get directory params
    string date = getParentModule()->par("timestamp");
    string user = getParentModule()->par("user");
    string path = "../simulations/" + user + "/" + date + "/inputs/";

    //get scheduler type from agent
    int type = par("sched_type");
    string scheduler_name;
    switch (type){
        case EDF: scheduler_name = "EDF"; break;
        case RM: scheduler_name = "RM"; break;
        default: scheduler_name = "UNKNOWN"; break;
        }
    if (!ag_settings->get_ag_has_scheduler()) {
        EV << "SETTING " << scheduler_name << " SCHEDULER\n";
        //associate scheduler
        ag_Sched = new Ag_Scheduler((SchedType) type);
        ag_settings->set_ag_has_scheduler(
                ag_Sched->ag_create_scheduler(tGen->read_tasks_from_json(path + "taskset.json", getIndex())));

        //note CBS -> initialize servers
//        vector<int> servers_ids = { 1, 2, 3 };
//        ag_Server_Handler = new ServerHandler(servers_ids);

        if (!ag_settings->get_ag_has_scheduler()) {
            //TODO: TO DECIDE WITH [MM] WHAT TO DO IN THIS CASE.
            //      TO STOP THE SIMULATION?
            EV << "Taskset not schedulable\n";
        }
    }

    if (!ag_Sched->get_tasks_vector_to_release().empty()) {
        //schedula gli arrivi dei task (carico il vett dei ready)
        ag_Sched->ag_sort_tasks_arrival();
        ag_Sched->ev_ag_tasks_vector_to_release();

        Task *p_task = ag_Sched->get_tasks_vector_to_release()[0];
        Task *p_server = nullptr;

        //Se il tempo di arrivo del task è maggiore dell'istante attuale,
        //rimanda il messaggio all'arrival time del task in considerazione
        //(in poche parole si mette in attesa)
        if (fabs(p_task->getTaskArrivalTime() - simTime().dbl()) > ag_Sched->EPSILON) {
            //write utilization report
            write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "release");

            agentMSG *task_activation_msg = set_next_task_arrival();

            // set priorità dei messaggi
            task_activation_msg->setSchedulingPriority(1);

            scheduleAt(p_task->getTaskArrivalTime(), task_activation_msg);
            EV << "t: " << simTime().dbl() << ", task [" << p_task->getTaskId()
                      << "] arrival is scheduled at t: "
                      << p_task->getTaskArrivalTime() << "\n";

            //L'else si "attiva" quando si è arrivati al tempo di arrivo del task
            //(in poche parole, dopo l'attesa)
        } else if (fabs(p_task->getTaskArrivalTime() - simTime().dbl()) < ag_Sched->EPSILON) {

            //if the task's number of execution is set, decrease it
            int n_exec = p_task->getTaskNExec();
            if(n_exec > 0){
                p_task->setTaskNExec(n_exec - 1);
            }

            //if the task has not been activated, set the release time at t_now
            if (p_task->getTaskFirstActivation() == -1){
                p_task->setTaskReleaseTime(simTime().dbl());
                // CBS: handle service
                int s_id = p_task->getTaskServer();
                if (s_id != -1) {
                    p_server = ag_Server_Handler->get_server(s_id);
                    if (p_server->is_empty()) {
                        p_server->setTaskId(p_task->getTaskId());
                        p_server->setTaskDemander(p_task->getTaskDemander());
                        p_server->setTaskExecuter(p_task->getTaskExecuter());
                        p_server->setTaskReleaseTime(simTime().dbl());
                        p_server->setTaskArrivalTime(p_task->getTaskArrivalTime());
                        p_server->setTaskDeadLine(p_server->get_curr_ddl());
                        //note si potrebbe aggiungere
//                        p_task->setTaskDeadLine(p_server->get_curr_ddl());
                        p_server->push_back(p_task);

                        p_server->reset(simTime().dbl(), p_task->getTaskCompTime());
                        //replace the task with the server
                        ag_Sched->ag_replace_task_to_release(p_server);
                    } else {
                        p_server->push_back(p_task);
                    }
                }
            }

            EV << "t: " << simTime().dbl() << ", ARRIVED tskId:["
                                      << p_task->getTaskId() << "] tskDm: " << p_task->getTaskDemander() <<" tskRt: " << p_task->getTaskReleaseTime() << endl;

            // task's number of executions
            EV << "Executions left: " << n_exec << endl;

            //check if t is periodic
            if (p_task->getTaskPeriod() > 0) {
                EV << "Task:[" << p_task->getTaskId()
                          << "] is periodic, copied back into the -to-be-released-queue!\n";
                double n_arrival_time = simTime().dbl() + p_task->getTaskPeriod();
                Task* np_task;
                np_task = tGen->cloneTask(p_task);
                np_task->setTaskLastActivation(-1);
                np_task->setTaskFirstActivation(-1);
                np_task->setTaskCompTimeRes(p_task->getTaskCompTime());
                np_task->setTaskArrivalTime(n_arrival_time);
                n_exec = p_task->getTaskNExec();
                if (n_exec > 0 || n_exec == -1) {
                    ag_Sched->ag_add_task_in_vector_to_release(np_task);
                }
            }
            if (!ag_Sched->get_tasks_vector_to_release().empty()) {
                ag_Sched->ag_sort_tasks_arrival();
                agentMSG *task_arrival_msg = set_next_task_arrival();

                // set priorit� dei messaggi
                task_arrival_msg->setSchedulingPriority(1);

                scheduleAt(
                        ag_Sched->get_tasks_vector_to_release()[0]->getTaskArrivalTime(),
                        task_arrival_msg);
                EV
                          << "More Task(s) to release in the vector, scheduling next check for arrival\n";
            }

            //task ddl_miss check at arrival time (skip for servers!)
            double t_ddl;
            if (p_task->getTaskServer() == -1) {
                t_ddl = p_task->getTaskArrivalTime()
                        + p_task->getTaskDeadLine();
                p_task->setTaskDeadLine(t_ddl);
            }

            // controlla c_res_head_ready negativo!
            double c_res_head_ready = 0;
            if (!ag_Sched->get_tasks_vector_ready().empty()) {
                if (ag_Sched->get_tasks_vector_ready()[0]->is_server()) {
                    c_res_head_ready =
                            ag_Sched->get_tasks_vector_ready()[0]->get_head()->getTaskCompTimeRes()
                                    - (simTime().dbl()
                                            - ag_Sched->get_tasks_vector_ready()[0]->get_head()->getTaskLastActivation());
                } else {
                    c_res_head_ready =
                            ag_Sched->get_tasks_vector_ready()[0]->getTaskCompTimeRes()
                                    - (simTime().dbl()
                                            - ag_Sched->get_tasks_vector_ready()[0]->getTaskLastActivation());
                }
            }

            //note pu� servire [?]
            //ag_Sched->ag_sort_tasks_ddl(c_res_head_ready);

            // cbs
            bool single_ready_task = ag_Sched->ag_task_arrived(p_server);


            //EV <<"AG: " << getIndex() << " T: "<< p_task->getTaskId() << " TD: " << p_task->getTaskDemander() << "\n";

            if (p_task->getTaskServer() == -1) { // cbs
                agentMSG *check_task_ddl_miss_msg = set_check_task_ddl_miss(
                        p_task);
                scheduleAt(t_ddl, check_task_ddl_miss_msg);
                EV << "t: " << simTime().dbl() << ", DDL check for task:["
                          << p_task->getTaskId() << "] scheduled at t: "
                          << t_ddl << "\n";
            }

            if (single_ready_task) {
                // only one task in the ready queue so it gets the cpu
                // scheduling the task execution
                if(p_server == nullptr || p_server->queue_length() == 1) {
                    agentMSG *task_activation_msg = set_task_activation();
                    scheduleAt(simTime().dbl(), task_activation_msg);
                }
            } else if (!ag_Sched->get_tasks_vector_ready().empty()) {
                // edf preemption
                // more than one task in the ready queue: evaluate possible preemption
                Task *f_task;
                EV << "Non ordinato \n";
                EV << "CRes testa ready: " << c_res_head_ready << endl;
                ag_Sched->ev_ag_tasks_vector_ready();

                //NOTE: order according to algorithm
                ag_Sched->ag_sort_tasks_ready(c_res_head_ready);

                f_task = ag_Sched->get_tasks_vector_ready()[0];

                // check
                EV << "Ordinato \n";
                ag_Sched->ev_ag_tasks_vector_ready();

                EV << "First task id: [" << f_task->getTaskId()
                          << "] task ddl: " << f_task->getTaskDeadLine()
                          << endl;

                //Se il task da rilasciare (p_task) � lo stesso che sta in cima alla coda ready (f_task)
                if (p_task->getTaskId() == f_task->getTaskId()
                        && p_task->getTaskDemander()
                                == f_task->getTaskDemander()
                        && p_task->getTaskReleaseTime()
                                == f_task->getTaskReleaseTime()) {
                    // Preemption
                    //note: test per il gantt
                    Task* preempted_task = ag_Sched->get_tasks_vector_ready()[1];
                    agentMSG *task_preemption_msg = set_task_preemption(p_task, preempted_task->getTaskId());
                    task_preemption_msg->setSchedulingPriority(0);
                    scheduleAt(simTime().dbl(), task_preemption_msg);
                } // otherwise no preemption, the scheduler keeps going
            }

            EV << "Tasks running: " << ag_Sched->get_tasks_vector_ready().size()
                      << endl;
        }


        else if ((simTime().dbl()
                > ag_Sched->get_tasks_vector_to_release()[0]->getTaskArrivalTime())
                && (ag_Sched->get_tasks_vector_to_release()[0]->getTaskCompTimeRes()
                        > 0)) {
            EV << "SONO FINITO QUI-------COSA---DEVO---FARE???";
        }
    }
    cancelAndDelete(msg);
}

void agent::check_task_completion_rt(agentMSG *agMsg) {

    //--CHECK TASK FINITO--
    if (!ag_Sched->get_tasks_vector_ready().empty()) {
        Task *p_task;
        Task *p_server = nullptr;
        p_task = ag_Sched->get_tasks_vector_ready()[0];
        EV << "t: " << simTime().dbl() << ", checking COMPLETION for task ["
                  << agMsg->getAg_task_id() <<"] tskDm " << agMsg->getAg_task_demander() << "\n";
        /*  it might have been killed due to ddl_miss so we need the following check
         *  or it can be preempted so it didn't finish and we need to check in a second time
         */
        if ((agMsg->getAg_task_id() == p_task->getTaskId())
                && (p_task->getTaskDemander() == agMsg->getAg_task_demander())
                && (p_task->getTaskReleaseTime() == agMsg->getAg_task_release_time())
                && (p_task->getTaskLastActivation() != -1)
                && (p_task->getTaskLastActivation() < simTime().dbl())) {
            // EV<<"t: " << simTime().dbl() << ", check task: "<< p_task->getTaskId() << " completion\n";

            // server
            if(p_task->is_server()){
                p_server = p_task;
                p_task = p_server->get_head();
            }

            double t_CRes = p_task->getTaskCompTimeRes();
            double last_computation = simTime().dbl() - p_task->getTaskLastActivation();
            double comp_time_res = t_CRes - last_computation;

                // changed from "comp_time_res == 0"
            if (fabs(comp_time_res) < ag_Sched->EPSILON) {

                if(p_server != nullptr){
                    EV << "t: " << simTime().dbl() << ", SERVER "
                              << p_server->getTaskServer() << " COMPLETED tskId:["
                              << p_task->getTaskId() << "] tskDm: ag["
                              << p_task->getTaskDemander() << "] tskEx: ag["
                              << p_task->getTaskExecuter() << "] tskRt: "
                              << p_task->getTaskReleaseTime() << " budget: "
                              << p_server->get_curr_budget() << endl;
                } else {
                    EV << "t: " << simTime().dbl() << ", COMPLETED tskId:["
                              << p_task->getTaskId() << "] tskDm: ag["
                              << p_task->getTaskDemander() << "] tskEx: ag["
                              << p_task->getTaskExecuter() << "] tskRt: "
                              << p_task->getTaskReleaseTime() << endl;
                }

                //remove head on the ordered vector

                //note: Test per registrare solo i task completi (gantt)
//                char msgname[30];
//                sprintf(msgname, "Completed: %d", p_task->getTaskId());
//                agentMSG *complete = new agentMSG(msgname);
//                complete->setInformative(-1);
//                scheduleAt(simTime().dbl(), complete);
                //**************************************

                ag_Sched->ag_remove_head_in_ready_tasks_vector();

                // SERVERS : task completed
                if (p_server != nullptr) {
                    p_server->update_budget(last_computation);
                    p_server->pop_head();
                    if(p_server->get_server_type() == CBS) {
                         p_server->reset(simTime().dbl());
                    } else if(p_server->get_server_type() == TBS){
                        double c_req = 0;
                        if(p_server->get_head() != nullptr) c_req = p_server->get_head()->getTaskCompTimeRes();
                        p_server->reset(simTime().dbl(), c_req);
                    }
                    else if (p_server->get_server_type() == DSS){
                        agentMSG *release_msg = set_replenish_dss(p_task->getTaskServer(), last_computation);
                        scheduleAt(p_server->get_curr_ddl(), release_msg);
                        p_server->set_delay(p_server->get_curr_ddl());
                    }
                    //note controlla
                    int n_exec = p_task->getTaskNExec();
                    //note: added for repeated services
                    if (n_exec != -1){
                        n_exec -= 1;
                        if (n_exec != 0 && n_exec != -1 && p_task->get_period() != 0) {
                            EV << "Service executions left: " << n_exec << endl;
                            p_task->setTaskNExec(n_exec);
                            p_server->push_back(p_task);
                        }
                    }
                    if (!p_server->is_empty()) {
                        p_server->setTaskId(p_server->get_head()->getTaskId());
                        p_server->setTaskDemander(p_server->get_head()->getTaskDemander());
                        p_server->setTaskExecuter(p_server->get_head()->getTaskExecuter());
                        p_server->setTaskReleaseTime(p_server->get_head()->getTaskReleaseTime());
                        p_server->setTaskArrivalTime(p_server->get_head()->getTaskArrivalTime());
                        p_server->setTaskDeadLine(p_server->get_curr_ddl());
                        p_server->setTaskArrivalTime(simTime().dbl());
                        ag_Sched->ag_add_task_in_vector_to_release(p_server);
                        //write utilization report
                        write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "server-activation");
                        //note test per evitare ridondanza di messaggi set_next_task_arrival
                        cancel_redundant_msg("Setting next task arrival");

                        agentMSG *release_msg = set_next_task_arrival();
                        release_msg->setSchedulingPriority(1);
                        scheduleAt(simTime().dbl(), release_msg);
                    }
                    p_server->ev_queue();
                    //note Process message tasks
                    if(p_task->is_msg_task()){
                        if (strcmp(p_task->getType(), "read") == 0) {
                            p_task->getMessage()->setProcessed(true);
                            handleMessageRT(p_task->getMessage());
                        } else if (strcmp(p_task->getType(), "write") == 0){
                            forwardMessage(p_task->getMessage());
                        }
                    }
                }

                //write lateness report note: commented for faster test
                double lateness = simTime().dbl() - p_task->getTaskDeadLine();
                if (lateness > 0) {
                    int agent_id = getIndex();
                    write_lateness_json_report(p_task, agent_id, lateness, simTime().dbl());
                }

                //write response time report
                double resp_time = simTime().dbl() - p_task->getTaskReleaseTime();
                write_response_json_report(p_task, getIndex(), simTime().dbl(), resp_time);

                //write response time per task report
                write_json_resp_per_task(p_task, getIndex(), simTime().dbl(), resp_time);

                //write utilization report
                write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "task completed");

                //schedule next activation
                if (!ag_Sched->get_tasks_vector_ready().empty()) {
                    p_task = ag_Sched->get_tasks_vector_ready()[0];
                    agentMSG *task_activation_msg = set_task_activation();
                    scheduleAt(simTime().dbl(), task_activation_msg);
                }
            }
            //SERVERS: aperiodic task - not completed
            else if (p_server != nullptr) {
                double next_release = simTime().dbl();
                //if the budget has expired
                if (fabs(p_server->get_curr_budget() - last_computation) < ag_Sched->EPSILON) {
                    ag_Sched->ag_remove_head_in_ready_tasks_vector();
                    p_server->update_budget(last_computation);
                    if (p_server->get_server_type() == CBS || p_server->get_server_type() == TBS) {
                        p_server->reset(simTime().dbl());
                    } else if (p_server->get_server_type() == DSS) {
                        agentMSG *release_msg = set_replenish_dss(p_task->getTaskServer(), last_computation);
                        scheduleAt(p_server->get_curr_ddl(), release_msg);
                        double delay  = p_server->get_delay();
                        if(delay > simTime().dbl()) next_release = delay;
                        else next_release = p_server->get_curr_ddl();
                    }
                    p_server->setTaskDeadLine(p_server->get_curr_ddl());
                    p_task->setTaskCompTimeRes(comp_time_res);
                    p_task->setTaskLastActivation(simTime().dbl());
                    p_server->setTaskLastActivation(simTime().dbl());

                    // il server deve ripassare nella release queue!
                    p_server->setTaskArrivalTime(next_release);
                    ag_Sched->ag_add_task_in_vector_to_release(p_server);
                    //write utilization report
                    write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "server-release");
                    //note test per evitare ridondanza di messaggi set_next_task_arrival
                    cancel_redundant_msg("Setting next task arrival");

                    agentMSG *release_msg = set_next_task_arrival();
                    release_msg->setSchedulingPriority(1);
                    scheduleAt(simTime().dbl(), release_msg);

                    EV << "t: " << simTime().dbl() << ", SERVER "
                              << p_server->getTaskServer()
                              << " EXPIRED tskId:[" << p_task->getTaskId()
                              << "] tskDm: ag[" << p_task->getTaskDemander()
                              << "] tskEx: ag[" << p_task->getTaskExecuter()
                              << "] tskRt: " << p_task->getTaskReleaseTime()
                              << endl;

                    agentMSG *task_activation_msg = set_task_activation();
                    scheduleAt(simTime().dbl(), task_activation_msg);
                    p_server->ev_queue();
                }
            }
        }
    }
    cancelAndDelete(agMsg);
}

void agent::preempt(agentMSG *agMsg) {
    //PREEMPTION
    Task* running_task = ag_Sched->get_tasks_vector_ready()[0];
    if (agMsg->getAg_task_id() == running_task->getTaskId()
            && agMsg->getAg_task_demander() == running_task->getTaskDemander()
            && agMsg->getAg_task_release_time() == running_task->getTaskReleaseTime()
    ) {
        Task *preempted_task;
        Task *p_server = nullptr;
        preempted_task = ag_Sched->get_tasks_vector_ready()[1];

        if(preempted_task->is_server()){
            p_server = preempted_task;
            preempted_task = p_server->get_head();
        }

        EV << "t: " << simTime().dbl() << ", tskId:[" << running_task->getTaskId()
                  << "] tskDm: "<< running_task->getTaskDemander()<< " tskDDL: "<< running_task->getTaskDeadLine() <<" PREEMPTS task:[" << preempted_task->getTaskId()
                  << "]\n";

        double t_CRes = preempted_task->getTaskCompTimeRes();
        double last_computation = 0;
        double n_t_CRes = t_CRes;
        if (preempted_task->getTaskFirstActivation() != -1) {
             last_computation = simTime().dbl()
                    - preempted_task->getTaskLastActivation();
        }
        if (last_computation > 0) {
            preempted_task->setTaskCompTimeRes(t_CRes - last_computation);
            n_t_CRes = t_CRes - last_computation;

            //server
            if(p_server != nullptr){
                p_server->update_budget(last_computation);
            }

        }

        if (p_server != nullptr) {
            EV << "t: " << simTime().dbl() << ", SERVER "
                      << p_server->getTaskServer() << " PREEMPTED tskId:["
                      << preempted_task->getTaskId() << "] tskDm: ag["
                      << preempted_task->getTaskDemander() << "] tskEx: ag["
                      << preempted_task->getTaskExecuter() << "] tskRt: "
                      << preempted_task->getTaskReleaseTime() << " cRes: "
                      << n_t_CRes << " ddl: "
                      << preempted_task->getTaskDeadLine()  << " budget: "
                      << p_server->get_curr_budget() << endl;
        } else {
            EV << "t: " << simTime().dbl() << ", PREEMPTED tskId:["
                      << preempted_task->getTaskId() << "] tskDm: ag["
                      << preempted_task->getTaskDemander() << "] tskEx: ag["
                      << preempted_task->getTaskExecuter() << "] tskRt: "
                      << preempted_task->getTaskReleaseTime() << " cRes: "
                      << n_t_CRes << " ddl: "
                      << preempted_task->getTaskDeadLine() << endl;
        }

        // schedule preempting task exec
        agentMSG *task_activation_msg = set_task_activation();
        scheduleAt(simTime().dbl(), task_activation_msg);
    }
    else EV << "MAGIA" << endl;
    cancelAndDelete(agMsg);
}

void agent::replenish(agentMSG *agMsg){
    int server_id = agMsg->getAg_task_server();
    Task* p_server = ag_Server_Handler->get_server(server_id);
    p_server->replenish(agMsg->getReplenish());
    double budget = 0;
    if(!p_server->is_empty()){
        budget = p_server->get_curr_budget() - (simTime().dbl() - p_server->getTaskLastActivation());
    }
    else budget = p_server->get_curr_budget();
    EV << "t: " << simTime().dbl() << ", SERVER " << server_id
              << " REPLENISH tskId:[" << p_server->getTaskId() << "] tskDm: ag["
              << p_server->getTaskDemander() << "] tskEx: ag["
              << p_server->getTaskExecuter() << "] tskRt: "
              << p_server->getTaskReleaseTime() << " amount: "
              << agMsg->getReplenish() << " budget: "
              << budget << endl;
}

// *****************************************************************************
// *******                         NEGOTIATION                           *******
// *****************************************************************************

void agent::process_list(agentMSG *agMsg) {
    int neg_type = par("neg_type");
    //check if at least I have one possible executor - call for proposal
    if (!agMsg->getAgents_per_need().empty()) {
        EV << "List of possible AG executors received\n";
        vector<int> contractors = agMsg->getAgents_per_need();

        for (int id : contractors) {
            EV << " - Agent[" << id << "]\n";
        }

//        vector<int> p_needed_task_ids = agMsg->getAg_needed_tasks();
//        double p_needed_task_R = agMsg->getAg_needed_t_R();
//        double p_needed_task_E = agMsg->getAg_needed_t_E();
//        int p_needed_n_exec = agMsg->getAg_needed_n_exec();
//        int p_need_id = agMsg->getAg_need_id();
        // Initialize negotiation session - now takes need_id! ()
        Need *p_need = agMsg->getNeed();
        ag_Neg_Handler->add_neg_session(p_need);
        // note: Implement heuristic selection (user) -> to select the contractor(s)
        // try with random subset
        int heuristic = par("contractor_heuristic");
        ag_Heuristic_Handler->select_contractors(heuristic, contractors);
        for (int i = 0; i < contractors.size(); i++) {
            agentMSG *init_neg_msg = init_msg(p_need, contractors[i]);
            if (neg_type == EN || neg_type == DU) {
                double init_bid = ag_Heuristic_Handler->rand_in_range(0, 5000); // NOTE: set min and max as constants
                init_neg_msg->setBid(init_bid);
                ag_Neg_Handler->get_neg_session(p_need)->set_best_bid(init_bid);
            }
            if ((bool) par("msg_server_mode") == true) {
                create_msg_task(init_neg_msg, "write");
            } else {
                forwardMessage(init_neg_msg);
            }
        }
        // Schedule acknowldgement
        agentMSG *ack_neg_msg = ack_msg(p_need);
        if(neg_type == DU) ack_neg_msg->setAgents_per_need(contractors);
        // scheduleAt(simTime().dbl() + NEG_TIMEOUT, ack_neg_msg);
        scheduleAt(simTime().dbl() + p_need->get_timeout(), ack_neg_msg);
    } else {
        EV << "Nobody can help me :(\n";
    }
}

void agent::begin_neg(agentMSG *agMsg) {
    // update received requests
    update_requests();
    // contractor side
    int p_initiator = agMsg->getSource();
    Need* p_need = agMsg->getNeed();
    for (int needed_id : p_need->get_needed_t_ids()) {
        auto it = find_if(ag_tasks_vector.begin(), ag_tasks_vector.end(),
                [needed_id](Task* task)
                { return (task->getTaskId() == needed_id);});
        if (it != ag_tasks_vector.end()) {
            double min_T = p_need->get_needed_t_min();
            Task* pend_task = *it;
            pend_task->setTaskDemander(agMsg->getSource());
            if(min_T > 1){ //note: check if task parameters have been set for RBNP [using min_T as sentinel]
                pend_task->setTaskDeadLine(min_T);
                pend_task->setTaskPeriod(min_T);
            }
            ag_Sched->ag_add_pending_task(pend_task);
        }
    }
    bool policy_holds = false;
    double bid = 0;
    double utilization = -1;
    const char* reason;
    int policy = par("neg_type");
    switch (policy) {
    case CNCP:
    case CNET: {
        policy_holds = ag_Sched->check_cnet(getIndex(), busy, p_need);
        reason = "agent busy";
        break;
    }
    case DU: {
        policy_holds = ag_Sched->check_cnet(getIndex(), busy, p_need) && ag_Heuristic_Handler->get_raise_chance(1, policy);
        reason = "yet too much for me...";
        break;
    }
    case EN: {
        policy_holds = ag_Sched->check_cnet(getIndex(), busy, p_need);
        reason = "agent busy";
        bid = ag_Heuristic_Handler->rand_in_range(agMsg->getBid(), 10000); //fixme see minimum/maximum difference and set a default number for both
        break;
    }
    case RBN: {
        policy_holds = ag_Sched->check_rbn(getIndex(), ag_Server_Handler, p_need);
        reason = "utilization above limit";
        break;
    }
    case RBN_PLUS: {
        policy_holds = ag_Sched->check_rbn_plus(getIndex(), bid, utilization, ag_Server_Handler, p_need);
        reason = "utilization above limit";
        break;
    }
    default: {
        EV << "Policy not supported!";
        break;
    }
    }
    if (policy_holds) {
        agentMSG *set_bid_msg = bid_msg(p_need, p_initiator, bid);
        set_bid_msg->setUtilization(utilization);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_bid_msg, "write");
        } else {
            forwardMessage(set_bid_msg);
        }
    } else {
        agentMSG *set_reject_msg = reject_msg(p_need, p_initiator, reason);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_reject_msg, "write");
        } else {
            forwardMessage(set_reject_msg);
        }
    }
}

void agent::receive_bid(agentMSG *agMsg) {
    int p_executor = agMsg->getSource();
    Need* p_need = agMsg->getNeed();
    double msg_arrival_time = agMsg->getArrivalTime().dbl();

    //TODO: during negotiation time window
//    if (simTime().dbl() < (msg_arrival_time + NEG_TIMEOUT)) {
        if (simTime().dbl() < (msg_arrival_time + p_need->get_timeout())) {
        EV << "Received a bid from agent ag[" << p_executor << "] for tasks:\n";
        for(int task : p_need->get_needed_t_ids()){
            EV << " - Task[" << task << "]\n";
        }
        //NOTE: For RBN_PLUS -> check if utilization is set
        double utilization = agMsg->getUtilization();
        double offer = agMsg->getBid();
        Bid* n_bid = new Bid(p_executor, offer, utilization);

        // Retrieve negotiation session
        NegSession* open_session = ag_Neg_Handler->get_neg_session(p_need);
        open_session->make_bid(n_bid);
        EV << "Negotiation session: <" << open_session->get_need_id() << ","
                  << open_session->get_task_release() << ","
                  << open_session->get_task_end() << ">\n";
    } else {
        agentMSG *refuse_neg_msg = refuse_msg(p_need, p_executor);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(refuse_neg_msg, "write");
        } else {
            forwardMessage(refuse_neg_msg);
        }
    }
}

void agent::reject(agentMSG *agMsg){
    int contractor = agMsg->getSource();
    EV << "Proposal rejected by agent ag[" << contractor << "]\n";
    if (agMsg->getContent() == RETRY) {
        Need* p_need = agMsg->getNeed();
        // Remove rejected bid
        NegSession* open_session = ag_Neg_Handler->get_neg_session(p_need);
        open_session->remove_bid_by_contractor(contractor);

        // Re-Schedule acknowledgment
        agentMSG *ack_neg_msg = ack_msg(p_need);
        scheduleAt(simTime().dbl(), ack_neg_msg);
    }
}

void agent::close(agentMSG *agMsg) {
    Need* p_need = agMsg->getNeed();
    if (p_need->get_needed_t_R() >= simTime().dbl()) {
        // update accepted requests
        update_accepted();

        EV << "Agent ag[" << getIndex() << "] took in charge tasks: \n";
        vector<Task*> pending_tasks = ag_Sched->get_pending_tasks_vector();
        //1 - Retrieve requested tasks
        for (int needed_id : p_need->get_needed_t_ids()) {
            auto task_it = find_if(pending_tasks.begin(), pending_tasks.end(),
                    [needed_id](Task* task)
                    {return (task->getTaskId() == needed_id);});
            if (task_it != pending_tasks.end()) {
                //2 - Clone requested tasks
                Task* needed_task = tGen->cloneTask(*task_it);
                needed_task->setTaskDemander(agMsg->getSource());
                needed_task->setTaskArrivalTime(p_need->get_needed_t_R());
                //needed_task->setTaskDeadLine(p_need->get_needed_t_E());
                needed_task->setTaskNExec(p_need->get_needed_t_n_exec());
                //write utilization report
                write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "pre-neg");
                ag_Sched->ag_add_task_in_vector_to_release(needed_task);
                //write utilization report
                write_util_json_report(getIndex(), simTime().dbl(), ag_Sched->get_current_util(ag_Server_Handler), "post-neg");
                EV << "- T_id[" << needed_task->getTaskId() << "]   "
                        "tskDm: ag[" << agMsg->getSource() << "]   "
                        "R: " << p_need->get_needed_t_R() << "  "
                        "DDL: " << p_need->get_needed_t_E() << "  "
                        "N_exec: " << p_need->get_needed_t_n_exec() << "\n";
                ag_Sched->ag_remove_pending_task(needed_id);
                agentMSG *task_arrival_msg = set_next_task_arrival();
                scheduleAt(needed_task->getTaskArrivalTime(), task_arrival_msg);
            }
        }
    } else {
        agentMSG* msg = reject_msg(p_need, agMsg->getSource(), "Late request");
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(msg, "write");
        } else {
            forwardMessage (msg);
        }
    }
    // release the state variable
    busy = false;
}

void agent::refuse(agentMSG *agMsg) {
    EV << "The initiator has refused the proposal\n";
    // remove pending task
    if (!ag_Sched->get_pending_tasks_vector().empty()) {
        for (int id : agMsg->getNeed()->get_needed_t_ids()) {
            ag_Sched->ag_remove_pending_task(id);
        }
    }
    busy = false;
}

void agent::df_publish(agentMSG *agMsg) {
    EV << "-DF: [Service List] received\n";
    bubble("List of services received");
    Service* n_service;
    for (int id : agMsg->getPublic_tasks()) {
        n_service = df_Service_Handler->create_service(id, agMsg->getSource());
        df_Service_Handler->add_service_in_vector(n_service);
    }
    df_Service_Handler->ev_services_table();
}

void agent::df_request(agentMSG *agMsg) {
    EV << "-DF: REQ_[agents per task]  received\n";
    int ag_sender_id = agMsg->getSource();
//    vector<int> p_needed_task_ids = agMsg->getAg_needed_tasks();
//    double p_needed_task_R = agMsg->getAg_needed_t_R();
//    double p_needed_task_E = agMsg->getAg_needed_t_E();
//    int p_needed_n_exec = agMsg->getAg_needed_n_exec();
//    int p_need_id = agMsg->getAg_need_id();
    Need *p_need = agMsg->getNeed();
    vector<int> p_needed_task_ids = p_need->get_needed_t_ids();
    EV << "ID SENDER: " << ag_sender_id << "\t";

    if (p_needed_task_ids.size() > 1) {
        EV << "Needed aggregate tasks: \n";
        for (int id : p_needed_task_ids) {
            EV << " - Task[" << id << "]\n";
        }
    } else {
        EV << "ID TASK: " << p_needed_task_ids[0] << "\n";
    }
    agentMSG *msg = set_ag_list_per_service(p_need, ag_sender_id);
    if ((bool) par("msg_server_mode") == true) {
        create_msg_task(msg, "write");
    } else {
        forwardMessage(msg);
    }
}

// Only for CNCP
void agent::confirm(agentMSG *agMsg){
    int p_initiator = agMsg->getSource();
    Need *p_need = agMsg->getNeed();
    bool luck = ag_Heuristic_Handler->flip_coin();
    if (luck) {
        EV << "Agent ag[" << getIndex() << "] confirmed the offer\n";
        agentMSG *set_conf_msg = conf_msg(p_need, p_initiator);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_conf_msg, "write");
        } else {
            forwardMessage(set_conf_msg);
        }
    } else {
        EV << "Agent ag[" << getIndex() << "] rejected the offer\n";
        agentMSG *set_reject_msg = reject_msg(p_need, p_initiator, "no available resources");
        set_reject_msg->setContent(RETRY);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_reject_msg, "write");
        } else {
            forwardMessage(set_reject_msg);
        }
    }
}

void agent::on_confirm(agentMSG *agMsg){
    int p_executor = agMsg->getSource();
    Need *p_need = agMsg->getNeed();
    NegSession* open_session = ag_Neg_Handler->get_neg_session(p_need);
    vector<Bid*> bids = open_session->get_bids();
    agentMSG *close_neg_msg = close_msg(p_need, p_executor);
    if ((bool) par("msg_server_mode") == true) {
        create_msg_task(close_neg_msg, "write");
    } else {
        forwardMessage(close_neg_msg);
    }
    //refuse all the remaining proposals
    if (!bids.empty()) {
        for (int i = 0; i < bids.size(); i++) {
            if (bids[i]->getContractor() != p_executor) {
                agentMSG *refuse_neg_msg = refuse_msg(p_need,
                        bids[i]->getContractor());
                if ((bool) par("msg_server_mode") == true) {
                    create_msg_task(refuse_neg_msg, "write");
                } else {
                    forwardMessage(refuse_neg_msg);
                }
            }
        }
    }
    bids.clear();
    ag_Neg_Handler->remove_neg_session(p_need);
}

// Only for EN, DU
void agent::on_bid_broadcast(agentMSG *agMsg){
    int neg_type = par("neg_type");
    int p_initiator = agMsg->getSource();
    int round = agMsg->getRound();
    double new_bid = 0;
    Need *p_need = agMsg->getNeed();
    double raise_chance = ag_Heuristic_Handler->get_raise_chance(round, neg_type);
    if(raise_chance){
        double curr_bid = agMsg->getBid();
        if(neg_type == DU) new_bid = agMsg->getBid();
        else new_bid = ag_Heuristic_Handler->rand_in_range(curr_bid, 10000); //FIXME upper bound
        agentMSG *set_bid_msg = bid_msg(p_need, p_initiator, new_bid);
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_bid_msg, "write");
        } else {
            forwardMessage(set_bid_msg);
        }
    } else {
        agentMSG *set_reject_msg = reject_msg(p_need, p_initiator, "Not willing to bid");
        if ((bool) par("msg_server_mode") == true) {
            create_msg_task(set_reject_msg, "write");
        } else {
            forwardMessage(set_reject_msg);
        }
    }
}

// To compute acceptance ratio
void agent::update_requests(){
    this->requests++;
}

void agent::update_accepted(){
    this->accepted++;
}

double agent::get_accept_ratio(){
    if(this->requests > 0) return (double) this->accepted/this->requests;
    else return 0;
}


// *****************************************************************************
// *******                      SETTER/GETTER                            *******
// *****************************************************************************

//Event trigger: comunica all'agente di impostare il taskset
agentMSG *agent::set_ag_tasks() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting ag taskset");

    // Create message object and set the contents
    agentMSG *msg = new agentMSG(msgname);

    msg->setInformative(SET_AG_TASKSET);
    msg->setContent(10);  // DUBBIO: perch� content 10?
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
//Event trigger: comunica all'agente di impostare lo scheduler
agentMSG *agent::set_ag_scheduler() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting Scheduler");

    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);

    // sendDirect(msg1, targetModule, "dirGate");

    msg->setInformative(SCHEDULE);
    msg->setContent(10);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

// *****************************************************************************
// *******                       SCHEDULER MSGS                          *******
// *****************************************************************************

agentMSG *agent::set_next_task_arrival() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting next task arrival");

    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);

    // sendDirect(msg1, targetModule, "dirGate");

    msg->setInformative(SCHEDULE);
    //msg->setContent(10);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_task_activation() {
    //task get cpu ...
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting next activation");

    // Create message object and set the contents
    agentMSG *msg = new agentMSG(msgname);

    msg->setInformative(ACTIVATE_TASK);
    //msg->setContent(10);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_check_task_complete(Task *p_task, double t_comp) {
    // schedulo controllo task finito
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];
    sprintf(msgname, "Checking task completion");
    agentMSG *msg = new agentMSG(msgname);
    // Informative discriminate the meaning of the message
    msg->setInformative(CHECK_TASK_TERMINATED);
    msg->setAg_task_id(p_task->getTaskId());
    msg->setAg_task_t_finito(t_comp);
    msg->setSource(src);
    msg->setDestination(dest);
    //note added for edf
    msg->setAg_task_release_time(p_task->getTaskReleaseTime());
    msg->setAg_task_demander(p_task->getTaskDemander());
    return msg;
}

agentMSG *agent::set_check_task_ddl_miss(Task *p_task) {
    // schedulo controllo ddl miss
    int src = p_task->getTaskDemander();  // the task's demander: we need this in case we execute a task requested from someone else
    int dest = getIndex();
    char msgname[30];
    sprintf(msgname, "Checking task ddl miss");
    agentMSG *msg = new agentMSG(msgname);
    // Informative discriminate the meaning of the message
    msg->setInformative(CHECK_DDL_MISS);
    msg->setAg_task_id(p_task->getTaskId());
    msg->setAg_task_release_time(p_task->getTaskReleaseTime());
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_df_tasks() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting df taskset");

    // Create message object and set the contents
    agentMSG *msg = new agentMSG(msgname);

    msg->setInformative(SET_DF_TASKSET);
    msg->setContent(10);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_task_preemption(Task *p_task, int preempted_task) {
    // schedulo meccanismo preemption
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];
    //note: gantt
    sprintf(msgname, "Task Preemption: %d", preempted_task);
    agentMSG *msg = new agentMSG(msgname);
    msg->setInformative(PREEMPT);
    msg->setAg_task_id(p_task->getTaskId());
    msg->setSource(src);
    msg->setDestination(dest);
    // edf
    msg->setAg_task_release_time(p_task->getTaskReleaseTime());
    msg->setAg_task_demander(p_task->getTaskDemander());
    msg->setAg_task_ddl(p_task->getTaskDeadLine());
    msg->setAg_task_server(p_task->getTaskServer());
    return msg;
}
//not used
agentMSG *agent::set_task_resume_post_preemption(Task *p_task) {
    // schedulo resume post-preemption
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];
    sprintf(msgname, "Checking task ddl miss");
    agentMSG *msg = new agentMSG(msgname);
    // Informative discriminate the meaning of the message
    msg->setInformative(RESUME_POST_PREEMPTION);
    msg->setAg_task_id(p_task->getTaskId());
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_replenish_dss(int server_id, double amount){
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];
    sprintf(msgname, "Replenish server by: %f", amount);
    agentMSG *msg = new agentMSG(msgname);
    msg->setInformative(REPLENISH);
    msg->setAg_task_server(server_id);
    msg->setReplenish(amount);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
// *****************************************************************************
// *******                        SERVICES MSGS                          *******
// *****************************************************************************

agentMSG *agent::set_ag_services() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting Ag Public Services");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);

    msg->setInformative(PUBLISH_SERVICES_DF);
    //msg->setContent(10);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::publish_services_to_DF() {
    int src = getIndex();  // our module index
    int my_dest = 0;       // default DF input gate
    char msgname[40];
    sprintf(msgname, "Ag %d is Publishing services to the DF", src);

    agentMSG *msg = new agentMSG(msgname);
    msg->setContent(PUBLISH);

    vector<int> public_tasks;
    for(auto task : ag_tasks_vector){
        if(task->get_t_is_public()){
            public_tasks.push_back(task->getTaskId());
        }
    }
    msg->setPublic_tasks(public_tasks);
    msg->setSource(src);
    msg->setDestination(my_dest);

    //send(msg, "gate$o", dest);
    return msg;
}

agentMSG *agent::get_service_ag_list_from_DF(Need *p_need) {
    int src = getIndex();  // our module index
    int my_msg_dest;
    char msgname[40];
    //sprintf(msgname, "Ag %d is asking Ag list for the %d service to the DF",src,p_id_task_needed);
    sprintf(msgname, "Asking for AgList for a service");
    agentMSG *t_n_msg = new agentMSG(msgname);
//    t_n_msg->setAg_needed_tasks(p_needed_task_ids);
//    t_n_msg->setAg_needed_t_R(p_needed_t_R);
//    t_n_msg->setAg_needed_t_E(p_needed_t_E);
//    t_n_msg->setAg_needed_n_exec(p_needed_n_exec);
//    t_n_msg->setAg_need_id(need_id);
    t_n_msg->setNeed(p_need);
    t_n_msg->setContent(REQUEST);
    t_n_msg->setSource(src);
    my_msg_dest = 0;
    // EV << "DESTINATION SET_2: " << my_msg_dest<<"\n";
    t_n_msg->setDestination(my_msg_dest);
    //EV << "DESTINATION CHECK_: " << t_n_msg->getDestination()<<"\n";
    return t_n_msg;
}

//agentMSG *agent::set_ag_list_per_service(int p_needed_task_id,
//        int p_ag_sender_id, double p_needed_t_R, double p_needed_t_E, int p_needed_n_exec) {
//    int src = getIndex();  // our module index
//
//    char msgname[40];
//    sprintf(msgname, "Giving list of AGs per service to Ag %d", p_ag_sender_id);
//    agentMSG *msg = new agentMSG(msgname);
//    msg->setContent(PROCESS_LIST);
//    int i = 0;
//    int ag_id = 0;
//
//    //TODO: controllare la tabella dei servizi del df
//    vector<Service*> serv_by_id_vector =
//            df_Service_Handler->get_services_vector_by_id(p_ag_sender_id,
//                    p_needed_task_id);
//
//    while (i < serv_by_id_vector.size()) {
//        ag_id = serv_by_id_vector[i]->get_ag_id();
//        msg->setDf_pub_agents_per_task(i, ag_id);
//        //EV <<"IN-CICLE preparing POSS_EXEC_LIST: " << ag_id << "\n";
//        i++;
//
//    }
//    //EV <<"END-CICLE i: " << i << "\n";
//
//    for (; i < DIM_df_pub_agents_per_task; i++) {
//        msg->setDf_pub_agents_per_task(i, -1);
//    }
//
//    msg->setSource(src);
//    //EV <<"WTF is wrong with this ID: " << p_ag_sender_id << "\n";
//    msg->setDestination(p_ag_sender_id);
//    msg->setAg_needed_task_id(p_needed_task_id);
//    msg->setAg_needed_t_R(p_needed_t_R);
//    msg->setAg_needed_t_E(p_needed_t_E);
//    msg->setAg_needed_n_exec(p_needed_n_exec);
//
//    //send(msg, "gate$o", dest);
//    return msg;
//}

agentMSG *agent::set_ag_list_per_service(Need *p_need,
        int p_ag_sender_id) {
    int src = getIndex();
    char msgname[40];
    sprintf(msgname, "Giving list of AGs per service to Ag %d", p_ag_sender_id);
    agentMSG *msg = new agentMSG(msgname);
    msg->setContent(PROCESS_LIST);

//    msg->setAg_needed_tasks(needed_tasks);
    msg->setNeed(p_need);
    df_Service_Handler->set_agents_per_need(p_need->get_needed_t_ids(), msg->getAgents_per_need(), p_ag_sender_id);
    msg->setSource(src);
    msg->setDestination(p_ag_sender_id);
//    msg->setAg_needed_t_R(p_needed_t_R);
//    msg->setAg_needed_t_E(p_needed_t_E);
//    msg->setAg_needed_n_exec(p_needed_n_exec);
//    msg->setAg_need_id(p_need_id);

    return msg;
}

// *****************************************************************************
// *******                          NEEDS MSGS                           *******
// *****************************************************************************

agentMSG *agent::set_ag_needs() {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting Ag Needs");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);

    msg->setInformative(GENERATE_AG_NEEDS);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::set_release_need(Need* p_need) {
    int src = getIndex();  // our module index
    int dest = getIndex();
    char msgname[30];

    sprintf(msgname, "Setting release Ag Need");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);
    msg->setInformative(RELEASE_NEED);
//    msg->setAg_need_id(p_need->get_need_id());
//    msg->setAg_need_r(p_need->get_need_release());
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

// *****************************************************************************
// *******                       NEGOTIATION MSGS                        *******
// *****************************************************************************

void agent::forwardMessage(agentMSG *msg) {
    int k = msg->getDestination();
    EV << "Forwarding message: " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

void agent::forwardMessageDelayed(agentMSG *msg, double delay) {
    int k = msg->getDestination();
    EV << "Forwarding message: " << msg << " on gate[" << k << "]\n";
    sendDelayed(msg, delay, "gate$o", k);
}

agentMSG *agent::init_msg(Need *p_need, int p_executor) {
    int src = getIndex();  // our module index
    int dest = ag_settings->get_ag_gate_out(p_executor);
    char msgname[30];

    sprintf(msgname, "Call for proposal");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(INIT);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::bid_msg(Need *p_need, int p_initiator, double bid) {
    int src = getIndex();
    int dest = ag_settings->get_ag_gate_out(p_initiator);
    char msgname[30];

    sprintf(msgname, "Bidding for job: %f", round(bid)); // to display bid value for debugging/fun
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(BID);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setBid(bid);
    return msg;
}

agentMSG *agent::ack_msg(Need *p_need) {
    int src = getIndex();
    char msgname[30];
    sprintf(msgname, "Awarding job");
    agentMSG *msg = new agentMSG(msgname);
    msg->setInformative(ACKNOWLEDGE);
    msg->setNeed(p_need);
    msg->setSource(src);
    return msg;
}

agentMSG *agent::close_msg(Need* p_need, int p_executor) {
    int src = getIndex();
    int dest = ag_settings->get_ag_gate_out(p_executor);
    char msgname[30];
    sprintf(msgname, "Job awarded for task");
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(CLOSE);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::reject_msg(Need *p_need, int p_initiator, const char* reason) {
    int src = getIndex();
    int dest = ag_settings->get_ag_gate_out(p_initiator);
    char msgname[100];

    sprintf(msgname, "Proposal rejected: %s", reason);
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(REJECTED);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::refuse_msg(Need* p_need, int p_initiator) {
    int src = getIndex();
    int dest = ag_settings->get_ag_gate_out(p_initiator);
    char msgname[30];

    sprintf(msgname, "Initiator refused");
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeed(p_need);
    msg->setNeg_step(REFUSED);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::req_conf_msg(Need* p_need, int p_executor){
    int src = getIndex();  // our module index
    int dest = ag_settings->get_ag_gate_out(p_executor);
    char msgname[30];

    sprintf(msgname, "Request confirmation");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(CONF_REQ);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::conf_msg(Need* p_need, int p_initiator){
    int src = getIndex();  // our module index
    int dest = ag_settings->get_ag_gate_out(p_initiator);
    char msgname[30];

    sprintf(msgname, "Offer confirmed");
    // Create message object and and set the contents
    agentMSG *msg = new agentMSG(msgname);
    msg->setNeg_step(CONFIRMED);
    msg->setNeed(p_need);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

agentMSG *agent::bid_broadcast_msg(Need *p_need, int p_executor, int round, double best_bid){
    int src = getIndex();  // our module index
        int dest = ag_settings->get_ag_gate_out(p_executor);
        char msgname[30];

        sprintf(msgname, "Broadcasting best offer");
        // Create message object and and set the contents
        agentMSG *msg = new agentMSG(msgname);
        msg->setNeg_step(BID_BROADCAST);
        msg->setNeed(p_need);
        msg->setBid(best_bid);
        msg->setRound(round);
        msg->setSource(src);
        msg->setDestination(dest);
        return msg;
}

// *****************************************************************************
// *******                         UTILITIES                             *******
// *****************************************************************************

void agent::cancel_redundant_msg(const char* name){
    int k = 0;
    bool found = false;
    cObject *event;
    while (!found && k < this->getSimulation()->getFES()->getLength()) {
        event = this->getSimulation()->getFES()->get(k);
        if (event != nullptr && (strcmp(event->getName(), name) == 0)) {
            agentMSG* msg = check_and_cast<agentMSG*>(event);
            if (msg->getSenderModule()->getFullName() == getFullName()) {
                found = true;
                cancelAndDelete(msg);
            }
        }
        k++;
    }
}

void agent::create_msg_task(agentMSG* agMsg, const char* type) {
    int server;
    if(strcmp("read", type) == 0) server = 100;
    else server = 200;
    Task* r_task = new MsgTask(agMsg, getIndex(), server, simTime().dbl(), type);
    ag_Sched->ag_add_task_in_vector_to_release(r_task);
    cancel_redundant_msg("Setting next task arrival");
    agentMSG *task_activation_msg = set_next_task_arrival();
    task_activation_msg->setSchedulingPriority(1);
    scheduleAt(simTime().dbl(), task_activation_msg);
}
