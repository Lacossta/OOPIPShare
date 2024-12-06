cmake_minimum_required(VERSION 3.27)
project(kursach)

set(CMAKE_CXX_STANDARD 17)


add_executable(kursach main.cpp
        config/config.cpp
        config/config.h

        Auth/Registration/Registration.cpp
        Auth/Registration/Registration.h

        Auth/Login/Login.cpp
        Auth/Login/Login.h

        Auth/Auth.cpp
        Auth/Auth.h

        Auth/User/User.cpp
        Auth/User/User.h

        DataTypeValidators/DataTypes.cpp
        DataTypeValidators/DataTypes.h

        MainLogic/SubsAndRateLogic/Subcriber/Subcriber.cpp
        MainLogic/SubsAndRateLogic/Subcriber/Subcriber.h

        MainLogic/SubsAndRateLogic/Rate/Rate.cpp
        MainLogic/SubsAndRateLogic/Rate/Rate.h

        MainLogic/SubsAndRateLogic/Client/Client.cpp
        MainLogic/SubsAndRateLogic/Client/Client.h

        Utils/Utils.cpp
        Utils/Utils.h

        Auth/UserFileSystem/UserFileSystem.cpp
        Auth/UserFileSystem/UserFileSystem.h

        MainLogic/Start.cpp
        MainLogic/Start.h

        DisplayMenuUtil/DisplayMenuUtil.cpp
        DisplayMenuUtil/DisplayMenuUtil.h

        MainLogic/EnteredUserLogic/EnteredUser.cpp
        MainLogic/EnteredUserLogic/EnteredUser.h
        PathToLibs.h
        SubsAndRateFileSystem/SubsAndRateFileSystem.cpp
        SubsAndRateFileSystem/SubsAndRateFileSystem.h
        MainLogic/SubsAndRateLogic/Subcriber/SubcriberRegistration.cpp
        MainLogic/SubsAndRateLogic/Subcriber/SubcriberRegistration.h
        MainLogic/SubsAndRateLogic/SubsLogic.cpp
        MainLogic/SubsAndRateLogic/SubsLogic.h
)
