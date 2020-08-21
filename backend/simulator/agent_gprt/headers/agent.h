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
 *  Created on: 25 set 2017
 *      Author: peppe
 */

#ifndef HEADERS_AGENT_H_
#define HEADERS_AGENT_H_

#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <algorithm>

//custom lib autogenerate from agentMSG.msg with "build"
#include "ag_heuristic_handler.h"
#include "ag_scheduler.h"
#include "ag_settings.h"
#include "agentMSG_m.h"
#include "ag_needs_handler.h"
#include "df_service_handler.h"
#include "server.h"
#include "msg_task.h"
#include "task_handler.h"
#include "server_handler.h"
#include "ag_session_handler.h"

//custom triggers that are sent as informative in agMsg
enum Triggers {
    SET_AG_TASKSET,
    SCHEDULE,
    SET_DF_TASKSET,
    ACTIVATE_TASK,
    CHECK_TASK_TERMINATED,
    CHECK_DDL_MISS,
    PREEMPT,
    RESUME_POST_PREEMPTION,
    PUBLISH_SERVICES_DF,
    GENERATE_AG_NEEDS,
    RELEASE_NEED,
    ACKNOWLEDGE,
    REPLENISH
};
//Negotiation type
enum NegType{
    CNET = 0, RBN = 1, CNCP = 2, EN = 3, DU = 4, RBN_PLUS = 5,
};

//Service statuses
enum ServiceStatus {
    PUBLISH = 100, REQUEST = 101, PROCESS_LIST = 102, RETRY = 103
};

//Negotiation step
enum NegStep {
    INIT = 200, INIT_RB = 201 , BID = 202, CLOSE = 203, CLOSE_RB = 204, REJECTED = 205, REFUSED = 206, CONF_REQ = 207, CONFIRMED = 208, BID_BROADCAST = 209,
};

using namespace omnetpp;
using namespace std;

class agent: public cSimpleModule {
    friend class Ag_msg_handler;
private:
    simsignal_t ddl_miss_signal;
    int index;
    //state variable used for exclusive negotiation (CNET)
    bool busy = false;

    Ag_settings *ag_settings;
    TaskHandler *tGen;
    Ag_Scheduler *ag_Sched;
    ServiceHandler *df_Service_Handler;
    NeedsHandler *ag_Needs_Handler;
    Hhandler *ag_Heuristic_Handler;

    //CBS: Server handler
    ServerHandler* ag_Server_Handler;

    //negotiation related
    NegSessionHandler* ag_Neg_Handler;
    double NEG_TIMEOUT; // not needed anymore
    int requests = 0;
    int accepted = 0;

    //AG tasks vector
    vector<Task *> ag_tasks_vector;
    vector<Task *> ag_specific_tasks_vector;
    //Ag_msg_handler *ag_msg_handler;

    // DF tasks vector
    vector<Task *> df_tasks_vector;
    vector<Task *> df_specific_tasks_vector;



public:
    agent();
    virtual ~agent();

protected:
    //override basic functions

    /**
     Initializes the agent
     */
    virtual void initialize() override;
    virtual void finish() override;

    /**
     This function is called when the agent receives a message

     @param *msg the pointer to the message received (can be a self-message)
     */
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleMessageGP(cMessage *msg);
    virtual void handleMessageRT(cMessage *msg);

    //These functions implement the agent's behaviours

    /**
     Initializes the agent's taskset
     */
    virtual void set_ag_taskset(agentMSG *msg);

    /**
     Sets the scheduler for the tasks
     */
    virtual void schedule_taskset(agentMSG *msg);
    virtual void schedule_taskset_rt(agentMSG *msg);
    virtual void preempt(agentMSG *agMsg);
    virtual void replenish(agentMSG *agMsg);

    /**
     Sets the DF's taskset
     */
    virtual void set_df_taskset(agentMSG *msg);

    /**
     Activates the first ready task
     */
    virtual void activate_task(agentMSG *msg);

    /**
     Checks if the task has completed
     */
    virtual void check_task_completion(agentMSG *msg);
    virtual void check_task_completion_rt(agentMSG *msg);
    /**
     Checks if the task has passed his deadline
     */
    virtual void check_ddl_miss(agentMSG *agMsg);

    /**
     Publish services on DF table
     */
    virtual void publish_services(agentMSG *msg);

    /**
     Creates needs for an agent
     */
    virtual void generate_ag_needs(agentMSG *msg);

    /**
     Releases a need at time need_R
     */
    virtual void release_need(agentMSG *msg);

    /**
     Acknowledge job
     */
    virtual void acknowledge_job(agentMSG *msg);

    /**
     Sends a message which triggers the tasks' generation
     */
    virtual agentMSG *set_ag_tasks();

    /**
     Sends a message which triggers the scheduler's setting
     */
    virtual agentMSG *set_ag_scheduler();

    /**
     Sends a message that triggers the DF's taskset setting
     */
    virtual agentMSG *set_df_tasks();

    /**
     Sends a message which triggers a task's arrival
     */
    agentMSG *set_next_task_arrival();

    /**
     Sends a message which triggers a task's activation
     */
    agentMSG *set_task_activation();

    /**
     Sends a message which triggers the check for the task's completion
     */
    agentMSG *set_check_task_complete(Task*, double);

    /**
     Sends a message which triggers the check for deadline missing
     */
    agentMSG *set_check_task_ddl_miss(Task*);


    agentMSG *set_task_preemption(Task*, int);

    /**
     * Sets replenishment msg for Dynamic Sporadic Server
     */
    agentMSG *set_replenish_dss(int, double);

    //not used
    agentMSG *set_task_resume_post_preemption(Task*);

    //DF Services related

    /**
     Sends a message which triggers the services' publication
     */
    agentMSG *set_ag_services();

    /**
     Sends a message which triggers the services' publication
     */
    agentMSG *publish_services_to_DF();

    /**
     Sends a message to the DF asking for the list of agents able to satisfy the need
     */
    agentMSG *get_service_ag_list_from_DF(Need* p_need);

    /**
     Sends a message containing the list of the agents and the services they offer
     */
    //agentMSG *set_ag_list_per_service(int, int, double, double, int);
    //note new version
    agentMSG *set_ag_list_per_service(Need *p_need, int sender);
    //Needs related

    /**
     Sends a message which triggers the needs' generation
     */
    virtual agentMSG *set_ag_needs();

    /**
     Sends a message which triggers a need's release
     */
    virtual agentMSG *set_release_need(Need*);

    //Utils
    virtual void forwardMessage(agentMSG *msg);

    virtual void forwardMessageDelayed(agentMSG *msg, double delay);
    /**
     Handles normal agent's messages
     */
    virtual void handle_ag_msg(agentMSG *msg);

    /**
     Handles DF's messages
     */
    virtual void handle_df_msg(agentMSG *msg);

    // AGs negotiation related

    /**
     Sends a message which triggers the initialization phase of the negotiation
     */
    agentMSG *init_msg(Need *p_need, int);

    /**
     Sends a message which triggers the bidding phase of the negotiation
     */
    agentMSG *bid_msg(Need *p_need, int, double init_bid = -1);

    /**
    Sends a message which triggers the acknowledging phase of the negotiation
     */
    agentMSG *ack_msg(Need* p_need);

    /**
    Sends a message which triggers the confirmation request of the negotiation (CNCP)
     */
    agentMSG *req_conf_msg(Need* p_need, int);

    /**
    Sends a message which triggers the confirmation of a previous offer (CNCP)
     */
    agentMSG *conf_msg(Need *p_need, int);

    /**
    Returns a message to broadcast bid in auctions (English/Dutch)
     */
    agentMSG *bid_broadcast_msg(Need *p_need, int, int, double);

    /**
     Sends a message which triggers the closing phase of the negotiation
     */
    agentMSG *close_msg(Need*, int);
    agentMSG *reject_msg(Need*, int, const char*);
    agentMSG *refuse_msg(Need*, int);

    /**
     Negotiation functions
     */
    void df_publish(agentMSG *msg);
    void df_request(agentMSG *msg);
    void process_list(agentMSG *msg);
    void begin_neg(agentMSG *msg);
    void receive_bid(agentMSG *msg);
    void reject(agentMSG *msg);
    void close(agentMSG *msg);
    void refuse(agentMSG *msg);
    void confirm(agentMSG *msg);
    void on_confirm(agentMSG *msg);
    void on_bid_broadcast(agentMSG *msg);
    void update_requests();
    void update_accepted();
    double get_accept_ratio();

    /**
     Simulation utilities
     */
    void cancel_redundant_msg(const char*);
    void create_msg_task(agentMSG*, const char*);
};

Define_Module(agent);

#endif /* HEADERS_AGENT_H_ */
