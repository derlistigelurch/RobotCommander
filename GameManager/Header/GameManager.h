#ifndef GAMEMANAGER_GAMEMANAGER_H
#define GAMEMANAGER_GAMEMANAGER_H


#include <string>

class GameManager
{
public:
    GameManager();

    int writeToPipe();

    void createPipe();

    void deletePipe();

    void loadConfig();

    void start();

    void exit();

    std::string mapPipe;

    const __mode_t PIPE_MODE = 0600;
};


#endif //GAMEMANAGER_GAMEMANAGER_H
