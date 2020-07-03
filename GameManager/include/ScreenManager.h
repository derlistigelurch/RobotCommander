#ifndef GAMEMANAGER_SCREENMANAGER_H
#define GAMEMANAGER_SCREENMANAGER_H


#include <iostream>

class ScreenManager
{
public:
    ScreenManager() = default;

    ~ScreenManager() = default;

    static void FightMenu() ;

    void Exit();

    static void ShowMainScreen() ;
};


#endif //GAMEMANAGER_SCREENMANAGER_H
