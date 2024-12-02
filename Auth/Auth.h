using namespace std;
//#include "User/User.h"
#include <vector>

#include "../PathToLibs.h"

class Auth{
private:
    vector <User> users;
public:
    const vector<User> &getUsers() const;

    void setUsers(const vector<User> &users);

    void addUsers(const User &user);

    void ChangeLogin(string newLogin, int id);

    void ChangePassword(string newPassword, int id);

    void CleanUsers();

    int Authentication();

};

extern Auth auth;

