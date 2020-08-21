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
 *  Created on: 05 feb 2018
 *      Author: peppe
 */

#ifndef SRC_AG_NEG_SESSION_H_
#define SRC_AG_NEG_SESSION_H_

#include "ag_bid.h"
#include "ag_need.h"
//#include "agent.h"

using namespace std;

class NegSession {
private:
    int need_id;
    int round;
    double task_release;
    double task_end;
    double  best_bid;
    vector<Bid*> bids;
    // helpers

public:
    NegSession(Need*);
    ~NegSession();
    int get_need_id();
    int get_round();
    double get_task_release();
    double get_task_end();
    double get_tmp_best();
    double get_max_bid();
    double get_min_bid();
    double get_curr_best(int policy);
    void set_best_bid(double);
    void increase_round();
    void make_bid(Bid*);
    void remove_bid_by_contractor(int);
    vector<Bid*> get_bids();
};

#endif /* SRC_AG_NEG_SESSION_H_ */
