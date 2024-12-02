//#include "DataTypes.h"
//#include "../config/config.h"
#include <string>
#include <iostream>
using namespace std;

#include "../PathToLibs.h"

DataTypesValidators dataTypesValidators;

void DataTypesValidators::RemoveSpaces(string& str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

int DataTypesValidators::CheckToInt(){
    int Integer;
    cin.clear();
    while (true) {
        cin >> Integer;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Вы ввели не число, повторите попытку " << endl;
        }
        else {
            break;
        }
    }
    cin.clear();
    return Integer;
}

string DataTypesValidators::InputString(){
    string str;

    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    getline(cin, str);

    if (cin.fail())
    {
        cin.clear();
        cerr << "read_error" << std::endl;
    }

    RemoveSpaces(str);
    return str;
}

bool DataTypesValidators::CheckToBool(){
    bool Boolean;
    while (true) {
        cin >> Boolean;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Вы ввели не bool, повторите попытку " << endl;
        }
        else {
            break;
        }
    }
    return Boolean;
}
