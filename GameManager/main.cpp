#include <iostream>

#include "include/GameManager.h"
#include "include/ScreenManager.h"
#include "../MessageManager/include/ConfigManager.h"

int main(int argc, char *argv[])
{
    auto configManager = new ConfigManager();

    system(("gnome-terminal -- " + configManager->mapPath).c_str());
    system(("gnome-terminal -- " + configManager->logPath).c_str());
    system(("gnome-terminal -- " + configManager->statsPath).c_str());

    auto *gameManager = new GameManager();

    gameManager->Fight();

    delete configManager;
    delete gameManager;

    return EXIT_SUCCESS;
}
