//#include "Utils.h"
//#include "../Auth/Auth.h"

#include "../PathToLibs.h"
#include "../MainLogic/SubsAndRateLogic//Client//Client.h"

Utils utilsModule;

User Utils::FindUserByLogin(const string& login)
{
    User user;

    for(int i = 0; i < auth.getUsers().size(); i++){
        if(login == auth.getUsers()[i].getLogin()){
            user.setId(auth.getUsers()[i].getId());
            user.setLogin(login);
            user.setPassword(auth.getUsers()[i].getPassword());
            user.setIsAdmin(auth.getUsers()[i].getIsAdmin());
            user.setIsHasAccess(auth.getUsers()[i].getIsHasAccess());
            return user;
        }
    }
    return user;
}

User Utils::FindUserById(const int id) {
    User user;

    for(int i = 0; i < auth.getUsers().size(); i++){
            user.setId(auth.getUsers()[i].getId());
            user.setIsAdmin(auth.getUsers()[i].getIsAdmin());
            user.setLogin(auth.getUsers()[i].getLogin());
            return user;
    }
    return user;
}

Subcriber Utils::FindSubcriberById(const int id) {
    Subcriber localSubcriber;

    for(int i = 0; i < subcriber.getSubcribers().size(); i++){
            localSubcriber.setSubId(subcriber.getSubcribers()[i].getSubId());
            //localSubcriber.setMachineModel(machine.getSubcribers()[i].getMachineModel());
            return localSubcriber;

    }
    return localSubcriber;
}

int Utils::FindByIdIntoRates(const int id) {
    vector <Rate> rates = rate.getRates();
    for(int i =0; i<rates.size(); i++)
    {
        if(rates[i].getRateId() == id)
        {
            return i;
        }
    }
    return -1;
}

int Utils::FindByIdIntoClient(const int id) {
    vector <Client> clients = client.getClients();
    for(int i =0; i<clients.size(); i++)
    {
        if(clients[i].getClientId() == id)
        {
            return i;
        }
    }
    return -1;
}

int Utils::FindByIdIntoUsers(const int id) {
    vector <User> users = auth.getUsers();
    for(int i =0; i<users.size(); i++)
    {
        if(users[i].getId() == id)
        {
            return i;
            break;
        }
    }
    return -1;
}

int Utils::GenerateID(){
    if(auth.getUsers().size() > 0) {
        return auth.getUsers()[auth.getUsers().size() - 1].getId() + 1;
    }
    else {
        return 0;
    }
}
