#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "Map.h"

class GameManager
{
private:
    /**
     * Creates a new pipe in the directory which is stated in the RobotCommander.config
     */
    void CreatePipe();

    /**
     * Deletes the pipe
     */
    void DeletePipe();

    /**
     * Loads the content of the RobotCommander.config
     */
    void LoadConfig();

    /**
     * Write the content of the map to the pipe
     */
    void WriteToPipe();

    /**
     * Convert a string to lowercase
     * @param string - Input string
     * @return returns the converted string
     */
    std::string ToLower(std::string string);

    std::string mapPipe;
    const __mode_t PIPE_MODE = 0600;
    Map *map;

public:
    /**
     * Creates a new instance of the GameManager class
     * @param map - Map which stores the terrain and player/robot position
     * @param players - number of players max. 9
     * @param enemies - number of enemies max. 9
     */
    GameManager(Map *map, int players, int enemies);

    ~GameManager();

    /**
     * Parses the input and sends it to the correct receiver
     * @param string - User input
     * @return returns EXIT_SUCCESS(0) on success otherwise EXIT_FAILURE(1)
     */
    int Input(std::string string);

    void Start();

    void Exit();
};


#endif //GAMEMANAGER_GAMEMANAGER_H
