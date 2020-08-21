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
 *  Created on: 21/apr/2017
 *      Author: iDavide
 */

#ifndef HEADERS_AG_SETTINGS_H_
#define HEADERS_AG_SETTINGS_H_

#include <vector>

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <vector>

#include "../headers/agentMSG_m.h"
#include "../headers/task.h"

using namespace omnetpp;
using namespace std;

class Ag_settings {

private:

    bool ag_has_scheduler = false;
    int ddl_miss = 0;
    int ddl_check = 0;
    double ag_utilization_factor_trend =0;
    double ag_acceptance_ratio_trend =0;
    //int ag_conn_table[16-1][2];
    vector< vector<int> > ag_conn_table;

public:

    //costruttore
    Ag_settings();

    //
    void set_ag_conn_table(int, int);
    int get_ag_gate_out(int);

    //setter scheduler-related
    void set_ag_has_scheduler(bool);
    void add_ddl_miss();
    void add_ddl_check();

    //getter scheduler-related
    bool get_ag_has_scheduler();
    int get_ddl_miss();
    int get_ddl_check();

    //setter agent-parameters
    void set_ag_UF_trend();

    //gettere agent-parameters
    double get_ag_UF_trend(int);

    //distruttore
    ~Ag_settings();

};



#endif /* HEADERS_AG_SETTINGS_H_ */
