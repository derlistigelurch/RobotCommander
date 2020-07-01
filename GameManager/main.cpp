#include <iostream>

#include "Header/GameManager.h"

int main()
{
    auto *gameManager = new GameManager();
    std::cout << gameManager->mapPipe << std::endl;

    int input = 0;
    while(true)
    {
        std::cin >> input;
        if((int) input == 0)
        {
            return EXIT_SUCCESS;
        }
        gameManager->writeToPipe();
    }

    return 0;
}
