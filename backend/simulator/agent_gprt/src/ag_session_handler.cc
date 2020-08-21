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

#include "../headers/ag_session_handler.h"

using namespace std;

NegSessionHandler::NegSessionHandler(){

}

NegSessionHandler::~NegSessionHandler() {
    for (auto session : neg_sessions) {
        delete session;
    }
    neg_sessions.clear();
}

NegSession* NegSessionHandler::get_neg_session(Need* p_need){
    NegSession* target = nullptr;
    bool found = false;
    int k = 0;
    while(!found){
        NegSession* session = neg_sessions[k];
        if(session->get_need_id() == p_need->get_need_id() &&
           session->get_task_release() == p_need->get_needed_t_R() &&
           session->get_task_end() == p_need->get_needed_t_E()){
            target = session;
            found = true;
        }
        k++;
    }
    return target;
}

void NegSessionHandler::add_neg_session(Need *p_need){
    NegSession* new_session = new NegSession(p_need);
    this->neg_sessions.push_back(new_session);
}

void NegSessionHandler::remove_neg_session(Need *p_need){
    bool found = false;
    int k = 0;
    while (!found) {
        NegSession* session = neg_sessions[k];
        if (session->get_need_id() == p_need->get_need_id()
                && session->get_task_release() == p_need->get_needed_t_R()
                && session->get_task_end() == p_need->get_needed_t_E()) {
            found = true;
            if(neg_sessions.size() == 1){
                neg_sessions.clear();
            } else {
                neg_sessions.erase(neg_sessions.begin() + k);
            }
        }
        k++;
    }
}

