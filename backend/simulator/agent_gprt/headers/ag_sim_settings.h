/*
 * settings.h
 *
 *  Created on: Feb 13, 2017
 *      Author: davide
 */

#ifndef AG_SIM_SETTINGS_H_
#define AG_SIM_SETTINGS_H_

#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <omnetpp.h>
// code to install this in ubuntu: sudo apt-get install libtinyxml-dev
//#include <tinyxml.h>
//#include <tinyxml2.h>

using namespace omnetpp;
using namespace std;
//using namespace geo;



// Simulator's param
extern bool ag_sim_has_settings;

// Needs' param
extern int MAX_t_to_release_needs;
extern int MAX_task_iterations;

extern int DIM_df_pub_agents_per_task;
extern int DIM_ag_pub_tasks_ids;

// Simulator's func
extern void load_ag_sim_settings_from_xml();

#endif /* AG_SIM_SETTINGS_H_ */
