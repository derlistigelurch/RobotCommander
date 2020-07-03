#include "../include/ScreenManager.h"

void ScreenManager::Exit()
{

}

std::string ScreenManager::ShowMainScreen()
{
    return " ____       _           _   \n"
           "|  _ \\ ___ | |__   ___ | |_ \n"
           "| |_) / _ \\| '_ \\ / _ \\| __|\n"
           "|  _ < (_) | |_) | (_) | |_ \n"
           "|_| \\_\\___/|_.__/ \\___/ \\__|\n"
           "  ____                                          _           \n"
           " / ___|___  _ __ ___  _ __ ___   __ _ _ __   __| | ___ _ __ \n"
           "| |   / _ \\| '_ ` _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\ '__|\n"
           "| |__| (_) | | | | | | | | | | | (_| | | | | (_| |  __/ |   \n"
           " \\____\\___/|_| |_| |_|_| |_| |_|\\__,_|_| |_|\\__,_|\\___|_| \n\n"
           "1 - Fight\n"
           "2 - Workshop\n"
           "3 - Exit\n";
}

void ScreenManager::FightMenu()
{
    std::cout << "1 - Move" << std::endl;
    std::cout << "2 - Attack" << std::endl;
    std::cout << "3 - Retreat" << std::endl << std::endl;
}
