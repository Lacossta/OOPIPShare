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

void Subcriber::DisplaySingleSubcriber(int subId, bool isblock, int age, int rateId, string connectDate,
                                       string phone, string surname, string name, string midName) {
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + ".";
        return str;
    };

    cout << "\n╔═════════════════════════════════════════════════════════════════════════════╗\n";
    cout <<   "║                              Данные абонента                                ║\n";
    cout <<   "╠════════════════╤════════════════════════════════════════════════════════════╣\n";
    cout << "║ " << setw(14) << left << "ID:"
         << " │ " << setw(58) << left << subId << " ║\n";
    cout << "║ " << setw(17) << left << "ФИО:"
         << " │ " << setw(58) << left << trim(surname + " " + name + " " + midName, 53) << " ║\n";
    cout << "║ " << setw(21) << left << "Возраст:"
         << " │ " << setw(58) << left << age << " ║\n";
    cout << "║ " << setw(21) << left << "Телефон:"
         << " │ " << setw(58) << left << trim(phone, 50) << " ║\n";
    cout << "║ " << setw(20) << left << "ID тарифа:"
         << " │ " << setw(58) << left << rateId << " ║\n";
    cout << "║ " << setw(21) << left << "Дата подключ.:"
         << " │ " << setw(58) << left << trim(connectDate, 50) << " ║\n";
    cout << "║ " << setw(26) << left << "Заблокирован:"
         << " │ " << setw(58) << left << isblock << " ║" << endl;
    cout << "╚════════════════╧════════════════════════════════════════════════════════════╝\n";

}

void Subcriber::DisplaySingleSubcriber(int age, int rateId, string connectDate,
                                       string phone, string surname, string name, string midName) {
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + ".";
        return str;
    };

    cout << "\n╔═════════════════════════════════════════════════════════════════════════════╗\n";
    cout <<   "║                              Данные абонента                                ║\n";
    cout <<   "╠════════════════╤════════════════════════════════════════════════════════════╣\n";
    cout << "║ " << setw(17) << left << "ФИО:"
         << " │ " << setw(58) << left << trim(surname + " " + name + " " + midName, 53) << " ║\n";
    cout << "║ " << setw(21) << left << "Возраст:"
         << " │ " << setw(58) << left << age << " ║\n";
    cout << "║ " << setw(21) << left << "Телефон:"
         << " │ " << setw(58) << left << trim(phone, 50) << " ║\n";
    cout << "║ " << setw(20) << left << "ID тарифа:"
         << " │ " << setw(58) << left << rateId << " ║\n";
    cout << "║ " << setw(21) << left << "Дата подключ.:"
            << " │ " << setw(58) << left << trim(connectDate, 50) << " ║\n";
    cout << "╚════════════════╧════════════════════════════════════════════════════════════╝\n";
}

vector<Subcriber> Subcriber::FindByFullName(const string& surname, const string& name, const string& midName) {
    vector<Subcriber> result;
    for (const auto& subcriber : subcriber.getSubcribers()) { // subcribers - список всех абонентов
        if (subcriber.getSurname() == surname && subcriber.getName() == name && subcriber.getMidName() == midName) {
            result.push_back(subcriber);
        }
    }
    return result;
}

string Subcriber::FindSubscriberByPhone(const string& phone){
    for (const auto& item : subcriber.getSubcribers()) {
        if (item.getPhone() == phone) {
            return item.getPhone();
        }
    }
    return "none";
}

string Subcriber::getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm *local_time = localtime(&now_time);

    stringstream ss;
    ss << put_time(local_time, "%Y-%m-%d"); // ГГГГ-ММ-ДД
    return ss.str();
}

void Subcriber::UpdateBlockStatus() {
    string currentDate = getCurrentDate();
    cout << currentDate;

    vector<Subcriber> localSubcribers = subcriber.getSubcribers();
    for (int i = 0; i < localSubcribers.size(); ++i) {
        if (localSubcribers[i].getConnectDate() == currentDate && localSubcribers[i].isblock != false) {
            localSubcribers[i].isblock = false;
        }
    }
    subcriber.setSubcribers(localSubcribers);
    SubsFileSystem.RewriteSubcriberInfo(); // save to file
}

