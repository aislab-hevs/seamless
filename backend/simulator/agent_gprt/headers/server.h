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
 *  Created on: 19 gen 2018
 *      Author: peppe
 */

#ifndef HEADERS_SERVER_H_
#define HEADERS_SERVER_H_

#include "task.h"
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

enum ServerType { CBS = 0, TBS = 1, DSS = 2 };

class Server : public Task {
protected:
    // Scheduler type -> algorithm
    ServerType type;

    //Time value sensitivity (epsilon)
    const double ERROR = 0.05;
    const double DEF_BANDWIDTH = 1.0/6.0;
    const double DEF_BUDGET = 2.0;

    vector<Task*> queue;
    double bandwidth;
    double budget;
    double period;
    double curr_budget;
    double curr_ddl;
    double delay;
    bool released;

public:
    Server(int);
    Server(int, double, double, ServerType);
    virtual int get_server_type() override;
    virtual double get_bandwidth() override;
    virtual double get_budget() override;
    virtual double get_period() override;
    virtual double get_curr_budget() override;
    virtual double get_curr_ddl() override;
    virtual double get_delay() override;
    virtual void set_bandwidth(double) override;
    virtual void set_budget(double) override;
    virtual void set_period(double) override;
    virtual void set_curr_budget(double) override;
    virtual void set_curr_ddl(double) override;
    virtual void set_delay(double) override;
    virtual void reset(double, double) override;
    virtual void update_budget(double) override;
    virtual void update_ddl() override;
    virtual void replenish(double) override;
    virtual void push_back(Task*) override;
    virtual Task* get_head() override;
    virtual void pop_head() override;
    virtual void ev_queue() override;
    virtual void sort_svc_arrival() override;
    virtual bool is_server() override;
    virtual bool is_empty() override;
    virtual int queue_length() override;
    virtual ~Server();
};

#endif /* HEADERS_SERVER_H_ */
