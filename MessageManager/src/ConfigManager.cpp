#include "../include/ConfigManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager()
{
    this->LoadConfig();
}

// TODO: refactor
void ConfigManager::LoadConfig()
{
    std::string line;
    std::ifstream configFile(CONFIG_PATH);

    if(!configFile.is_open())
    {
        std::cerr << "ERROR: Unable to read from config file" << std::endl << std::flush;
        std::exit(EXIT_FAILURE);
    }

    while(getline(configFile, line))
    {
        if(line == "\n" || line == "\r")
        {
            continue;
        }

        line = ConfigManager::RemoveNewLine(line);

        if(line == ConfigManager::LOG_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->logPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::STATS_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->statsPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::MAP_PIPE_IDENTIFIER)
        {
            getline(configFile, line);
            this->mapPipe = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::IO_KEY_IDENTIFIER)
        {
            getline(configFile, line);
            this->ioKey = stoi(ConfigManager::RemoveNewLine(line), nullptr, 10);
            continue;
        }

        if(line == ConfigManager::GAME_KEY_IDENTIFIER)
        {
            getline(configFile, line);
            this->gameKey = stoi(ConfigManager::RemoveNewLine(line), nullptr, 10);
            continue;
        }

        if(line == ConfigManager::PERMISSION_IDENTIFIER)
        {
            getline(configFile, line);
            this->mode = stoi(ConfigManager::RemoveNewLine(line), nullptr, 8);
            continue;
        }

        if(line == ConfigManager::GM_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->gameManagerPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::IO_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->ioPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::LOG_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->logPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::MAP_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->mapPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::STATS_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->statsPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::PLAYER_ROBOTS_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->playerRobotsPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::ENEMY_ROBOTS_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->enemyRobotsPath = ConfigManager::RemoveNewLine(line);
            continue;
        }

        if(line == ConfigManager::PICTURE_PATH_IDENTIFIER)
        {
            getline(configFile, line);
            this->picturePath = ConfigManager::RemoveNewLine(line);
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

    return string;
}
