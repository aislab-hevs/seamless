/*
 * task.cc
 *
 *  Created on: Feb 21, 2017
 *      Author: davide
 */

#include "../headers/ag_heuristic_handler.h"
#include "../headers/agent.h"
#include <random>
#include <chrono>

Hhandler::Hhandler() {
}

Hhandler::~Hhandler(){

}

int Hhandler::gen_random(int range){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //we use clock as a seed

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, range);

    return dist(gen);
}

double Hhandler::rand_in_range(double min, double max){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //we use clock as a seed
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> unif(min, max);
    return unif(gen);
}

bool Hhandler::flip_coin(){
    return gen_random(1) % 2;
}

bool Hhandler::get_raise_chance(int round, int neg_type){
    if(neg_type == EN){
        return gen_random(100) < (1.0/round)*100;
    } else{
        return !(gen_random(100) < (1.0/round)*100);
    }
}

//Select contractor to send cfp
void Hhandler::select_first(vector<int> &p_ag_ids_vector) {
    p_ag_ids_vector.erase(p_ag_ids_vector.begin() + 1, p_ag_ids_vector.end());
}

//Check random generation of subset
void Hhandler::select_random_subset(vector<int> &p_ag_ids_vector){
    std::set<unsigned int> indices;
    //note qui va deciso QUANTI elementi del vettore originale vengono presi (dimensione del subset)
    //al momento ne prende la met�
    while (indices.size() < p_ag_ids_vector.size() - 1)
        indices.insert(gen_random(p_ag_ids_vector.size()));
    for(auto index : indices) {
      if(index < p_ag_ids_vector.size())
      p_ag_ids_vector.erase(p_ag_ids_vector.begin() + index);
    }
}

void Hhandler::select_random_contractor(vector<int> &p_ag_ids_vector){
    int temp = p_ag_ids_vector[gen_random(p_ag_ids_vector.size() - 1)];
    p_ag_ids_vector.clear();
    p_ag_ids_vector.push_back(temp);
}

void Hhandler::select_contractors(int policy, vector<int> &p_ag_ids_vector){
    switch(policy){
    case FIRST:{
        select_first(p_ag_ids_vector);
        break;
    }
    case RANDOM:{
        select_random_contractor(p_ag_ids_vector);
        break;
    }
    case RAND_SUBSET:{
        select_random_subset(p_ag_ids_vector);
        break;
    }
    case ALL:{
        break;
    }
    default:{
        EV_WARN << "Heuristic not found!\n";
        break;
    }
    }
}

//Select contractor to acknowledge
int Hhandler::select_first_bidder(vector<Bid*> bids){
    return bids[0]->getContractor();
}

int Hhandler::select_random_bidder(vector<Bid*> bids) {
//  uniformly-distributed integer random number generator that produces non-deterministic random numbers.
//  mt19937: Mersenne Twister
//  uniform_int_distribution: produces random integer values i, uniformly distributed on the closed interval [a, b]
//  this was used to avoid the bias of rand() function generating uneven probability distribution
    return bids[gen_random(bids.size() - 1)]->getContractor();
}

int Hhandler::select_best_offerer(vector<Bid*> bids, int neg_type){
    Bid* bid;
    if(neg_type == DU) {
        auto min = std::min_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) { return a->getOffer() < b->getOffer(); });
        bid = *min;
   } else {
       auto max = std::max_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) { return a->getOffer() < b->getOffer(); });
       bid = *max;
   }
   return bid->getContractor();
}

int Hhandler::select_min_period_min_util(vector<Bid*> bids){
    Bid* bid;
    auto min = std::min_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) {
        return ((a->getOffer() < b->getOffer())) ||
               ((a->getOffer() == b->getOffer()) && (a->getUtilization() < b->getUtilization())); });
    bid = *min;
    return bid->getContractor();
}

int Hhandler::select_min_period_max_util(vector<Bid*> bids){
    Bid* bid;
    auto min = std::min_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) {
        return ((a->getOffer() < b->getOffer())) ||
               ((a->getOffer() == b->getOffer()) && (a->getUtilization() > b->getUtilization())); });
    bid = *min;
    return bid->getContractor();
}

int Hhandler::select_min_util(vector<Bid*> bids){
    Bid* bid;
    auto min = std::min_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) {
        return (a->getUtilization() < b->getUtilization()); });
    bid = *min;
    return bid->getContractor();
}

int Hhandler::select_max_util(vector<Bid*> bids){
    Bid* bid;
    auto max = std::max_element(bids.begin(), bids.end(), [](Bid* a, Bid* b) {
        return (a->getUtilization() < b->getUtilization()); });
    bid = *max;
    return bid->getContractor();
}

int Hhandler::select_bidder(int policy, vector<Bid*> bids, int neg_type){
    int contractor_id = -1;
    switch(policy){
    case FIRST:{
        contractor_id = select_first_bidder(bids);
        break;
    }
    case RANDOM:{
        contractor_id = select_random_bidder(bids);
        break;
    }
    case BEST:{
        contractor_id = select_best_offerer(bids, neg_type);
        break;
    }
    case MIN_WLB:{
        contractor_id = select_min_period_min_util(bids);
        break;
    }
    case MIN_WLM:{
        contractor_id = select_min_period_max_util(bids);
        break;
    }
    case WLB: {
        contractor_id = select_min_util(bids);
        break;
    }
    case WLM: {
        contractor_id = select_max_util(bids);
        break;
    }
    default:{
        EV_WARN << "Heuristic not found!\n";
        break;
    }
    }
    return contractor_id;
}

void Hhandler::prova_heuristica() {
    EV << "ECCOMI QUI :D\n";
}

