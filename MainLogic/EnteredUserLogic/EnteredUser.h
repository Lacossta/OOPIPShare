#ifndef KURSACH_ENTEREDUSER_H
#define KURSACH_ENTEREDUSER_H

#include <string>
//#include "../../Auth/User/User.h"
//#include "../../Auth/Auth.h"
//#include "../../DataTypeValidators/DataTypes.h"
//#include "../../Auth/UserFileSystem/UserFileSystem.h"
//#include "../../DisplayMenuUtil/DisplayMenuUtil.h"
//#include "../../config/config.h"
//#include "../../Utils/Utils.h"

#include "../../PathToLibs.h"
using namespace std;


class EnteredUser{
public:
    int UserMenu(User& user);

    void ChangeLoginMethod(string newLogin, User& user);

    void ChangePasswordMethod(string newPassword, User& user);

    void RemoveUserMethod(int removeId);

    void AllowAccessMethod(int accessId);

    void DenyAccess(int accessId);

    void GrantAdmin(int adminId);

    void DenyAdmin(int adminId, string login);

    void ChangePasswordMenu();

    void ChangesChoose(User& user);


};

extern EnteredUser enteredUser;

#endif //KURSACH_ENTEREDUSER_H
