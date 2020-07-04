#ifndef GAMEMANAGER_SCREENMANAGER_H
#define GAMEMANAGER_SCREENMANAGER_H


#include <iostream>

class ScreenManager
{
public:
    ScreenManager() = default;

    ~ScreenManager() = default;

    static std::string ShowFightMenu() ;

    static std::string ShowFightScreen();

    static std::string ShowMainScreen() ;

    static std::string ShowMainMenu();
};


#endif //GAMEMANAGER_SCREENMANAGER_H
