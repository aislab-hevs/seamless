/*
 * writer.cc
 *
 *  Created on: 28 set 2017
 *      Author: peppe
 */

#include "../../headers/writer.h"
#include "../../headers/json.hpp" // to write to json file

#include <vector>
#include <fstream>

using namespace std;
using namespace boost::filesystem;
using namespace chrono;
using json = nlohmann::json;

const string REPORT_PATH = "/reports/";
const string STATS = "/stats.json";
const string UTIL = "/util.json";
const string POT_UTIL = "pot_util.json";
const string RESP_TIME = "/resp_time.json";
const string LATENESS = "/lateness.json";
const string DMR = "/ddl_miss.json";
const string RESP_PER_TASK = "/resp_per_task.json";
const string ACC_RATIO = "/acc_ratio.json";

json ddl_json;
json lateness_json;
json stats_json;
json resp_time_json;
json resp_time_per_task_json;
json util_json;
json pot_util_json;
json acc_ratio_json;

// *****************************************************************************
// *******                            JSON                               *******
// *****************************************************************************

void write_response_json_report(Task *task, int agent_id, double finish_time,
        double resp_time) {
    json resp = { { "taskId", task->getTaskId() }, { "compTime",
            task->getTaskCompTime() }, { "responseTime", resp_time }, {
            "finishTime", finish_time } };
    resp_time_json[agent_id].push_back(resp);
}

void write_util_json_report(int agent_id, double time, double utilization,
        const char* action) {
    json util = { { "action", action }, { "time", time }, { "utilization",
            utilization } };
    util_json[agent_id].push_back(util);
}

void write_lateness_json_report(Task *task, int agent_id, double lateness,
        double finish_time) {
    json late = { { "id", task->getTaskId() }, { "executor",
            task->getTaskExecuter() }, { "demander", task->getTaskDemander() },
            { "computationTime", task->getTaskCompTime() }, { "arrivalTime",
                    task->getTaskArrivalTime() }, { "releaseTime",
                    task->getTaskReleaseTime() }, { "relativeDeadline",
                    task->getTaskDeadLine() }, { "firstActivation",
                    task->getTaskFirstActivation() }, { "lastActivation",
                    task->getTaskLastActivation() }, { "isPublic",
                    task->get_t_is_public() },
            { "server", task->getTaskServer() }, { "period",
                    task->getTaskPeriod() }, { "finishTime", finish_time }, {
                    "lateness", lateness } };
    lateness_json[agent_id].push_back(late);
}

void write_ddl_json_report(Task *task, double cast_time, double c_res,
        double ag_utilization, int num_tasks) {
    json ddl = { { "id", task->getTaskId() }, { "executor",
            task->getTaskExecuter() }, { "demander", task->getTaskDemander() },
            { "computationTime", task->getTaskCompTime() }, { "arrivalTime",
                    task->getTaskArrivalTime() }, { "releaseTime",
                    task->getTaskReleaseTime() }, { "relativeDeadline",
                    task->getTaskDeadLine() }, { "firstActivation",
                    task->getTaskFirstActivation() }, { "lastActivation",
                    task->getTaskLastActivation() }, { "isPublic",
                    task->get_t_is_public() },
            { "server", task->getTaskServer() }, { "period",
                    task->getTaskPeriod() }, { "ddlMissTime", cast_time }, {
                    "agUtilization", ag_utilization }, { "runningTasks",
                    num_tasks } };
    ddl_json.push_back(ddl);
}

void write_json_resp_per_task(Task *task, int agent_id, double finish_time,
        double resp_time) {
    json resp = { { "finishTime", finish_time }, { "responseTime", resp_time } };
    string task_id = to_string(task->getTaskId());
    resp_time_per_task_json[agent_id][task_id].push_back(resp);
}

void write_pot_util_json(int agent_id, double time, double u_pot) {
    json pot_util = { { "time", time }, { "u_pot", u_pot } };
    pot_util_json[agent_id].push_back(pot_util);
}

void write_stats_json_report(int agent_id, int ddl_checks, int ddl_miss,
        string timestamp, string user) {
    stats_json[agent_id] = {
        {   "ddlCheckCount", ddl_checks},
        {   "ddlMissCount", ddl_miss}
    };

    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + STATS);
    o << std::setw(4) << stats_json << std::endl;
}

void write_acceptance_ratio(int agent_id, double ratio, string timestamp, string user){
    acc_ratio_json[agent_id] = {
        {   "acc_ratio", ratio},
    };

    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + ACC_RATIO);
    o << std::setw(4) << acc_ratio_json << std::endl;
}

void save_util_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + UTIL);
    o << std::setw(4) << util_json << std::endl;
}

void save_pot_util_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + POT_UTIL);
    o << std::setw(4) << pot_util_json << std::endl;
}

void save_response_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + "/resp_time.json");
    o << std::setw(4) << resp_time_json << std::endl;
}

void save_lateness_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + LATENESS);
    o << std::setw(4) << lateness_json << std::endl;
}

void save_ddl_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + DMR);
    o << std::setw(4) << ddl_json << std::endl;
}

void save_resp_per_task_json(string timestamp, string user) {
    check_reports_dir(timestamp, user);
    path report_dir("../simulations/" + user + "/" + timestamp + REPORT_PATH);
    std::ofstream o(report_dir.string() + RESP_PER_TASK);
    o << std::setw(4) << resp_time_per_task_json << std::endl;
}

void check_reports_dir(string timestamp, string user) {
    path user_dir("../simulations/" + user);
    if (!exists(user_dir)) {
        cout << user_dir << " doesn't exist" << endl;
        if (create_directory(user_dir))
            cout << "....Successfully Created !" << endl;
    }

    path main_dir = user_dir.append(timestamp);
    if (!exists(main_dir)) {
        cout << main_dir << " doesn't exist" << endl;
        if (create_directory(main_dir))
            cout << "....Successfully Created !" << endl;
    }

    path report_dir = main_dir.append(REPORT_PATH);
    if (!exists(report_dir)) {
        cout << report_dir << " doesn't exist" << endl;
        if (create_directory(report_dir))
            cout << "....Successfully Created !" << endl;
    }
}
