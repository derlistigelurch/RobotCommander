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
    std::string mapPipe;
    const __mode_t PIPE_MODE = 0600;
    Map *map;

public:
    explicit GameManager(Map *map);

    ~GameManager();

    int WriteToPipe();

    void CreatePipe();

    void DeletePipe();

    void LoadConfig();

    void Start();

    void Exit();
};


#endif //GAMEMANAGER_GAMEMANAGER_H
