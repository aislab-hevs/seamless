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
