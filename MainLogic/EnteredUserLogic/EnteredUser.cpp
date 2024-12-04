//#include "EnteredUser.h"

#include "../../PathToLibs.h"

EnteredUser enteredUser;

int EnteredUser::UserMenu(User& user) { // Меню пользователя
    bool work = true;
    while(work)
    {
        switch (dataTypesValidators.CheckToInt())
        {
            case 1: // change info
                displayMenuUtil.DisplayChangeInfoMenu(user);
                enteredUser.ChangesChoose(user);
                work = false;
                break;
            case 2: // exit account
                return 0;
            case 0:
                return 1;
            default:
                cout << "Ошибка!" << endl;
                break;
        }
    }
    return 0;
}

void EnteredUser::ChangeLoginMethod(string newLogin, User& user) {
    auth.ChangeLogin(newLogin, user.getId());
    userFileSystem.RewriteUserInfo();
}

void EnteredUser::ChangePasswordMethod(string newPassword, User& user) {
    auth.ChangePassword(newPassword, user.getId());
    userFileSystem.RewriteUserInfo();
}

void EnteredUser::RemoveUserMethod(int removeId) {

    vector <User> users = auth.getUsers();
    User user = utilsModule.FindUserById(removeId);
    int index = utilsModule.FindByIdIntoUsers(removeId);

    if(user.getIsAdmin() == false && user.getId() != -1 && index != -1) {
        users.erase(users.begin() + index);
        auth.setUsers(users);
        userFileSystem.RewriteUserInfo();
        cout << "Пользователь №" << index << " был удален" << endl;
    }
    else
    {
        cout << "Error!";
    }
}

void EnteredUser::AllowAccessMethod(int accessId) {
    vector <User> users = auth.getUsers();
    User user = utilsModule.FindUserById(accessId);
    int index = utilsModule.FindByIdIntoUsers(accessId);

    if(user.getId() != -1 && index != -1) {
        users[index].setIsHasAccess(true);
        auth.setUsers(users);
        userFileSystem.RewriteUserInfo();
        cout << "Пользователь №" << index << " был допущен к работе" << endl;
    }
    else
    {
        cout << "Пользователя с данным ID не существует";
    }
}

void EnteredUser::DenyAccess(int accessId) {
    vector <User> users = auth.getUsers();
    User user = utilsModule.FindUserById(accessId);
    int index = utilsModule.FindByIdIntoUsers(accessId);

    if(user.getId() != -1 && index != -1) {
        users[index].setIsHasAccess(false);
        auth.setUsers(users);
        userFileSystem.RewriteUserInfo();
        cout << "У пользователь №" << index << " теперь нет доступа" << endl;
    }
    else
    {
        cout << "Error!";
    }
}

void EnteredUser::GrantAdmin(int adminId) {
    vector <User> users = auth.getUsers();
    User user = utilsModule.FindUserById(adminId);
    int index = utilsModule.FindByIdIntoUsers(adminId);

    if(user.getIsAdmin() == false && user.getId() != -1 && index != -1) {
        users[index].setIsAdmin(true);
        auth.setUsers(users);
        userFileSystem.RewriteUserInfo();
        cout << "Пользователь №" << index << " получил парва админа" << endl;
    }
    else
    {
        cout << "Error!";
    }
}

void EnteredUser::DenyAdmin(int adminId, string login) {
    vector <User> users = auth.getUsers();
    User user = utilsModule.FindUserById(adminId);
    int index = utilsModule.FindByIdIntoUsers(adminId);

    if(user.getIsAdmin() == true && user.getId() != -1 && index != -1 && user.getLogin() != login) {
        users[index].setIsAdmin(false);
        auth.setUsers(users);
        userFileSystem.RewriteUserInfo();
        cout << "Пользователь №" << index << " больше не админ" << endl;
    }
    else
    {
        cout << "Права админа у самого себя забрать невозможно";
    }
}

void EnteredUser::ChangesChoose(User& user) { // выбрать что изменить
    bool work = true;
    string newLogin, newPassword;
    while(work){
        switch (dataTypesValidators.CheckToInt()) {
            case 1:
                cout << "Введите новый логин:" << endl;
                newLogin = dataTypesValidators.InputString();
                if(!utilsModule.FindUserByLogin(newLogin).getLogin().empty()){
                    cout << "Такой логин уже существует! " << endl;
                }
                else if(!newLogin.empty() && newLogin.size() >= config.minLoginLength && newLogin.size() <= config.maxLoginLength)
                {
                    cout << "Логин был изменен!" << endl;
                    enteredUser.ChangeLoginMethod(newLogin, user);
                }
                else{
                    cout << "Некоректный логин!" << endl;
                }
                work = false;
                break;
            case 2:
                cout << "Введите новый пароль:" << endl;
                newPassword = dataTypesValidators.InputString();
                if(!newPassword.empty() && newPassword.size() >= config.minPasswordLength && newPassword.size() <= config.maxPasswordLength)
                {
                    cout << "Пароль был изменен!" << endl;
                    enteredUser.ChangePasswordMethod(newPassword, user);
                }
                else{
                    cout << "Некоректный пароль!" << endl;
                }
                work = false;
                break;

            case 3: // remove user
                if(user.getIsAdmin()){
                    cout << "Введите id пользователя для удаления: ";
                    enteredUser.RemoveUserMethod(dataTypesValidators.CheckToInt());
                    cout << endl;
                    work = false;
                }
                else{
                    cerr << "Отказано в доступе!" << endl;
                }
                break;

            case 4: // access true
                if(user.getIsAdmin()){
                    cout << "Введите id пользователя: ";
                    enteredUser.AllowAccessMethod(dataTypesValidators.CheckToInt());
                    cout << endl;
                    work = false;
                }
                else{
                    cerr << "Отказано в доступе!" << endl;
                }

                break;
            case 5: // access false
                if(user.getIsAdmin()){
                    cout << "Введите id пользователя: ";
                    enteredUser.DenyAccess(dataTypesValidators.CheckToInt());
                    cout << endl;
                    work = false;
                }
                else{
                    cerr << "Отказано в доступе!" << endl;
                }
                break;
            case 6: // admin tue
                if(user.getIsAdmin()){
                    cout << "Введите id пользователя: ";
                    enteredUser.GrantAdmin(dataTypesValidators.CheckToInt());
                    cout << endl;
                    work = false;
                }
                else{
                    cerr << "Отказано в доступе!" << endl;
                }
            break;

            case 7:
                if(user.getIsAdmin()){
                    cout << "Введите id пользователя: ";
                    enteredUser.DenyAdmin(dataTypesValidators.CheckToInt(), user.getLogin());
                    cout << endl;
                    work = false;
                }
                else{
                    cerr << "Отказано в доступе!" << endl;
                }
                break;

            case 0:
                work =  false;
                break;
            default:
                cout << "Ошибка!" << endl;
                break;
        }
    }
}

