#include "../include/MessageManager.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <iostream>
#include <algorithm>

#include "../include/ConfigManager.h"
#include "../../GameManager/include/ScreenManager.h"

MessageManager::~MessageManager()
{
    this->DeletePipe(Sender::LOG);
    this->DeletePipe(Sender::MAP);
    this->DeletePipe(Sender::STATS);
    this->DeleteMsgQueue(Sender::IO);
    this->DeleteMsgQueue(Sender::GAME);
}

void MessageManager::CreatePipe(const std::string &identifier)
{
    if(mkfifo(this->GetPipe(identifier).c_str(), ConfigManager().mode) == EOF && errno != ERRNO_FILE_EXISTS)
    {
        std::cerr << "ERROR: Unable to create pipe." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::DeletePipe(const std::string &identifier)
{
    if(std::remove(this->GetPipe(identifier).c_str()) != EXIT_SUCCESS && errno != ERRNO_FILE_NOT_FOUND)
    {
        std::cout << errno << std::endl;
        std::cerr << "ERROR: Unable to delete pipe." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::CreateMsgQueue(const std::string &identifier)
{
    this->SetId(msgget(this->GetKey(identifier), ConfigManager().mode | IPC_CREAT), identifier);
    if(this->GetId(identifier) == EOF)
    {
        std::cerr << "ERROR: Creating message queue." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MessageManager::DeleteMsgQueue(const std::string &identifier) const
{
    if(msgctl(this->GetId(identifier), IPC_RMID, nullptr) == EOF)
    {
        fprintf(stderr, "Message queue could not be deleted.\n");
        exit(EXIT_FAILURE);
    }
}

MessageManager::MessageManager()
{
    this->CreatePipe(MessageManager::Sender::MAP);
    this->CreatePipe(MessageManager::Sender::LOG);
    this->CreatePipe(MessageManager::Sender::STATS);
    this->CreateMsgQueue(MessageManager::IO);
    this->CreateMsgQueue(MessageManager::Sender::GAME);
}

void MessageManager::Run()
{
    Message message{};
    std::string errorMessage;

    while(true)
    {
        std::fill(message.text, message.text + sizeof(message.text), 0);

        message = this->ReceiveMessage(MessageManager::IO);
        errorMessage = "";

        switch(message.text[0])
        {
            case FIGHT:
                system(ConfigManager().gameManagerPath.c_str());
                break;

            case WORKSHOP:
                // Open Workshop
                break;

            case EXIT:
                return;

            case REGISTRATION:
                break;

            default:
                errorMessage = "ERROR: Unrecognised symbol.\n";
                break;
        }

        ScreenManager::ShowMainScreen();
        ScreenManager::ShowMainMenu();

        this->SendMessage(1, errorMessage, MessageManager::Sender::IO);
    }
}
