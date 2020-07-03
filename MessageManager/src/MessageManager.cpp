#include "../include/MessageManager.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <fstream>
#include <algorithm>

#include "../include/Message.h"
#include "../include/ConfigManager.h"

MessageManager::MessageManager()
{
    ConfigManager().LoadConfig();
}

MessageManager::~MessageManager()
{
    this->DeletePipe();
    this->DeleteMsgQueue();
}

void MessageManager::CreatePipe()
{
    if(mkfifo(ConfigManager().ioPipe.c_str(), ConfigManager().mode) == -1 && errno != ERRNO_FILE_EXISTS)
    {
        std::cerr << "ERROR: Unable to create pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::DeletePipe()
{
    if(std::remove(ConfigManager().ioPipe.c_str()) != EXIT_SUCCESS && errno != ERRNO_FILE_NOT_FOUND)
    {
        std::cout << errno << std::endl;
        std::cerr << "ERROR: Unable to delete pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::WriteToPipe(const std::string &string)
{
    std::fstream pipe(ConfigManager().ioPipe);

    if(!pipe.is_open())
    {
        std::cerr << "ERROR: Unable to open file";
        std::exit(EXIT_FAILURE);
    }

    pipe << string;
    pipe.close();
}

void MessageManager::ReadFromPipe()
{
    std::fstream pipe(ConfigManager().ioPipe);
    if(!pipe.is_open())
    {
        std::cerr << "ERROR: Unable to read from pipe";
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    while(getline(pipe, line))
    {
        std::cout << line << std::endl;
    }
    pipe.close();
}

void MessageManager::CreateMsgQueue()
{
    int messageId = 0;

    if((messageId = msgget(ConfigManager().ioKey, ConfigManager().mode | IPC_CREAT)) == -1)
    {
        std::cerr << "ERROR: Creating message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    this->ioMessageId = messageId;
}

void MessageManager::DeleteMsgQueue() const
{
    if(msgctl(this->ioMessageId, IPC_RMID, nullptr) == EOF)
    {
        fprintf(stderr, "Message queue could not be deleted.\n");
        exit(EXIT_FAILURE);
    }
}

void MessageManager::SendMessage()
{
    struct Message message;
    if(msgsnd(this->ioMessageId, &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
    {
        std::cerr << "ERROR: Can't send message" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

std::string MessageManager::ReceiveMessage() const
{
    struct Message message{};
    if(msgrcv(this->ioMessageId, &message, sizeof(message) - sizeof(long), 0, 0) == EOF)
    {
        std::cerr << "ERROR: Can't receive from message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::string a = message.text;
    return a;
}
