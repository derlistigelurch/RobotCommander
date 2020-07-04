#include "../include/MessageManager.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "../include/Message.h"
#include "../include/ConfigManager.h"

MessageManager::MessageManager()
{
    ConfigManager().LoadConfig();
}

MessageManager::~MessageManager()
{
    this->DeletePipe();
    this->DeleteMsgQueue(IO);
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

void MessageManager::WriteToPipe(const std::string &content)
{
    std::fstream pipe(ConfigManager().ioPipe);

    if(!pipe.is_open())
    {
        std::cerr << "ERROR: Unable to open file";
        std::exit(EXIT_FAILURE);
    }

    pipe << content;
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

void MessageManager::CreateMsgQueue(const std::string &identifier)
{
    this->setId(msgget(getKey(identifier), ConfigManager().mode | IPC_CREAT), identifier);
    if(this->getId(identifier) == EOF)
    {
        std::cerr << "ERROR: Creating message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::DeleteMsgQueue(const std::string &identifier) const
{
    if(msgctl(this->getId(identifier), IPC_RMID, nullptr) == EOF)
    {
        fprintf(stderr, "Message queue could not be deleted.\n");
        exit(EXIT_FAILURE);
    }
}

/*void MessageManager::SendMessage(long type, const std::string &text, const std::string &identifier) const
{
    struct Message message{};
    message.type = type;
    std::strncpy(message.text, text.c_str(), text.length());

    if(msgsnd(this->getId(identifier), &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
    {
        std::cerr << "ERROR: Can't send message" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}*/

/*Message MessageManager::ReceiveMessage(const std::string &identifier) const
{
    struct Message message{};

    if(msgrcv(this->getId(identifier), &message, sizeof(message) - sizeof(long), 0, 0) == EOF)
    {
        std::cerr << "ERROR: Can't receive from message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return message;
}*/

/*int MessageManager::getId(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return this->ioMessageId;
    }

    if(identifier == GAME)
    {
        return this->gameMessageId;
    }
}*/

/*void MessageManager::setId(int id, const std::string &identifier)
{
    if(identifier == IO)
    {
        this->ioMessageId = id;
    }

    if(identifier == GAME)
    {
        this->gameMessageId = id;
    }
}*/

/*int MessageManager::getKey(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return ConfigManager().ioKey;
    }

    if(identifier == GAME)
    {
        return ConfigManager().gameKey;
    }
}*/
