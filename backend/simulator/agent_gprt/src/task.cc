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
 *  Created on: Feb 21, 2017
 *      Author: davide
 */

#include "../headers/task.h"

Task::Task(int nt_id, int nt_Ag_Executer, int nt_Ag_Demander, double nt_C,
        double nt_CRes, double nt_R, double nt_DDL, double nt_FirstActivation,
        double nt_LastActivation, bool nt_is_public, int nt_Server,
        double nt_Period, int n_exec) {

    t_id = nt_id;
//    strcpy(t_description, nt_description);
    t_Ag_Executer = nt_Ag_Executer;
    t_Ag_Demander = nt_Ag_Demander;
    t_C = nt_C;
    t_CRes = nt_CRes;
    t_R = nt_R;
    t_DDL = nt_DDL;
    t_FirstActivation = nt_FirstActivation;
    t_LastActivation = nt_LastActivation;
    t_is_public = nt_is_public;
    t_Server = nt_Server;
    t_Period = nt_Period;
    t_release = -1;
    t_abs_ddl = t_R + t_DDL;
    t_n_exec = n_exec;
}

Task::Task(){

}

Task::~Task(){

}


// setter methods

void Task::setTaskId(int nt_id) {
    t_id = nt_id;
}

void Task::setTaskExecuter(int nt_Ag_Executer) {
    t_Ag_Executer = nt_Ag_Executer;
}
void Task::setTaskDemander(int nt_Ag_Demander) {
    t_Ag_Demander = nt_Ag_Demander;
}
void Task::setTaskCompTime(double nt_C) {
    t_C = nt_C;
}
void Task::setTaskCompTimeRes(double nt_CRes) {
    t_CRes = nt_CRes;
}
void Task::setTaskArrivalTime(double nt_R) {
    t_R = nt_R;
}
void Task::setTaskDeadLine(double nt_DDL) {
    t_DDL = nt_DDL;
}
void Task::setTaskFirstActivation(double nt_FirstActivation) {
    t_FirstActivation = nt_FirstActivation;
}
void Task::setTaskLastActivation(double nt_LastActivation) {
    t_LastActivation = nt_LastActivation;
}
void Task::set_t_is_public(bool nt_is_public) {
    t_is_public = nt_is_public;
}

void Task::setTaskReleaseTime(double nt_release) {
    t_release = nt_release;
}

void Task::setTaskServer(int nt_Server) {
    t_Server = nt_Server;
}
void Task::setTaskPeriod(double nt_Period) {
    t_Period = nt_Period;
}

void Task::setTaskNExec(int n_exec){
    t_n_exec = n_exec;
}

// getter methods

int Task::getTaskId() {
    //printf("METODO ESEGUITO CORRETTAMENTE\n");
    return t_id;
}
int Task::getTaskExecuter() {
    return t_Ag_Executer;
}
int Task::getTaskDemander() {
    return t_Ag_Demander;
}
double Task::getTaskCompTime() {
    return t_C;
}
double Task::getTaskCompTimeRes() {
    return t_CRes;
}
double Task::getTaskArrivalTime() {
    return t_R;
}
double Task::getTaskDeadLine() {
    return t_DDL;
}
double Task::getTaskAbsDDL() {
    return t_abs_ddl;
}
double Task::getTaskFirstActivation() {
    return t_FirstActivation;
}
double Task::getTaskLastActivation() {
    return t_LastActivation;
}
bool Task::get_t_is_public() {
    return t_is_public;
}
double Task::getTaskReleaseTime() {
    return t_release;
}
int Task::getTaskServer() const {
    return t_Server;
}
double Task::getTaskPeriod() {
    return t_Period;
}

int Task::getTaskNExec(){
    return t_n_exec;
}

//Binding dinamico - Server

double Task::get_bandwidth() {
    return 0;
}

double Task::get_budget() {
    return 0;
}

double Task::get_period() {
    return 0;
}

double Task::get_curr_budget() {
    return 0;
}

double Task::get_curr_ddl() {
    return 0;
}

int Task::get_server_type(){
    return -1;
}

double Task::get_delay() {
    return 0;
}

void Task::set_delay(double delay){

}

void Task::set_bandwidth(double n_bandwidth){

}

void Task::set_budget(double n_budget){

}

void Task::set_period(double n_period){

}

void Task::set_curr_budget(double budget){

}

void Task::set_curr_ddl(double ddl){

}

void Task::push_back(Task* task){

}

void Task::reset(double t_now, double c_req) {
}

void Task::update_budget(double t_comp){

}

void Task::update_ddl(){

}

void Task::pop_head(){
}

Task* Task::get_head(){
    return nullptr;
}

void Task::ev_queue() {
}

void Task::sort_svc_arrival() {
}

bool Task::is_server(){
    return false;
}

bool Task::is_empty(){
    return false;
}

int Task::queue_length(){
    return -1;
}

void Task::replenish(double){

}

//Binding dinamico - ReadTask
void Task::setMessage(agentMSG* msg){

}

agentMSG* Task::getMessage(){
    return nullptr;
}

bool Task::is_msg_task(){
    return false;
}

const char* Task::getType(){
    return nullptr;
}
