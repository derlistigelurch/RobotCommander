#include <iostream>
#include <unistd.h>

#include "include/Message.h"
#include "include/MessageManager.h"
#include "../GameManager/include/ScreenManager.h"
#include "include/ConfigManager.h"

int main()
{
    auto *messageManager = new MessageManager();
    messageManager->CreateMsgQueue(MessageManager::IO);
    Message message{};
    std::string content;

    while(true)
    {
        std::fill(message.text, message.text + sizeof(message.text), 0);

        message = messageManager->ReceiveMessage(MessageManager::IO);
        content = "";

        try
        {
            switch(std::stoi(message.text, nullptr, 10))
            {
                case 1:
                    // create gameMessageQueue
                    messageManager->CreateMsgQueue(MessageManager::Sender::GAME);

                    // Create Pipes
                    messageManager->CreatePipe(MessageManager::Sender::MAP);
                    messageManager->CreatePipe(MessageManager::Sender::LOG);
                    messageManager->CreatePipe(MessageManager::Sender::STATS);

                    // automatically waits for process to finish
                    system(ConfigManager().gameManagerPath.c_str());

                    // delete gameMessageQueue
                    messageManager->DeleteMsgQueue(MessageManager::Sender::GAME);
                    messageManager->DeletePipe(MessageManager::Sender::MAP);
                    messageManager->DeletePipe(MessageManager::Sender::LOG);
                    messageManager->DeletePipe(MessageManager::Sender::LOG);
                    break;

                case 2:
                    break;

                case 3:
                    delete messageManager;
                    return EXIT_SUCCESS;

                default:
                    break;
            }
        }
        catch(const std::exception &e)
        {
            content = "ERROR: Unrecognised symbol\n";
        }

        messageManager->SendMessage(1, ScreenManager::ShowMainScreen() + content, MessageManager::Sender::IO);
    }
}
