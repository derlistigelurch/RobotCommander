#include "../include/Sender.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <cstring>

#include "../../MessageManager/include/ConfigManager.h"

void Sender::SendMessage(long type, const std::string &text, const std::string &identifier) const
{
    struct Message message{};
    message.type = type;
    std::strncpy(message.text, text.c_str(), text.length());

    if(msgsnd(this->getId(identifier), &message, sizeof(message) - sizeof(long), IPC_NOWAIT) == EOF)
    {
        std::cerr << "ERROR: Can't send message" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Message Sender::ReceiveMessage(const std::string &identifier) const
{
    struct Message message{};

    if(msgrcv(this->getId(identifier), &message, sizeof(message) - sizeof(long), 0, 0) == EOF)
    {
        std::cerr << "ERROR: Can't receive from message queue" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return message;
}

int Sender::getKey(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return ConfigManager().ioKey;
    }

    if(identifier == GAME)
    {
        return ConfigManager().gameKey;
    }
}

void Sender::setId(int id, const std::string &identifier)
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

int Sender::getId(const std::string &identifier) const
{
    if(identifier == IO)
    {
        return this->ioMessageId;
    }

    if(identifier == GAME)
    {
        return this->gameMessageId;
    }
}