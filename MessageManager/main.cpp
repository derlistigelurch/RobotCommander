#include <iostream>
#include <unistd.h>

#include "include/Message.h"
#include "include/MessageManager.h"
#include "../GameManager/include/ScreenManager.h"
#include "include/ConfigManager.h"

int main()
{
    // 1. create msgqueue
    // 2. write to msgqueue
    // 3. read from msgqueue
    // 4. process data
    // 5. send response

    auto *messageManager = new MessageManager();
    messageManager->CreateMsgQueue(MessageManager::IO);
    Message message{};
    std::string content;

    while(true)
    {
        std::fill(message.text, message.text + sizeof(message.text), 0);

        message = messageManager->ReceiveMessage(MessageManager::IO);
        std::cout << message.text << std::endl;
        content = "";

        try
        {
            switch(std::stoi(message.text, nullptr, 10))
            {
                case 1:
                {
                    // create gameMessageQueue
                    messageManager->CreateMsgQueue(MessageManager::Sender::GAME);

                    // automatically waits for process to finish
                    system("../../GameManager/cmake-build-debug/GameManager");

                    // delete gameMessageQueue
                    messageManager->DeleteMsgQueue(MessageManager::Sender::GAME);
                    break;

                }
                case 2:
                    break;
                case 3:
                    delete messageManager;
                    return EXIT_SUCCESS;
                default:
                    throw std::bad_cast();
            }
        }
        catch(const std::exception &e)
        {
            content = "ERROR: Unrecognised symbol\n";
        }

        messageManager->SendMessage(1, ScreenManager::ShowMainScreen() + content, MessageManager::Sender::IO);
    }
}
