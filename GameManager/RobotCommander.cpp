#include <iostream>

#include "include/GameManager.h"
#include "include/ScreenManager.h"

int main(int argc, char *argv[])
{
    int input = 0;

    auto *gameManager = new GameManager();

    while(true)
    {
        ScreenManager::ShowMainScreen();
        std::cout << "_>> ";
        std::cin >> input;
        if(input == 0)
        {
            break;
        }

        //gameManager->Fight();
    }

    delete gameManager;
}
