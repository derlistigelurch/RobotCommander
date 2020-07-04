#include "../include/GameManager.h"

#include <unistd.h>

GameManager::GameManager()
{
    this->playerCount = 0;
    this->enemyCount = 0;
    this->map = nullptr;

    this->Initialize();
}

GameManager::~GameManager()
{
    delete this->map;
}

void GameManager::Fight()
{
    while(true)
    {
        int input = 0;
        std::cin >> input;
        switch(input)
        {
            case MOVE:
                std::cout << "move" << std::endl;
                break;
            case ATTACK:
                std::cout << "attack" << std::endl;
                break;
            case RETREAT:
                std::cout << "retreat" << std::endl;
                return;
            default:
                std::cout << "move" << std::endl;
                break;
        }
    }
}

std::string GameManager::ToLower(std::string string)
{
    for(auto &c : string)
    {
        c = std::tolower(c);
    }

    return string;
}

void GameManager::Initialize()
{
    std::string errorMessage;
    this->GetMessageQueue(GameManager::Sender::GAME);

    ScreenManager::ShowFightScreen();
    this->ShowConfiguration();
    usleep(100);

    while(true)
    {
        this->SendMessage(1, errorMessage + "Enter a valid path to your map\n", GameManager::Sender::GAME);
        std::fstream file(this->path = this->ReceiveMessage(GameManager::Sender::GAME).text);

        if(file.is_open())
        {
            this->map = new Map(this->path);
            errorMessage = "";
            break;
        }

        errorMessage = "ERROR: Invalid path\n\n";
    }

    ScreenManager::ShowFightScreen();
    this->ShowConfiguration();

    while(true)
    {
        this->SendMessage(1, errorMessage + "Enter the number of player robots\n", GameManager::Sender::GAME);
        try
        {
            this->playerCount = std::stoi(this->ReceiveMessage(GameManager::Sender::GAME).text, nullptr, 10);
        }
        catch(const std::exception &e)
        {
            errorMessage = "ERROR: Invalid symbol\n\n";
            continue;
        }

        if(this->playerCount > 0 && this->playerCount < 10)
        {
            errorMessage = "";
            break;
        }

        errorMessage = "ERROR: Invalid number of players\n\n";
    }

    ScreenManager::ShowFightScreen();
    this->ShowConfiguration();

    while(true)
    {
        this->SendMessage(1, errorMessage + "Enter the number of enemy robots\n", GameManager::Sender::GAME);
        try
        {
            this->enemyCount = std::stoi(this->ReceiveMessage(GameManager::Sender::GAME).text, nullptr, 10);
        }
        catch(const std::exception &e)
        {
            errorMessage = "ERROR: Invalid symbol\n\n";
            errorMessage = "";
            continue;
        }

        if(this->enemyCount > 0 && this->enemyCount < 10)
        {
            break;
        }

        errorMessage = "ERROR: Invalid number of enemies\n\n";
    }

    ScreenManager::ShowFightScreen();
    this->ShowConfiguration();
}

void GameManager::ShowConfiguration() const
{
    std::cout << "Map Path: " << this->path << std::endl;
    std::cout << "Number of Players: ";
    if(this->playerCount > 1 && this->playerCount < 10)
    {
        std::cout << this->playerCount;
    }

    std::cout << std::endl << "Number of Players: ";
    if(this->enemyCount > 1 && this->enemyCount < 10)
    {
        std::cout << this->enemyCount;
    }

    std::cout << std::endl;
}

std::string GameManager::DrawMap() const
{
    return this->map->Draw();
}
