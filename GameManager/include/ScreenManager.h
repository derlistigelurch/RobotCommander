#ifndef GAMEMANAGER_SCREENMANAGER_H
#define GAMEMANAGER_SCREENMANAGER_H


#include <iostream>

class ScreenManager
{
public:
    ScreenManager() = default;

    ~ScreenManager() = default;

    static void ShowFightMenu() ;

    static void ShowFightScreen();

    static void ShowMainScreen() ;

    static void ShowMainMenu();
};


#endif //GAMEMANAGER_SCREENMANAGER_H
