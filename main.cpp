#include <iostream>

#include "./PathToLibs.h"
#include "./MainLogic/SubsAndRateLogic/Subcriber/Subcriber.h"

int main() {
    //system("chcp 65001");
    userFileSystem.LoadUserInfo();
    SubsFileSystem.LoadRateInfo();
    SubsFileSystem.LoadSubcriberInfo();
    SubsFileSystem.LoadClientInfo();

//    int age =12, rateId = 12, subId = 12;
//    string connectDate = "2222-22-22", phone = "+375(23)1232323";
//    string surname= "Костюкевич", name = "Евгенийлыралырвалывралыва", midName = "Вииииииииииииииииитальевич";
//    string surname= "Kostsiuckevich", name = "Evgeny", midName = "Viiiiiiiiiiiitalievichsdfsdfkshdfkshdfkhsdkfhsdfsdf";
//    bool isblock = false;
//
//    subcriber.DisplaySingleSubcriber( subId,  isblock,  age,  rateId,  connectDate,
//             phone,  surname,  name,  midName);

    auth.Authentication();
    return 0;
}