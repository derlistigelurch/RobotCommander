#include <iostream>

#include "Header/GameManager.h"

int main()
{
    auto *gameManager = new GameManager(new Map(15, 15));

    int input = 0;
    while(true)
    {
        std::cin >> input;
        if((int) input == 0)
        {
            gameManager->DeletePipe();
            break;
        }
        gameManager->WriteToPipe();
    }

    delete gameManager;
    return EXIT_SUCCESS;
}
