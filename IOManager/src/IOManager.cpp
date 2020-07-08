#include <iostream>
#include "../include/IOManager.h"


void IOManager::GameMode()
{
    struct Message message{};
    std::string input;

    this->GetMessageQueue(IOManager::Sender::GAME);

    while(true)
    {
        std::cout << "\033[2J\033[1;1H";
        message = this->ReceiveMessage(IOManager::Sender::GAME);
        std::cout << message.text << std::endl << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        this->SendMessage(1, input, IOManager::Sender::GAME);

        if(input == "R")
        {
            break;
        }
    }
}
