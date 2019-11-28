/*
 * ag_msg_handler.h
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
