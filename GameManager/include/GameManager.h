#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H


#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <random>

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
     * Converts a character into a std::string
     * @param c
     * @return returns the character as string
     */
    std::string ToString(char c) const;

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

    /**
     * Returns a pointer to a robot that should perform the action
     * @param line - string which contains the id and the symbol of a robot
     * @return returns a pointer to the currently active robot
     */
    Robot *GetActiveRobot(const std::string &line);

    /**
     * Resets the Action Points (AP) of all robots
     */
    void ResetActionPoints();

    /**
     * Checks if a robot can move in a given direction
     * @param robot
     * @param direction
     * @return returns the movement costs or ERR_NOT_ENOUGH_AP(29) if robot has not enough AP or ERR_MOVE_BLOCKED(32)
     * if movement is blocked
     */
    int CanMove(Robot robot, Directions direction);

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

    /**
     * Deletes one robot based on the id and symbol, does nothing if robot not exists
     * @param symbol - symbol of the robot
     * @param id - id of the robot
     */
    void DeleteRobot(char symbol, int id);

    /**
     * Checks if a robot can attack another robot
     * @param robot
     * @param enemy
     * @return returns the damage dealt by the robot, returns ERR_OUT_OF_RANGE if enemy robot is not in range or
     * ERR_ATTACK_IS_BLOCKED if the enemy robot is out of sight
     */
    int CanAttack(Robot *robot, Robot *enemy);

    /**
     * Checks if a mountain is between the attacking robot and an enemy
     * @param robotPosition - position of the attacking robot
     * @param enemyPosition - position of the enemy robot
     * @param point
     * @return returns true if a mountain ('M') is found
     */
    bool IsAttackBlocked(Point robotPosition, Point enemyPosition, Point point);

    /**
     * Checks if an enemy robot is in range of an attacking robot
     * @param robotPosition - position of the attacking robot
     * @param enemyPosition - position of the enemy robot
     * @return returns true if an enemy robot is in range
     */
    bool IsInRange(Point robotPosition, Point enemyPosition);

    /**
     * calculates the distance to every enemy robot and returns a robot pointer to the nearest enemy robot
     * @param identifier - string identifier, player or enemy
     * @param position - start position
     * @return returns a robot pointer of the nearest enemy robot
     */
    Robot *GetNearestRobot(const std::string &identifier, Point position);

    void Attack(Robot *robot, Robot *enemy, int damage);

    int playerCount;
    int enemyCount;

    std::string path;

    Map *map;

    std::vector<std::string> robotPictures;

    std::vector<Robot *> players;
    std::vector<Robot *> enemies;

    static const int MOVEMENT_COST = 1;
    static const int ATTACK_COST = 1;
    static const int ERR_NOT_ENOUGH_AP = 29;
    static const int ERR_MOVE_BLOCKED = 32;
    static const int ERR_OUT_OF_RANGE = 33;
    static const int ERR_ATTACK_IS_BLOCKED = 34;
    static const int DESTROYED = 36;

    static const char DELIMITER = ':';
    static const char MOVE = 'M';
    static const char ATTACK = 'A';
    static const char HELP = 'H';
    static const char SHOW = 'S';
    static const char RETREAT = 'R';
    static const char END_TURN = 'E';

    inline static const std::string PLAYER = "P";
    inline static const std::string ENEMY = "E";
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

    void LoadPictures();
};


#endif //GAMEMANAGER_GAMEMANAGER_H
