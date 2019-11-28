/*
 * task.cc
 *
 *  Created on: Feb 21, 2017
 *      Author: davide
 */

#include "../headers/ag_service.h"



//Service::Service(int nt_id, int n_ag_id, double n_ag_utilization_factor, double n_ag_utilization_factor_trend, double n_ag_acceptance_ratio, double n_ag_acceptance_ratio_trend){
Service::Service(int nt_id, int n_ag_id){
    t_id = nt_id;
    ag_id = n_ag_id;
//    ag_utilization_factor = n_ag_utilization_factor;
//    ag_utilization_factor_trend = n_ag_utilization_factor_trend;
//    ag_acceptance_ratio = n_ag_acceptance_ratio;
//    ag_acceptance_ratio_trend = n_ag_acceptance_ratio_trend;
}

Service::~Service(){

}

//setter methods
void Service::set_task_id(int nt_id){
    t_id = nt_id;
}

void Service::set_ag_id(int n_ag_id){
    ag_id = n_ag_id;
}
/*
void Service::set_ag_utilization_factor(double n_ag_utilization_factor){
    ag_utilization_factor = n_ag_utilization_factor;
}

void Service::set_ag_utilization_factor_trend(double n_ag_utilization_factor_trend){
    ag_utilization_factor_trend = n_ag_utilization_factor_trend;
}

void Service::set_ag_acceptance_ratio(double n_ag_acceptance_ratio){
    ag_acceptance_ratio = n_ag_acceptance_ratio;
}
void Service::set_ag_acceptance_ratio_trend(double n_ag_acceptance_ratio_trend){
    ag_acceptance_ratio_trend = n_ag_acceptance_ratio_trend;
}
*/


//getter methods
int Service::get_task_id(){
    return t_id;
}

int Service::get_ag_id(){
    return ag_id;
}

/*
double Service::get_ag_utilization_factor(){
    return ag_utilization_factor;
}

double Service::get_ag_utilization_factor_trend(){
    return ag_utilization_factor_trend;
}

double Service::get_ag_acceptance_ratio(){
    return ag_acceptance_ratio;
}

double Service::get_ag_acceptance_ratio_trend(){
    return ag_acceptance_ratio_trend;
}
*/
