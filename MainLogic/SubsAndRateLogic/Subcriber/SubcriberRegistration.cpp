#include "SubcriberRegistration.h"

SubcriberRegistration subcriberRegModule;


string SubcriberRegistration::getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm *local_time = localtime(&now_time);

    stringstream ss;
    ss << put_time(local_time, "%Y-%m-%d"); // ГГГГ-ММ-ДД
    return ss.str();
}

void SubcriberRegistration::printTable(const int subId, const int age, const int rateId,
                const string& connectDate, const string& phone,
                const string& surname, const string& name,
                const string& midName, const bool isblock) {
    cout << "\n┌────────────────────────┐\n";
    cout << "│      Введенные данные   │\n";
    cout << "├────────────────────────┤\n";
    cout << "│ " << setw(15) << "subId:" << setw(6) << subId << "         │\n";
    cout << "│ " << setw(15) << "Возраст:" << setw(6) << age << "             │\n";
    cout << "│ " << setw(15) << "rateId:" << setw(6) << rateId << "          │\n";
    cout << "│ " << setw(15) << "Дата подключения:" << setw(6) << connectDate << " │\n";
    cout << "│ " << setw(15) << "Телефон:" << setw(6) << phone << "          │\n";
    cout << "│ " << setw(15) << "Фамилия:" << setw(6) << surname << "         │\n";
    cout << "│ " << setw(15) << "Имя:" << setw(6) << name << "            │\n";
    cout << "│ " << setw(15) << "Отчество:" << setw(6) << midName << "        │\n";
    cout << "│ " << setw(15) << "Заблокирован:" << setw(6) << boolalpha << isblock << " │\n";
    cout << "└────────────────────────┘\n";
}

void SubcriberRegistration::SubcriberRegister(User &user) {
    int subId, age, rateId;
    string connectDate, phone, surname, name, midName;
    bool isblock = false;

    cout << "Введите ФИО (фамилия имя отчество): ";
    string fullName = dataTypesValidators.InputString();
    istringstream ss(fullName);
    ss >> surname >> name >> midName;
    cout << endl;

    cout << "Введите возраст: ";
    age = dataTypesValidators.CheckToInt();
    cout << endl;

    cout << "Введите id тарифного плана: ";
    rateId = dataTypesValidators.CheckToInt();
    cout << endl;

    cout << "Введите номер телефона: ";
    phone = dataTypesValidators.InputString(); // TODO: поиск занят ли номер
    cout << endl;

    subId = subcriber.generateId();
    connectDate = getCurrentDate();

    printTable(subId, age, rateId, connectDate, phone, surname, name, midName, isblock);

    if(subId !=-1){
        Subcriber addsSubcriber(subId, isblock, age, rateId, connectDate,
                                phone, surname, name, midName);
        subcriber.addSubcriber(addsSubcriber);
        //TODO: SubsFileSystem.SaveSubcriberInfo(addsMachineAdd);
    }
}


