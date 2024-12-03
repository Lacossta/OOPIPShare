#ifndef KURSACH_CLIENT_H
#define KURSACH_CLIENT_H

#include "../../../PathToLibs.h"
//#include "../Rate/Rate.h"

//Id name age
class Client{
private:
    int clientId = -1;
    int age;
    string surname;
    string name;
    string midName;
    vector <Client> clients;
public:
    int getClientId() const;
    void setClientId(int clientId);

    int getAge() const;
    void setAge(int age);

    const string &getSurname() const;
    void setSurname(const string &surname);

    const string &getName() const;
    void setName(const string &name);

    const string &getMidName() const;
    void setMidName(const string &midName);

    const vector<Client> &getClients() const;
    void setClients(const vector<Client> &clients);

    Client();
    Client(int clientId, int age, string surname,  string name, string midName);

public:
    void addClient(const Client &clientAdd);

    int generateClientId();

    void DisplaySingleClient(int clientId, int age, string surname, string name, string midName);
};

extern Client client;


#endif //KURSACH_CLIENT_H
