#ifndef KURSACH_REGISTRATION_H
#define KURSACH_REGISTRATION_H

using namespace std;

//#include "../Auth.h"
//#include "../../DataTypeValidators/DataTypes.h"
//#include "../../config/config.h"
//#include "../UserFileSystem/UserFileSystem.h"

#include "../../Utils/Utils.h"
#include "../../PathToLibs.h"

class Registration{
private:
    Utils utilsModule;
public:
    void Register();

    string CreateLogin();

    string CreatePassword(string);
};

extern Registration regModule;

#endif
