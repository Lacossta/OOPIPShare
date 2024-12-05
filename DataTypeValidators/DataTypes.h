#ifndef KURSACH_DATATYPES_H
#define KURSACH_DATATYPES_H

#include <string>
#include <iostream>
using namespace std;

class DataTypesValidators{
public:
    void RemoveSpaces(string& str);
    int CheckToInt();
    string InputString();
    bool CheckToBool();
    float CheckToFloat();
};

extern DataTypesValidators dataTypesValidators;


#endif //KURSACH_DATATYPES_H
