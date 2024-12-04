#include <iostream>
#include <string>


#include <stdio.h>
#include <iostream>
#include <limits>

#include "../../PathToLibs.h"

Login login;

string Login::InputPassword(string password, User& user){
    while (true) {
        cout << "Введите пароль: ";
        password = dataTypesValidators.InputString();
        if(password == user.getPassword()){
            return password;
        }
        else {
            cout << "Неверный пароль, повторите" << endl;
        }
    }
}

User Login::LoginMethod() {
    string login;
    string password;
    bool work = true;
    User user;

    while(work){
        cout << "Введите логин: ";
        login = dataTypesValidators.InputString();

        if(login.empty()){
            return user;
        }

        else {
            user = utilsModule.FindUserByLogin(login);
            if (login == user.getLogin() && user.getId()!=-1){
                password = InputPassword(password, user);
                if(!password.empty()){
                    return user;
                }
                break;
            }
            else {
                cout << "Пользователь с указанным логином не найден" << std::endl;
            }
            }
        }
    }

    Login::Login() {

    }
