#include <sys/msg.h>

#include <iostream>

#include "include/Message.h"
#include "include/MessageManager.h"
#include "../GameManager/include/ScreenManager.h"

int main()
{
    // 1. create msgqueue
    // 2. write to msgqueue
    // 3. read from msgqueue
    // 4. process data
    // 5. send response

    auto *messageManager = new MessageManager();

    messageManager->CreateMsgQueue();
    while(true)
    {
        // messageManager->ReadFromPipe();
        // messageManager->WriteToPipe(ScreenManager::ShowMainScreen());
        // int input = 0;
        // std::cin >> input;
        // if(!input)
        // {
        //     break;
        // }
        std::cout << messageManager->ReceiveMessage() << std::endl;
    }

    delete messageManager;

    return EXIT_SUCCESS;
}
