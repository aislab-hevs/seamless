/*
 * server_handler.h
 *
 *  Created on: 23 gen 2018
 *      Author: peppe
 */

#ifndef HEADERS_SERVER_HANDLER_H_
#define HEADERS_SERVER_HANDLER_H_

#include "server.h"

class ServerHandler {
private:
    vector<Server*> servers;

public:
    ServerHandler();
    ServerHandler(int);
    ServerHandler(vector<int>);
    ~ServerHandler();
    Server* get_server(int);
    void add_server(Server*);
    vector<Server*> get_all_servers();
    void read_servers_from_json(string, int);
};



#endif /* HEADERS_SERVER_HANDLER_H_ */
