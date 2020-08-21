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

#ifndef AG_SERVICE_H_
#define AG_SERVICE_H_


#include <cstdint>
#include <stdio.h>
#include <string.h>

// Task states
//typedef enum { TSK_IDLE, TSK_READY, TSK_EXEC, TSK_BLOCKED } task_state;


class Service {

private:

       int t_id;
       int ag_id;
//       double       ag_utilization_factor       = 0;
//       double       ag_utilization_factor_trend = 0;
//       double       ag_acceptance_ratio         = 0;
//       double       ag_acceptance_ratio_trend   = 0;

public:
       //Service(int nt_id, int n_ag_id, double n_ag_utilization_factor, double n_ag_utilization_factor_trend, double ag_acceptance_ratio, double ag_acceptance_ratio_trend);
       Service(int nt_id, int n_ag_id);



       //setter methods
       void set_task_id(int);
       void set_ag_id(int);
       /*
       void set_ag_utilization_factor(double);
       void set_ag_utilization_factor_trend(double);
       void set_ag_acceptance_ratio(double);
       void set_ag_acceptance_ratio_trend(double);
       */

       //getter methods
       int get_task_id();
       int get_ag_id();
       /*
       double get_ag_utilization_factor();
       double get_ag_utilization_factor_trend();
       double get_ag_acceptance_ratio();
       double get_ag_acceptance_ratio_trend();
       */
       ~Service();
};

#endif /* AG_SERVICE_H_ */
