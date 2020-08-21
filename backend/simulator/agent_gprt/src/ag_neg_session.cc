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

#include "../headers/ag_neg_session.h"
#include "../headers/agent.h"
#include <vector>
#include <algorithm>

using namespace std;

NegSession::NegSession(Need *p_need){
    this->need_id = p_need->get_need_id();
    this->task_release = p_need->get_needed_t_R();
    this->task_end = p_need->get_needed_t_E();
    this->round = 1;
}

NegSession::~NegSession(){
    for(auto bid : bids){
        delete bid;
    }
    bids.clear();
}

int NegSession::get_need_id(){
    return this->need_id;
}

int NegSession::get_round(){
    return this->round;
}

double NegSession::get_task_release(){
    return this->task_release;
}

double NegSession::get_task_end(){
    return this->task_end;
}

double NegSession::get_tmp_best(){
    return this->best_bid;
}

double NegSession::get_curr_best(int policy){
    switch(policy){
        case EN: return get_max_bid(); break;
        case DU: return get_min_bid(); break;
        default: return 0;
    }
}

double NegSession::get_max_bid(){
    auto max = std::max_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) { return a->getOffer() < b->getOffer(); });
    Bid* bid = *max;
    return bid->getOffer();
}

double NegSession::get_min_bid(){
    auto min = std::min_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) { return a->getOffer() < b->getOffer(); });
    Bid* bid = *min;
    return bid->getOffer();
}

void NegSession::set_best_bid(double best_bid){
    this->best_bid = best_bid;
}

void NegSession::increase_round(){
    this->round++;
}

void NegSession::make_bid(Bid* n_bid){
    int contractor = n_bid->getContractor();
    auto it = find_if(bids.begin(), bids.end(), [&contractor](Bid* bid) {return bid->getContractor() == contractor;}); // to avoid multiple bids from the same contractor
    if (it == bids.end()) {
        bids.push_back(n_bid);
    } else {
        bids.erase(it);
        bids.push_back(n_bid);
    }
}

vector<Bid*> NegSession::get_bids(){
    return this->bids;
}

void NegSession::remove_bid_by_contractor(int contractor) {
    auto it = find_if(bids.begin(), bids.end(), [&contractor](Bid *bid){return bid->getContractor() == contractor;});
    if(it != bids.end()){
        bids.erase(it);
    }
}
