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

