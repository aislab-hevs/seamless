/*
 * df_service_handler.cc
 *
 *  Created on: Jun 22, 2017
 *      Author: davide
 */

#include "../headers/df_service_handler.h"

ServiceHandler::~ServiceHandler() {
    if (!df_services_vector.empty()) {
        for(auto item : df_services_vector){
            delete item;
        }
        df_services_vector.clear();
    }
}

Service* ServiceHandler::create_service(int p_t_id, int p_ag_id) {
    Service* n_service;
    n_service = new Service(p_t_id, p_ag_id);
    return n_service;
}

Service* ServiceHandler::clone_service(Service* p_service) {
    Service* n_service;
    n_service = new Service(0, 0);
    n_service->set_task_id(p_service->get_task_id());
    n_service->set_ag_id(p_service->get_ag_id());
    /*
     n_service->set_ag_utilization_factor(p_service->get_ag_utilization_factor());
     n_service->set_ag_utilization_factor_trend(p_service->get_ag_utilization_factor_trend());
     n_service->set_ag_acceptance_ratio(p_service->get_ag_acceptance_ratio());
     n_service->set_ag_acceptance_ratio_trend(p_service->get_ag_acceptance_ratio_trend());
     */
    return n_service;
}

void ServiceHandler::add_service_in_vector(Service* p_service) {
    df_services_vector.push_back(p_service);
}

void ServiceHandler::remove_service_in_vector(Service* p_service) {
//df_services_vector.push_back(p_service);
    //TODO
}

vector<Service*> ServiceHandler::get_services_vector() {
    return df_services_vector;
}

vector<Service*> ServiceHandler::get_services_vector_by_id(int p_ag_sender_id,
        int p_service_task_id) {
    vector<Service*> serv_by_id_vector;
    for (int i = 0; i < df_services_vector.size(); i++) {
        if ((df_services_vector[i]->get_task_id() == p_service_task_id)
                && (df_services_vector[i]->get_ag_id() != p_ag_sender_id)) {
            serv_by_id_vector.push_back(df_services_vector[i]);
        }
    }

    return serv_by_id_vector;
}

vector<Service*> ServiceHandler::get_required_services_vector(int p_t_id) {
    vector<Service*> req_services_vector;

    return req_services_vector;

}

void ServiceHandler::set_agents_per_need(vector<int> needed_tasks, vector<int> &agents_ids, int self_id){
    int task_id = -1;
    int ag_id = -1;
    int first_id = df_services_vector[0]->get_ag_id();
    vector<int> tasks;
    for (auto service : df_services_vector) {
        ag_id = service->get_ag_id();
        if (ag_id != self_id) {
            task_id = service->get_task_id();
            if (ag_id == first_id) {
                tasks.push_back(task_id);
            } else {
                if (is_subset_or_equal(needed_tasks, tasks)) {
                    agents_ids.push_back(first_id);
                }
                first_id = ag_id;
                tasks.clear();
                tasks.push_back(task_id);
            }
        }
    }
    //FIXME: there should be a better way...
    if (is_subset_or_equal(needed_tasks, tasks)) {
        agents_ids.push_back(first_id);
    }
}

bool ServiceHandler::is_subset_or_equal(vector<int> a, vector<int> b){
    for(int el : a){
        if(find(b.begin(), b.end(), el) == b.end())
            return false;
    }
    return true;
}

void ServiceHandler::ev_services_table() {

    EV << "[DF]: Current List of Services\n";
    for (int i = 0; i < df_services_vector.size(); i++) {
        EV << "Service: " << df_services_vector[i]->get_task_id() << ", Agent: "
                  << df_services_vector[i]->get_ag_id() << "\n";
    }
}

/* NN DOVREBBERO SERVIRE
 void ServiceHandler::set_df_has_services_vector_true(){
 df_has_service_vector = true;
 }

 bool ServiceHandler::get_df_has_services_vector(){
 return df_has_service_vector;
 }

 vector<Task*> TaskGen::create_common_tasks(const char* ag_name,int id){

 vector<Task*> ag_common_tasks_vector;


 if (strcmp("ag", ag_name) == 0){

 //TASK-TEST
 Task* T1   = new Task(1,id,id,2,2,1,5,true,0,1,1,10);
 Task* T2   = new Task(2,id,id,3,3,4,8,true,0,1,1,10);
 Task* T3   = new Task(3,id,id,3,3,2,3,true,0,1,1,10);

 ag_common_tasks_vector.push_back(T1);
 ag_common_tasks_vector.push_back(T2);
 ag_common_tasks_vector.push_back(T3);
 }

 return ag_common_tasks_vector;
 }
 */
