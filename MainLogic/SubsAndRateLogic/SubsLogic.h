#ifndef KURSACH_SUBSLOGIC_H
#define KURSACH_SUBSLOGIC_H

#include "../../PathToLibs.h"

class SubsLogic {
public:
    int  MainMenu(User &user);

    tuple<string, string, string> InputFullName();
    string PhoneInput();

    // ---Subs---
    void SubcriberMenu();
    void AddSubcriber();
    void EditSubcriber();
    void RemoveSubcriber();
    void SearchSubcriber();
    void SortSubcriber();
    void BanSubcriber();
    void CreateSubscriberFromClient();
    void DisplayAllSubcribers(vector<Subcriber> subcribers);
    void DisplayAllSubcribers();

    // ---Client---
    void ClientMenu();
    void AddClient();
    void EditClient();
    void RemoveClient();
    void SearchClient();
    void SortClient();
    void DisplayAllClients(vector<Client> clients);
    void DisplayAllClients();

    // ---Rate---
    void RateMenu();
    void AddRate();
    void EditRate();
    void RemoveRate();
    void SearchRate();
    void SortRate();
    void DisplayRates();
    void DisplayRate(vector<Rate> rates);

};

extern SubsLogic subsLogic;


#endif //KURSACH_SUBSLOGIC_H
