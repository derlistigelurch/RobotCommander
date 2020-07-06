#include <iostream>
#include <fstream>

#include "../../MapDisplay/include/Colors.h"
#include "../../MessageManager/include/ConfigManager.h"

#define PLAYER 'P'
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
        std::ifstream pipe(ConfigManager().statsPipe);

        if(!pipe.is_open())
        {
            std::cerr << "ERROR: Unable to read from pipe" << std::endl << std::flush;
            std::exit(EXIT_FAILURE);
        }

        while(getline(pipe, line))
        {
            // P|E:ID:SYMBOL:NAME:HEALTH:MOVEMENT_SPEED:DAMAGE:ATTACK_RADIUS:DESCRIPTION
            line = ConfigManager::RemoveNewLine(line);

            if(line == "shutdown")
            {
                pipe.close();
                return EXIT_SUCCESS;
            }

            char color = line.substr(0, pos = line.find(DELIMITER))[0];
            std::string bgColor = BG_RED;
            line.erase(0, pos + 1);

            if(color == PLAYER)
            {
                bgColor = BG_BLUE;
            }

            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "ID:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "SYMBOL:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "NAME:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "HEALTH:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "SPEED:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "DAMAGE:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "ATTACK_RADIUS:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
            std::cout << ESCAPE << bgColor << SEPARATOR << FG_BLACK << END_ESCAPE << "DESCRIPTION:" << RESET << " "
                      << GetValue(line) << std::flush << std::endl;
        }

        pipe.close();
    }

    return EXIT_SUCCESS;
}

