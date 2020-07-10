#include <iostream>
#include <fstream>

#include "../../MapDisplay/include/Colors.h"
#include "../../MessageManager/include/ConfigManager.h"

#define MOVE 'M'
#define ATTACK 'A'
#define RETREAT 'R'
#define DESTROY 'D'
#define WIN 'W'
#define LOSE 'L'
#define END_TURN 'E'
#define INFO 'I'
#define DELIMITER ':'

std::string GetValue(std::string &line)
{
    int pos = line.find(DELIMITER);
    std::string value = line.substr(0, pos);
    line.erase(0, pos + 1);
    return value;
}

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
            line = ConfigManager::RemoveNewLine(line);

            if(line == "shutdown")
            {
                pipe.close();
                return EXIT_SUCCESS;
            }

            char action = line.substr(0, pos = line.find(DELIMITER))[0];
            line.erase(0, pos + 1);

            switch(action)
            {
                case MOVE:
                    // M:R:OLD_POS:NEW_POS
                    std::cout << ESCAPE << BG_BLUE << SEPARATOR << FG_BLACK << END_ESCAPE << "MOVE:" << RESET << " "
                              << GetValue(line) << " moved from " << GetValue(line) << " to " << GetValue(line) << "."
                              << std::endl << std::flush;
                    break;

                case ATTACK:
                    // A:R:R:DMG
                    std::cout << ESCAPE << BG_GREEN << SEPARATOR << FG_BLACK << END_ESCAPE << "ATTACK:" << RESET << " "
                              << GetValue(line) << " attacked " << GetValue(line) << " and dealt " << GetValue(line)
                              << " damage." << std::endl << std::flush;
                    break;

                case DESTROY:
                    // D:R
                    std::cout << ESCAPE << BG_RED << SEPARATOR << FG_BLACK << END_ESCAPE << "DESTROY:" << RESET << " "
                              << GetValue(line) << " has been destroyed." << std::endl << std::flush;
                    break;

                case RETREAT:
                    // R:
                    std::cout << ESCAPE << BG_MAGENTA << SEPARATOR << FG_BLACK << END_ESCAPE << "RETREAT:" << RESET
                              << " Player retreated from the fight." << std::endl;
                    break;

                case END_TURN:
                    // E:TURN
                    std::cout << ESCAPE << BG_LIGHT_RED << SEPARATOR << FG_BLACK << END_ESCAPE << "END TURN "
                              << GetValue(line) << ":" << RESET << " AP have been restored" << std::endl << std::flush;
                    break;

                case WIN:
                    // W:
                    std::cout << ESCAPE << BG_YELLOW << SEPARATOR << FG_BLACK << END_ESCAPE << "WIN:" << RESET
                              << " Player won battle." << std::endl << std::flush;
                    break;

                case LOSE:
                    // L:
                    std::cout << ESCAPE << BG_YELLOW << SEPARATOR << FG_BLACK << END_ESCAPE << "LOSE:" << RESET
                              << " Player lost battle." << std::endl << std::flush;
                    break;

                case INFO:
                    // I:MESSAGE
                    std::cout << ESCAPE << BG_GREY << SEPARATOR << FG_BLACK << END_ESCAPE << "INFO:" << RESET
                              << " " << GetValue(line) << std::endl << std::flush;
                    break;

                default:
                    break;
            }
        }

        pipe.close();
    }

    return EXIT_SUCCESS;
}

