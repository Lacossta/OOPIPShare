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
    void DisplayAllSubcribers();

    // ---Client---
    void ClientMenu();
    void AddClient();
    void EditClient();
    void RemoveClient();
    void SearchClient();
    void SortClient();
    void DisplayClient();

    // ---Rate---
    void RateMenu();
    void AddRate();
    void EditRate();
    void RemoveRate();
    void SearchRate();
    void SortRate();
    void DisplayRate();


//    void DeleteMachine(User &user);
//    void DisplayMachines(User &user, int variant);
//
//
//    void RepairMenu(User &user);
//    void AddRepair();
//    void DisplayAllRepairsTypes();
//    void DeleteRepairType();
//
//    void AddToRepair(User &user);
//    void DeleteRepair(User &user);
//    void DisplayRepairs(User &user);
//
//    void DisplayAll(User &user);

};

extern SubsLogic subsLogic;


#endif //KURSACH_SUBSLOGIC_H
