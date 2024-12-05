//#include "DataTypes.h"
//#include "../config/config.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#include "../PathToLibs.h"

DataTypesValidators dataTypesValidators;

void DataTypesValidators::RemoveSpaces(string& str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

//int DataTypesValidators::CheckToInt(){
//    int Integer;
//    cin.clear();
//    while (true) {
//        cin >> Integer;
//        if (cin.fail()) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cerr << "Вы ввели не число, повторите попытку " << endl;
//        }
//        else {
//            break;
//        }
//    }
//    cin.clear();
//    return Integer;
//}

int DataTypesValidators::CheckToInt() {
    int Integer =0;
    cin.clear();
    while (true) {
        char c = cin.peek();
        if (c == '\n') {
            cin.ignore();
            return -1;
        }

        cin >> Integer;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Вы ввели не число, повторите попытку " << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    cin.clear();
    return Integer;
}

float DataTypesValidators::CheckToFloat() {
    float number = 0.0;
    cin.clear();
    while (true) {
        char c = cin.peek();
        if (c == '\n') {
            cin.ignore();
            return -1.0f;
        }

        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Вы ввели не число или неверный формат. Повторите попытку." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    cin.clear();
    return number;
}


string DataTypesValidators::InputString(){
    string str;

    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    getline(cin, str);

    if(str.empty()){
        return "";
    }

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
