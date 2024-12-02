#ifndef KURSACH_SUBSANDRATEFILESYSTEM_H
#define KURSACH_SUBSANDRATEFILESYSTEM_H

#include "../PathToLibs.h"
#include "../MainLogic/SubsAndRateLogic//Rate/Rate.h"
#include "../MainLogic/SubsAndRateLogic/Client/Client.h"

class SubsAndRateFileSystem {
public:
    void LoadSubcriberInfo();
    void SaveSubcriberInfo(const Subcriber &machine);
    void RewriteSubcriberInfo();

    void LoadRateInfo();
    void SaveRateInfo(const Rate& repairType);
    void RewriteRateInfo();

    void LoadClientInfo();
    void SaveClientInfo(const Client& repair);
    void RewriteClientInfo();

    SubsAndRateFileSystem();
};

extern SubsAndRateFileSystem SubsFileSystem;

#endif //KURSACH_SUBSANDRATEFILESYSTEM_H
