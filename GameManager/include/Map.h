#ifndef GAMEMANAGER_MAP_H
#define GAMEMANAGER_MAP_H

#include <vector>
#include <string>
#include <fstream>

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

    int height;
    int width;
    std::string path;
    std::vector<std::vector<char>> grid;

public:
    /**
     * Creates a new map with a given path to a .map file
     * @param path absolute or relative path to a valid .map file
     */
    explicit Map(std::string path);

    ~Map();

    /**
     * Transforms the 2D grid into a 1D string
     * @return returns a string with all map tiles (e.g. "MMMMMGGGGGF")
     */
    std::string Draw();
};


#endif //GAMEMANAGER_MAP_H
