#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "../headers/task_handler.h"
#include "../headers/task.h"
#include "../headers/json.hpp" // to read from json file

using namespace omnetpp;
using namespace std;
using json = nlohmann::json;

/*
 1 reg_to_AMS
 2 reg_to_DF
 3 req_to_DF
 4 read_mex
 5 write_mex
 6 sched_test
 */
TaskHandler::~TaskHandler() {
}

Task* TaskHandler::createTask() {
    Task* n_task;
    n_task = new Task(0, 0, 0, 0, 0, 0, 0, true, 0, 0, 0, 0, -1);
    return n_task;
}

Task* TaskHandler::cloneTask(Task* p_task) {
    Task* n_task;
    n_task = new Task(0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1);
    n_task->setTaskId(p_task->getTaskId());
    n_task->setTaskExecuter(p_task->getTaskExecuter());
    n_task->setTaskDemander(p_task->getTaskDemander());
    n_task->setTaskCompTime(p_task->getTaskCompTime());
    n_task->setTaskCompTimeRes(p_task->getTaskCompTime());
    n_task->setTaskArrivalTime(p_task->getTaskArrivalTime());
    n_task->setTaskDeadLine(p_task->getTaskDeadLine());
    n_task->setTaskFirstActivation(-1);
    n_task->setTaskLastActivation(p_task->getTaskLastActivation());
    n_task->set_t_is_public(p_task->get_t_is_public());
    n_task->setTaskServer(p_task->getTaskServer());
    n_task->setTaskPeriod(p_task->getTaskPeriod());
    n_task->setTaskNExec(p_task->getTaskNExec());
    return n_task;
}

//TODO check
vector<Task*> TaskHandler::create_df_tasks(const char* ag_name, int id) {

    vector<Task*> df_specific_tasks_vector;

    if (strcmp("df", ag_name) == 0) {
        //t_id,t_C,t_executer,t_demander, t_CRes,t_R,t_DDL,t_LastActivation,t_status,t_server,t_period
        Task* t_read_mex = new Task(3, id, id, 2, 1, true, 0, 1, 1, 1, 1, 1,
                -1);
        Task* t_write_mex = new Task(4, id, id, 2, 1, true, 0, 1, 1, 1, 1, 1,
                -1);
        df_specific_tasks_vector.push_back(t_read_mex);
        df_specific_tasks_vector.push_back(t_write_mex);
    }

    return df_specific_tasks_vector;
}

vector<Task*> TaskHandler::read_tasks_from_json(string path, int ag_id) {
    vector<Task*> ag_tasks_vector;
    ifstream i(path.c_str());
    if (!i.fail()) {
        json taskset;
        i >> taskset;
        string id = to_string(ag_id);
        for (const auto& task : taskset[id]) {
            int t_id = stoi(task["id"].get<string>());
            int t_ag_executor = stoi(task["agentExecutor"].get<string>());
            int t_ag_demander = stoi(task["agentDemander"].get<string>());
            double t_comp = stod(task["computationTime"].get<string>());
            double t_CRes = stod(task["residualComputationTime"].get<string>());
            double t_R = stod(task["arrivalTime"].get<string>());
            double t_DDL = stod(task["relativeDeadline"].get<string>());
            double t_period = stod(task["period"].get<string>());
            int t_n_exec = stoi(task["n_exec"].get<string>());
            double t_first_activation = stod(task["firstActivationTime"].get<string>());
            double t_last_activation = stod(task["lastActivationTime"].get<string>());
            bool t_is_public = task["isPublic"].get<bool>();
            int t_server = stoi(task["server"].get<string>());

            Task *new_task = new Task(t_id, t_ag_executor, t_ag_demander,
                    t_comp, t_CRes, t_R, t_DDL, t_first_activation,
                    t_last_activation, t_is_public, t_server, t_period,
                    t_n_exec);
            ag_tasks_vector.push_back(new_task);
        }
        // check if there are common tasks
        if (!taskset["-1"].empty()) {
            for (const auto& task : taskset["-1"]) {
                int t_id = stoi(task["id"].get<string>());
                int t_ag_executor = ag_id;
                int t_ag_demander = ag_id;
                double t_comp = stod(task["computationTime"].get<string>());
                double t_CRes = stod(task["residualComputationTime"].get<string>());
                double t_R = stod(task["arrivalTime"].get<string>());
                double t_DDL = stod(task["relativeDeadline"].get<string>());
                double t_period = stod(task["period"].get<string>());
                int t_n_exec = stoi(task["n_exec"].get<string>());
                double t_first_activation = stod(task["firstActivationTime"].get<string>());
                double t_last_activation = stod(task["lastActivationTime"].get<string>());
                bool t_is_public = task["isPublic"].get<bool>();
                int t_server = stoi(task["server"].get<string>());

                Task *new_task = new Task(t_id, t_ag_executor, t_ag_demander,
                        t_comp, t_CRes, t_R, t_DDL, t_first_activation,
                        t_last_activation, t_is_public, t_server, t_period,
                        t_n_exec);
                ag_tasks_vector.push_back(new_task);

            }
        }
    } else {
        EV_WARN << "Cannot find file!" << endl;
        throw std::runtime_error("Could not open file taskset.json");
    }
    return ag_tasks_vector;
}
