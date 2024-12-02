#include "../../../PathToLibs.h"


Subcriber subcriber;

Subcriber::Subcriber() {

}

Subcriber::Subcriber(int subId, bool isblock, int age, int rateId, string connectDate,
                     string phone, string surname, string name, string midName)
{
    this -> subId = subId;
    this -> isblock = isblock;
    this -> age = age;
    this -> rateId = rateId;
    this -> connectDate = connectDate;
    this -> phone = phone;
    this -> surname = surname;
    this -> name = name;
    this ->midName = midName;
}


int Subcriber::getSubId() const {
    return subId;
}
void Subcriber::setSubId(int subId) {
    Subcriber::subId = subId;
}

bool Subcriber::getIsblock() const {
    return isblock;
}
void Subcriber::setIsblock(bool isblock) {
    Subcriber::isblock = isblock;
}

int Subcriber::getAge() const {
    return age;
}
void Subcriber::setAge(int age) {
    Subcriber::age = age;
}

int Subcriber::getRateId() const {
    return rateId;
}
void Subcriber::setRateId(int rateId) {
    Subcriber::rateId = rateId;
}

const string &Subcriber::getConnectDate() const {
    return connectDate;
}
void Subcriber::setConnectDate(const string &connectDate) {
    Subcriber::connectDate = connectDate;
}

const string &Subcriber::getPhone() const {
    return phone;
}
void Subcriber::setPhone(const string &phone) {
    Subcriber::phone = phone;
}

const string &Subcriber::getSurname() const {
    return surname;
}
void Subcriber::setSurname(const string &surname) {
    Subcriber::surname = surname;
}

const string &Subcriber::getName() const {
    return name;
}
void Subcriber::setName(const string &name) {
    Subcriber::name = name;
}

const string &Subcriber::getMidName() const {
    return midName;
}
void Subcriber::setMidName(const string &midName) {
    Subcriber::midName = midName;
}


void Subcriber::addSubcriber(const Subcriber &subcriberLoad) {
    subcribers.push_back(subcriberLoad);
}

int Subcriber::generateId() {
    if(subcriber.getSubcribers().size() >0){
        return subcriber.getSubcribers()[subcriber.getSubcribers().size()-1].getSubId() +1;
    }
}

const vector<Subcriber> &Subcriber::getSubcribers() const {
    return subcribers;
}
void Subcriber::setSubcribers(const vector<Subcriber> &subcribers) {
    Subcriber::subcribers = subcribers;
}

void DisplaySingleSubcriber(int subId, bool isblock, int age, int rateId, string connectDate,
                            string phone, string surname, string name, string midName){
    cout << "\n┌────────────────────────────────────┐\n";
    cout << "│          Данные абонента          │\n";
    cout << "├────────────────────────────────────┤\n";
    cout << "│ " << setw(20) << "ID:" << setw(20) << subId << " │\n";
    cout << "│ " << setw(20) << "ФИО:" << setw(10) << (surname + " " + name + " " + midName) << " │\n";
    cout << "│ " << setw(20) << "Возраст:" << setw(20) << age << " │\n";
    cout << "│ " << setw(20) << "Телефон:" << setw(20) << phone << " │\n";
    cout << "│ " << setw(20) << "ID тарифа:" << setw(20) << rateId << " │\n";
    cout << "│ " << setw(20) << "Дата подключения:" << setw(20) << connectDate << " │\n";
    cout << "│ " << setw(20) << "Заблокирован:" << setw(20) << boolalpha << isblock << " │\n";
    cout << "└────────────────────────────────────┘\n";
}

void DisplaySingleSubcriber(int age, int rateId, string connectDate,
                            string phone, string surname, string name, string midName) {
    cout << "\n┌────────────────────────────────────┐\n";
    cout << "│          Введенные данные          │\n";
    cout << "├────────────────────────────────────┤\n";
    cout << "│ " << setw(20) << "ФИО:" << setw(10) << (surname + " " + name + " " + midName) << " │\n";
    cout << "│ " << setw(20) << "Возраст:" << setw(20) << age << " │\n";
    cout << "│ " << setw(20) << "Телефон:" << setw(20) << phone << " │\n";
    cout << "│ " << setw(20) << "ID тарифа:" << setw(20) << rateId << " │\n";
    cout << "│ " << setw(20) << "Дата подключения:" << setw(20) << connectDate << " │\n";
    cout << "└────────────────────────────────────┘\n";
}