#ifndef GAMEMANAGER_SCREENMANAGER_H
#define GAMEMANAGER_SCREENMANAGER_H

#include <iostream>

class ScreenManager
{
public:
    ScreenManager() = default;

    ~ScreenManager() = default;

    void FightMenu();

    void Exit();

    void ShowMainScreen();
};


#endif //GAMEMANAGER_SCREENMANAGER_H
