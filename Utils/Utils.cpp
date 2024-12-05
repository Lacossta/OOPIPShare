//#include "Utils.h"
//#include "../Auth/Auth.h"

#include "../PathToLibs.h"
#include "../MainLogic/SubsAndRateLogic//Client//Client.h"

Utils utilsModule;

// ==USER==
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

int Utils::FindByIdIntoUsers(const int id) {
    vector <User> users = auth.getUsers();
    for(int i =0; i<users.size(); i++)
    {
        if(users[i].getId() == id)
        {
            return i;
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


// ==Subcriber==

Subcriber Utils::FindSubcriberById(const int id) {

    for (auto it : subcriber.getSubcribers()){
        if (it.getSubId() == id){
            return it;
        }
    }

    // Объект не найден, возвращаем Subcriber с subId = -1
    return Subcriber();
}

// ==Rate==

Rate Utils::FindRateById(const int id) {
    for (auto it : rate.getRates()){
        if (it.getRateId() == id){
            return it;
        }
    }

    return Rate();
}

// ==Client==

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

Client Utils::FindClientById(const int id) {
//    Client localClient;
//
//    for(int i = 0; i < client.getClients().size(); i++){
//        localClient.setClientId(client.getClients()[i].getClientId());
//        return localClient;
//    }
//    return localClient;

    for (auto it : client.getClients()){
        if (it.getClientId() == id){
            return it;
        }
    }

    // Объект не найден Id = -1
    return Client();
}
