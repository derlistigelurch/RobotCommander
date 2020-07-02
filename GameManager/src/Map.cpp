#include "Header/Map.h"

#include <utility>
#include <fstream>
#include <iostream>

Map::Map(std::string path)
{
    this->path = std::move(path);
    this->CreateGrid();
    this->LoadGrid();
}

Map::~Map()
{
    this->DeleteGrid();
}

void Map::CreateGrid()
{
    for(int i = 0; i < this->width; i++)
    {
        this->grid.emplace_back(this->height);
    }
}

void Map::LoadGrid()
{
    std::string line;
    std::ifstream map(this->path);

    if(map.is_open())
    {
        while(getline(map, line))
        {
            // std::cout << line;
        }
        map.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to read map from " << this->path << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Map::DeleteGrid()
{
    for(auto &v : this->grid)
    {
        v.clear();
    };
    this->grid.clear();
}

std::string Map::Draw()
{
    std::string map;
    for(auto &v : this->grid)
    {
        for(auto &c : v)
        {
            map += c;
        }
        map += "\n";
    }

    return map;
}
