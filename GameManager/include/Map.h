#ifndef GAMEMANAGER_MAP_H
#define GAMEMANAGER_MAP_H


#include <vector>
#include <string>
#include <fstream>
#include "Point.h"

class Map
{
private:
    /**
     * Creates a new grid which stores the terrain tiletypes
     */
    void CreateGrid();

    /**
     * Fills the grid with tiletypes (e.g. 'M' -> Mountain)
     */
    void LoadGrid();

    /**
     * Deletes the grid and free memory
     */
    void DeleteGrid();

    /**
     * Loads the Width and eight from a .map file
     */
    void SetDimensions();

    /**
     * Sets private playerCount and enemyCount variables
     */
    void SetNumberOfRobots();

    void SetSpawnPoints();

    int height;
    int width;

    std::string path;

    std::vector<std::vector<char>> grid;

    static const char DELIMITER = 'x';
    static const char SPAWN_POINT = 'S';

public:

    /**
     * Creates a new map with a given path to a .map file
     * @param path absolute or relative path to a valid .map file
     */
    explicit Map(const std::string &path);

    ~Map();

    std::vector<std::vector<char>> GetGrid();

    int playerCount;
    int enemyCount;

    std::vector<Point> playerSpawnPoints;
    std::vector<Point> enemySpawnPoints;
};


#endif //GAMEMANAGER_MAP_H
