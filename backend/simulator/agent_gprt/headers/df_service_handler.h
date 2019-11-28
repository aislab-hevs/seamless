/*
 * ag_service_handler.h
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
