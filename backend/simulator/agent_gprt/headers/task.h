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

#ifndef HEADERS_TASK_H_
#define HEADERS_TASK_H_

#include <cstdint>
#include <stdio.h>
#include <string.h>
#include "agentMSG_m.h"

// Task states
//typedef enum { TSK_IDLE, TSK_READY, TSK_EXEC, TSK_BLOCKED } task_state;


class Task {

protected:
// TODO: aggiungere time window per validità dei servizi offerti e.g., sempre o from t=10 to t=100
    int t_id;
//     char         t_description[20];  // task name ~ description
    int t_Ag_Executer;      // agent executing the task
    int t_Ag_Demander;      // agent demanding the task
    // inserire WCET per C (poi da usare un random C <= C_WCET reale)
    double t_C;                // task computational time
    double t_CRes;             // residual task computational time
    double t_R;                // task arrival ~ release time
    double t_DDL;              // task deadline (from its server)
    double t_abs_ddl;          // task absolute deadline
    double t_FirstActivation;  // first time the C of a task is computed
    double t_LastActivation;   // computed C if preempted
    bool t_is_public;          // running, ready, preempted, ...
    double t_release;          // time when the task is first release
    int t_Server;              // associated server
    double t_Period;           // possible period if required, 0 if not
    int t_n_exec;              // number of executions of the task (jobs)

public:
    Task(int nt_id, int nt_Ag_Executer, int nt_Ag_Demander, double nt_C,
            double nt_CRes, double nt_R, double nt_DDL,
            double nt_FirstActivation, double nt_LastActivation,
            bool nt_is_public, int nt_Server, double nt_Period, int n_exec);
    Task();
    virtual ~Task();

    int flag;
    //setter methods
    void setTaskId(int);
    void setTaskExecuter(int);
    void setTaskDemander(int);
    void setTaskCompTime(double);
    void setTaskCompTimeRes(double);
    void setTaskArrivalTime(double);
    void setTaskDeadLine(double);
    void setTaskFirstActivation(double);
    void setTaskLastActivation(double);
    void set_t_is_public(bool nt_is_public);
    void setTaskReleaseTime(double);
    void setTaskServer(int);
    void setTaskPeriod(double);
    void setTaskNExec(int);

    //getter methods
    int getTaskId();
    //getTaskDescription();
    int getTaskExecuter();
    int getTaskDemander();
    double getTaskCompTime();
    double getTaskCompTimeRes();
    double getTaskArrivalTime();
    double getTaskDeadLine();
    double getTaskFirstActivation();
    double getTaskLastActivation();
    bool get_t_is_public();
    double getTaskReleaseTime();
    double getTaskAbsDDL();
    int getTaskServer() const;
    double getTaskPeriod();
    int getTaskNExec();

    //For the dynamic binding - Server
    virtual double get_bandwidth();
    virtual double get_budget();
    virtual double get_period();
    virtual double get_curr_budget();
    virtual double get_curr_ddl();
    virtual int get_server_type();
    virtual double get_delay();
    virtual void set_delay(double);
    virtual void set_bandwidth(double);
    virtual void set_budget(double);
    virtual void set_period(double);
    virtual void set_curr_budget(double);
    virtual void set_curr_ddl(double);
    virtual void push_back(Task*);
    virtual void reset(double, double c_req = 0);
    virtual void update_budget(double);
    virtual void update_ddl();
    virtual void pop_head();
    virtual Task* get_head();
    virtual void ev_queue();
    virtual void sort_svc_arrival();
    virtual bool is_server();
    virtual bool is_empty();
    virtual int queue_length();
    virtual void replenish(double);

    //For the dynamic binding - ReadTask
    virtual bool is_msg_task();
    virtual void setMessage(agentMSG*);
    virtual agentMSG* getMessage();
    virtual const char* getType();
};

#endif /* HEADERS_TASK_H_ */
