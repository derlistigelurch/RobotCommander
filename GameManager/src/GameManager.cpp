#include "../include/GameManager.h"

#include <utility>

GameManager::GameManager()
{
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
    if(mkfifo(this->mapPipe.c_str(), this->PIPE_MODE) == -1 && errno != FILE_EXISTS)
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

int GameManager::Input(std::string string)
{
    std::string input = this->ToLower(std::move(string));

    if(input == "move")
    {
        // TODO: Move Robot around the map
        std::cout << input << std::endl;
        return EXIT_SUCCESS;
    }

    // TODO: extract player/enemy/action/direction from string
    if(input == "show")
    {
        // TODO: Show stats of the tile or robot
        std::cout << input << std::endl;
        return EXIT_SUCCESS;
    }

    if(input == "attack")
    {
        // TODO: Attack enemy Robot
        std::cout << input << std::endl;
        return EXIT_SUCCESS;
    }

    if(input == "retreat")
    {
        // TODO: End fight
        std::cout << input << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
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
