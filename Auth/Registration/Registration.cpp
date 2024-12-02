#include <iostream>
#include "Registration.h"

using namespace std;

Registration regModule;

string Registration::CreateLogin(){
    User user;
    while(true)
    {
        cout << "Введите логин: ";
        string login = dataTypesValidators.InputString();
        user = utilsModule.FindUserByLogin(login);
        if(login.empty())
        {
            cout << "Регитсрация отменена" << endl << endl;
            break;
        }
        else if(user.getLogin() == login )
        {
            cout << "Этот логин занят" << endl;
        }
        else if(login.size() < config.minLoginLength)
        {
            cout << "Логин должен содержать более чем " << config.minLoginLength << " символов" << endl;
        }
        else if(login.size() >= config.maxLoginLength)
        {
            cout << "Логин слишком длинный" << endl;
        }
        else
        {
            user.setId(utilsModule.GenerateID());
            return login;
        }
    }
    return "";
}

string Registration::CreatePassword(string login){

    bool work = true;
    if(!login.empty())
    {
        while (work)
        {
            cout << "Введите пароль: ";
            string password = dataTypesValidators.InputString();

            if (password.empty()) // если пароль не ввели отменяется регестрация
            {
                cout << "Регистраиция отмененеа" << endl << endl ;
                break;
            }
            else {

                 if (password.size() < config.minPasswordLength)
                 {
                     cout << "Пароль должен содержать более чем " << config.minPasswordLength << " символов" << endl;
                 }
                 else if (password.size() >= config.maxPasswordLength)
                 {
                     cout << "Пароль слишком длинный" << endl;
                 }
                 else {
                     while (true) {
                                 cout << "Повторите пароль: ";
                                 string passwordRepeat = dataTypesValidators.InputString();
                                 if (passwordRepeat.compare(password) == false) {
                                     cout << endl << "Регистрация успешно завершена" << endl << endl;
                                     return password;
                                 } else {
                                     cout << "Пароли не совпадают" << endl;
                         }
                     }
                 }
            }
        }
    }
    return "";
}

void Registration::Register(){
    UserFileSystem file;
    string password, login;
    login = CreateLogin();
    int id = utilsModule.GenerateID();
    password = CreatePassword(login);

    if(!login.empty() && !password.empty()) {
        User user(id, login, password);
        auth.addUsers(user);
        file.SaveUserInfo(user);
    }
}