#ifndef GAMEMANAGER_SCREENMANAGER_H
#define GAMEMANAGER_SCREENMANAGER_H


#include <iostream>

class ScreenManager
{
public:
    ScreenManager() = default;

    ~ScreenManager() = default;

    /**
     * Shows the fight menu (M, A, R, E)
     */
    static void ShowFightMenu() ;

    /**
     * Shows the FIGHTMODE screen
     */
    static void ShowFightScreen();

    /**
     * Shows the ROBOTCOMMANDER screen
     */
    static void ShowMainScreen() ;

    /**
     * Shows the main menu (F, W, E)
     */
    static void ShowMainMenu();

    /**
     * Prints the manual of the game
     */
    static void PrintManual();
};


#endif //GAMEMANAGER_SCREENMANAGER_H
