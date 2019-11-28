/*
 * writer.h
 *
 *  Created on: 28 set 2017
 *      Author: peppe
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>
#include <vector>
#include "task.h"

using namespace std;

void initialize_json_report();
void write_ddl_json_report(Task *task, double cast_time, double c_res, double utilization, int num_tasks);
void write_lateness_json_report(Task *task, int agent_id, double lateness, double finish_time);
void write_response_json_report(Task *task, int agent_id, double finish_time, double resp_time);
void write_json_resp_per_task(Task *task, int agent_id, double finish_time, double resp_time);
void write_util_json_report(int agent_id, double time, double utilization, const char*);
void write_pot_util_json(int agent_id, double time, double u_pot);
void write_stats_json_report(int agent_id, int ddl_checks, int ddl_miss, string timestamp, string user);
void write_acceptance_ratio(int agent_id, double ratio, string timestamp, string user);

void check_reports_dir(string timestamp, string user);

void save_response_json(string timestamp, string user);
void save_util_json(string timestamp, string user);
void save_pot_util_json(string timestamp, string user);
void save_lateness_json(string timestamp, string user);
void save_ddl_json(string timestamp, string user);
void save_resp_per_task_json(string timestamp, string user);

#endif /* WRITER_H_ */

