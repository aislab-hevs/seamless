/*
 * task.cc
 *
 *  Created on: Feb 21, 2017
 *      Author: davide
 */

#include "../headers/ag_need.h"
#include <cstdint>
#include <stdio.h>
#include <string.h>

Need::Need(int n_need_id, double n_need_R, vector<int> n_needed_t_ids,
        double n_needed_t_R, double n_needed_t_E, int n_needed_t_n_exec, double n_needed_timeout,
        double n_needed_t_min, double n_needed_t_max) {

    need_id = n_need_id;
    need_R = n_need_R;
    needed_t_ids = n_needed_t_ids;
    needed_t_R = n_needed_t_R;
    needed_t_E = n_needed_t_E;
    needed_t_n_exec = n_needed_t_n_exec;
    needed_timeout = n_needed_timeout;
    needed_t_min = n_needed_t_min;
    needed_t_max = n_needed_t_max;
}

Need::~Need(){

}

//setter methods
void Need::set_need_id(int n_need_id) {
    need_id = n_need_id;
}

void Need::set_need_release(double n_need_R) {
    need_R = n_need_R;
}

void Need::set_needed_t_id(int n_needed_t_id) {
    needed_t_ids.push_back(n_needed_t_id);
}

void Need::set_needed_t_R(double n_needed_t_R) {
    needed_t_R = n_needed_t_R;
}

void Need::set_needed_t_E(double n_needed_t_E) {
    needed_t_E = n_needed_t_E;
}

void Need::set_needed_t_n_exec(int n_needed_t_n_exec) {
    needed_t_n_exec = n_needed_t_n_exec;
}

void Need::set_needed_t_min(double n_needed_t_min){
    needed_t_min = n_needed_t_min;
}

void Need::set_needed_t_max(double n_needed_t_max){
    needed_t_max = n_needed_t_max;
}

//getter methods
int Need::get_need_id() {
    return need_id;
}

double Need::get_need_release() {
    return need_R;
}

vector<int> Need::get_needed_t_ids() {
    return needed_t_ids;
}

double Need::get_needed_t_R() {
    return needed_t_R;
}

double Need::get_needed_t_E() {
    return needed_t_E;
}

int Need::get_needed_t_n_exec() {
    return needed_t_n_exec;
}

double Need::get_timeout() {
    return needed_timeout;
}

double Need::get_needed_t_min(){
    return needed_t_min;
}

double Need::get_needed_t_max(){
    return needed_t_max;
}
