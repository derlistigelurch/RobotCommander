#include <iostream>
#include <fstream>

#include "../../MapDisplay/include/Colors.h"
#include "../../MessageManager/include/ConfigManager.h"

#define MOVE 'M'
#define ATTACK 'A'
#define RETREAT 'R'
#define DELIMITER ':'

int main()
{
    while(true)
    {
        std::string line;
        int pos = 0;
        std::ifstream pipe(ConfigManager().logPipe);

        if(!pipe.is_open())
        {
            std::cerr << "ERROR: Unable to read from pipe" << std::endl << std::flush;
            std::exit(EXIT_FAILURE);
        }

        while(getline(pipe, line))
        {
            std::string token;

            line = ConfigManager::RemoveNewLine(line);

            char action = line.substr(0, pos = line.find(DELIMITER))[0];
            line.erase(0, pos + 1);

            switch(action)
            {
                case MOVE:
                {
                    // M:P:OLD_POS:NEW_POS
                    pos = line.find(DELIMITER);
                    std::string robot = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(DELIMITER);
                    std::string oldPos = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(DELIMITER);
                    std::string newPos = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    std::cout << ESCAPE << BG_BLUE << SEPARATOR << FG_BLACK << END_ESCAPE << "MOVE:" << RESET << " "
                              << robot << " moved from " << oldPos << " to " << newPos << "." << std::endl
                              << std::flush;
                    break;
                }

                case ATTACK:
                {
                    // A:P:DMG:E
                    pos = line.find(DELIMITER);
                    std::string player = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(DELIMITER);
                    std::string damage = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(DELIMITER);
                    std::string enemy = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    std::cout << BG_GREEN << SEPARATOR << FG_BLACK << END_ESCAPE << "ATTACK:" << RESET << " " << player
                              << " attacked " << enemy << " and dealt " << damage << " damage." << std::endl
                              << std::flush;
                    break;
                }

                case RETREAT:
                {
                    // R:
                    std::cout << "RETREAT" << ": " << "Player retreated from the fight." << std::endl;
                    break;
                }

                default:
                    break;
            }
        }

        pipe.close();
        return EXIT_SUCCESS;
    }
}

