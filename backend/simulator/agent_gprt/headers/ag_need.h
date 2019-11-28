/*
 * task.h
 *
 *  Created on: Feb 21, 2017
 *      Author: davide
 */

#ifndef NEED_H_
#define NEED_H_
#include <vector>
using namespace std;

class Need {

private:

    int          need_id;
    double       need_R;          // when the need arise
    vector<int>  needed_t_ids;
    double       needed_t_R;      // start need of the task
    double       needed_t_E;      // end need of the task
    int          needed_t_n_exec; // requested number of execution of the task
    double       needed_t_C;      // requested computation time [double just to be sure]
    double       needed_t_min;    // requested minimum period [RBNP + Performance degradation]
    double       needed_t_max;    // requested maximum period [RBNP + Performance degradation]
    double       needed_timeout;  // requested maximum time limit for negotiating the services

public:
    Need(int need_id, double need_R, vector<int> n_needed_t_ids,
            double needed_t_R, double needed_t_E, int needed_t_n_exec,
            double needed_timeout = 0, double needed_t_min = -1,
            double needed_t_max = -1);

       //setter methods
       void set_need_id(int);
       void set_need_release(double);

       void set_needed_t_id(int);
       void set_needed_t_R(double);
       void set_needed_t_E(double);
       void set_needed_t_n_exec(int);

       //RBNP + performance degradation
       void set_needed_t_min(double);
       void set_needed_t_max(double);

       //getter methods
       int get_need_id();
       double get_need_release();
       double get_timeout();

       vector<int> get_needed_t_ids();
       double get_needed_t_R();
       double get_needed_t_E();
       int get_needed_t_n_exec();
       ~Need();

       //RBNP + performance degradation
       double get_needed_t_min();
       double get_needed_t_max();
};

#endif /* TASK_H_ */
