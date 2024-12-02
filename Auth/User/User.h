#ifndef KURSACH_USER_H
#define KURSACH_USER_H

#include <string>
using  namespace std;

class User{
private:
    string password;
    int ID = -1;
    string login;
    bool isAdmin = false;
    bool isHasAccess = false;

public:
    User();

    User(int ID, string login, string password, bool isAdmin, bool isHasAccess);

    User(int ID, string login, string password);

    ~User();

    string getPassword() const;
    void setPassword(string password);

    int getId() const;
    void setId(int id);

    string getLogin() const;
    void setLogin(const string &login);

    bool getIsAdmin() const;
    void setIsAdmin(bool isAdmin);

    bool getIsHasAccess() const;
    void setIsHasAccess(bool isHasAccess);


};

#endif //KURSACH_USER_H
