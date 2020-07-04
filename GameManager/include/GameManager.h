#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H


#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "Map.h"
#include "ScreenManager.h"
#include "../../IOManager/include/Sender.h"

class GameManager : public Sender
{
private:
    /**
     * Convert a string to lowercase
     * @param string - Fight string
     * @return returns the converted string
     */
    std::string ToLower(std::string string);

    /**
     * Initializes private variables
     */
    void Initialize();

    void ShowConfiguration() const;

    int playerCount;
    int enemyCount;
    std::string path;
    Map *map;

    static const int MOVE = 1;
    static const int ATTACK = 2;
    static const int RETREAT = 3;

public:
    GameManager();

    ~GameManager();

    /**
     *
     */
    void Fight();

    std::string DrawMap() const;
};


#endif //GAMEMANAGER_GAMEMANAGER_H
