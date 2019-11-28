/*
 * ag_session_handler.h
 *
 *  Created on: 05 feb 2018
 *      Author: peppe
 */

#ifndef HEADERS_AG_SESSION_HANDLER_H_
#define HEADERS_AG_SESSION_HANDLER_H_

#include <vector>
#include "ag_neg_session.h"
#include "ag_need.h"

using namespace std;

class NegSessionHandler {
private:
    vector<NegSession*> neg_sessions;
public:
    NegSessionHandler();
    ~NegSessionHandler();
    NegSession* get_neg_session(Need*);
    void add_neg_session(Need*);
    void remove_neg_session(Need*);
};

#endif /* HEADERS_AG_SESSION_HANDLER_H_ */
