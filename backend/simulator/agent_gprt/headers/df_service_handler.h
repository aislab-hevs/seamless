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
 *  Created on: Jun 22, 2017
 *      Author: davide
 */

#ifndef DF_SERVICE_HANDLER_H_
#define DF_SERVICE_HANDLER_H_

#include <vector>
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <algorithm>
#include "../headers/ag_service.h"

using namespace omnetpp;
using namespace std;

class ServiceHandler{
public:
    Service* create_service(int, int);
    Service* clone_service(Service*);

    void add_service_in_vector(Service*);
    void remove_service_in_vector(Service*);
    void ev_services_table();
    void set_agents_per_need(vector<int> needed_tasks, vector<int>&, int self_id);

    vector<Service*> get_required_services_vector(int);
    vector<Service*> get_services_vector();
    vector<Service*> get_services_vector_by_id(int,int);
    ~ServiceHandler();

private:
    vector<Service*> df_services_vector;
    bool is_subset_or_equal(vector<int>, vector<int>);
    //vector<Service*> df_public_services_vector;

};




#endif /* DF_SERVICE_HANDLER_H_ */
