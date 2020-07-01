#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "Header/GameManager.h"

GameManager::GameManager()
{
    this->loadConfig();
    this->createPipe();
}

int GameManager::writeToPipe()
{
    std::ofstream pipe(this->mapPipe);

     if(pipe.is_open())
     {
         // TODO Send Map to Map
         pipe << "This is a line." << std::endl << std::flush;
         pipe << "This is another line." << std::endl << std::flush;
         pipe.close();
     }
     else
     {
         std::cerr << "ERROR: Unable to open file";
         std::exit(EXIT_FAILURE);
     }
}

void GameManager::createPipe()
{
    if(mkfifo(this->mapPipe.c_str(), this->PIPE_MODE) == -1)
    {
        std::cerr << "ERROR: Unable to create the pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::deletePipe()
{
    if(std::remove(this->mapPipe.c_str()) != EXIT_SUCCESS)
    {
        std::cerr << "ERROR: Unable to delete pipe" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GameManager::start()
{

}

void GameManager::exit()
{

}

void GameManager::loadConfig()
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
