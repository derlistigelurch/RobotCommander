#include <iostream>

#include "include/GameManager.h"
#include "include/ScreenManager.h"
#include "../MessageManager/include/ConfigManager.h"

int main(int argc, char *argv[])
{
    system(("gnome-terminal -- " + ConfigManager().mapPath).c_str());
    // system(("gnome-terminal -- " + ConfigManager().logPath).c_str());
    // system(("gnome-terminal -- " + ConfigManager().statsPath).c_str());

    int input = 0;

    std::cout << ScreenManager::ShowFightScreen() << std::endl << std::flush;

    auto *gameManager = new GameManager();

    while(true)
    {
        gameManager->SendMessage(1, ScreenManager::ShowFightMenu(), GameManager::Sender::GAME);

        gameManager->WriteToPipe(gameManager->DrawMap(), GameManager::Sender::MAP);

        std::string content = gameManager->ReceiveMessage(GameManager::Sender::GAME).text;

        if(content == "3")
        {
            break;
        }
    }

    delete gameManager;
}
