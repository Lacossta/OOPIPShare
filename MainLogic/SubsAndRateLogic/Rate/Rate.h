#ifndef KURSACH_RATE_H
#define KURSACH_RATE_H

#include "../../../PathToLibs.h"

using namespace std;
#include <string>

// Id cost network calltime

class Rate {
protected:
    int rateId =-1;
    float cost;
    int amountOfNetwork;
    int callTime;

    vector<Rate> rates;
public:
    int getRateId() const;
    void setRateId(int rateId);

    float getCost() const;
    void setCost(float cost);

    int getAmountOfNetwork() const;
    void setAmountOfNetwork(int amountOfNetwork);

    int getCallTime() const;
    void setCallTime(int callTime);

    const vector<Rate> &getRates() const;
    void setRates(const vector<Rate> &repairTypes);

    int generateId();

    void addRate(const Rate &rateAdd);

    Rate();
    Rate(int rateId, float cost, int amountOfNetwork, int callTime);

    void DisplaySingleRate(int rateId, float cost, int amountOfNetwork, int callTime) const;

    vector<Rate> FindRatesByCost(float cost);


};

extern Rate rate;
#endif //KURSACH_RATE_H
