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

Client::Client(int clientId, int age, string surname,  string name, string midName) {
    this->clientId = clientId;
    this->age = age;
    this->surname = surname;
    this->name = name;
    this->midName = midName;

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

void Client::DisplaySingleClient(int clientId, int age, string surname, string name, string midName) {
//    cout << "\n┌────────────────────────────────────┐\n";
//    cout << "│           Данные клиента           │\n";
//    cout << "├────────────────────────────────────┤\n";
//    cout << "│ " << setw(20) << "ID:" << setw(20) << clientId << " │\n";
//    cout << "│ " << setw(20) << "ФИО:" << setw(10) << (surname + " " + name + " " + midName) << " │\n";
//    cout << "│ " << setw(20) << "Возраст:" << setw(20) << age << " │\n";
//    cout << "└────────────────────────────────────┘\n";

    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + ".";
        return str;
    };

    cout << "\n╔═════════════════════════════════════════════════════════════════════════════╗\n";
    cout <<   "║                              Данные клиента                                 ║\n";
    cout <<   "╠════════════════╤════════════════════════════════════════════════════════════╣\n";
    cout << "║ " << setw(14) << left << "ID:"
         << " │ " << setw(58) << left << clientId << " ║\n";
    cout << "║ " << setw(17) << left << "ФИО:"
         << " │ " << setw(58) << left << trim(surname + " " + name + " " + midName, 53) << " ║\n";
    cout << "║ " << setw(21) << left << "Возраст:"
         << " │ " << setw(58) << left << age << " ║" << endl;
    cout << "╚════════════════╧════════════════════════════════════════════════════════════╝\n";
}

vector<Client> Client::FindClientsByFullName(const string& surname, const string& name, const string& midName) {
    vector<Client> foundClients;

    for (const auto& client : clients) {
        if (client.getSurname() == surname && client.getName() == name && client.getMidName() == midName) {
            foundClients.push_back(client);
        }
    }

    return foundClients;
}



