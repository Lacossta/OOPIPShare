#include <iostream>

//#include "../DataTypeValidators/DataTypes.h"
//#include "User/User.h"
//#include "Login/Login.h"
//#include "Registration/Registration.h"
//#include "../MainLogic/Start.h"
//#include "../DisplayMenuUtil/DisplayMenuUtil.h"

#include "../PathToLibs.h"

using namespace std;

Auth auth;

int Auth::Authentication() {
    bool work = true;
    User user;
    while(work){
        displayMenuUtil.DisplayAuthMenu();
        switch(dataTypesValidators.CheckToInt()){
            case 1:
                regModule.Register();
                break;
            case 2:
                user = login.LoginMethod();
                if(user.getId()!=-1){
                    start.StartMethod(user);
                }
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "Некорректный ввод! Повторите попытку" << endl;
                break;
        }
    }
    return 0;
}

const vector<User> &Auth::getUsers() const {
    return users;
}

void Auth::setUsers(const vector<User> &users) {
    this->users = users;
}

void Auth::addUsers(const User &user) {
    users.push_back(user);
}

void Auth::ChangeLogin(string newLogin, int id) {
    int index = utilsModule.FindByIdIntoUsers(id);
    users[index].setLogin(newLogin);
}

void Auth::ChangePassword(std::string newPassword, int id) {
    int index = utilsModule.FindByIdIntoUsers(id);
    users[index].setPassword(newPassword);
}

void Auth::CleanUsers() {
    users.clear();
}
