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
#include "../headers/server.h"
#include <omnetpp.h>

using namespace std;
using namespace omnetpp;

Server::Server(int server_id) :
        Task() {
    t_id = 0;
    t_Ag_Executer = -1;
    t_Ag_Demander = -1;
    t_C = 0;
    t_CRes = 0;
    t_R = 0;
    t_DDL = 0;
    t_FirstActivation = -1;
    t_LastActivation = -1;
    t_is_public = false;
    t_Server = server_id;
    t_Period = 0;
    t_release = -1;

    this->bandwidth = DEF_BANDWIDTH;
    this->budget = DEF_BUDGET;
    this->period = budget / bandwidth;
    this->curr_budget = budget;
    this->curr_ddl = period;
    this->released = false;
    this->t_n_exec = -1;
}

Server::Server(int server_id, double n_period, double n_budget,
        ServerType n_type) :
        Task() {
    t_id = 0;
    t_Ag_Executer = -1;
    t_Ag_Demander = -1;
    t_C = 0;
    t_CRes = 0;
    t_R = 0;
    t_DDL = 0;
    t_FirstActivation = -1;
    t_LastActivation = -1;
    t_is_public = false;
    t_Server = server_id;
    t_Period = 0;
    t_release = -1;

    this->type = n_type;
    this->bandwidth = n_budget / n_period;
    this->budget = n_budget;
    this->period = n_period; //n_budget / n_bandwidth;
    this->curr_budget = budget;
    this->curr_ddl = period;
    this->delay = 0;
    this->released = false;
    this->t_n_exec = -1;
}

Server::~Server() {
    if (!queue.empty()) {
        for (auto task : queue) {
            delete task;
        }
        queue.clear();
    }
}

double Server::get_bandwidth() {
    return bandwidth;
}

double Server::get_budget() {
    return budget;
}

double Server::get_period() {
    return period;
}

double Server::get_curr_budget() {
    return this->curr_budget;
}

double Server::get_curr_ddl() {
    return curr_ddl;
}

double Server::get_delay(){
    return this->delay;
}

int Server::get_server_type() {
    return this->type;
}

void Server::set_delay(double delay){
    this->delay = delay;
}

void Server::set_bandwidth(double n_bandwidth) {
    bandwidth = n_bandwidth;
}

void Server::set_budget(double n_budget) {
    budget = n_budget;
}

void Server::set_period(double n_period) {
    period = n_period;
}

void Server::set_curr_budget(double budget) {
    curr_budget = budget;
}

void Server::set_curr_ddl(double ddl) {
    curr_ddl = ddl;
}

void Server::push_back(Task* task) {
    queue.push_back(task);
}

void Server::reset(double t_now, double c_req) {
    switch (this->type) {
        case CBS: {
            if (curr_budget > ((curr_ddl - t_now) * bandwidth)) {
                curr_budget = budget;
                curr_ddl = t_now + period;
            } else if (fabs(curr_budget) < ERROR) {
                curr_budget = budget;
                curr_ddl += period;
            }
            //else c_s and d_s remain unchanged
            break;
        }
        case TBS: {
            curr_ddl = max(t_now, curr_ddl) + c_req / bandwidth;
            curr_budget = c_req;
            break;
        }
        case DSS: {
            if (!is_empty() && curr_budget > 0)
                curr_ddl = t_now + period;
            break;
        }
    }
}

void Server::replenish(double amount) {
    curr_budget += amount;
}

void Server::update_budget(double t_comp) {
    curr_budget -= t_comp;
}

void Server::update_ddl() {
    if (!queue.empty()) {
        for (auto &task : queue) {
            task->setTaskDeadLine(curr_ddl);
        }
    }
}

Task* Server::get_head() {
    Task* temp = nullptr;
    if (!queue.empty()) {
        temp = queue.front();
    }
    return temp;
}

void Server::pop_head() {
    if (queue.size() > 1) {
        queue.erase(queue.begin());
    } else if (queue.size() == 1) {
        queue.clear();
    }
}

void Server::ev_queue() {
    EV << "Server " << this->t_Server << " queue: ";
    if (!queue.empty()) {
        for (auto task : queue) {
            EV << "\n - S_id:[" << task->getTaskId() << "] at t: "
                      << task->getTaskArrivalTime() << " svcDm: "
                      << task->getTaskDemander() << " svcDdl: "
                      << task->getTaskDeadLine() << " svcCres: "
                      << task->getTaskCompTimeRes();
        }
        EV << "\n";
    } else {
        EV << " empty\n";
    }
}

void Server::sort_svc_arrival() {
    sort(queue.begin(), queue.end(), [](Task* a, Task* b) {
        return a->getTaskArrivalTime() < b->getTaskArrivalTime();
    });
}

bool Server::is_server() {
    return true;
}

bool Server::is_empty() {
    return queue.empty();
}

int Server::queue_length() {
    return queue.size();
}
