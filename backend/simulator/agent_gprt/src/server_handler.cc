/*
 * server_handler.cc
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
            double bandwidth = stod(server["bandwidth"].get<string>());
            double budget = stod(server["budget"].get<string>());
            ServerType type = (ServerType) (server["type"]);

            add_server(new Server(server_id, bandwidth, budget, type));
        }
        if (servers.find("-1") != servers.end()) {
            for (const auto& server : servers["-1"]) {
                int server_id = stoi(server["server_id"].get<string>());
                double bandwidth = stod(server["bandwidth"].get<string>());
                double budget = stod(server["budget"].get<string>());
                ServerType type = (ServerType) (server["type"]);

                add_server(new Server(server_id, bandwidth, budget, type));
            }
        }
    } else {
        //note: we can stop the simulation or not!
//        throw std::runtime_error("Could not open file");
        EV_WARN << "Servers not found! Continuing the simulation...\n";
    }
}

