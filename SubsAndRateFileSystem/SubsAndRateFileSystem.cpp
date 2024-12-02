#include "SubsAndRateFileSystem.h"

SubsAndRateFileSystem machineFileSystem;

void SubsAndRateFileSystem::LoadSubcriberInfo() {
    ifstream file(config.SubcriberDataPath);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int subId, age, rateId;
        bool isblock;
        string connectDate, phone, surname, name, midName;

        if (iss >> subId >> isblock >> surname >> name >> midName >> age >> phone >> rateId >> connectDate) {
            Subcriber subLoad(subId, isblock, age, rateId, connectDate, phone, surname, name, midName);
            subcriber.addSubcriber(subLoad);
        }
    }
}

void SubsAndRateFileSystem::SaveSubcriberInfo(const Subcriber &sub) {
    ofstream file(config.SubcriberDataPath, ios::app);
    if (file.is_open() && sub.getSubId() != -1) {
        file << sub.getSubId() << " " << sub.getIsblock() << " " << sub.getSurname() << " " << sub.getName() << " "
             << sub.getMidName() << " " << sub.getAge() << " " << sub.getPhone() << " " << sub.getRateId() << " "
             << sub.getConnectDate() << endl;
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

void SubsAndRateFileSystem::RewriteSubcriberInfo() {
    ofstream file(config.SubcriberDataPath, ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        vector<Subcriber> subs = subcriber.getSubcribers();
        for (int i = 0; i < subs.size(); i++) {
            file << subs[i].getSubId() << " " << subs[i].getIsblock() << " " << subs[i].getSurname() << " "
                 << subs[i].getName() << " " << subs[i].getMidName() << " " << subs[i].getAge() << " "
                 << subs[i].getPhone() << " " << subs[i].getRateId() << " " << subs[i].getConnectDate() << endl;
        }
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}




void SubsAndRateFileSystem::LoadRateInfo() {
    ifstream file(config.RateDataPath);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int rateId, amountOfNetwork, callTime;
        float cost;

        if (iss >> rateId >> cost >> amountOfNetwork >> callTime) {
            Rate rateLoad(rateId, cost, amountOfNetwork, callTime);
            rate.addRate(rateLoad);
        }
    }
}

void SubsAndRateFileSystem::SaveRateInfo(const Rate& rate) {
    ofstream file(config.RateDataPath, ios::app);
    if (file.is_open() && rate.getRateId() != -1) {
        file << rate.getRateId() << " " << rate.getCost() << " " << rate.getAmountOfNetwork() << " " << rate.getCallTime() << endl;
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

void SubsAndRateFileSystem::RewriteRateInfo() {
    ofstream file(config.RateDataPath, ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        vector<Rate> rates = rate.getRates();
        for (int i = 0; i < rates.size(); i++) {
            file << rates[i].getRateId() << " " << rates[i].getCost() << " " << rates[i].getAmountOfNetwork() << " " << rates[i].getCallTime() << endl;
        }
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}




void SubsAndRateFileSystem::LoadClientInfo() {
    ifstream file(config.ClientDataPath);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int clientId, age;
        string surname, name, midName;

        if (iss >> clientId >> surname >> name >> midName >> age) {
            Client clientLoad(clientId, age, surname, name, midName);
            client.addClient(clientLoad);
        }
    }
}

void SubsAndRateFileSystem::SaveClientInfo(const Client &client) {
    ofstream file(config.ClientDataPath, ios::app);
    if (file.is_open() && client.getClientId() != -1) {
        file << client.getClientId() << " " << client.getSurname() << " " << client.getName() << " "
             << client.getMidName() << " " << client.getAge() << endl;
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

void SubsAndRateFileSystem::RewriteClientInfo() {
    ofstream file(config.ClientDataPath, ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        vector<Client> clients = client.getClients();
        for (int i = 0; i < clients.size(); i++) {
            file << clients[i].getClientId() << " " << clients[i].getSurname() << " " << clients[i].getName() << " "
                 << clients[i].getMidName() << " " << clients[i].getAge() << endl;
        }
        file.close();
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}


SubsAndRateFileSystem::SubsAndRateFileSystem() {

}
