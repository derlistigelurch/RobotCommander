#include "../include/ConfigManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager()
{
    this->LoadConfig();
}

void ConfigManager::LoadConfig()
{
    std::string line;
    std::ifstream configFile("../../config/RobotCommander.config");

    if(!configFile.is_open())
    {
        std::cerr << "ERROR: Unable to read from config file";
        std::exit(EXIT_FAILURE);
    }

    while(getline(configFile, line))
    {
        if(line == "\n" || line == "\r")
        {
            continue;
        }

        line = ConfigManager::RemoveNewLine(line);

        if(line == ConfigManager::IO_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->ioPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::MAP_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->mapPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::WORKSHOP_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->workshopPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::IO_KEY_IDENTIFIER)
        {
            getline(configFile, line);
            this->ioKey = stoi(ConfigManager::RemoveNewLine(line), nullptr, 10);
            continue;
        }
        if(line == ConfigManager::PERMISSION_IDENTIFIER)
        {
            getline(configFile, line);
            this->mode = stoi(ConfigManager::RemoveNewLine(line), nullptr, 8);
            continue;
        }
    }
    configFile.close();
}

std::string ConfigManager::RemoveNewLine(std::string string)
{
    if(string.empty() || (string[string.length() - 1] != '\n' && string[string.length() - 1] != '\r'))
    {
        return string;
    }

    if(string[string.length() - 1] == '\n')
    {
        string.erase(std::remove(string.begin(), string.end(), '\n'), string.end());
        return string;
    }

    if(string[string.length() - 1] == '\r')
    {
        string.erase(std::remove(string.begin(), string.end(), '\r'), string.end());
        return string;
    }
}