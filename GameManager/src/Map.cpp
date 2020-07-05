#include "../include/Map.h"

#include <utility>
#include <iostream>

Map::Map(std::string path)
{
    this->path = std::move(path);
    this->SetDimensions();
    this->SetNumberOfRobots();
    this->CreateGrid();
    this->LoadGrid();
}

Map::~Map()
{
    this->DeleteGrid();
}

void Map::SetDimensions()
{
    std::string line;
    std::fstream map(this->path);

    if(!map.is_open())
    {
        std::cerr << "ERROR: Unable to read map from " << this->path << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int pos = 0;

    getline(map, line);
    this->width = stoi(line.substr(0, (pos = line.find(DELIMITER))), nullptr, 10);
    this->height = stoi(line.substr(pos + 1, line.length()), nullptr, 10);

    map.close();

}

void Map::CreateGrid()
{
    for(int i = 0; i < this->height; i++)
    {
        this->grid.emplace_back();
    }
}

void Map::LoadGrid()
{
    std::string line;
    std::ifstream map(this->path);

    if(!map.is_open())
    {
        std::cerr << "ERROR: Unable to read map from " << this->path << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int y = 0;
    getline(map, line);
    getline(map, line);

    while(getline(map, line))
    {
        for(auto &c : line)
        {
            if(c == '\r' || c == '\n')
            {
                continue;
            }
            this->grid[y].push_back(c);
        }
        y++;
    }

    map.close();
}

void Map::DeleteGrid()
{
    for(auto &row : this->grid)
    {
        row.clear();
    }

    this->grid.clear();
}

std::string Map::Draw()
{
    std::string map;
    for(auto &row : this->grid)
    {
        for(auto &c : row)
        {
            map += c;
        }
        map += "\n";
    }

    return map;
}

void Map::SetNumberOfRobots()
{
    std::string line;
    std::fstream map(this->path);

    if(!map.is_open())
    {
        std::cerr << "ERROR: Unable to read map from " << this->path << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int pos = 0;

    getline(map, line);
    getline(map, line);

    this->playerCount = stoi(line.substr(0, (pos = line.find(DELIMITER))), nullptr, 10);
    this->enemyCount = stoi(line.substr(pos + 1, line.length()), nullptr, 10);

    if(this->enemyCount < 0 || this->enemyCount > 10 || this->playerCount < 0 && this->playerCount > 10)
    {
        std::cerr << "ERROR: Invalid number of robots " << std::endl;
        std::exit(EXIT_FAILURE);
    }

    map.close();
}
