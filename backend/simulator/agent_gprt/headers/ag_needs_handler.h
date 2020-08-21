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
