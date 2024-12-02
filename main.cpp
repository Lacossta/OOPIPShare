#include <iostream>

#include "./PathToLibs.h"

int main() {
    userFileSystem.LoadUserInfo();
    SubsFileSystem.LoadRateInfo();
    SubsFileSystem.LoadSubcriberInfo();
    SubsFileSystem.LoadClientInfo();
    auth.Authentication();
    return 0;
}