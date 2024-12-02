#include <string>
#include <iostream>
//#include "User.h"
#include <string>

#include "../../PathToLibs.h"
using  namespace std;

    User::User(){}

    User::User(int ID, string login, string password, bool isAdmin, bool isHasAccess){
        this->login = login;
        this->password = password;
        this->ID = ID;
        this->isAdmin = isAdmin;
        this->isHasAccess = isHasAccess;
    }

    User::User(int ID, string login, string password){
        this->login = login;
        this->password = password;
        this->ID = ID;
    }

    User::~User(){

    }

    string User::getPassword() const {
        return password;
    }
    void User::setPassword(string password) {
        User::password = password;
    }

    int User::getId() const {
        return ID;
    }
    void User::setId(int id) {
        User::ID = id;
    }

    string User::getLogin() const {
        return login;
    }
    void User::setLogin(const string &login) {
        User::login = login;
    }

    bool User::getIsAdmin() const {
        return isAdmin;
    }
    void User::setIsAdmin(bool isAdmin) {
        User::isAdmin = isAdmin;
    }

    void User::setIsHasAccess(bool isHasAccess) {
        User::isHasAccess = isHasAccess;
    }
    bool User::getIsHasAccess() const{
        return isHasAccess;
    }





