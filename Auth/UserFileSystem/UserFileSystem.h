//
// Created by Evgeny Kost on 8.04.24.
//

#ifndef KURSACH_USERFILESYSTEM_H
#define KURSACH_USERFILESYSTEM_H

//#include "../User/User.h"
#include "../../PathToLibs.h"


class UserFileSystem {
public:
    void LoadUserInfo();
    void SaveUserInfo(const User& user);
    void RewriteUserInfo();

    UserFileSystem();
};

extern UserFileSystem userFileSystem;


#endif //KURSACH_USERFILESYSTEM_H
