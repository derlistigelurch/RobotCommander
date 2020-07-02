#include "Header/GameManager.h"

#include <utility>

GameManager::GameManager(Map *map, int players, int enemies)
{
    this->map = map;
    this->LoadConfig();
    this->CreatePipe();
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
    if(mkfifo(this->mapPipe.c_str(), this->PIPE_MODE) == -1)
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

void GameManager::Start()
{

}

void GameManager::Exit()
{

}

void GameManager::LoadConfig()
{
    std::string line;
    std::ifstream configFile("../RobotCommander.config");

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
    std::string input = this->ToLower(string);
    if(input == "show")
    {

    }
    return EXIT_SUCCESS;
}

std::string GameManager::ToLower(std::string string)
{
    for(auto &c : string)
    {
        c = std::tolower(c);
    }

    return string;
}
