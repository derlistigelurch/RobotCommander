#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <cstring>

#include "../MessageManager/include/ConfigManager.h"
#include "../MessageManager/include/Message.h"

int main()
{
    std::string input;

    /*std::fstream pipe("../../MessageManager/cmake-build-debug/" + ConfigManager().ioPipe);
    if(!pipe.is_open())
    {
        std::cerr << "ERROR: Unable to read from pipe";
        std::exit(EXIT_FAILURE);
    }*/

    int messageId = 0;
    if((messageId = msgget(ConfigManager().ioKey, ConfigManager().mode)) == -1)
    {
        std::cerr << "Can't access message queue" << std::endl;
        return EXIT_FAILURE;
    }



    while(true)
    {
        std::cout << "_>> ";
        getline(std::cin, input);

        if(input == "end")
        {
            break;
        }

        struct Message message{};
        message.type = 1;
        std::strncpy(message.text, input.c_str(), input.length());

        if(msgsnd(messageId, &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
        {
            std::cerr << "ERROR: Can't send message" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // delete [] message.text;

        // pipe << input;

        // std::string line;
        // while(getline(pipe, line))
        // {
        //     std::cout << line << std::endl;
        // }
    }
}
