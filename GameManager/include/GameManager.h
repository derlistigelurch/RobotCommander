#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "Map.h"

#define FILE_EXISTS 17

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

    /**
     * Initializes private variables
     */
    void Initialize();

    int playerCount;
    int enemyCount;
    std::string path;
    std::string mapPipe;
    const __mode_t PIPE_MODE = 0600;
    Map *map;

public:
    GameManager();

    ~GameManager();

    /**
     * Parses the input and sends it to the correct receiver
     * @param string - User input
     * @return returns EXIT_SUCCESS(0) on success otherwise EXIT_FAILURE(1)
     */
    int Input(std::string string);

    void Fight();
};


#endif //GAMEMANAGER_GAMEMANAGER_H
