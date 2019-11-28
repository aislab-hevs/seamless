/*
 * bid.cc
 *
 *  Created on: 14 gen 2018
 *      Author: peppe
 */
#include "../headers/ag_bid.h"

Bid::Bid(int contractor, double offer, double utilization){
    this->contractor = contractor;
    this->offer = offer;
    this->utilization = utilization;
}

Bid::~Bid(){

}

Bid::Bid(int contractor){
    this->contractor = contractor;
    this->offer = 0.0;
}

int Bid::getContractor(){
    return this->contractor;
}

double Bid::getOffer(){
    return this->offer;
}

double Bid::getUtilization(){
    return this->utilization;
}

bool Bid::equals(int contractor){
    return this->contractor == contractor;
}




