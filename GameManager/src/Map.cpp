#include "../include/Map.h"

#include <utility>
#include <fstream>
#include <iostream>

Map::Map(std::string path)
{
    this->path = std::move(path);
    this->getDimensions();
    this->CreateGrid();
    this->LoadGrid();
}

Map::~Map()
{
    this->DeleteGrid();
}

void Map::getDimensions()
{
    std::string line;
    std::ifstream map(this->path);

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
    // skip dimensions
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
    };
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
