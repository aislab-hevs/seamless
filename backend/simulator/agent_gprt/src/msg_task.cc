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
 *  Created on: May 4, 2018
 *      Author: darth
 */

#include "../headers/msg_task.h"

MsgTask::MsgTask(agentMSG* msg, int ag_id, int server, double t_now, const char* type) {
    this->message = msg;
    this->type = type;

    t_id = msg->getId();
    t_Ag_Executer = ag_id;
    t_Ag_Demander = ag_id;
    t_C = DEF_COMP_TIME;
    t_CRes = t_C;
    t_R = t_now;
    t_DDL = DEF_DDL;
    t_FirstActivation = -1;
    t_LastActivation = -1;
    t_is_public = false;
    t_Server = server;
    t_Period = 0;
    t_release = -1;
    t_abs_ddl = t_R + t_DDL;
    t_n_exec = 1;
}

MsgTask::~MsgTask() {
    delete message;
}

bool MsgTask::is_msg_task(){
    return true;
}

const char* MsgTask::getType(){
    return this->type;
}

void MsgTask::setMessage(agentMSG* n_msg){
    this->message = n_msg;
}

agentMSG* MsgTask::getMessage(){
    return this->message;
}
