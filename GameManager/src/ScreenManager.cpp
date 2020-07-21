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
    std::cout << "F - Fight\n"
                 "W - Workshop\n"
                 "E - Exit\n"
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
    std::cout << "M - Move\t- M:R:N|E|S|W\n"
                 "A - Attack\t- A:R:R\n"
                 "S - Show\t- S:R\n"
                 "E - End turn\t- E\n"
                 "H - Help\t- S:R\n"
                 "R - Retreat\t- R\n"
              << std::endl << std::flush;
}

void ScreenManager::PrintManual()
{
    std::cout << "HELP" << std::endl
              << "Welcome to the ROBOT COMMANDER manual" << std::endl
              << "**** ROBOT STATS *****" << std::endl
              << " * ID:Id - random numeric value" << std::endl
              << " * NAME - name of the robot" << std::endl
              << " * SYMBOL - char which represents your robot on the map (P - Player, E - Enemy)" << std::endl
              << " * ACTION POINTS - Number of actions a robot can perform in one round" << std::endl
              << " * ATTACK RADIUS - Attack range of the robot" << std::endl
              << " * DAMAGE - number of d3(0,1,2, so not really a d3 ;)) rolled to determine the damage" << std::endl
              << " * DESCRIPTION - description of a robot" << std::endl
              << " * HEALTH - amount of damage a robot can take " << std::endl << std::endl
              << "**** FIGHT COMMANDS ****" << std::endl
              << " ** ** MOVE" << std::endl
              << " Move a robot one tile in any direction" << std::endl
              << " M:R:N|E|S|W" << std::endl
              << " * R -> Robot you want to move e.g. (P1, P2, P3)" << std::endl
              << " * N|E|S|W -> Direction the robot should go" << std::endl << std::endl
              << " ** ** ATTACK" << std::endl
              << " Attack a robot in range" << std::endl
              << " * A:R:R" << std::endl
              << " * R -> Attacking robot" << std::endl
              << " * R -> Target robot" << std::endl << std::endl
              << " ** ** SHOW" << std::endl
              << " Shows the stats of a robot on the StatsDisplay" << std::endl
              << " S:R" << std::endl
              << " * R -> Robot you want to examine" << std::endl << std::endl
              << " ** ** END TURN" << std::endl
              << " End your turn and restore all AP" << std::endl
              << " E" << std::endl << std::endl
              << " ** ** RETREAT" << std::endl
              << " Retreat from the fight" << std::endl
              << " R" << std::endl << std::endl
              << "** ** HELP" << std::endl
              << " Prints the manual" << std::endl
              << std::endl << std::flush;
}
