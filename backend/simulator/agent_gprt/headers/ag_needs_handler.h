/*
 * task_generator.h
 *
 *  Created on: Mar 2, 2017
 *      Author: davide
 * ciao
 */

#ifndef NEEDS_HANDLER_H_
#define NEEDS_HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omnetpp.h>
#include <vector>

#include "../headers/ag_need.h"
#include "../headers/ag_sim_settings.h"

using namespace std;

class NeedsHandler {
public:
//    Need*         generate_need();
//    void          create_rnd_needs_vector();
//    void          create_static_needs_vector(const char*, int);
    void read_needs_from_json(string, int);
    vector<Need*> get_needs_vector();
    Need* get_need_by_id(int);


    /*
     * TODO: (maybe)
     * - online single need generator
     * - ??
     */
    ~NeedsHandler();

private:
    vector<Need*> ag_needs_vector;

};

#endif /* TASK_GENERATOR_H_ */
