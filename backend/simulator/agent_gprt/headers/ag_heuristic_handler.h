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

#ifndef HEADERS_AG_HEURISTIC_HANDLER_H_
#define HEADERS_AG_HEURISTIC_HANDLER_H_

#include <cstdint>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <omnetpp.h>
#include "ag_bid.h"

using namespace std;
using namespace omnetpp;

class Hhandler {

//private:
//    int task_id;
//    int single_agent_id;
public:
    enum HPolicy {
        FIRST,
        RANDOM,
        RAND_SUBSET,
        BEST,
        MIN_WLB, // Minimum period - WorkLoad Balance (minimum utilization)
        MIN_WLM, // Minimum period - Workload Maximization (maximum utilization)
        WLB,
        WLM,
        ALL
    };

       Hhandler();
       int gen_random(int);
       double rand_in_range(double min, double max);
       bool flip_coin();
       bool get_raise_chance(int, int);
       //Select contractor to send cfp
       void select_first(vector<int>&);
       void select_random_contractor(vector<int>&);
       void select_random_subset(vector<int>&);
       void select_contractors(int, vector<int>&);
       //Select contractor to acknowledge
       int select_first_bidder(vector<Bid*>);
       int select_random_bidder(vector<Bid*>);
       int select_best_offerer(vector<Bid*>, int neg_type = 0);
       int select_min_period_max_util(vector<Bid*>);
       int select_min_period_min_util(vector<Bid*>);
       int select_max_util(vector<Bid*>);
       int select_min_util(vector<Bid*>);
       int select_bidder(int, vector<Bid*>, int neg_type = 0);
       void prova_heuristica();


       ~Hhandler();
};

#endif /* HEADERS_AG_HEURISTIC_HANDLER_H_ */
