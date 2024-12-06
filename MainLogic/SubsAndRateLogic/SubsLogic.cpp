#include "SubsLogic.h"
#include <algorithm>
#include <regex>

SubsLogic subsLogic;

tuple<string, string, string> SubsLogic::InputFullName() {
    //TODO: пофиксить лишний энтер
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Введите ФИО одной строкой (Фамилия Имя Отчество): ";
        string fullName;
//        if (cin.peek() == '\n') {
//            cin.ignore(); // Удалить остатки символов новой строки.
//        }

        getline(cin, fullName); // Читаем всю строку
        istringstream iss(fullName);
        if(fullName.empty()){
            return make_tuple("","","");
        }
        vector<string> words;
        string word;

        // Разделяем строку на слова
        while (iss >> word) {
            words.push_back(word);
        }

        // Проверяем, введено ли три слова
        if (words.size() < 3) {
            cout << "Ошибка: необходимо ввести три слова (Фамилия Имя Отчество). Попробуйте снова.\n";
        } else {
            // Возвращаем первые три слова
            return make_tuple(words[0], words[1], words[2]);
        }
    }
}

string SubsLogic::PhoneInput() {
    cout << "Введите номер телефона (формат +375(XX)XXXXXXX): ";
    while (true) {
        string phone = dataTypesValidators.InputString();

        if(phone.empty()){
            return "";
        }

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
    return 0;
}


//      ===Subs===
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
            case 8: // из клиента
                CreateSubscriberFromClient();
                break;
            case 0: // Назад
                return;
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

        if (surname == ""){
            cout << "\nОтменено!"<< endl;
            return;
        }

        cout << "Введите возраст: ";
        int age = dataTypesValidators.CheckToInt();
        if (age == -1){
            cout << "\nОтменено!"<< endl;
            return;
        }
        if (age <= 0) {
            cout << "Ошибка: возраст должен быть положительным числом." << endl;
            continue;
        }

        string phone;
        while(true) {
            phone = PhoneInput();
            if (subcriber.FindSubscriberByPhone(phone) == phone){
                cout << "Ошибка, попробуйте ввести еще раз" << endl;
                continue;
            }
            else if (phone.empty()) {
                cout << "\nОтменено!" << endl;
                return;
            }
            else{
                break;
            }
        }

        int rateId = -1;
        DisplayRates();
        while(true) {
            cout << "Введите ID тарифа: ";
            rateId = dataTypesValidators.CheckToInt();

            if(rateId != utilsModule.FindRateById(rateId).getRateId()){
                cout << "Тарифный план с ID:" << rateId << " не найден, повторите ввод" << endl;
                continue;
            }
            else if (rateId == -1) {
                cout << "\nОтменено!" << endl;
                return;
            }
            else{
                break;
            }
        }

        string connectDate;
        bool isblock = false;

        while (true) {
            cout << "Введите дату подключения в формате YYYY-MM-DD (оставьте пустым, если дата текущая): ";
            connectDate = dataTypesValidators.InputString();

            if (connectDate.empty()) {
                connectDate = subcriber.getCurrentDate();
                isblock = false;
                break;
            }
            else{
                regex datePattern(R"(\d{4}-\d{2}-\d{2})");
                if (!regex_match(connectDate, datePattern)) {
                    cout << "Ошибка: дата должна быть в формате YYYY-MM-DD." << endl;
                    continue; // Повторяем ввод
                }

                // Сравниваем дату с текущей
                string currentDate = subcriber.getCurrentDate();

                if (connectDate < currentDate) {
                    cout << "Ошибка: дата не может быть из прошлого. Попробуйте снова." << endl;
                    continue; // Повторяем ввод
                }
                if (connectDate > currentDate) {
                    isblock = true; // Если дата из будущего, блокируем
                    break;
                }
            }
        }

        // Подтверждение ввода
        if(rateId != -1) {
            subcriber.DisplaySingleSubcriber(age, rateId, connectDate, phone, surname, name, midName);
        }

        cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";

        string answer = dataTypesValidators.InputString();
        if (answer.empty()){ //TODO:: починить
            cout << "\nОтменено!"<< endl;
            return;
        }
        if (answer=="1") {
            Subcriber addsSubcriber(subId, isblock, age, rateId, connectDate,
                                    phone, surname, name, midName);
            subcriber.addSubcriber(addsSubcriber);
            SubsFileSystem.RewriteSubcriberInfo();
            cout << "Абонент успешно добавлен." << endl;
            break;
        }
        else if (answer == "0"){
            cout << "Давайте попробуем заполнить данные заново.\n" << endl;
        }
    }
}

void SubsLogic::EditSubcriber() { // Метод для редактирования абонента
        DisplayAllSubcribers();
        cout << "Введите ID абонента для редактирования: ";
        int id = dataTypesValidators.CheckToInt();

        Subcriber localSubcriber = utilsModule.FindSubcriberById(id);
        if (localSubcriber.getSubId() == -1) {
            cerr << "Абонент с указанным ID не найден.\n";
            return;
        }

        localSubcriber.DisplaySingleSubcriber(localSubcriber.getSubId(), localSubcriber.getIsblock(), localSubcriber.getAge(),
                                              localSubcriber.getRateId(), localSubcriber.getConnectDate(), localSubcriber.getPhone(),
                                              localSubcriber.getSurname(), localSubcriber.getName(), localSubcriber.getMidName());

        cout << "\nЧто вы хотите отредактировать?\n";
        cout << "1. ФИО\n";
        cout << "2. Возраст\n";
        cout << "3. Телефон\n";
        cout << "4. ID тарифа\n";
        cout << "0. Отмена\n";
        cout << "Ваш выбор: ";

        int choice = dataTypesValidators.CheckToInt();

        if (choice == -1){
            cout << "\nОтменено!"<< endl;
            return;
        }

        switch (choice) {
            case 1: { // Редактирование ФИО
                cout << "Введите новое ФИО (одной строкой): ";
                auto [surname, name, midName] = InputFullName();
                localSubcriber.setSurname(surname);
                localSubcriber.setName(name);
                localSubcriber.setMidName(midName);
                break;
            }
            case 2: { // Редактирование возраста
                cout << "Введите новый возраст: ";
                int age = dataTypesValidators.CheckToInt();
                if (age <= 0) {
                    cerr << "Возраст должен быть положительным.\n";
                    return;
                }
                localSubcriber.setAge(age);
                break;
            }
            case 3: { // Редактирование телефона
                cout << "Введите новый номер телефона: ";
                string phone;
                while(true) {
                    phone = PhoneInput();
                    if (subcriber.FindSubscriberByPhone(phone) == phone){
                        cout << "Ошибка, попробуйте ввести еще раз" << endl;
                        continue;
                    }
                    else if (phone.empty()) {
                        cout << "\nОтменено!" << endl;
                        return;
                    }
                    else{
                        break;
                    }
                }
                localSubcriber.setPhone(phone);
                break;
            }
            case 4: { // Редактирование ID тарифа
                cout << "Введите новый ID тарифа: ";
                int rateId = dataTypesValidators.CheckToInt();
                localSubcriber.setRateId(rateId);
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
        for (int i = 0; i < subcribers.size(); ++i) {
            if (subcribers[i].getSubId() == id) {
                subcribers[i] = localSubcriber;
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

    subcriber.DisplaySingleSubcriber(subcriberToRemove.getSubId(), subcriberToRemove.getIsblock(), subcriberToRemove.getAge(),
                                     subcriberToRemove.getRateId(), subcriberToRemove.getConnectDate(), subcriberToRemove.getPhone(),
                                     subcriberToRemove.getSurname(), subcriberToRemove.getName(), subcriberToRemove.getMidName());

    cout << "\nВы уверены, что хотите удалить этого абонента? (Да/Нет): ";
    string confirm = dataTypesValidators.InputString();
    if (confirm == "Нет" && confirm.empty()) {
        cout << "Удаление отменено." << endl;
        return;
    } else if (confirm == "Да") {

        vector<Subcriber> subcribers = subcriber.getSubcribers();
        subcribers.erase(remove_if(subcribers.begin(), subcribers.end(),
                                   [subId](const Subcriber &sub) { return sub.getSubId() == subId; }),
                         subcribers.end());

        subcriber.setSubcribers(subcribers);
        SubsFileSystem.RewriteSubcriberInfo(); // save to file
        cout << "Абонент с ID " << subId << " был успешно удален." << endl;
    }
}

void SubsLogic::SearchSubcriber() {
    cout << "Выберите способ поиска абонента:\n";
    cout << "1 - По ID\n";
    cout << "2 - По ФИО\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    if(choice == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

    if (choice == 1) {
        cout << "Введите ID абонента для поиска: ";
        int subId = dataTypesValidators.CheckToInt();

        Subcriber subcriberToFind = utilsModule.FindSubcriberById(subId);
        if (subcriberToFind.getSubId() == -1) {
            cout << "Абонент с ID " << subId << " не найден!" << endl;
        }
        else {
            subcriber.DisplaySingleSubcriber(
                    subcriberToFind.getSubId(), subcriberToFind.getIsblock(), subcriberToFind.getAge(),
                    subcriberToFind.getRateId(), subcriberToFind.getConnectDate(), subcriberToFind.getPhone(),
                    subcriberToFind.getSurname(), subcriberToFind.getName(), subcriberToFind.getMidName()
            );
        }
    }

    else if (choice == 2) {
        // Поиск по ФИО
        auto [surname, name, midName] = InputFullName();

        vector<Subcriber> foundSubcribers = subcriber.FindByFullName(surname, name, midName);
        if (foundSubcribers.empty()) {
            cout << "Абонент с ФИО \"" << surname << " " << name << " " << midName << "\" не найден!" << endl;
        }
        else {
            cout << "\nНайдено " << foundSubcribers.size() << " абонент(ов):\n";
            for (const auto& item : foundSubcribers) {
                subcriber.DisplaySingleSubcriber(
                        item.getSubId(), item.getIsblock(), item.getAge(),
                        item.getRateId(), item.getConnectDate(), item.getPhone(),
                        item.getSurname(), item.getName(), item.getMidName()
                );
            }
        }
    } else {
        cout << "Ошибка: некорректный выбор. Попробуйте снова.\n";
    }
}

void SubsLogic::SortSubcriber() {
    cout << "Выберите критерий сортировки:\n";
    cout << "1. По ID\n";
    cout << "2. По возрасту\n";
    cout << "3. По имени \n";
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

    if (id == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

    Subcriber subcriberToFind = utilsModule.FindSubcriberById(id);

    if (subcriberToFind.getSubId() == -1) {
        cout << "Абонент с таким ID не найден.\n";
        return;
    }

    cout << "Абонент найден:\n";
    subcriber.DisplaySingleSubcriber(subcriberToFind.getSubId(), subcriberToFind.getIsblock(), subcriberToFind.getAge(),
                                     subcriberToFind.getRateId(), subcriberToFind.getConnectDate(), subcriberToFind.getPhone(),
                                     subcriberToFind.getSurname(),  subcriberToFind.getName(),  subcriberToFind.getMidName());


    cout << "Вы действительно хотите заблокировать этого абонента? (Да/Нет): ";
    string confirmation = dataTypesValidators.InputString();

    if (confirmation == "Да") {
        subcriberToFind.setIsblock(true);

        vector<Subcriber> subcribers = subcriber.getSubcribers();
        for (int i = 0; i < subcribers.size(); ++i) {
            if (subcribers[i].getSubId() == id) {
                subcribers[i] = subcriberToFind;
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

void SubsLogic::CreateSubscriberFromClient() {
    cout << "Список доступных клиентов:" << endl;
    DisplayAllClients();

    cout << "Введите ID клиента, которого хотите преобразовать в абонента: ";
    int clientId = dataTypesValidators.CheckToInt();

    if (clientId == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    Client existingClient = utilsModule.FindClientById(clientId);
    if (existingClient.getClientId() == -1) {
        cout << "Ошибка: клиент с указанным ID не найден!" << endl;
        return;
    }

    string surname = existingClient.getSurname();
    string name = existingClient.getName();
    string midName = existingClient.getMidName();
    int age = existingClient.getAge();

    cout << "Перенесенные данные: " << endl;
    cout << "Фамилия: " << surname << ", Имя: " << name << ", Отчество: " << midName << ", Возраст: " << age << endl << endl;


    cout << "Введите номер телефона: ";
    string phone = PhoneInput();
    if (phone.empty()) {
        cout << "\nОтменено!" << endl;
        return;
    }

    int rateId = -1;
    DisplayRates();
    while (true) {
        cout << "Введите ID тарифа: ";
        rateId = dataTypesValidators.CheckToInt();

        if (rateId != utilsModule.FindRateById(rateId).getRateId()) {
            cout << "Тарифный план с ID:" << rateId << " не найден, повторите ввод." << endl;
            continue;
        } else {
            break;
        }

        if (rateId == -1) {
            cout << "\nОтменено!" << endl;
            return;
        }
    }

    // Ввод даты подключения
    string connectDate;
    bool isblock = false;

    while (true) {
        cout << "Введите дату подключения в формате YYYY-MM-DD (оставьте пустым, если дата текущая): ";
        connectDate = dataTypesValidators.InputString();

        if (connectDate.empty()) {
            connectDate = subcriber.getCurrentDate();
            isblock = false;
            break;
        } else {
            regex datePattern(R"(\d{4}-\d{2}-\d{2})");
            if (!regex_match(connectDate, datePattern)) {
                cout << "Ошибка: дата должна быть в формате YYYY-MM-DD." << endl;
                continue; // Повторяем ввод
            }

            // Сравниваем дату с текущей
            string currentDate = subcriber.getCurrentDate();

            if (connectDate < currentDate) {
                cout << "Ошибка: дата не может быть из прошлого. Попробуйте снова." << endl;
                continue; // Повторяем ввод
            } else if (connectDate > currentDate) {
                isblock = true; // Если дата из будущего, блокируем
                break;
            }
        }
    }

    vector<Client> clients = client.getClients();
    clients.erase(remove_if(clients.begin(), clients.end(),
                            [clientId](const Client& client) { return client.getClientId() == clientId; }), clients.end());

    client.setClients(clients);
    SubsFileSystem.RewriteClientInfo();



    cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        cin.clear();
    string answer = dataTypesValidators.InputString();
    if (answer.empty()){ //TODO:: починить
        cout << "\nОтменено!"<< endl;
        return;
    }
    if (answer=="1") {
        int subId = subcriber.generateId();
        Subcriber newSubscriber(subId, isblock, age, rateId, connectDate, phone, surname, name, midName);
        subcriber.addSubcriber(newSubscriber);
        SubsFileSystem.RewriteSubcriberInfo();
    }
    else if (answer == "0"){
        cout << "\nОтменено!" << endl;
        return;
    }

    cout << "Клиент успешно преобразован в абонента." << endl;
}

void SubsLogic::DisplayAllSubcribers(vector<Subcriber> subcribers) { // Метод для отображения абонентов
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + "."; // Обрезать и добавить "."
        return str;
    };

    if (!subcribers.empty()) {
        cout <<  "\n╔════════╤══════════════╤══════════════╤══════════════╤═════════╤══════════════════════╤═══════╤═══════════════════╤═══════════╗\n";
        cout <<    "║   ID   │    Фамилия   │     Имя      │  Отчество    │ Возраст │       Телефон        │ Тариф │  Дата подключения │  Заблок.  ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪══════════════╪═════════╪══════════════════════╪═══════╪═══════════════════╪═══════════╣\n";

        for (const auto &item : subcribers) {
            cout <<"║ " << setw(6) << left << item.getSubId() << " │ "
                 << setw(12) << left << trim(item.getSurname(), 14) << " │ "
                 << setw(12) << left << trim(item.getName(), 14) << " │ "
                 << setw(12) << left << trim(item.getMidName(), 14) << " │ "
                 << setw(7) << left << item.getAge() << " │ "
                 << setw(20) << left << trim(item.getPhone(), 20) << " │ "
                 << setw(5) << left << item.getRateId() << " │ "
                 << setw(17) << left << trim(item.getConnectDate(), 17) << " │ "
                 << setw(9) << left << item.getIsblock() << " ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧══════════════╧═════════╧══════════════════════╧═══════╧═══════════════════╧═══════════╝\n";
    }
    else{
        cout << "Список абонентов пуст" << endl;
    }
}

void SubsLogic::DisplayAllSubcribers() {
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + "."; // Обрезать и добавить "."
        return str;
    };

    if (!subcriber.getSubcribers().empty()) {
        cout <<  "\n╔════════╤══════════════╤══════════════╤══════════════╤═════════╤══════════════════════╤═══════╤═══════════════════╤═══════════╗\n";
        cout <<    "║   ID   │    Фамилия   │     Имя      │  Отчество    │ Возраст │       Телефон        │ Тариф │  Дата подключения │  Заблок.  ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪══════════════╪═════════╪══════════════════════╪═══════╪═══════════════════╪═══════════╣\n";

        for (const auto &item : subcriber.getSubcribers()) {
            cout <<"║ " << setw(6) << left << item.getSubId() << " │ "
                 << setw(12) << left << trim(item.getSurname(), 12) << " │ "
                 << setw(12) << left << trim(item.getName(), 12) << " │ "
                 << setw(12) << left << trim(item.getMidName(), 12) << " │ "
                 << setw(7) << left << item.getAge() << " │ "
                 << setw(20) << left << trim(item.getPhone(), 20) << " │ "
                 << setw(5) << left << item.getRateId() << " │ "
                 << setw(17) << left << trim(item.getConnectDate(), 17) << " │ "
                 << setw(9) << left << item.getIsblock() << " ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧══════════════╧═════════╧══════════════════════╧═══════╧═══════════════════╧═══════════╝\n";
    }
    else{
        cout << "Список абонентов пуст" << endl;
    }
}


//      ===Client===
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
        tie(surname, name, midName) = InputFullName();

        if (surname.empty()){
            cout << "\nОтменено!"<< endl;
            return;
        }

        cout << "Введите возраст: ";
        int age = dataTypesValidators.CheckToInt();

        if (age == -1){
            cout << "\nОтменено!"<< endl;
            return;
        }

        if (age <= 0) {
            cerr << "Ошибка: возраст должен быть положительным числом." << endl;
            continue;
        }

        client.DisplaySingleClient(clientId, age, surname, name, midName);

        cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";
        string answer = dataTypesValidators.InputString();
        if (answer == "1") {
            Client newClient(clientId, age, surname, name, midName);
            client.addClient(newClient);
            SubsFileSystem.RewriteClientInfo();
            cout << "Клиент успешно добавлен." << endl;
            break;
        }
        else if (answer.empty()){
            cout << "\nОтменено!"<< endl;
            return;
        }
        else {
            cout << "Давайте попробуем заполнить данные заново.\n" << endl;
        }
    }
}

void SubsLogic::EditClient() {
    DisplayAllClients();
    cout << "Введите ID клиента для редактирования: ";
    int id = dataTypesValidators.CheckToInt();

    if (id == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

    Client LocalClient = utilsModule.FindClientById(id);
    if (LocalClient.getClientId() == -1) {
        cerr << "Клиент с указанным ID не найден.\n";
        return;
    }

    client.DisplaySingleClient(LocalClient.getClientId(), LocalClient.getAge(), LocalClient.getSurname(), LocalClient.getName(), LocalClient.getMidName());

    cout << "\nЧто вы хотите отредактировать?\n";
    cout << "1. ФИО\n";
    cout << "2. Возраст\n";
    cout << "0. Отмена\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    if (choice == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

    switch (choice) {
        case 1: {
            cout << "Введите новое ФИО (одной строкой): ";
            auto [surname, name, midName] = InputFullName();
            LocalClient.setSurname(surname);
            LocalClient.setName(name);
            LocalClient.setMidName(midName);
            break;
        }
        case 2: {
            cout << "Введите новый возраст: ";
            int age = dataTypesValidators.CheckToInt();
            if (age <= 0) {
                cerr << "Возраст должен быть положительным.\n";
                return;
            }
            LocalClient.setAge(age);
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
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].getClientId() == id) {
            clients[i] = LocalClient;
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

    if(clientId == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

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

void SubsLogic::SearchClient() {
    cout << "Выберите способ поиска клиента:\n";
    cout << "1 - По ID\n";
    cout << "2 - По ФИО\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    if(choice == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

    if (choice == 1) {
        // Поиск по ID
        cout << "Введите ID клиента для поиска: ";
        int clientId = dataTypesValidators.CheckToInt();

        Client clientToFind = utilsModule.FindClientById(clientId);
        if (clientToFind.getClientId() == -1) {
            cout << "Клиент с ID " << clientId << " не найден!" << endl;
        }
        else {
            clientToFind.DisplaySingleClient(
                    clientToFind.getClientId(), clientToFind.getAge(),
                    clientToFind.getSurname(), clientToFind.getName(),
                    clientToFind.getMidName());
        }
    }

    else if (choice == 2) {
        // Поиск по ФИО
        auto [surname, name, midName] = InputFullName();

        vector<Client> foundClients = client.FindClientsByFullName(surname, name, midName);
        if (foundClients.empty()) {
            cout << "Клиент с ФИО \"" << surname << " " << name << " " << midName << "\" не найден!" << endl;
        } else {
            cout << "\nНайдено " << foundClients.size() << " клиент(ов):\n";
            for (const auto& item : foundClients) {
                client.DisplaySingleClient(
                        item.getClientId(), item.getAge(),
                        item.getSurname(), item.getName(),
                        item.getMidName()
                );
            }
        }
    } else {
        cout << "Ошибка: некорректный выбор. Попробуйте снова.\n";
    }
}

void SubsLogic::SortClient() { // Метод для сортировки клиентов
    cout << "Выберите критерий сортировки:\n";
    cout << "1. По ID\n";
    cout << "2. По фамилии\n";
    cout << "3. По возрасту\n";
    cout << "Введите номер критерия (1/2/3): ";

    int choice = dataTypesValidators.CheckToInt();

    if(choice == -1){
        cout << "\nОтменено!"<< endl;
        return;
    }

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
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + "."; // Обрезать и добавить "."
        return str;
    };

    if (!clients.empty()) {
        cout <<  "\n╔════════╤══════════════╤══════════════╤══════════════╤═════════╗\n";
        cout <<    "║   ID   │    Фамилия   │     Имя      │  Отчество    │ Возраст ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪══════════════╪═════════╣\n";

        for (const auto &item : clients) {
            cout <<"║ " << setw(6) << left << item.getClientId() << " │ "
                 << setw(12) << left << trim(item.getSurname(), 12) << " │ "
                 << setw(12) << left << trim(item.getName(), 12) << " │ "
                 << setw(12) << left << trim(item.getMidName(), 12) << " │ "
                 << setw(7) << left << item.getAge() << " ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧══════════════╧═════════╝\n";
    }
    else{
        cout << "Список клиентов пуст" << endl;
    }
}

void SubsLogic::DisplayAllClients() {
    auto trim = [](const string &str, size_t maxLength) {
        if (str.length() > maxLength)
            return str.substr(0, maxLength - 1) + "."; // Обрезать и добавить "."
        return str;
    };

    if (!subcriber.getSubcribers().empty()) {
        cout <<  "\n╔═══════════════════════════════════════════════════════════════╗\n";
        cout <<    "║                            Клиенты                            ║\n";
        cout <<    "╠════════╤══════════════╤══════════════╤════════════════════════╣\n";
        cout <<    "║   ID   │    Фамилия   │     Имя      │  Отчество    │ Возраст ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪══════════════╪═════════╣\n";

        for (const auto &item : client.getClients()) {
            cout <<"║ " << setw(6) << left << item.getClientId() << " │ "
                 << setw(12) << left << trim(item.getSurname(), 12) << " │ "
                 << setw(12) << left << trim(item.getName(), 12) << " │ "
                 << setw(12) << left << trim(item.getMidName(), 12) << " │ "
                 << setw(7) << left << item.getAge() << " ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧══════════════╧═════════╝\n";
    }
    else{
        cout << "Список клиентов пуст" << endl;
    }
}


//      ===Rate===
void SubsLogic::RateMenu() { // Меню тарифов
    bool work = true;
    while (work) {
        displayMenuUtil.DisplayActionRateMenu();
        switch (dataTypesValidators.CheckToInt()) {
            case 1: // Добавить тариф
                AddRate();
                break;
            case 2: // Изменить тариф
                EditRate();
                break;
            case 3: // Удалить тариф
                RemoveRate();
                break;
            case 4: // Найти тариф
                SearchRate();
                break;
            case 5: // Сортировать тарифы
                SortRate();
                break;
            case 6: // Отобразить все тарифы
                DisplayRates();
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

void SubsLogic::AddRate() {
    while (true) {
        cout << "Добавление нового тарифа:" << endl;

        int rateId = rate.generateId();

        cout << "Введите стоимость тарифа: ";
        float cost = dataTypesValidators.CheckToFloat();

        if (cost <= 0) {
            cerr << "Ошибка: стоимость должна быть положительным числом." << endl;
            continue;
        }
        else if(cost == -1.0f){
            cout << "\nОтменено!" << endl;
            return;
        }

        cout << "Введите количество сетевого трафика (в МБ): ";
        int amountOfNetwork = dataTypesValidators.CheckToInt();

        if (amountOfNetwork <= 0) {
            cerr << "Ошибка: количество трафика должно быть положительным числом." << endl;
            continue;
        }
        else if(amountOfNetwork == -1){
            cout << "\nОтменено!" << endl;
            return;
        }


        cout << "Введите время звонков (в минутах): ";
        int callTime = dataTypesValidators.CheckToInt();

        if (callTime <= 0) {
            cerr << "Ошибка: время звонков должно быть положительным числом." << endl;
            continue;
        }
        else if(callTime == -1){
            cout << "\nОтменено!" << endl;
            return;
        }

        rate.DisplaySingleRate(rateId, cost, amountOfNetwork, callTime);
        cout << "\nВсе ли данные введены правильно? (0 - Нет, 1 - Да): ";
        string answer = dataTypesValidators.InputString();
        if (answer == "1") {
            Rate newRate(rateId, cost, amountOfNetwork, callTime);
            rate.addRate(newRate);
            SubsFileSystem.RewriteRateInfo();
            cout << "Тариф успешно добавлен." << endl;
            break;
        }
        else if (answer.empty()) {
            cout << "\nОтменено!" << endl;
            return;
        }
        else {
            cout << "Давайте попробуем заполнить данные заново.\n" << endl;
        }
    }
}

void SubsLogic::EditRate() {
    DisplayRates();
    cout << "Введите ID тарифа для редактирования: ";
    int id = dataTypesValidators.CheckToInt();

    if (id == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    Rate Localrate = utilsModule.FindRateById(id);
    if (Localrate.getRateId() == -1) {
        cerr << "Тариф с указанным ID не найден.\n";
        return;
    }

    rate.DisplaySingleRate(Localrate.getRateId(), Localrate.getCost(), Localrate.getAmountOfNetwork(), Localrate.getCallTime());

    cout << "\nЧто вы хотите отредактировать?\n";
    cout << "1. Стоимость\n";
    cout << "2. Количество сетевого трафика\n";
    cout << "3. Время звонков\n";
    cout << "0. Отмена\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    if (choice == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    switch (choice) {
        case 1: {
            cout << "Введите новую стоимость: ";
            float cost = dataTypesValidators.CheckToFloat();
            if (cost <= 0) {
                cerr << "Ошибка: стоимость должна быть положительным числом.\n";
                return;
            }
            Localrate.setCost(cost);
            break;
        }
        case 2: {
            cout << "Введите новое количество трафика: ";
            int amountOfNetwork = dataTypesValidators.CheckToInt();
            if (amountOfNetwork <= 0) {
                cerr << "Ошибка: количество трафика должно быть положительным.\n";
                return;
            }
            Localrate.setAmountOfNetwork(amountOfNetwork);
            break;
        }
        case 3: {
            cout << "Введите новое время звонков: ";
            int callTime = dataTypesValidators.CheckToInt();
            if (callTime <= 0) {
                cerr << "Ошибка: время звонков должно быть положительным.\n";
                return;
            }
            Localrate.setCallTime(callTime);
            break;
        }
        case 0:
            cout << "Редактирование отменено.\n";
            return;
        default:
            cerr << "Неверный выбор! Попробуйте снова.\n";
            return;
    }

    vector<Rate> rates = rate.getRates();
    for (int i = 0; i < rates.size(); ++i) {
        if (rates[i].getRateId() == id) {
            rates[i]= Localrate;
            break;
        }
    }

    rate.setRates(rates);
    SubsFileSystem.RewriteRateInfo();
    cout << "Данные тарифа успешно обновлены.\n";
}

void SubsLogic::RemoveRate() {
    cout << "Введите ID тарифа для удаления: ";
    int rateId = dataTypesValidators.CheckToInt();

    if (rateId == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    Rate rateToRemove = utilsModule.FindRateById(rateId);
    if (rateToRemove.getRateId() == -1) {
        cout << "Тариф с ID " << rateId << " не найден!" << endl;
        return;
    }

    rateToRemove.DisplaySingleRate(rateToRemove.getRateId(), rateToRemove.getCost(),
                                   rateToRemove.getAmountOfNetwork(), rateToRemove.getCallTime());

    cout << "\nВы уверены, что хотите удалить этот тариф? (Да/Нет): ";
    string confirm = dataTypesValidators.InputString();
    if (confirm != "Да" && confirm.empty()) {
        cout << "Удаление отменено." << endl;
        return;
    }

    vector<Rate> rates = rate.getRates();
    rates.erase(remove_if(rates.begin(), rates.end(),
                          [rateId](const Rate &rate) { return rate.getRateId() == rateId; }),
                rates.end());

    rate.setRates(rates);
    SubsFileSystem.RewriteRateInfo();
    cout << "Тариф с ID " << rateId << " был успешно удален." << endl;
}

void SubsLogic::SearchRate() {
    cout << "Выберите способ поиска тарифа:\n";
    cout << "1 - По ID\n";
    cout << "2 - По стоимости\n";
    cout << "Ваш выбор: ";

    int choice = dataTypesValidators.CheckToInt();

    if (choice == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    if (choice == 1) {
        cout << "Введите ID тарифа для поиска: ";
        int rateId = dataTypesValidators.CheckToInt();

        Rate rateToFind = utilsModule.FindRateById(rateId);
        if (rateToFind.getRateId() == -1) {
            cout << "Тариф с ID " << rateId << " не найден!" << endl;
        } else {
            rateToFind.DisplaySingleRate(rateToFind.getRateId(), rateToFind.getCost(),
                                         rateToFind.getAmountOfNetwork(), rateToFind.getCallTime());
        }
    } else if (choice == 2) {
        cout << "Введите стоимость тарифа: ";
        float cost = dataTypesValidators.CheckToFloat();

        vector<Rate> foundRates = rate.FindRatesByCost(cost);
        if (foundRates.empty()) {
            cout << "Тариф с указанной стоимостью не найден!" << endl;
        } else {
            cout << "\nНайдено " << foundRates.size() << " тариф(ов):\n";
            for (const auto &item : foundRates) {
                item.DisplaySingleRate(item.getRateId(), item.getCost(), item.getAmountOfNetwork(), item.getCallTime());
            }
        }
    } else {
        cout << "Ошибка: некорректный выбор. Попробуйте снова.\n";
    }
}

void SubsLogic::SortRate() {
    cout << "Выберите критерий сортировки:\n";
    cout << "1. По ID\n";
    cout << "2. По стоимости\n";
    cout << "3. По количеству трафика\n";
    cout << "4. По времени звонков\n";
    cout << "Введите номер критерия (1/2/3/4): ";

    int choice = dataTypesValidators.CheckToInt();

    if (choice == -1) {
        cout << "\nОтменено!" << endl;
        return;
    }

    while (choice < 1 || choice > 4) {
        cout << "Неверный ввод! Пожалуйста, выберите 1, 2, 3 или 4.\n";
        choice = dataTypesValidators.CheckToInt();
    }

    vector<Rate> sortedRates = rate.getRates();

    switch (choice) {
        case 1:
            sort(sortedRates.begin(), sortedRates.end(),
                 [](const Rate &a, const Rate &b) { return a.getRateId() < b.getRateId(); });
            break;
        case 2:
            sort(sortedRates.begin(), sortedRates.end(),
                 [](const Rate &a, const Rate &b) { return a.getCost() < b.getCost(); });
            break;
        case 3:
            sort(sortedRates.begin(), sortedRates.end(),
                 [](const Rate &a, const Rate &b) { return a.getAmountOfNetwork() < b.getAmountOfNetwork(); });
            break;
        case 4:
            sort(sortedRates.begin(), sortedRates.end(),
                 [](const Rate &a, const Rate &b) { return a.getCallTime() < b.getCallTime(); });
            break;
    }

    rate.setRates(sortedRates);
    DisplayRate(sortedRates);
    SubsFileSystem.RewriteRateInfo();
}

void SubsLogic::DisplayRates() {
    if (!rate.getRates().empty()) {
        cout <<  "\n╔══════════════════════════════════════════════════════╗\n";
        cout <<    "║                        ТАРИФЫ                        ║\n";
        cout <<    "╠════════╤══════════════╤══════════════╤═══════════════╣\n";
        cout <<    "║   ID   │   Стоимость  │    Трафик    │ Беспл. минуты ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪═══════════════╣\n";

        for (const auto &item : rate.getRates()) {
            cout << "║ " << setw(6) << left << item.getRateId() << " │ "
                 << setw(12) << left << item.getCost() << " │ "
                 << setw(12) << left << item.getAmountOfNetwork() << " │ "
                 << setw(12) << left << item.getCallTime() << "  ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧═══════════════╝\n";
    } else {
        cout << "Список тарифов пуст." << endl;
    }
}

void SubsLogic::DisplayRate(vector<Rate> rates) {    // Метод для отображения тарифных планов
    if (!rates.empty()) {
        cout <<  "\n╔════════╤══════════════╤══════════════╤═══════════════╗\n";
        cout <<    "║   ID   │   Стоимость  │    Трафик    │ Беспл. минуты ║\n";
        cout <<    "╠════════╪══════════════╪══════════════╪═══════════════╣\n";

        for (const auto &item : rates) {
            cout << "║ " << setw(6) << left << item.getRateId() << " │ "
                 << setw(12) << left << item.getCost() << " │ "
                 << setw(12) << left << item.getAmountOfNetwork() << " │ "
                 << setw(12) << left << item.getCallTime() << "  ║" << endl;
        }
        cout <<    "╚════════╧══════════════╧══════════════╧═══════════════╝\n";
    } else {
        cout << "Список тарифов пуст." << endl;
    }
}