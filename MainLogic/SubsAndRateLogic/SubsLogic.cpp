#include "SubsLogic.h"
#include <algorithm>
#include <regex>

SubsLogic subsLogic;

tuple<string, string, string> SubsLogic::InputFullName() {
    while (true) {
        cout << "Введите ФИО одной строкой (Фамилия Имя Отчество): ";
        string fullName;
        cin >> fullName;

        // Разделение
        istringstream iss(fullName);
        string surname, name, midName;

        iss >> surname >> name >> midName;

        // Проверка корректности ввода
        if (surname.empty() || name.empty() || midName.empty()) {
            cerr << "Ошибка: необходимо ввести три слова (Фамилия Имя Отчество). Попробуйте снова.\n";
        } else {
            return make_tuple(surname, name, midName);
        }
    }
}

string SubsLogic::PhoneInput() {
    cout << "Введите номер телефона (формат +375(XX)XXXXXXX): ";
    while (true) {
        string phone = dataTypesValidators.InputString();

        // Проверка формата телефона
        regex phonePattern(R"(\+375\(\d{2}\)\d{7})");

        if (regex_match(phone, phonePattern)) {
            return phone;
            break;
        } else {
            cerr << "Ошибка: номер телефона должен быть в формате +375(XX)XXXXXXX. Попробуйте снова: ";
        }
    }
}

int SubsLogic::MainMenu(User &user) {
    bool work = true;
    while(work)
    {
        switch (dataTypesValidators.CheckToInt())
        {
            case 1: // Мею взаимодействия с абонентами

                work = false;
                break;
            case 2: // Мею взаимодействия с клиентами

                work = false;
                break;
            case 3: // Мею взаимодействия с тарифными планами

                work = false;
                break;
            case 0:
                work = false;
                break;
            default:
                cout << "Ошибка! Неверный выбор." << endl;
                break;
        }
    }
}


//      ---Subs---
void SubsLogic::SubcriberMenu() { // Меню абонента
    bool work = true;
    while (work) {
        displayMenuUtil.DisplayActionSubcriberMenu();
        switch (dataTypesValidators.CheckToInt()) {
            case 1: // Добавить абонента
                AddSubcriber();
                break;
            case 2: // Изменить абонента
                EditSubcriber();
                break;
            case 3: // Удалить абонента
                RemoveSubcriber();
                break;
            case 4: // Найти абонента
                SearchSubcriber();
                break;
            case 5: // Сортировать абонентов
                SortSubcriber();
                break;
            case 6: // Отобразить всех абонентов
                DisplayAllSubcribers();
                break;
            case 7: // Блокировать абонента
                BanSubcriber();
                break;
            case 0: // Назад
                work = false;
                break;
            default:
                cout << "Ошибка! Неверный выбор." << endl;
                break;
        }
    }
}

void SubsLogic::AddSubcriber() {// Метод для добавления абонента
    while (true) {
        cout << "Добавление нового абонента:" << endl;

        int subId = subcriber.generateId();

        string surname, name, midName;
        tie(surname, name, midName) = InputFullName(); //распакоука

        cout << "Введите возраст: ";
        int age = dataTypesValidators.CheckToInt();
        if (age <= 0) {
            cerr << "Ошибка: возраст должен быть положительным числом." << endl;
            continue;
        }

        string phone = PhoneInput();

        cout << "Введите ID тарифа: ";
        DisplayRate();
        int rateId = dataTypesValidators.CheckToInt();

        cout << "Введите дату подключения в формате YYYY-MM-DD (оставьте пустым, если дата текущая): ";
        string connectDate = dataTypesValidators.InputString();
        bool isblock = false;

        if (connectDate.empty()) {
            connectDate = subcriberRegModule.getCurrentDate();
            isblock = false;
        } else {
            regex datePattern(R"(\d{4}-\d{2}-\d{2})");
            if (!regex_match(connectDate, datePattern) || connectDate[4] != '-' || connectDate[7] != '-') {
                cerr << "Ошибка: дата должна быть в формате YYYY-MM-DD." << endl;
                continue;
            }

            // Сравниваем дату с текущей
            string currentDate = subcriberRegModule.getCurrentDate();

            if (connectDate < currentDate) {
                cerr << "Ошибка: дата не может быть из прошлого. Попробуйте снова." << endl;
                continue;
            } else if (connectDate > currentDate) {
                isblock = true; // Если дата из будущего блокируем
            }
        }

        // Подтверждение ввода
        subcriber.DisplaySingleSubcriber(age, rateId, connectDate, phone, surname, name, midName);


        cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";
        if (dataTypesValidators.CheckToBool()) {
            // Добавление абонента
            Subcriber addsSubcriber(subId, isblock, age, rateId, connectDate,
                                    phone, surname, name, midName);
            subcriber.addSubcriber(addsSubcriber);
            cout << "Абонент успешно добавлен." << endl;
            break;
        } else {
            cout << "Давайте попробуем заполнить данные заново.\n" << endl;
        }
    }
}

void SubsLogic::EditSubcriber() { // Метод для редактирования абонента
        cout << "Введите ID абонента для редактирования: ";
        int id = dataTypesValidators.CheckToInt();

        // Поиск абонента по ID
        Subcriber subcriber = utilsModule.FindSubcriberById(id);
        if (subcriber.getSubId() == -1) {
            cerr << "Абонент с указанным ID не найден.\n";
            return;
        }

        // Вывод данных абонента
        subcriber.DisplaySingleSubcriber(subcriber.getSubId(), subcriber.getIsblock(), subcriber.getAge(),
                                         subcriber.getRateId(), subcriber.getConnectDate(), subcriber.getPhone(),
                                         subcriber.getSurname(),  subcriber.getName(),  subcriber.getMidName());

        cout << "\nЧто вы хотите отредактировать?\n";
        cout << "1. ФИО\n";
        cout << "2. Возраст\n";
        cout << "3. Телефон\n";
        cout << "4. ID тарифа\n";
        cout << "0. Отмена\n";
        cout << "Ваш выбор: ";

        int choice = dataTypesValidators.CheckToInt();

        switch (choice) {
            case 1: { // Редактирование ФИО
                cout << "Введите новое ФИО (одной строкой): ";
                auto [surname, name, midName] = InputFullName();
                subcriber.setSurname(surname);
                subcriber.setName(name);
                subcriber.setMidName(midName);
                break;
            }
            case 2: { // Редактирование возраста
                cout << "Введите новый возраст: ";
                int age = dataTypesValidators.CheckToInt();
                if (age <= 0) {
                    cerr << "Возраст должен быть положительным.\n";
                    return;
                }
                subcriber.setAge(age);
                break;
            }
            case 3: { // Редактирование телефона
                cout << "Введите новый номер телефона: ";
                string phone = PhoneInput();
                subcriber.setPhone(phone);
                break;
            }
            case 4: { // Редактирование ID тарифа
                cout << "Введите новый ID тарифа: ";
                int rateId = dataTypesValidators.CheckToInt();
                subcriber.setRateId(rateId);
                break;
            }
            case 0: // Отмена
                cout << "Редактирование отменено.\n";
                return;
            default:
                cerr << "Неверный выбор. Попробуйте снова.\n";
                return;
        }

        // Замена в векторе абонентов
        vector<Subcriber> subcribers = subcriber.getSubcribers();
        for (auto &item : subcribers) {
            if (item.getSubId() == subcriber.getSubId()) {
                item = subcriber;
                break;
            }
        }

        subcriber.setSubcribers(subcribers);

        cout << "Данные абонента успешно обновлены.\n";
}

void SubsLogic::RemoveSubcriber() {
    cout << "Введите ID абонента для удаления: ";
    int subId = dataTypesValidators.CheckToInt();

    Subcriber subcriberToRemove = utilsModule.FindSubcriberById(subId); // Используем метод поиска
    if (subcriberToRemove.getSubId() == -1) { // Если абонент не найден
        cout << "Абонент с ID " << subId << " не найден!" << endl;
        return;
    }

    subcriber.DisplaySingleSubcriber(subcriber.getSubId(), subcriber.getIsblock(), subcriber.getAge(),
                                     subcriber.getRateId(), subcriber.getConnectDate(), subcriber.getPhone(),
                                     subcriber.getSurname(),  subcriber.getName(),  subcriber.getMidName());

    cout << "\nВы уверены, что хотите удалить этого абонента? (Да/Нет): ";
    string confirm = dataTypesValidators.InputString();
    if (confirm == "Нет" && confirm.empty()) {
        cout << "Удаление отменено." << endl;
        return;
    }

    vector<Subcriber> subcribers = subcriber.getSubcribers();
    subcribers.erase(remove_if(subcribers.begin(), subcribers.end(),
                               [subId](const Subcriber& sub) { return sub.getSubId() == subId; }), subcribers.end());

    subcriber.setSubcribers(subcribers);

    cout << "Абонент с ID " << subId << " был успешно удален." << endl;
}

void SubsLogic::SearchSubcriber() {
    cout << "Введите ID абонента для поиска: ";
    int subId = dataTypesValidators.CheckToInt();

    Subcriber subcriberToFind = utilsModule.FindSubcriberById(subId);
    if (subcriberToFind.getSubId() == -1) {
        cout << "Абонент с ID " << subId << " не найден!" << endl;
        return;
    }

    subcriber.DisplaySingleSubcriber(subcriber.getSubId(), subcriber.getIsblock(), subcriber.getAge(),
                                     subcriber.getRateId(), subcriber.getConnectDate(), subcriber.getPhone(),
                                     subcriber.getSurname(),  subcriber.getName(),  subcriber.getMidName());
}

void SubsLogic::SortSubcriber() {
    cout << "Выберите критерий сортировки:\n";
    cout << "1. По имени\n";
    cout << "2. По возрасту\n";
    cout << "3. По ID\n";
    cout << "Введите номер критерия (1/2/3): ";

    int choice = dataTypesValidators.CheckToInt();

    while (choice < 1 || choice > 3) {
        cout << "Неверный ввод! Пожалуйста, выберите 1, 2 или 3.\n";
        cout << "Введите номер критерия (1/2/3): ";
        choice = dataTypesValidators.CheckToInt();
    }

    vector<Subcriber> subcribers = subcriber.getSubcribers();
    switch (choice) {
        case 1:
            sort(subcribers.begin(), subcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getSubId() < b.getSubId(); // Сортировка по ID
            });
            break;
        case 2:
            sort(subcribers.begin(), subcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getAge() < b.getAge(); // Сортировка по возрасту
            });
            break;
        case 3:
            sort(subcribers.begin(), subcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getSurname() < b.getSurname(); // Сортировка по фамилии
            });
            break;
        default:
            cout << "Некорректный выбор.\n";
            return;
    }
    cout << "Сортировка завершена.\n";
}

void SubsLogic::BanSubcriber() {
    cout << "Введите ID абонента для блокировки: ";
    int id = dataTypesValidators.CheckToInt();

    Subcriber subcriberToFind = utilsModule.FindSubcriberById(id);

    if (subcriberToFind.getSubId() == -1) {
        cout << "Абонент с таким ID не найден.\n";
        return;
    }

    cout << "Абонент найден:\n";
    subcriber.DisplaySingleSubcriber(subcriber.getSubId(), subcriber.getIsblock(), subcriber.getAge(),
                                     subcriber.getRateId(), subcriber.getConnectDate(), subcriber.getPhone(),
                                     subcriber.getSurname(),  subcriber.getName(),  subcriber.getMidName());


    cout << "Вы действительно хотите заблокировать этого абонента? (Да/Нет): ";
    string confirmation = dataTypesValidators.InputString();

    if (confirmation == "Да") {
        subcriberToFind.setIsblock(true);

        vector<Subcriber> subcribers = subcriber.getSubcribers();
        for (auto &item : subcribers) {
            if (item.getSubId() == subcriber.getSubId()) {
                item = subcriber;
                break;
            }
        }

        subcriber.setSubcribers(subcribers);

        cout << "Абонент заблокирован.\n";
    }
    else {
        cout << "Операция блокировки отменена.\n";
    }
}

void SubsLogic::DisplayAllSubcribers() { // Метод для отображения абонентов
    if (subcriber.getSubcribers().size() != 0) {
        cout << "\n┌────────────────────────────────────┐\n";
        cout << "│          Данные абонентов          │\n";
        cout << "├────────────────────────────────────┤\n";
        for (auto &item: subcriber.getSubcribers()) {
            cout << "│ " << setw(20) << "ID:" << setw(20) << item.getSubId() << " │\n";
            cout << "│ " << setw(20) << "Фамилия:" << setw(20) << item.getSurname() << " │\n";
            cout << "│ " << setw(20) << "Имя:" << setw(20) << item.getName() << " │\n";
            cout << "│ " << setw(20) << "Отчество:" << setw(20) << item.getMidName() << " │\n";
            cout << "│ " << setw(20) << "Возраст:" << setw(20) << item.getAge() << " │\n";
            cout << "│ " << setw(20) << "Телефон:" << setw(20) << item.getPhone() << " │\n";
            cout << "│ " << setw(20) << "ID тарифа:" << setw(20) << item.getRateId() << " │\n";
            cout << "│ " << setw(20) << "Дата подключения:" << setw(20) << item.getConnectDate() << " │\n";
            cout << "│ " << setw(20) << "Заблокирован:" << setw(20) << boolalpha << item.getIsblock() << " │\n";
        }
        cout << "└────────────────────────────────────┘\n";
    }
    else{
        cout << "Список абонентов пуст" << endl;
    }
}


//      ---Client---
void SubsLogic::ClientMenu() {
    // Меню клиента
}

void SubsLogic::AddClient() {
    // Метод для добавления клиента
}

void SubsLogic::EditClient() {
    // Метод для редактирования клиента
}

void SubsLogic::RemoveClient() {
    // Метод для удаления клиента
}

void SubsLogic::SearchClient() {
    // Метод для поиска клиента
}

void SubsLogic::SortClient() {
    // Метод для сортировки клиентов
}

void SubsLogic::DisplayClient() {
    // Метод для отображения клиентов
}


//      ---Rate---
void SubsLogic::RateMenu() {
    // Меню тарифных планов
}

void SubsLogic::AddRate() {
    // Метод для добавления тарифного плана
}

void SubsLogic::EditRate() {
    // Метод для редактирования тарифного плана
}

void SubsLogic::RemoveRate() {
    // Метод для удаления тарифного плана
}

void SubsLogic::SearchRate() {
    // Метод для поиска тарифного плана
}

void SubsLogic::SortRate() {
    // Метод для сортировки тарифных планов
}

void SubsLogic::DisplayRate() {
    // Метод для отображения тарифных планов
}
