#include <iostream>

#include "./PathToLibs.h"

int main() {
    userFileSystem.LoadUserInfo();
    machineFileSystem.LoadRateInfo();
    machineFileSystem.LoadSubcriberInfo();
    machineFileSystem.LoadClientInfo();
    auth.Authentication();
    return 0;
}