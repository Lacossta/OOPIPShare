//#include "config.h"
#include <fstream>
#include <iostream>

//string userDataPath = "./../Auth/bin/UserData.txt";
//string configDataPath = "../Auth/bin/config.txt";

#include "../PathToLibs.h"

void Config::SaveToFile()
{
    ofstream outputFile(Config::configDataPath);

    if(outputFile.is_open())
    {
        outputFile << "minPasswordLength: " << Config::minPasswordLength << endl;
        outputFile << "maxPasswordLength: " << Config::maxPasswordLength << endl;

        outputFile << "maxLoginLength: " <<  Config::maxLoginLength << endl;
        outputFile << "minLoginLength: " <<  Config::minLoginLength << endl;

        outputFile << "userDataPath: " <<  Config::userDataPath << endl;
        outputFile << "configDataPath: " <<  Config::configDataPath << endl;
        outputFile << "SubcriberDataPath: " << Config::SubcriberDataPath << endl;
        outputFile << "RateDataPath: " << Config::RateDataPath << endl;
        outputFile << "ClientDataPath: " << Config::ClientDataPath << endl;



        outputFile << "adminLogin: " << Config::adminLogin;
        outputFile << "adminPassword: " << Config::adminPassword;

        outputFile.close();
    }
    else
    {
        cerr << "error_to_save_config" << endl;
    }
}

void Config::LoadFromFile()
{
    ifstream inputFile(Config::configDataPath);
    if(inputFile.is_open()){
        string line;
        while (getline(inputFile, line)) {

            if (line.find("minPasswordLength: ") != string::npos)
            {
                config.minPasswordLength = stoi(line.substr(line.find(":") + 2));
                //substr получения подстроки из исходной строки
                //string::npos представляет максимальное возможное значение
            }

            else if (line.find("maxPasswordLength: ") != string::npos)
            {
                config.maxPasswordLength = stoi(line.substr(line.find(":") + 2));
            }

            else if (line.find("maxLoginLength: ") != string::npos)
            {
                config.maxLoginLength = stoi(line.substr(line.find(":") + 2));
            }

            else if (line.find("minLoginLength: ") != string::npos)
            {
                config.minLoginLength = stoi(line.substr(line.find(":") + 2));
            }
            else if (line.find("minLoginLength: ") != string::npos)
            {
                config.adminLogin = stoi(line.substr(line.find(":") + 2));
            }

            else if (line.find("minLoginLength: ") != string::npos)
            {
                config.adminPassword = stoi(line.substr(line.find(":") + 2));
            }
            else if (line.find("userDataPath: ") != string::npos)
            {
                config.userDataPath = line.substr(line.find(":") + 2);
            }

            else if (line.find("configDataPath: ") != string::npos)
            {
                config.configDataPath = line.substr(line.find(":") + 2);
            }

            else if (line.find("SubcriberDataPath: ") != string::npos)
            {
                config.SubcriberDataPath = line.substr(line.find(":") + 2);
            }

            else if (line.find("RateDataPath: ") != string::npos)
            {
                config.RateDataPath = line.substr(line.find(":") + 2);
            }

            else if (line.find("ClientDataPath: ") != string::npos)
            {
                config.ClientDataPath = line.substr(line.find(":") + 2);
            }
        }
        inputFile.close();
    }
    else
    {
        cerr << "error_to_load_config" << endl;
    }
}

Config::Config() {
    Config::LoadFromFile();
}

Config::~Config(){

}

Config config;

