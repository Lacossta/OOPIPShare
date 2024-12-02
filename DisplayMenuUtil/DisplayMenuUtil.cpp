//#include "DisplayMenuUtil.h"
//#include "../Auth/User/User.h"
#include <iostream>
using namespace std;

#include "../PathToLibs.h"

DisplayMenuUtil displayMenuUtil;

void DisplayMenuUtil::DisplayMenuMethod(){
    cout << endl << "———————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl
         <<"1. Меню пользователя" << endl
         <<"2. Меню взаимодействия" << endl
         <<"0. Выход" << endl;
    cout << "———————————————————————" << endl;
} //!! пользователь взаимодействие

void DisplayMenuUtil::DisplayUserMenu(User& user){
    //user
    cout << endl << "———————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl <<
    "1. Изменить данные" << endl <<
    "2. Выйти" << endl <<
    "0. Назад" << endl;
    cout << "———————————————————————" << endl;
} //!! меню пользователя

void DisplayMenuUtil::DisplayActionMenu(){
    cout << endl << "———————————————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl <<
            "1. Мею взаимодействия с абонентами" << endl <<
            "2. Мею взаимодействия с клиентами" << endl <<
            "3. Мею взаимодействия с тарифными планами" << endl <<
            "0. Назад" << endl;
    cout <<  "———————————————————————————————" << endl;
} // выбор взаимодействие


void DisplayMenuUtil::DisplayActionSubcriberMenu() {
    cout << endl << "———————————————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl <<
         "1. Добавить абонента" << endl <<
         "2. Изменить абонента" << endl <<
         "3. Удалить абонента" << endl <<
         "4. Найти абонента" << endl <<
         "5. Сортировать абонентов" << endl <<
         "6. Отобразить всех абонентов" << endl <<
         "7. Блокировать абонента" << endl <<
         "0. Назад" << endl;
    cout <<  "———————————————————————————————" << endl;
} // работа с абонентами

void DisplayMenuUtil::DisplayActionClientMenu() {
    cout << endl << "———————————————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl <<
         "1. Добавить клиента" << endl <<
         "2. Изменить клиента" << endl <<
         "3. Удалить клиента" << endl <<
         "4. Найти клиента" << endl <<
         "5. Сортировать клиентов" << endl <<
         "6. Отобразить всех клиентов" << endl <<
         "0. Назад" << endl;
    cout <<  "———————————————————————————————" << endl;
} // работа с клиентами

void DisplayMenuUtil::DisplayActionRateMenu() {
    cout << endl << "———————————————————————————————" << endl;
    cout << "Выберите желаемое меню" << endl <<
         "1. Добавить тарифный план" << endl <<
         "2. Изменить тарифный план" << endl <<
         "3. Удалить тарифный план" << endl <<
         "4. Найти тарифный план" << endl <<
         "5. Сортировать тарифные планы" << endl <<
         "6. Отобразить все тарифные планы" << endl <<
         "0. Назад" << endl;
    cout <<  "———————————————————————————————" << endl;
} // работа с траифными планами


void DisplayMenuUtil::DisplayRateMenu() {
    cout <<
         "—————————————————————————————" << endl <<
         "1. Создать новый тарифный план " << endl <<
         "2. Использовать существующий " << endl <<
         "—————————————————————————————" << endl;
} //!! меню тарифного плана

void DisplayMenuUtil::DisplayAuthMenu(){
    cout <<endl << "———————————————————" << endl;
    cout<< " 1. Регистрация " << endl  << " 2. Войти"  << endl << " 0. Выйти"<< endl;
    cout << "———————————————————" << endl;
} //!! авторизация

void DisplayMenuUtil::DisplayChangeInfoMenu(User& user) {
        cout << endl << "———————————————————" << endl;
        cout << "1. Изменить логин " << endl
             << "2. Изменить пароль" << endl;
    if(user.getIsAdmin() == true){
        cout << "3. Удалить пользователя" << endl
             << "4. Разрешить доступ" << endl
             << "5. Закрыть доступ" << endl
             << "6. Выдать права админа" << endl
             << "7. Забрать права админа" << endl;
    }

    cout << "0. Назад" << endl << "———————————————————" << endl;
} //!! изменить данные пользователя



