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

    // ioManager->GameMode();

    std::string input;
    struct Message message{};

    ioManager->GetMessageQueue(IOManager::Sender::IO);

    ioManager->SendMessage(6, "89", IOManager::Sender::IO);
    // ioManager->Wait(250000);
    while(true)
    {
        message = ioManager->ReceiveMessage(IOManager::Sender::IO);
        std::cout << message.text << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        ioManager->SendMessage(1, input, IOManager::Sender::IO);

        if(input == "1")
        {
            ioManager->Wait(500000);
            ioManager->GameMode();
        }

        if(input == "2")
        {
            // ioManager->WorkshopMode();
        }

        if(input == "3")
        {
            break;
        }
    }

    delete ioManager;
    return EXIT_SUCCESS;
}
