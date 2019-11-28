/*
 * ag_msg_handler.cc
 *
 *  Created on: 21/apr/2017
 *      Author: iDavide
 */


#include "../headers/ag_settings.h"

using namespace omnetpp;
using namespace std;

//virtual void handleMessage(cMessage *msg) override;

Ag_settings::Ag_settings(){

}

Ag_settings::~Ag_settings(){

}

// it maps the output gate with the related agent: [gate$o -> agent]
void Ag_settings::set_ag_conn_table(int ag_index, int n_ag){
    ag_conn_table = vector< vector<int> > (n_ag - 1, vector<int>(2));
    int k=1;
    // i=1 because the 0 is always connected to the DF
    for (int i = 0; i < n_ag; i++){
        if (ag_index != i){
            ag_conn_table[k-1][0]= k;
            ag_conn_table[k-1][1]= i;
            k++;
        }
    }
    // STAMPA TABELLA AGENTI
    EV <<"Connections Table for Ag: " << ag_index << endl;
    for (int ii = 0; ii < n_ag-1; ii++)
       EV << "Gate: " << ag_conn_table[ii][0] << " Ag: " << ag_conn_table[ii][1] << endl;
}

// TODO: sistema questa funz qui sotto
// aggiungi numero di agenti per fermare il ciclo
// (oppure usa la dim massima e metti in un while cosi ci fermiamo qnd è ora)
int Ag_settings::get_ag_gate_out(int p_ag_id){

    int gate_addr = -1;
    int i = 0;

    bool found = false;

    while (!found) {
        if (ag_conn_table[i][1] == p_ag_id) {
            gate_addr = ag_conn_table[i][0];
            found = true;
        }
        i++;
    }
return gate_addr;
}


//setter scheduler related
void Ag_settings::set_ag_has_scheduler(bool p_ag_has_scheduler){
ag_has_scheduler = p_ag_has_scheduler;
}

void Ag_settings::add_ddl_miss(){
    ddl_miss++;
}

void Ag_settings::add_ddl_check(){
    ddl_check++;
}

//getter scheduler related
bool Ag_settings::Ag_settings::get_ag_has_scheduler(){
return ag_has_scheduler;
}

int Ag_settings::get_ddl_miss(){
    return ddl_miss;
}

int Ag_settings::get_ddl_check(){
    return ddl_check;
}

