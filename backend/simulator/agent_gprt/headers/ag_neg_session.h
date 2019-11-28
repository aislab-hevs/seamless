/*
 * ag_neg_session.h
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
