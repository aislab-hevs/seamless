/*
 * Copyright (c) 2020, HES-SO Valais-Wallis (https://www.hevs.ch)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  Created on: Apr 6, 2017
 *      Author: davide
 */

#include "../headers/ag_scheduler.h"
#include "../headers/agentMSG_m.h"
#include "../headers/writer.h"

using namespace std;
using namespace omnetpp;

vector<Task*> ag_tasks_vector;

Ag_Scheduler::Ag_Scheduler(SchedType type) {
    this->type = type;
    this->quantum = RR_QUANTUM;
}

Ag_Scheduler::~Ag_Scheduler() {
    if (!ag_pending_tasks.empty()) {
        for (auto item : ag_pending_tasks) {
            delete item;
        }
    }
    ag_pending_tasks.clear();
    if (!ag_tasks_vector.empty()) {
        for (auto item : ag_tasks_vector) {
            delete item;
        }
    }
    ag_tasks_vector.clear();
    if (!ag_tasks_vector_to_release.empty()) {
        for (auto item : ag_tasks_vector_to_release) {
            delete item;
        }
    }
    ag_tasks_vector_to_release.clear();
    if (!ag_tasks_vector_ready.empty()) {
        for (auto item : ag_tasks_vector_ready) {
            delete item;
        }
        ag_tasks_vector_ready.clear();
    }
}

//create
bool Ag_Scheduler::ag_create_scheduler(vector<Task*> p_ag_tasks_vector) {
    /*
     * - sched test a T0
     * - Calcolare U_0
     * - ag_scheduling
     */
    ag_tasks_vector_to_release = p_ag_tasks_vector;
    //ag_tasks_vector = p_ag_tasks_vector;

    //agPotentialUF = ag_sched_test(ag_tasks_vector);
//    if (agPotentialUF <= 1){
//        agCurrentUF = agPotentialUF;
//        return true;
//    } else {
//        return false;
//        // what to do if it's not schedulable??
//        // (if the Tset fails the s_test)
//    }
    return true;
}

bool Ag_Scheduler::ag_task_arrived(Task* server) {
    if ((ag_tasks_vector_to_release.size() == 1)
            && (ag_tasks_vector_to_release.at(0)->getTaskArrivalTime()
                    == simTime().dbl())) {

        if (server == nullptr || server->queue_length() == 1) {
            ag_tasks_vector_ready.push_back(ag_tasks_vector_to_release[0]);
        }

        ag_tasks_vector_to_release.clear();
    } else if (ag_tasks_vector_to_release.size() > 1) {

        if (server == nullptr || server->queue_length() == 1) {
            ag_tasks_vector_ready.push_back(ag_tasks_vector_to_release[0]);
        }

        ag_tasks_vector_to_release.erase(ag_tasks_vector_to_release.begin());
    }

    //      EV << "--- SIZE of ag_tasks_vector_ready_by_ddl: " << ag_tasks_vector_ready_by_ddl.size() << "\n";
    //      ev_ag_tasks_vector_ready_by_ddl();

    if (ag_tasks_vector_ready.size() == 1) {
        return true;
    } else
        return false;
}

// schdulability test
double Ag_Scheduler::ag_sched_test(vector<Task*> p_ag_tasks_vector,
        ServerHandler* server_handler) {
    double test_UF = 0;
    double t_C;
    double t_Period;
    //note residual computation time [ok?] --> si pu� usare CRes per "migliorare" la stima di U, ottenendo un stima pi� ottimistica
    if (!p_ag_tasks_vector.empty()) {
        for (auto task : p_ag_tasks_vector) {
            int server = task->getTaskServer();
            if (server != -1 && server != 100 && server != 200
                    && server_handler != nullptr) {
                Server* server = server_handler->get_server(
                        task->getTaskServer());
                if (!server->is_empty()) {
                    test_UF += server->get_bandwidth();
                }
            } else {
                t_C = task->getTaskCompTime();
                if (task->getTaskPeriod() == 0) {
                    t_Period = task->getTaskDeadLine();
                } else
                    t_Period = task->getTaskPeriod();
                test_UF = test_UF + (t_C / t_Period);
            }
        }
    }
    //p_ag_tasks_vector.
//    double test_UF_trunc = trunc(100 * test_UF) / 100;
    return test_UF;
}

//Predict taskset to evaluate utilization
vector<Task*> Ag_Scheduler::eval_current_taskset(double window_start,
        double window_end) {
    vector<Task*> taskset;
    //eval release vector
    for (auto task : ag_tasks_vector_to_release) {
        int server = task->getTaskServer();
        if (server != 100 && server != 200) {
            if (server != -1) {
                auto it =
                        find_if(taskset.begin(), taskset.end(),
                                [&server](Task* obj) {return obj->getTaskServer() == server;});
                if (it == taskset.end()) {
                    taskset.push_back(task);
                }
            } else if (task->getTaskNExec() == -1) {
                int id = task->getTaskId();
                int demander = task->getTaskDemander();
                auto it =
                        find_if(taskset.begin(), taskset.end(),
                                [id, demander](Task* obj)
                                {   return (obj->getTaskId() == id) && (obj->getTaskDemander() == demander);}); // flip the condition below here
                if (it == taskset.end()) { // note: add check -> if task has not been activated and will not be activated in the window (t_now + period > window end), don't consider it!
                    taskset.push_back(task);
                }
            } else {
                int id = task->getTaskId();
                int demander = task->getTaskDemander();
                auto it =
                        find_if(taskset.begin(), taskset.end(),
                                [id, demander](Task* obj)
                                {   return (obj->getTaskId() == id) && (obj->getTaskDemander() == demander);});
                if (it == taskset.end()) {
                    int n_exec = task->getTaskNExec();
                    int task_start = task->getTaskArrivalTime();
                    int task_end = task_start
                            + ((n_exec + 1) * task->getTaskPeriod());
                    if (check_overlap(task_start, task_end, window_start,
                            window_end)) {
                        taskset.push_back(task);
                    }
                }
            }
        }

    }
//eval ready vector
    for (auto task : ag_tasks_vector_ready) {
        int server = task->getTaskServer();
        if (server != 100 && server != 200) {
            if (task->getTaskNExec() != -1) {
                int id = task->getTaskId();
                int demander = task->getTaskDemander();
                auto it =
                        find_if(taskset.begin(), taskset.end(),
                                [id, demander](Task* obj)
                                {   return (obj->getTaskId() == id) && (obj->getTaskDemander() == demander);});
                if (it == taskset.end()) {
                    int task_start = task->getTaskArrivalTime();
                    int task_end = task_start + task->getTaskPeriod();
                    if (check_overlap(task_start, task_end, window_start,
                            window_end)) {
                        taskset.push_back(task);
                    }
                }
            } else if (server != -1) {
                auto it =
                        find_if(taskset.begin(), taskset.end(),
                                [&server](Task* obj) {return obj->getTaskServer() == server;});
                if (it == taskset.end()) {
                    taskset.push_back(task);
                }
            }
        }
    }
    return taskset;

}

void Ag_Scheduler::eval_pending_taskset(vector<Task*> &pot_taskset) {
    for (auto task : ag_pending_tasks) {
        int server = task->getTaskServer();
        if (server != 100 && server != 200) {
            if (server != -1) {
                auto it =
                        find_if(pot_taskset.begin(), pot_taskset.end(),
                                [&server](Task* obj) {return obj->getTaskServer() == server;});
                if (it == pot_taskset.end()) {
                    pot_taskset.push_back(task);
                }
            } else {
                int id = task->getTaskId();
                int demander = task->getTaskDemander();
                auto it =
                        find_if(pot_taskset.begin(), pot_taskset.end(),
                                [id, demander](Task* obj)
                                {   return (obj->getTaskId() == id) && (obj->getTaskDemander() == demander);});
                if (it == pot_taskset.end()) {
                    pot_taskset.push_back(task);
                }
            }
        }
    }
}

vector<Task*> Ag_Scheduler::eval_taskset(double window_start,
        double window_end) {
    vector<Task*> pot_taskset = eval_current_taskset(window_start, window_end);
    eval_pending_taskset(pot_taskset);
    return pot_taskset;
}

bool Ag_Scheduler::check_overlap(double task_start, double task_end,
        double window_start, double window_end) {
    bool condition = false;
    if (((window_start <= task_start) && (task_start < window_end))
            || ((window_start < task_end) && (task_end <= window_end))
            || ((task_start <= window_start) && (task_end >= window_end))) {
        condition = true;
    }
    return condition;
}

double Ag_Scheduler::get_current_util(ServerHandler* server_handler, double msg_util) {
    return ag_sched_test(eval_current_taskset(0, INT32_MAX), server_handler) + msg_util;
}

/*
 * TASK RELEASE RELATED
 *
 */

void Ag_Scheduler::ag_sort_tasks_arrival() {
    std::sort(ag_tasks_vector_to_release.begin(),
            ag_tasks_vector_to_release.end(), [](Task* a, Task* b) {
                return a->getTaskArrivalTime() < b->getTaskArrivalTime();
            });
}

void Ag_Scheduler::ag_sort_tasks_ready(double comp_time_head_ready) {
    switch (this->type) {
    case EDF:
        ag_sort_tasks_ddl(comp_time_head_ready);
        break;
    case RM:
        ag_sort_tasks_period(comp_time_head_ready);
        break;
    case SJF:
        ag_sort_tasks_comp_time();
        break;
    default:
        throw invalid_argument("Invalid scheduling algorithm!");
        break;
    }
}

void Ag_Scheduler::ag_sort_tasks_period(double comp_time_head_ready) {
    if (fabs(comp_time_head_ready) < EPSILON) {
        std::sort(ag_tasks_vector_ready.begin() + 1,
                ag_tasks_vector_ready.end(),
                [](Task* a, Task* b) {
                    return ((a->getTaskPeriod() != b->getTaskPeriod()) && (a->getTaskPeriod() < b->getTaskPeriod()));
                });
    } else {
        std::sort(ag_tasks_vector_ready.begin(), ag_tasks_vector_ready.end(),
                [](Task* a, Task* b) {
                    return ((a->getTaskPeriod() != b->getTaskPeriod()) && (a->getTaskPeriod() < b->getTaskPeriod()));
                });
    }
}

void Ag_Scheduler::ag_sort_tasks_ddl(double comp_time_head_ready) {
    if (fabs(comp_time_head_ready) < EPSILON) {
        std::sort(ag_tasks_vector_ready.begin() + 1,
                ag_tasks_vector_ready.end(),
                [](Task* a, Task* b) {
                    return ((a->getTaskDeadLine() != b->getTaskDeadLine()) && (a->getTaskDeadLine() < b->getTaskDeadLine()));
                });
    } else {
        std::sort(ag_tasks_vector_ready.begin(), ag_tasks_vector_ready.end(),
                [](Task* a, Task* b) {
                    return ((a->getTaskDeadLine() != b->getTaskDeadLine()) && (a->getTaskDeadLine() < b->getTaskDeadLine()));
                });
    }
    //return ag_tasks_vector_to_release;
}

void Ag_Scheduler::ag_sort_tasks_comp_time() {
    std::sort(ag_tasks_vector_ready.begin() + 1, ag_tasks_vector_ready.end(),
            [](Task* a, Task* b) {
                return ((a->getTaskCompTime() < b->getTaskCompTime()));
            });
}
//void Ag_Scheduler::ag_sort_tasks_ddl() {
//    std::sort(ag_tasks_vector_ready.begin(),
//            ag_tasks_vector_ready.end(), [](Task* a, Task* b) {
//                return a->getTaskDeadLine() < b->getTaskDeadLine();
//            });
//    //return ag_tasks_vector_to_release;
//}

void Ag_Scheduler::ag_add_task_in_vector_to_release(Task* pn_task) {
    ag_tasks_vector_to_release.push_back(pn_task);
}

void Ag_Scheduler::ag_add_task_in_ready_tasks_vector(Task* pn_task) {
    ag_tasks_vector_ready.push_back(pn_task);
}

void Ag_Scheduler::ag_add_pending_task(Task* pn_task) {
    ag_pending_tasks.push_back(pn_task);
}

void Ag_Scheduler::ag_remove_head_in_ready_tasks_vector() {
    if (ag_tasks_vector_ready.size() == 1) {
        ag_tasks_vector_ready.clear();
    } else
        ag_tasks_vector_ready.erase(ag_tasks_vector_ready.begin());
}

void Ag_Scheduler::ag_remove_task_in_ready(int id) {
    bool found = false;
    int k = 0;
    while (!found && k < ag_tasks_vector_ready.size()) {
        if (ag_tasks_vector_ready[k]->getTaskId() == id) {
            found = true;
            if (ag_tasks_vector_ready.size() == 1) {
                ag_tasks_vector_ready.clear();
            } else {
                ag_tasks_vector_ready.erase(ag_tasks_vector_ready.begin() + k);
            }
        }
        k++;
    }
}

void Ag_Scheduler::ag_remove_task_to_release(int id) {
    bool found = false;
    int k = 0;
    while (!found && k < ag_tasks_vector_to_release.size()) {
        if (ag_tasks_vector_to_release[k]->getTaskId() == id) {
            found = true;
            if (ag_tasks_vector_to_release.size() == 1) {
                ag_tasks_vector_to_release.clear();
            } else {
                ag_tasks_vector_to_release.erase(
                        ag_tasks_vector_to_release.begin() + k);
            }
        }
        k++;
    }
}

void Ag_Scheduler::ag_remove_pending_task(int id) {
    bool found = false;
    int k = 0;
    while (!found && k < ag_pending_tasks.size()) {
        if (ag_pending_tasks[k]->getTaskId() == id) {
            found = true;
            if (ag_pending_tasks.size() == 1) {
                ag_pending_tasks.clear();
            } else {
                ag_pending_tasks.erase(ag_pending_tasks.begin() + k);
            }
        }
        k++;
    }
}

void Ag_Scheduler::update_active_task_in_sorted_tasks_vector(Task *p_task) {
    Task* first_task = ag_tasks_vector_ready[0];
    if (p_task->getTaskId() == first_task->getTaskId()
            && p_task->getTaskDemander() == first_task->getTaskDemander()
            && p_task->getTaskReleaseTime()
                    == first_task->getTaskReleaseTime()) {
        ag_tasks_vector_ready[0] = p_task;
    }
}

//void Ag_Scheduler::update_active_task_in_sorted_tasks_vector(Task *p_task) {
//    if (p_task->getTaskId() == ag_tasks_vector_ready[0]->getTaskId()) {
//        ag_tasks_vector_ready[0] = p_task;
//    }
//}

// Getter methods

SchedType Ag_Scheduler::get_sched_type() {
    return this->type;
}

double Ag_Scheduler::get_quantum() {

    return this->quantum;
}

vector<Task*> Ag_Scheduler::get_tasks_vector_ready() {
    return ag_tasks_vector_ready;
}

vector<Task*> Ag_Scheduler::get_tasks_vector_to_release() {
    return ag_tasks_vector_to_release;
}

vector<Task*> Ag_Scheduler::get_pending_tasks_vector() {
    return ag_pending_tasks;
}

//checks if a task has passed the deadline by calculating the residual computation time
double Ag_Scheduler::get_ddl_miss(Task *p_task, int first_task_id) {
    double c_res = -1;
    if (p_task != nullptr) {
        c_res = p_task->getTaskCompTimeRes();
        if ((p_task->getTaskFirstActivation() != -1)
                && (p_task->getTaskId() == first_task_id)) {
            //update c_res
            double last_computation = simTime().dbl()
                    - p_task->getTaskLastActivation();
            c_res -= last_computation;
        }
    }
    return c_res;
}

//finds a task by specifying its id and first activation time (fa)
Task* Ag_Scheduler::get_ready_task_by_id(int task_id, int task_demander,
        double task_release) {
    Task *m_task = nullptr;
    for (int k = 0; k < ag_tasks_vector_ready.size(); k++) {
        if ((ag_tasks_vector_ready[k]->getTaskId() == task_id)
                && (ag_tasks_vector_ready[k]->getTaskReleaseTime()
                        == task_release)
                && ag_tasks_vector_ready[k]->getTaskDemander()
                        == task_demander) {
            m_task = ag_tasks_vector_ready[k];
            return m_task;
        }
    }
    return m_task;
}

// Utility
void Ag_Scheduler::ev_ag_tasks_vector_to_release() {
    EV << "Release queue:\n";
    for (auto task : ag_tasks_vector_to_release) {
        if (task->is_server()) {
            task = task->get_head();
        }
        EV << "- T_id:[" << task->getTaskId() << "] at t: "
                  << task->getTaskArrivalTime() << " tskDm: "
                  << task->getTaskDemander() << " tskDdl: "
                  << task->getTaskDeadLine() << " tskCres: "
                  << task->getTaskCompTimeRes() << endl;
    }
}

void Ag_Scheduler::ev_ag_tasks_vector_ready() {
    EV << "Ready queue:\n";
    for (auto task : ag_tasks_vector_ready) {
        EV << "- T_id:[" << task->getTaskId() << "] at t: "
                  << task->getTaskArrivalTime() << " tskDdl: "
                  << task->getTaskDeadLine() << "\n";
    }
}

void Ag_Scheduler::ag_replace_task_to_release(Task* np_task) {
    ag_tasks_vector_to_release[0] = np_task;
}

// Negotiation policy
bool Ag_Scheduler::check_cnet(int ag_id, bool &busy, Need* p_need) {
    bool policy_holds = false;
    if (!busy) {
        busy = true;
        policy_holds = true;
        EV << "Ag[" << ag_id << "] received a request for bidding:\n";
        for (int task : p_need->get_needed_t_ids()) {
            EV << " - Task[" << task << "]\n";
        }
    }
    return policy_holds;
}

bool Ag_Scheduler::check_rbn(int ag_id, ServerHandler* ag_Server_Handler,
        Need* p_need, double msg_util) {
    bool policy_holds = false;
    vector<Task*> potential_taskset = eval_taskset(p_need->get_needed_t_R(),
            p_need->get_needed_t_E());
    double pending_util = ag_sched_test(ag_pending_tasks, ag_Server_Handler);
    double potential_util = ag_sched_test(potential_taskset, ag_Server_Handler)
            + msg_util;

    // write potential util report
    write_pot_util_json(ag_id, simTime().dbl(), potential_util);

    if (potential_util <= 1) {
        policy_holds = true;
        EV << "Ag[" << ag_id << "] received a request for bidding:\n";
        for (int task : p_need->get_needed_t_ids()) {
            EV << " - Task[" << task << "]\n";
        }
        EV << "Pending Utilization factor: " << pending_util
                  << "\nPotential Utilization factor: " << potential_util
                  << endl;
    } else {
        EV << "Ag[" << ag_id << "] received a request for bidding\n"
                  << "Pending Utilization factor: " << pending_util
                  << "\nPotential Utilization factor: " << potential_util
                  << "\nPOTENTIAL UTILIZATION ABOVE LIMIT!\n";
        for (int task : p_need->get_needed_t_ids()) {
            ag_remove_pending_task(task);
        }
    }
    return policy_holds;
}

bool Ag_Scheduler::check_rbn_plus(int ag_id, double& bid, double& utilization,
        ServerHandler* ag_Server_Handler, Need* p_need, double msg_util) {
    bool policy_holds = false;
    vector<Task*> current_taskset = eval_current_taskset(
            p_need->get_needed_t_R(), p_need->get_needed_t_E());
    vector<Task*> potential_taskset = eval_taskset(p_need->get_needed_t_R(),
            p_need->get_needed_t_E());
    double pending_util = ag_sched_test(ag_pending_tasks, ag_Server_Handler);
    double potential_util = ag_sched_test(potential_taskset, ag_Server_Handler)
            + msg_util;
    double current_util = ag_sched_test(current_taskset, ag_Server_Handler)
            + msg_util;

    // write potential util report
    write_pot_util_json(ag_id, simTime().dbl(), potential_util);

    utilization = current_util;
    if (potential_util <= 1) {
        policy_holds = true;
        bid = p_need->get_needed_t_min();
        EV << "Ag[" << ag_id << "] received a request for bidding:\n";
        EV << " - Task[" << p_need->get_needed_t_ids()[0] << "]\n";
        EV << "Pending Utilization factor: " << pending_util
                  << "\nPotential Utilization factor: " << potential_util
                  << endl;
    } else {
        Task* pending = ag_pending_tasks.front();
        double t_offer = ceil(pending->getTaskCompTime() / (1 - current_util));
        pending->setTaskPeriod(t_offer);
        pending->setTaskDeadLine(t_offer);
        bid = t_offer;
        EV << "Ag[" << ag_id << "] received a request for bidding\n"
                  << "Pending Utilization factor: " << pending_util
                  << "\nCurrent Utilization factor: " << current_util
                  << "\nPotential Utilization factor: " << potential_util
                  << "\nOffered period t_min: " << bid << endl;
        if (t_offer >= p_need->get_needed_t_min()
                && t_offer <= p_need->get_needed_t_max()) {
            policy_holds = true;
        } else
            policy_holds = false;
    }
    return policy_holds;
}

//NOTE non dovrebbe servire pi� (l'altra condizione � pi� generale e lo comprende)
//double Ag_Scheduler::get_fcfs_ddl_miss(Task *msg_task, int first_task_id) {
//    double c_res = -1;
//    if (msg_task != nullptr) {
//        if (!msg_task->getTaskFirstActivation()) {
//            c_res = msg_task->getTaskCompTimeRes()
//                    - (get_t_now() - msg_task->getTaskLastActivation());
//        } else {
//            c_res = msg_task->getTaskCompTimeRes();
//        }
//    }
//    return c_res;
//}
