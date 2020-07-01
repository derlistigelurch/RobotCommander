#include "Header/GameManager.h"

GameManager::GameManager(Map *map)
{
    this->map = map;
    this->LoadConfig();
    this->CreatePipe();
}

GameManager::~GameManager()
{
    delete this->map;
}

int GameManager::WriteToPipe()
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
