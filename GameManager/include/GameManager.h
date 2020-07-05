#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H


#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "Map.h"
#include "ScreenManager.h"
#include "Player.h"
#include "Enemy.h"
#include "../../IOManager/include/Sender.h"

class GameManager : public Sender
{
private:
    /**
     * Convert a string to lowercase
     * @param string - input
     * @return returns the converted string
     */
    std::string ToLower(std::string string);

    /**
     * Initializes private variables
     */
    void Initialize();

    /**
     * prints the current map path, number of players/enemies
     */
    void ShowConfiguration() const;

    /**
     * Deletes the both robot vectors
     */
    void DeleteRobots();

    int playerCount;
    int enemyCount;

    std::string path;

    Map *map;

    std::vector<Robot *> players;
    std::vector<Robot *> enemies;

    static const char DELIMITER = ':';

    inline static const std::string PLAYER = "PLAYER";
    inline static const std::string ENEMY = "ENEMY";
    inline static const std::string ID = "ID";
    inline static const std::string ATTACK_RADIUS = "ATTACK_RADIUS";
    inline static const std::string HEALTH = "HEALTH";
    inline static const std::string MOVEMENT_SPEED = "MOVEMENT_SPEED";
    inline static const std::string DAMAGE = "DAMAGE";
    inline static const std::string SYMBOL = "SYMBOL";
    inline static const std::string NAME = "NAME";
    inline static const std::string DESCRIPTION = "DESCRIPTION";
    inline static const std::string MOVE = "1";
    inline static const std::string ATTACK = "2";
    inline static const std::string HELP = "3";
    inline static const std::string RETREAT = "4";

public:
    GameManager();

    ~GameManager();

    /**
     *
     */
    void Fight();

    /**
     * Calls the draw function of the map
     * @return returns the current map as a string
     */
    std::string DrawMap() const;

    /**
     * Loads all robots from the .save file
     * @param identifier - string to decide which .save file should be loaded
     */
    void LoadRobots(const std::string &identifier);
};


#endif //GAMEMANAGER_GAMEMANAGER_H
