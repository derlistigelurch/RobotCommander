#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <cstring>

#include "../MessageManager/include/ConfigManager.h"
#include "../MessageManager/include/Message.h"

int main()
{
    std::string input;
    struct Message message{};

    int messageId = 0;
    if((messageId = msgget(ConfigManager().ioKey, ConfigManager().mode)) == -1)
    {
        std::cerr << "Can't access message queue" << std::endl;
        return EXIT_FAILURE;
    }

    message.type = 'P';
    std::string player = "1";
    std::strncpy(message.text, player.c_str(), player.length());

    if(msgsnd(messageId, &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
    {
        std::cerr << "ERROR: Can't send message" << std::endl;
        std::exit(EXIT_FAILURE);
    }


    while(true)
    {
        if(msgrcv(messageId, &message, sizeof(message) - sizeof(long), 0, 0) == EOF)
        {
            std::cerr << "ERROR: Can't receive from message queue" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::cout << message.text << std::endl << std::flush;

        std::fill(message.text, message.text + sizeof(message.text), 0);

        std::cout << "_>> ";
        getline(std::cin, input);

        message.type = 1;
        std::strncpy(message.text, input.c_str(), input.length());

        if(msgsnd(messageId, &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
        {
            std::cerr << "ERROR: Can't send message" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if(input == "3")
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}
