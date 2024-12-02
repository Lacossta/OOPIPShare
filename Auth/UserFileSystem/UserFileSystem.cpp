#include <fstream>
#include <iostream>
#include <sstream>
//#include "UserFileSystem.h"
//#include "../../config/config.h"
//#include "../Auth.h"
//#include "../User/User.h"

#include "../../PathToLibs.h"

UserFileSystem userFileSystem;

void UserFileSystem::LoadUserInfo() {

    ifstream check(config.userDataPath);

    if (!check.is_open())
    {
        ofstream inputfile(config.userDataPath, ios::app);
        inputfile << "0 admin admin 1 1" << endl;
        inputfile.close();
    }
    else{
        check.close();
    }

    ifstream file(config.userDataPath);
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string login, password;
        int id;
        bool isAdmin, isHasAccess;

        if (iss >> id >> login >> password >> isAdmin >> isHasAccess)
        {
            User user(id, login, password, isAdmin, isHasAccess);
            auth.addUsers(user);
        }
    }
}

void UserFileSystem::SaveUserInfo(const User& user){
    ofstream file(config.userDataPath, ios::app);
    if (file.is_open() && user.getId() != -1) {
        file << user.getId() << " " << user.getLogin() << " " << user.getPassword() << " "
             << user.getIsAdmin() << " " << user.getIsHasAccess() << endl;
        file.close();
    }
    else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

void UserFileSystem::RewriteUserInfo() {
    ofstream file(config.userDataPath, ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        vector <User> users = auth.getUsers();
        for(int i = 0; i<auth.getUsers().size(); i++) {
                file << users[i].getId() << " " << users[i].getLogin() << " " << users[i].getPassword() << " "
                     << users[i].getIsAdmin() << " " << users[i].getIsHasAccess() << endl;
        }
        file.close();
        auth.CleanUsers();
        UserFileSystem::LoadUserInfo();
    }
    else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

UserFileSystem::UserFileSystem() {

}