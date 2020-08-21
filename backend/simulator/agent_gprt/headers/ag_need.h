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
