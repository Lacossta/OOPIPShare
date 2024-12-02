//#include "Start.h"
//#include "../DataTypeValidators/DataTypes.h"
//#include "../DisplayMenuUtil/DisplayMenuUtil.h"
//#include "EnteredUserLogic/EnteredUser.h"
#include <iostream>

#include "../PathToLibs.h"

Start start;

int Start::StartMethod(User& user){
    while(true) {
        displayMenuUtil.DisplayMenuMethod();
        switch (dataTypesValidators.CheckToInt()) {
            case 1:
                displayMenuUtil.DisplayUserMenu(user);
                if(enteredUser.UserMenu(user) == 0){
                    return 0;
                }
                break;
            case 2:
                if(user.getIsHasAccess()) {
                    displayMenuUtil.DisplayActionMenu();
                    subsLogic.MainMenu(user);
                }
                else{
                    cout << "Отказано в доступе." << endl;
                }
                break;
            case 0:
                exit(0);
            default:
                cout << "Неизвестный вариант!" << endl;
                break;
        }
    }
}