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
*/

#include <fstream>

#include "../headers/ag_needs_handler.h"
#include "../headers/json.hpp"

using namespace omnetpp;
using namespace std;
using json = nlohmann::json;

NeedsHandler::~NeedsHandler() {
    if (!ag_needs_vector.empty()) {
        for (auto need : ag_needs_vector) {
            delete need;
        }
        ag_needs_vector.clear();
    }
}

void NeedsHandler::read_needs_from_json(string path, int demander) {
    ifstream i(path.c_str());
    if (!i.fail()) {
        json needs;
        i >> needs;
        int need_id = 0;
        string id = to_string(demander);
        for (const auto& need : needs[id]) {
            vector<string> ids = need["neededTasks"];
            double need_R = stod(need["releaseTime"].get<string>());
            double needed_t_R = stod(need["neededTaskRelease"].get<string>());
            double needed_t_ddl = stod(need["neededTaskDeadline"].get<string>());
            int needed_t_n_exec = stoi(need["neededTaskNExec"].get<string>());
            double needed_timeout = stod(need["neededTimeout"].get<string>());
            double needed_t_min = -1;
            double needed_t_max = -1;
            if(need.find("neededTaskTMin") != need.end()) needed_t_min = stod(need["neededTaskTMin"].get<string>());
            if(need.find("neededTaskTMax") != need.end()) needed_t_max = stod(need["neededTaskTMax"].get<string>());

            vector<int> needed_tasks_ids;
            for(auto id : ids){
                needed_tasks_ids.push_back(stoi(id));
            }

            Need *new_need = new Need(need_id, need_R, needed_tasks_ids,
                    needed_t_R, needed_t_ddl, needed_t_n_exec, needed_timeout,
                    needed_t_min, needed_t_max);
            ag_needs_vector.push_back(new_need);

            need_id++; // auto-increment need id
        }
    } else {
        //note: we can stop the simulation or not!
//        EV_ERROR << "Cannot find root node" << endl;
//        throw std::runtime_error("Could not open file");
        EV_WARN << "Needs not found! Continuing the simulation...\n";
    }
}

vector<Need*> NeedsHandler::get_needs_vector() {
    return ag_needs_vector;
}

//TODO upgrade with find_if
Need* NeedsHandler::get_need_by_id(int p_need_id) {
    Need *p_need;
    int i = 0;
    bool found = false;
    while ((!found) && (i < ag_needs_vector.size())) {
        if (ag_needs_vector[i]->get_need_id() == p_need_id) {
            p_need = ag_needs_vector[i];
            found = true;
        }
        i++;
    }
    return p_need;
}
