#ifndef GAMEMANAGER_MAP_H
#define GAMEMANAGER_MAP_H

#include <vector>
#include <string>

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
    void FillGrid();

    /**
     * Deletes the grid and free memory
     */
    void DeleteGrid();

    int height;
    int width;
    std::vector<std::vector<char>> grid;

public:
    /**
     * Creates a new map with the given width and height
     * @param width
     * @param height
     */
    Map(int width, int height);

    ~Map();

    /**
     * Transforms the 2D grid into a 1D string
     * @return returns a string with all map tiles (e.g. "MMMMMGGGGGF")
     */
    std::string Draw();
};


#endif //GAMEMANAGER_MAP_H
