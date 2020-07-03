#include <iostream>

#include "include/GameManager.h"
#include "include/ScreenManager.h"

static const int START = 1;
static const int CREATOR = 2;
static const int EXIT = 3;

int main(int argc, char *argv[])
{
    int input = 0;

    while(true)
    {
        ScreenManager::ShowMainScreen();
        std::cout << "_>> ";
        std::cin >> input;
        switch(input)
        {
            case START:
            {
                auto *gameManager = new GameManager();

                gameManager->Fight();

                delete gameManager;
                break;
            }

            case CREATOR:
                // TODO: Open Creator
                break;

            case EXIT:
                return EXIT_SUCCESS;

            default:
                std::cerr << "ERROR: Invalid symbol" << std::endl;
                break;

        }
    }
}
