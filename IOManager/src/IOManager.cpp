#include <iostream>
#include "../include/IOManager.h"


void IOManager::GameMode()
{
    struct Message message{};
    std::string input;

    this->GetMessageQueue(IOManager::Sender::GAME);

    // std::cout << this->ReceiveMessage(IOManager::Sender::GAME).text << std::endl << std::flush;

    while(true)
    {
        message = this->ReceiveMessage(IOManager::Sender::GAME);
        std::cout << message.text << std::endl << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        this->SendMessage(1, input, IOManager::Sender::GAME);

        if(input == "5")
        {
            break;
        }
    }
}
