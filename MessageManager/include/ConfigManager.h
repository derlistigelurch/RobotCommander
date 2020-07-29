#ifndef MESSAGEMANAGER_CONFIGMANAGER_H
#define MESSAGEMANAGER_CONFIGMANAGER_H

#include <string>

class ConfigManager
{
private:
    inline static const std::string CONFIG_PATH = "config/RobotCommander.config";

public:
    ConfigManager();

    ~ConfigManager() = default;

    /**
     * Loads the content of the RobotCommander.config
     */
    void LoadConfig();

    /**
     * removes the newline character from a string, returns the unchanged string if no newline character was found
     * @param string
     * @return Returns a string without the newline character
     */
    static std::string RemoveNewLine(std::string string);

    std::string mapPipe;
    std::string logPipe;
    std::string statsPipe;
    std::string gameManagerPath;
    std::string statsPath;
    std::string mapPath;
    std::string logPath;
    std::string ioPath;
    std::string playerRobotsPath;
    std::string enemyRobotsPath;
    std::string picturePath;

    int ioKey;
    int gameKey;

    __mode_t mode;

    inline static const std::string MAP_PIPE_IDENTIFIER = "MAP";
    inline static const std::string LOG_PIPE_IDENTIFIER = "LOG";
    inline static const std::string STATS_PIPE_IDENTIFIER = "STATS";
    inline static const std::string IO_KEY_IDENTIFIER = "IO_KEY";
    inline static const std::string GAME_KEY_IDENTIFIER = "GAME_KEY";
    inline static const std::string PERMISSION_IDENTIFIER = "PERMISSION";
    inline static const std::string GM_PATH_IDENTIFIER = "GAME_MANAGER_PATH";
    inline static const std::string MAP_PATH_IDENTIFIER = "MAP_PATH";
    inline static const std::string LOG_PATH_IDENTIFIER = "LOG_PATH";
    inline static const std::string STATS_PATH_IDENTIFIER = "STATS_PATH";
    inline static const std::string IO_PATH_IDENTIFIER = "IO_PATH";
    inline static const std::string PLAYER_ROBOTS_PATH_IDENTIFIER = "P_ROBOTS_PATH";
    inline static const std::string ENEMY_ROBOTS_PATH_IDENTIFIER = "E_ROBOTS_PATH";
    inline static const std::string PICTURE_PATH_IDENTIFIER = "PICTURE_PATH";
};


#endif //MESSAGEMANAGER_CONFIGMANAGER_H
