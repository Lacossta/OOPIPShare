#ifndef KURSACH_DISPLAYMENUUTIL_H
#define KURSACH_DISPLAYMENUUTIL_H
//#include "../Auth/User/User.h"

#include "../PathToLibs.h"


class DisplayMenuUtil {
public:
    void DisplayMenuMethod(); //!! пользователь взаимодействие

    void DisplayUserMenu(User& user); //!! меню пользователя

    void DisplayActionMenu(); // выбор взаимодействие

    void DisplayActionSubcriberMenu(); // работа с абонентами
    void DisplayActionClientMenu(); // работа с клиентами
    void DisplayActionRateMenu(); // работа с траифными планами

    void DisplayAuthMenu(); //!! авторизация

    void DisplayChangeInfoMenu(User& user); //!! изменить данные пользователя

    void DisplayRateMenu(); //!! меню тарифного плана


};

extern DisplayMenuUtil displayMenuUtil;


#endif //KURSACH_DISPLAYMENUUTIL_H
