#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <cstring>

#include "../MessageManager/include/ConfigManager.h"
#include "../MessageManager/include/Message.h"
#include "include/IOManager.h"

int main()
{
    auto *ioManager = new IOManager();
    ioManager->Wait(250000);

    ioManager->GameMode();

    std::string input;
    struct Message message{};

    ioManager->GetMessageQueue(IOManager::Sender::IO);

    ioManager->SendMessage(6, "R", IOManager::Sender::IO);
    while(true)
    {
        std::cout << "\033[2J\033[1;1H";
        message = ioManager->ReceiveMessage(IOManager::Sender::IO);
        std::cout << message.text << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        ioManager->SendMessage(1, input, IOManager::Sender::IO);

        if(input == "F")
        {
            ioManager->GameMode();
        }

        if(input == "W")
        {
            // ioManager->WorkshopMode();
        }

        if(input == "E")
        {
            break;
        }
    }

    delete ioManager;
    return EXIT_SUCCESS;
}
