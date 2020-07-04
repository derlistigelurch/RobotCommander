#ifndef MESSAGEMANAGER_CONFIGMANAGER_H
#define MESSAGEMANAGER_CONFIGMANAGER_H

#include <string>

class ConfigManager
{
public:
    ConfigManager();

    ~ConfigManager() = default;

    /**
     * Loads the content of the RobotCommander.config
     */
    void LoadConfig();

    std::string ioPipe;
    std::string workshopPipe;
    std::string mapPipe;

    int ioKey;
    int gameKey;
    int workshopKey;

    __mode_t mode;

    inline static const std::string IO_PIPE_IDENTIFIER = "IO";
    inline static const std::string WORKSHOP_PIPE_IDENTIFIER = "WORKSHOP";
    inline static const std::string MAP_PIPE_IDENTIFIER = "MAP";
    inline static const std::string IO_KEY_IDENTIFIER = "IO_KEY";
    inline static const std::string GAME_KEY_IDENTIFIER = "GAME_KEY";
    inline static const std::string PERMISSION_IDENTIFIER = "PERMISSION";

private:
    static std::string RemoveNewLine(std::string string);
};


#endif //MESSAGEMANAGER_CONFIGMANAGER_H
