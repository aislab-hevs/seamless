/*
 * task.h
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
