#ifndef KURSACH_SUBCRIBERREGISTRATION_H
#define KURSACH_SUBCRIBERREGISTRATION_H

#include "../../../PathToLibs.h"
#include <chrono>
#include <iomanip>

class SubcriberRegistration {
public:
    void SubcriberRegister(User &user);

    string getCurrentDate();
    void printTable(const int subId, const int age, const int rateId,
                    const string& connectDate, const string& phone,
                    const string& surname, const string& name,
                    const string& midName, const bool isblock);
};

extern SubcriberRegistration subcriberRegModule;


#endif //KURSACH_SUBCRIBERREGISTRATION_H
