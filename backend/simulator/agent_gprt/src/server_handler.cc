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
 *  Created on: 23 gen 2018
 *      Author: peppe
 */

#include "../headers/server_handler.h"
#include "../headers/json.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace omnetpp;
using json = nlohmann::json;

ServerHandler::ServerHandler(){

}

// Initialize the servers' queue given the list of servers' ids
ServerHandler::ServerHandler(vector<int> s_ids){
    for(int i = 0; i < s_ids.size(); i++){
        Server* server = new Server(s_ids[i]);
        this->servers.push_back(server);
    }
}

ServerHandler::ServerHandler(int id){
    Server* server = new Server(id);
    this->servers.push_back(server);
}

ServerHandler::~ServerHandler(){
    if (!servers.empty()) {
        for(auto server : servers){
            delete server;
        }
        servers.clear();
    }
}

void ServerHandler::add_server(Server* server){
    this->servers.push_back(server);
}

Server* ServerHandler::get_server(int server_id) {
    auto it = find_if(servers.begin(), servers.end(),
                    [server_id](Server* server) {return server->getTaskServer() == server_id;});
    if (it != servers.end()) {
        return *it;
    } else
        return nullptr;
}

vector<Server*> ServerHandler::get_all_servers(){
    return this->servers;
}

void ServerHandler::read_servers_from_json(string path, int ag_id) {
    ifstream i(path.c_str());
    if (!i.fail()) {
        json servers;
        i >> servers;
        string id = to_string(ag_id);
        for (const auto& server : servers[id]) {
            int server_id = stoi(server["server_id"].get<string>());
//          double bandwidth = stod(server["bandwidth"].get<string>());
            double period = stod(server["period"].get<string>());
            double budget = stod(server["budget"].get<string>());
            ServerType type = (ServerType) (server["type"]);

            add_server(new Server(server_id, period, budget, type));
        }
        if (servers.find("-1") != servers.end()) {
            for (const auto& server : servers["-1"]) {
                int server_id = stoi(server["server_id"].get<string>());
//              double bandwidth = stod(server["bandwidth"].get<string>());
                double period = stod(server["period"].get<string>());
                double budget = stod(server["budget"].get<string>());
                ServerType type = (ServerType) (server["type"]);

                add_server(new Server(server_id, period, budget, type));
            }
        }
    } else {
        //note: we can stop the simulation or not!
//        throw std::runtime_error("Could not open file");
        EV_WARN << "Servers not found! Continuing the simulation...\n";
    }
}

