/*
 * ag_session_handler.cc
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

