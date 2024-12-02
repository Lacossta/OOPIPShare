#include "../../../PathToLibs.h"

Client client;

void Client::addClient(const Client &clientAdd) {
    clients.push_back(clientAdd);
}

int Client::generateClientId() {
    if(client.getClients().size() >0){
        return client.getClients()[client.getClients().size() - 1].getClientId() + 1;
    }
}

Client::Client(int clientId, int age, string name) {
    this->clientId = clientId;
    this->age = age;
    this->name = name;

}

const vector<Client> &Client::getClients() const {
    return clients;
}
void Client::setClients(const vector<Client> &clients) {
    Client::clients = clients;
}

Client::Client() {

}

int Client::getClientId() const {
    return clientId;
}
void Client::setClientId(int clientId) {
    Client::clientId = clientId;
}

int Client::getAge() const {
    return age;
}
void Client::setAge(int age) {
    Client::age = age;
}

const string &Client::getSurname() const {
    return surname;
}
void Client::setSurname(const string &surname) {
    Client::surname = surname;
}

const string &Client::getName() const {
    return name;
}
void Client::setName(const string &name) {
    Client::name = name;
}

const string &Client::getMidName() const {
    return midName;
}
void Client::setMidName(const string &midName) {
    Client::midName = midName;
}

const string &Client::getName() const {
    return name;
}
void Client::setName(const string &name) {
    Client::name = name;
}

