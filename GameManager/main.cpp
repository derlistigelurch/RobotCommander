#include <iostream>
#include <getopt.h>

#include "include/GameManager.h"
#include "include/ScreenManager.h"

#define START 1
#define CREATOR 2
#define EXIT 3

int main(int argc, char *argv[])
{
    auto *screenManager = new ScreenManager();

    int input = 0;

    while(true)
    {
        screenManager->ShowMainScreen();
        std::cout << "_>> ";
        std::cin >> input;
        switch(input)
        {
            case START:
            {
                auto *gameManager = new GameManager();

                while(true)
                {
                    screenManager->FightMenu();
                    // TODO: move to gameManager Input function
                    std::cin >> input;
                    if((int) input == 0)
                    {
                        break;
                    }
                    std::string string;
                    std::cin >> string;
                    gameManager->Input(string);
                }

                delete gameManager;
                break;
            }

            case CREATOR:
                break;

            case EXIT:
                delete (screenManager);
                return EXIT_SUCCESS;
        }
    }
}
