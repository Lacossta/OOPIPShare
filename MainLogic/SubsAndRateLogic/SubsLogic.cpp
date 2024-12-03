#include "SubsLogic.h"
#include <algorithm>
#include <regex>

SubsLogic subsLogic;

tuple<string, string, string> SubsLogic::InputFullName() {
    while (true) {
        cout << "Введите ФИО одной строкой (Фамилия Имя Отчество): ";
        string fullName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, fullName);

        istringstream iss(fullName);
        string surname, name, midName;
        iss >> surname >> name >> midName;

        if (surname.empty() || name.empty() || midName.empty() || !iss.eof()) {
            cout << "Ошибка: необходимо ввести три слова (Фамилия Имя Отчество). Попробуйте снова.\n";
        } else {
            cout << "ФИО введено корректно" << endl;
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
                SubcriberMenu();
                work = false;
                break;
            case 2: // Мею взаимодействия с клиентами
                ClientMenu();
                work = false;
                break;
            case 3: // Мею взаимодействия с тарифными планами
                RateMenu();
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

        cout << "\nВведите возраст: ";
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
            SubsFileSystem.RewriteSubcriberInfo(); // save to file
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
        SubsFileSystem.RewriteSubcriberInfo(); // save to file
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
    SubsFileSystem.RewriteSubcriberInfo(); // save to file
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

    vector<Subcriber> sortedSubcribers = subcriber.getSubcribers();
    switch (choice) {
        case 1:
            sort(sortedSubcribers.begin(), sortedSubcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getSubId() < b.getSubId(); // Сортировка по ID
            });
            break;
        case 2:
            sort(sortedSubcribers.begin(), sortedSubcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getAge() < b.getAge(); // Сортировка по возрасту
            });
            break;
        case 3:
            sort(sortedSubcribers.begin(), sortedSubcribers.end(), [](const Subcriber& a, const Subcriber& b) {
                return a.getSurname() < b.getSurname(); // Сортировка по фамилии
            });
            break;
        default:
            cout << "Некорректный выбор.\n";
            return;
    }
    DisplayAllSubcribers(sortedSubcribers);

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
        SubsFileSystem.RewriteSubcriberInfo(); // save to file

        cout << "Абонент заблокирован.\n";
    }
    else {
        cout << "Операция блокировки отменена.\n";
    }
}

void SubsLogic::DisplayAllSubcribers(vector<Subcriber> subcribers) { // Метод для отображения абонентов
    if (subcriber.getSubcribers().size() != 0) {
        cout << "\n┌────────────────────────────────────┐\n";
        cout << "│          Данные абонентов          │\n";
        cout << "├────────────────────────────────────┤\n";
        for (auto &item: subcribers) {
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

void SubsLogic::DisplayAllSubcribers() {
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
void SubsLogic::ClientMenu() { // Меню клиента
    bool work = true;
    while (work) {
        displayMenuUtil.DisplayActionClientMenu();
        switch (dataTypesValidators.CheckToInt()) {
            case 1: // Добавить клиента
                AddClient();
                break;
            case 2: // Изменить клиента
                EditClient();
                break;
            case 3: // Удалить клиента
                RemoveClient();
                break;
            case 4: // Найти клиента
                SearchClient();
                break;
            case 5: // Сортировать клиентов
                SortClient();
                break;
            case 6: // Отобразить всех клиентов
                DisplayAllClients();
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

void SubsLogic::AddClient() {
    while (true) {
        cout << "Добавление нового клиента:" << endl;

        int clientId = client.generateClientId();

        string surname, name, midName;
        tie(surname, name, midName) = InputFullName(); // Ввод и разделение ФИО

        cout << "Введите возраст: ";
        int age = dataTypesValidators.CheckToInt();
        if (age <= 0) {
            cerr << "Ошибка: возраст должен быть положительным числом." << endl;
            continue;
        }

        client.DisplaySingleClient(clientId, age, surname, name, midName);

        cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";
        if (dataTypesValidators.CheckToBool()) {
            Client newClient(clientId, age, surname, name, midName);
            client.addClient(newClient);
            SubsFileSystem.RewriteClientInfo(); // to file
            cout << "Клиент успешно добавлен." << endl;
            break;
        }
        else {
            cout << "Давайте попробуем заполнить данные заново.\n" << endl;
        }
    }
}

void SubsLogic::EditClient() {
    cout << "Введите ID клиента для редактирования: ";
    int id = dataTypesValidators.CheckToInt();

    Client client = utilsModule.FindClientById(id);
    if (client.getClientId() == -1) {
        cerr << "Клиент с указанным ID не найден.\n";
        return;
    }

    client.DisplaySingleClient(client.getClientId(), client.getAge(), client.getSurname(), client.getName(), client.getMidName());

    cout << "\nЧто вы хотите отредактировать?\n";
    cout << "1. ФИО\n";
    cout << "2. Возраст\n";
    cout << "0. Отмена\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    switch (choice) {
        case 1: {
            cout << "Введите новое ФИО (одной строкой): ";
            auto [surname, name, midName] = InputFullName();
            client.setSurname(surname);
            client.setName(name);
            client.setMidName(midName);
            break;
        }
        case 2: {
            cout << "Введите новый возраст: ";
            int age = dataTypesValidators.CheckToInt();
            if (age <= 0) {
                cerr << "Возраст должен быть положительным.\n";
                return;
            }
            client.setAge(age);
            break;
        }
        case 0:
            cout << "Редактирование отменено.\n";
            return;
        default:
            cerr << "Неверный выбор! Попробуйте снова.\n";
            return;
    }

    vector<Client> clients = client.getClients();
    for (auto &item : clients) {
        if (item.getClientId() == client.getClientId()) {
            item = client;
            break;
        }
    }

    client.setClients(clients);
    SubsFileSystem.RewriteClientInfo();
    cout << "Данные клиента успешно обновлены.\n";
}

void SubsLogic::RemoveClient() { // Метод для удаления клиента
    cout << "Введите ID клиента для удаления: ";
    int clientId = dataTypesValidators.CheckToInt();

    Client clientToRemove = utilsModule.FindClientById(clientId);
    if (clientToRemove.getClientId() == -1) {
        cout << "Клиент с ID " << clientId << " не найден!" << endl;
        return;
    }

    clientToRemove.DisplaySingleClient(clientToRemove.getClientId(), clientToRemove.getAge(),
                                       clientToRemove.getSurname(), clientToRemove.getName(),
                                       clientToRemove.getMidName());

    cout << "\nВы уверены, что хотите удалить этого клиента? (Да/Нет): ";
    string confirm = dataTypesValidators.InputString();
    if (confirm != "Да" && confirm.empty()) { // Если ответ не "Да", отменяем операцию
        cout << "Удаление отменено." << endl;
        return;
    }

    vector<Client> clients = client.getClients();
    clients.erase(remove_if(clients.begin(), clients.end(),
                            [clientId](const Client& client) { return client.getClientId() == clientId; }), clients.end());

    client.setClients(clients);
    SubsFileSystem.RewriteClientInfo();
    cout << "Клиент с ID " << clientId << " был успешно удален." << endl;
}

void SubsLogic::SearchClient() { // Метод для поиска клиента
    cout << "Введите ID клиента для поиска: ";
    int clientId = dataTypesValidators.CheckToInt();

    Client clientToFind = utilsModule.FindClientById(clientId);
    if (clientToFind.getClientId() == -1) {
        cout << "Клиент с ID " << clientId << " не найден!" << endl;
        return;
    }

    clientToFind.DisplaySingleClient(clientToFind.getClientId(), clientToFind.getAge(),
                                     clientToFind.getSurname(), clientToFind.getName(),
                                     clientToFind.getMidName());
}

void SubsLogic::SortClient() { // Метод для сортировки клиентов
    cout << "Выберите критерий сортировки:\n";
    cout << "1. По ID\n";
    cout << "2. По фамилии\n";
    cout << "3. По возрасту\n";
    cout << "Введите номер критерия (1/2/3): ";

    int choice = dataTypesValidators.CheckToInt();

    while (choice < 1 || choice > 3) {
        cout << "Неверный ввод! Пожалуйста, выберите 1, 2 или 3.\n";
        cout << "Введите номер критерия (1/2/3): ";
        choice = dataTypesValidators.CheckToInt();
    }

    vector<Client> sortedClients = client.getClients();
    switch (choice) {
        case 1: // Сортировка по ID
            sort(sortedClients.begin(), sortedClients.end(), [](const Client& a, const Client& b) {
                return a.getClientId() < b.getClientId();
            });
            break;
        case 2: // Сортировка по фамилии
            sort(sortedClients.begin(), sortedClients.end(), [](const Client& a, const Client& b) {
                return a.getSurname() < b.getSurname();
            });
            break;
        case 3: // Сортировка по возрасту
            sort(sortedClients.begin(), sortedClients.end(), [](const Client& a, const Client& b) {
                return a.getAge() < b.getAge();
            });
            break;
        default:
            cout << "Некорректный выбор.\n";
            return;
    }

    DisplayAllClients(sortedClients);
}

void SubsLogic::DisplayAllClients(vector<Client> clients) {
    if (!clients.empty()) {
        cout << "\n┌────────────────────────────────────┐\n";
        cout << "│           Данные клиентов          │\n";
        cout << "├────────────────────────────────────┤\n";
        for (const auto& client : clients) {
            cout << "│ " << setw(20) << "ID:" << setw(20) << client.getClientId() << " │\n";
            cout << "│ " << setw(20) << "Фамилия:" << setw(20) << client.getSurname() << " │\n";
            cout << "│ " << setw(20) << "Имя:" << setw(20) << client.getName() << " │\n";
            cout << "│ " << setw(20) << "Отчество:" << setw(20) << client.getMidName() << " │\n";
            cout << "│ " << setw(20) << "Возраст:" << setw(20) << client.getAge() << " │\n";
        }
        cout << "└────────────────────────────────────┘\n";
    } else {
        cout << "Список клиентов пуст" << endl;
    }
}

void SubsLogic::DisplayAllClients() {
    vector<Client> clients = client.getClients();
    if (!clients.empty()) {
        cout << "\n┌────────────────────────────────────┐\n";
        cout << "│           Данные клиентов          │\n";
        cout << "├────────────────────────────────────┤\n";
        for (const auto& client : clients) {
            cout << "│ " << setw(20) << "ID:" << setw(20) << client.getClientId() << " │\n";
            cout << "│ " << setw(20) << "Фамилия:" << setw(20) << client.getSurname() << " │\n";
            cout << "│ " << setw(20) << "Имя:" << setw(20) << client.getName() << " │\n";
            cout << "│ " << setw(20) << "Отчество:" << setw(20) << client.getMidName() << " │\n";
            cout << "│ " << setw(20) << "Возраст:" << setw(20) << client.getAge() << " │\n";
        }
        cout << "└────────────────────────────────────┘\n";
    } else {
        cout << "Список клиентов пуст" << endl;
    }
}



//      ---Rate---
void SubsLogic::RateMenu() { // Меню тарифных планов
    cout << "123";
}

void SubsLogic::AddRate() { // Метод для добавления тарифного плана
    cout << "123";
}

void SubsLogic::EditRate() { // Метод для редактирования тарифного плана
    cout << "123";
}

void SubsLogic::RemoveRate() { // Метод для удаления тарифного плана
    cout << "123";
}

void SubsLogic::SearchRate() { // Метод для поиска тарифного плана
    cout << "123";
}

void SubsLogic::SortRate() {    // Метод для сортировки тарифных планов
    cout << "123";
}

void SubsLogic::DisplayRate() {    // Метод для отображения тарифных планов
    cout << "123";
}
