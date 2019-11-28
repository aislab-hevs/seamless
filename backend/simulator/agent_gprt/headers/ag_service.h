/*
 * task.h
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
