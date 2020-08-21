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
void write_ddl_checks(int task_id, int agent_id);

void check_reports_dir(string timestamp, string user);

void save_response_json(string timestamp, string user);
void save_util_json(string timestamp, string user);
void save_pot_util_json(string timestamp, string user);
void save_lateness_json(string timestamp, string user);
void save_ddl_json(string timestamp, string user);
void save_resp_per_task_json(string timestamp, string user);
void save_ddl_checks_json(string timestamp, string user);

#endif /* WRITER_H_ */

