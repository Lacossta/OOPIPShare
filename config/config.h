#ifndef KURSACH_CONFIG_H
#define KURSACH_CONFIG_H

#include <string>
using namespace std;

#include "../PathToLibs.h"

class Config{
public:
    int minPasswordLength = 3;
    int maxPasswordLength = 50;

    int minLoginLength = 3;
    int maxLoginLength = 30;

    string adminLogin = "admin";
    string adminPassword = "admin";

    string userDataPath = "./../bin/UserData.txt";
    string configDataPath = "./../bin/config.txt";
    string SubcriberDataPath = "./../bin/SubcriberData.txt";
    string RateDataPath = "./../bin/RateData.txt";
    string ClientDataPath = "./../bin/ClientData.txt";

    void LoadFromFile();

    void SaveToFile();

//  void SaveToFile(int id);


    Config();

    ~Config();
};

extern Config config;

#endif //KURSACH_CONFIG_H