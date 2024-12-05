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

void Rate::DisplaySingleRate(int rateId, float cost, int amountOfNetwork, int callTime) const {
    cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
    cout <<   "║                          Данные тарифа                         ║\n";
    cout <<   "╠════════════════╤═══════════════════════════════════════════════╣\n";
    cout << "║ " << setw(14) << left << "ID:"
         << " │ " << setw(45) << left << rateId << " ║\n";
    cout << "║ " << setw(23) << left << "Стоимость:"
         << " │ " << setw(45) << left << cost << " ║\n";
    cout << "║ " << setw(20) << left << "Трафик:"
         << " │ " << setw(45) << left << amountOfNetwork << " ║\n";
    cout << "║ " << setw(21) << left << "Беспл. минуты:"
         << " │ " << setw(45) << left << callTime <<" ║" << endl;
    cout <<  "╚════════════════╧═══════════════════════════════════════════════╝\n";
}

vector<Rate> Rate::FindRatesByCost(float cost){
    vector<Rate> foundRates;

    for (const auto& it : rates) {
        if (it.getCost() == cost) {
            foundRates.push_back(it);
        }
    }

    return foundRates;
}