#include <iostream>
#include <unistd.h>

#include "include/Message.h"
#include "include/MessageManager.h"
#include "include/ConfigManager.h"
#include "../GameManager/include/ScreenManager.h"

int main()
{
    auto *messageManager = new MessageManager();

    system(("gnome-terminal -- " + ConfigManager().ioPath).c_str());

    messageManager->Run();

    delete messageManager;
}

// TODO:
//  Player attack (M)
//  Show Ascii image in the StatsDisplay
//  Write error messages to log file
//  Signal handling
//  Enemy movement
//  Enemy attack
//  Workshop
