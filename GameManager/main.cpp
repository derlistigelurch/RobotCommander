#include <iostream>

#include "include/GameManager.h"
#include "include/ScreenManager.h"
#include "../MessageManager/include/ConfigManager.h"

int main(int argc, char *argv[])
{
    system(("gnome-terminal -- " + ConfigManager().mapPath).c_str());
    system(("gnome-terminal -- " + ConfigManager().logPath).c_str());
    // system(("gnome-terminal -- " + ConfigManager().statsPath).c_str());

    auto *gameManager = new GameManager();

    gameManager->Fight();

    delete gameManager;

    return EXIT_SUCCESS;
}
