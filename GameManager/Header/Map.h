#ifndef GAMEMANAGER_MAP_H
#define GAMEMANAGER_MAP_H

#include <vector>
#include <string>

class Map
{
private:
    void CreateGrid();

    void FillGrid();

    void DeleteGrid();

    int height;
    int width;
    std::vector<std::vector<char>> grid;

public:
    Map(int width, int height);

    ~Map();

    std::string Draw();
};


#endif //GAMEMANAGER_MAP_H
