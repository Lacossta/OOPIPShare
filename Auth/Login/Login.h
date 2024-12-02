#ifndef KURSACH_LOGIN_H
#define KURSACH_LOGIN_H
//#include "../User/User.h"

#include "../../PathToLibs.h"


class Login{
public:
    User LoginMethod();

    string InputPassword(string password, User& user);
};

extern Login login;
#endif //KURSACH_LOGIN_H
