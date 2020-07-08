#include <iostream>
#include <fstream>

#include "../include/TileTypes.h"
#include "../include/Colors.h"
#include "../../MessageManager/include/ConfigManager.h"

int main()
{
    while(true)
    {
        std::string line;
        std::ifstream pipe(ConfigManager().mapPipe);

        std::cout << "\033[2J\033[1;1H";

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

            for(char &c : line)
            {
                switch(c)
                {
                    case (char) TileTypes::SPAWN:
                        std::cout << ESCAPE << BG_LIGHT_GREEN << SEPARATOR << FG_BLACK << END_ESCAPE << 'G' << RESET;
                        break;

                    case (char) TileTypes::PLAYER:
                        std::cout << ESCAPE << BG_BLACK << SEPARATOR << FG_LIGHT_GREY << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::ENEMY:
                        std::cout << ESCAPE << BG_RED << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::MOUNTAIN:
                        std::cout << ESCAPE << BG_YELLOW << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::WATER:
                        std::cout << ESCAPE << BG_BLUE << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::GRASS:
                        std::cout << ESCAPE << BG_LIGHT_GREEN << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::BUILDING:
                        std::cout << ESCAPE << BG_GREY << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    case (char) TileTypes::FOREST:
                        std::cout << ESCAPE << BG_GREEN << SEPARATOR << FG_BLACK << END_ESCAPE << c << RESET;
                        break;

                    default:
                        std::cerr << "ERROR: Unrecognised character" << std::endl;
                        exit(EXIT_FAILURE);
                }
            }

            std::cout << std::endl << std::flush;
        }

        pipe.close();
    }

    return EXIT_SUCCESS;
}
