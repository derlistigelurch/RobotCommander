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
     * Converts a string to lowercase
     * @param string - input
     * @return returns the converted string
     */
    std::string ToLower(std::string string);

    /**
     * Converts a string to uppercase
     * @param string - input
     * @return returns the converted string
     */
    std::string ToUpper(std::string string);

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

    /**
     * Sends shutdown message to a given display
     * @param display - Identifier of the display pipe
     */
    void CloseDisplay(const std::string &display) const;

    /**
     * Transforms a 2D grid into a 1D string
     * @param grid - 2D grid which contains the characters of the map
     * @return returns a string with all map tiles (e.g. "MMMMMGGGGGF")
     */
    std::string ToString(const std::vector<std::vector<char>> &grid);

    /**
     * Prints the manual of the game
     */
    void PrintManual() const;

    /**
     * Splits a given string into its parts and returns the value on every call
     * @param line
     * @return Returns the first occurrence of string
     */
    std::string GetValue(std::string &line);

    Robot *GetActiveRobot(const std::string &line);

    void ResetActionPoints();

    /**
     * Checks if a robot can move in a given direction
     * @param robot
     * @param direction
     * @return returns the movement costs or ERR_NOT_ENOUGH_AP(29) if robot has not enough AP or ERR_MOVE_BLOCKED(32)
     * if movement is blocked
     */
    int CanMove(Robot robot, Directions direction);

    int playerCount;
    int enemyCount;

    std::string path;

    Map *map;

    std::vector<Robot *> players;
    std::vector<Robot *> enemies;

    static const int MOVEMENT_COST = 1;
    static const int ERR_NOT_ENOUGH_AP = 29;
    static const int ERR_MOVE_BLOCKED = 32;

    static const char DELIMITER = ':';
    static const char MOVE = 'M';
    static const char ATTACK = 'A';
    static const char HELP = 'H';
    static const char SHOW = 'S';
    static const char RETREAT = 'R';
    static const char END_TURN = 'E';

    inline static const std::string PLAYER = "PLAYER";
    inline static const std::string ENEMY = "ENEMY";
    inline static const std::string ID = "ID";
    inline static const std::string ATTACK_RADIUS = "ATTACK_RADIUS";
    inline static const std::string HEALTH = "HEALTH";
    inline static const std::string ACTION_POINTS = "ACTION_POINTS";
    inline static const std::string DAMAGE = "DAMAGE";
    inline static const std::string SYMBOL = "SYMBOL";
    inline static const std::string NAME = "NAME";
    inline static const std::string DESCRIPTION = "DESCRIPTION";
    inline static const std::string SHUTDOWN = "shutdown";

public:
    GameManager();

    ~GameManager();

    /**
     * Starts the Fight
     */
    void Run();

    /**
     * Calls the draw function of the map
     * @return returns the current map as a string
     */
    std::string DrawMap();

    /**
     * Loads all robots from the .save file
     * @param identifier - string to decide which .save file should be loaded
     */
    void LoadRobots(const std::string &identifier);
};


#endif //GAMEMANAGER_GAMEMANAGER_H
