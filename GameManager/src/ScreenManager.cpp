#include "../include/ScreenManager.h"

void ScreenManager::ShowMainScreen()
{
    std::cout << " ____       _           _   \n"
                 "|  _ \\ ___ | |__   ___ | |_ \n"
                 "| |_) / _ \\| '_ \\ / _ \\| __|\n"
                 "|  _ < (_) | |_) | (_) | |_ \n"
                 "|_| \\_\\___/|_.__/ \\___/ \\__|\n"
                 "  ____                                          _           \n"
                 " / ___|___  _ __ ___  _ __ ___   __ _ _ __   __| | ___ _ __ \n"
                 "| |   / _ \\| '_ ` _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\ '__|\n"
                 "| |__| (_) | | | | | | | | | | | (_| | | | | (_| |  __/ |   \n"
                 " \\____\\___/|_| |_| |_|_| |_| |_|\\__,_|_| |_|\\__,_|\\___|_| \n"
              << std::endl << std::flush;
}

void ScreenManager::ShowMainMenu()
{
    std::cout << "1 - Fight\n"
                 "2 - Workshop\n"
                 "3 - Exit\n"
              << std::endl << std::flush;
}

void ScreenManager::ShowFightScreen()
{
    std::cout << " _____ _       _     _     __  __           _      \n"
                 "|  ___(_) __ _| |__ | |_  |  \\/  | ___   __| | ___ \n"
                 "| |_  | |/ _` | '_ \\| __| | |\\/| |/ _ \\ / _` |/ _ \\\n"
                 "|  _| | | (_| | | | | |_  | |  | | (_) | (_| |  __/\n"
                 "|_|   |_|\\__, |_| |_|\\__| |_|  |_|\\___/ \\__,_|\\___|\n"
                 "         |___/\n"
              << std::endl << std::flush;
}

void ScreenManager::ShowFightMenu()
{
    std::cout << "1 - Move\n"
                 "2 - Attack\n"
                 "3 - Retreat\n"
              << std::endl << std::flush;
}
