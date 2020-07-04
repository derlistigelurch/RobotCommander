#include "../include/MessageManager.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "../include/Message.h"
#include "../include/ConfigManager.h"

MessageManager::~MessageManager()
{
    this->DeletePipe(Sender::LOG);
    this->DeletePipe(Sender::MAP);
    this->DeletePipe(Sender::STATS);
    this->DeleteMsgQueue(Sender::IO);
}

void MessageManager::CreatePipe(const std::string &identifier)
{
    if(mkfifo(this->getPipe(identifier).c_str(), ConfigManager().mode) == -1 && errno != ERRNO_FILE_EXISTS)
    {
        std::cerr << "ERROR: Unable to create pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::DeletePipe(const std::string &identifier)
{
    if(std::remove(this->getPipe(identifier).c_str()) != EXIT_SUCCESS && errno != ERRNO_FILE_NOT_FOUND)
    {
        std::cout << errno << std::endl;
        std::cerr << "ERROR: Unable to delete pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::CreateMsgQueue(const std::string &identifier)
{
    this->setId(msgget(this->getKey(identifier), ConfigManager().mode | IPC_CREAT), identifier);
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
