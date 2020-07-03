#include "../include/GameManager.h"

GameManager::GameManager()
{
    this->playerCount = 0;
    this->enemyCount = 0;
    this->map = nullptr;

    this->LoadConfig();
    this->CreatePipe();
    this->Initialize();
}

GameManager::~GameManager()
{
    this->DeletePipe();
    delete this->map;
}

void GameManager::WriteToPipe()
{
    std::ofstream pipe(this->mapPipe);

    if(pipe.is_open())
    {
        pipe << this->map->Draw();
        pipe.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to open file";
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::CreatePipe()
{
    if(mkfifo(this->mapPipe.c_str(), this->PIPE_MODE) == -1 && errno != ERRNO_FILE_EXISTS)
    {
        std::cerr << "ERROR: Unable to create the pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::DeletePipe()
{
    if(std::remove(this->mapPipe.c_str()) != EXIT_SUCCESS)
    {
        std::cerr << "ERROR: Unable to delete pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::LoadConfig()
{
    std::string line;
    std::ifstream configFile("../config/RobotCommander.config");

    if(configFile.is_open())
    {
        while(getline(configFile, line))
        {
            this->mapPipe = line;
        }
        configFile.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to read from config file";
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::Fight()
{
    while(true)
    {
        ScreenManager::FightMenu();
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
    while(true)
    {
        std::cout << "Enter a valid path to your map" << std::endl;
        std::cout << "_>> ";
        std::cin >> this->path;
        std::fstream f(this->path);
        if(f.is_open())
        {
            this->map = new Map(this->path);
            break;
        }

        std::cerr << "ERROR: Invalid path" << std::endl;
    }

    while(true)
    {
        std::cout << "Enter the number of player robots" << std::endl;
        std::cout << "_>> ";
        std::cin >> this->playerCount;
        if(this->playerCount > 0 && this->playerCount < 10)
        {
            break;
        }

        std::cerr << "ERROR: Invalid number of players" << std::endl;
    }

    while(true)
    {
        std::cout << "Enter the number of enemy robots" << std::endl;
        std::cout << "_>> ";
        std::cin >> this->enemyCount;
        if(this->enemyCount > 0 && this->enemyCount < 10)
        {
            break;
        }

        std::cerr << "ERROR: Invalid number of enemies" << std::endl;
    }

    this->WriteToPipe();
}
