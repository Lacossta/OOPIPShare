#include "../../../PathToLibs.h"

Rate rate;

int Rate::generateId() {
    if(rate.getRates().size() >0){
        return rate.getRates()[rate.getRates().size() - 1].getRateId() + 1;
    }
}

void Rate::addRate(const Rate &rateAdd) {
    rates.push_back(rateAdd);
}

Rate::Rate() {

}

Rate::Rate(int rateId, float cost, int amountOfNetwork, int callTime) {
    this -> rateId = rateId;
    this -> cost = cost;
    this -> amountOfNetwork = amountOfNetwork;
    this -> callTime = callTime;
}


const vector<Rate> &Rate::getRates() const {
    return rates;
}
void Rate::setRates(const vector<Rate> &repairTypes) {
    Rate::rates = repairTypes;
}

int Rate::getRateId() const {
    return rateId;
}
void Rate::setRateId(int rateId) {
    Rate::rateId = rateId;
}

float Rate::getCost() const {
    return cost;
}
void Rate::setCost(float cost) {
    Rate::cost = cost;
}

int Rate::getAmountOfNetwork() const {
    return amountOfNetwork;
}
void Rate::setAmountOfNetwork(int amountOfNetwork) {
    Rate::amountOfNetwork = amountOfNetwork;
}

int Rate::getCallTime() const {
    return callTime;
}
void Rate::setCallTime(int callTime) {
    Rate::callTime = callTime;
}
