#include <memory>

#include "include/GameManager.h"
#include "../MessageManager/include/ConfigManager.h"

int main()
{
    std::shared_ptr<ConfigManager> configManager = std::make_shared<ConfigManager>();
    std::shared_ptr<GameManager> gameManager = std::make_shared<GameManager>();

    // auto *gameManager = new GameManager();
    system(("gnome-terminal -- " + configManager->mapPath).c_str());
    system(("gnome-terminal -- " + configManager->logPath).c_str());
    system(("gnome-terminal -- " + configManager->statsPath).c_str());

    gameManager->Run();
    return EXIT_SUCCESS;
}
