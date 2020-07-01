#include "Header/Map.h"

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;

    this->CreateGrid();
    this->FillGrid();
}

Map::~Map()
{
    this->DeleteGrid();
}

void Map::CreateGrid()
{
    //this->grid = std::vector<char>();
    for(int i = 0; i < this->width; i++)
    {
        this->grid.emplace_back(this->height);
    }
}

void Map::FillGrid()
{
    for(int x = 0; x < this->width; x++)
    {
        for(int y = 0; y < this->height; y++)
        {
            this->grid[x][y] = 'F';
        }
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
