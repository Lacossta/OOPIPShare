#ifndef KURSACH_UTILS_H
#define KURSACH_UTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../PathToLibs.h"
#include "../MainLogic/SubsAndRateLogic/Subcriber/Subcriber.h"
#include "../MainLogic/SubsAndRateLogic/Client/Client.h"
#include "../MainLogic/SubsAndRateLogic/Rate/Rate.h"

using namespace std;

class Utils {
public:
    User FindUserByLogin(const string& login); // поиск по логину
    User FindUserById(const int id); // поиск по айди
    int FindByIdIntoUsers(const int id); // поиск по айди возврат айди

    Subcriber FindSubcriberById(const int id); // поиск по айди



    Rate FindRateById(const int id);

    int FindByIdIntoClient(const int id);
    Client FindClientById(const int id);


    int GenerateID();
};

extern Utils utilsModule;

#endif //KURSACH_UTILS_H
