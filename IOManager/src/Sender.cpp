#include "../include/Sender.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <cstring>

#include "../../MessageManager/include/ConfigManager.h"

void Sender::SendMessage(long type, const std::string &text, const std::string &identifier) const
{
    struct Message message{};
    message.type = type;
    std::strncpy(message.text, text.c_str(), text.length());

    if(msgsnd(this->GetId(identifier), &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
    {
        std::cerr << "ERROR: Can't send message" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Message Sender::ReceiveMessage(const std::string &identifier) const
{
    struct Message message{};

    if(msgrcv(this->GetId(identifier), &message, sizeof(message) - sizeof(long), 0, 0) == EOF)
    {
        std::cerr << "ERROR: Can't receive from message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return message;
}

int Sender::GetKey(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return ConfigManager().ioKey;
    }

    if(identifier == GAME)
    {
        return ConfigManager().gameKey;
    }

    return ERR_KEY_NOT_FOUND;
}

void Sender::SetId(int id, const std::string &identifier)
{
    if(identifier == IO)
    {
        this->ioMessageId = id;
    }

    if(identifier == GAME)
    {
        this->gameMessageId = id;
    }
}

int Sender::GetId(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return this->ioMessageId;
    }

    if(identifier == GAME)
    {
        return this->gameMessageId;
    }

    return ERR_ID_NOT_FOUND;
}

void Sender::GetMessageQueue(const std::string &identifier)
{
    this->SetId(msgget(GetKey(identifier), ConfigManager().mode), identifier);
    if(this->GetId(identifier) == EOF)
    {
        std::cerr << "Can't access message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Sender::WriteToPipe(const std::string &content, const std::string &identifier) const
{
    std::fstream pipe(this->GetPipe(identifier));

    if(!pipe.is_open())
    {
        std::cerr << "ERROR: Unable to open file";
        std::exit(EXIT_FAILURE);
    }

    pipe << content;
    pipe.close();
}

void Sender::ReadFromPipe(const std::string &identifier) const
{
    std::fstream pipe(this->GetPipe(identifier));
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

std::string Sender::GetPipe(const std::string &identifier) const
{
    if(identifier == MAP)
    {
        return ConfigManager().mapPipe;
    }

    if(identifier == LOG)
    {
        return ConfigManager().logPipe;
    }

    if(identifier == STATS)
    {
        return ConfigManager().statsPipe;
    }

    return ERR_PIPE_NOT_FOUND;
}

void Sender::Wait(int microseconds) const
{
    usleep(microseconds);
}
