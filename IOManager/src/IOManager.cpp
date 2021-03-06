#include "../include/IOManager.h"

#include <iostream>

#include "../../MapDisplay/include/Colors.h"

void IOManager::RunGameMode()
{
    struct Message message{};
    std::string input;

    this->GetMessageQueue(IOManager::Sender::GAME);

    while(true)
    {
        std::cout << CLEAR;
        message = this->ReceiveMessage(IOManager::Sender::GAME);
        std::cout << message.text << std::flush;

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
