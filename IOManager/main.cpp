#include <iostream>

#include "../MapDisplay/include/Colors.h"
#include "../MessageManager/include/ConfigManager.h"
#include "../MessageManager/include/Message.h"
#include "include/IOManager.h"

int main()
{
    auto *ioManager = new IOManager();
    ioManager->Wait(250000);

    // ioManager->RunGameMode();

    std::string input;
    struct Message message{};

    ioManager->GetMessageQueue(IOManager::Sender::IO);

    ioManager->SendMessage(6, "R", IOManager::Sender::IO);
    while(true)
    {
        std::cout << CLEAR;
        message = ioManager->ReceiveMessage(IOManager::Sender::IO);
        std::cout << message.text << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        ioManager->SendMessage(1, input, IOManager::Sender::IO);

        if(input == IOManager::FIGHT)
        {
            ioManager->RunGameMode();
        }

        if(input == IOManager::EXIT)
        {
            break;
        }
    }

    delete ioManager;
    return EXIT_SUCCESS;
}
