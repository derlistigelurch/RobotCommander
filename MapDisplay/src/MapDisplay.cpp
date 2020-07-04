#include <iostream>
#include <fstream>

#include "../include/TileTypes.h"
#include "../include/Colors.h"

int main()
{
    while(true)
    {
        std::string line;
        std::ifstream pipe("../../MessageManager/cmake-build-debug/mapPipe");

        if(!pipe.is_open())
        {
            std::cerr << "ERROR: Unable to read from pipe" << std::endl << std::flush;
            std::exit(EXIT_FAILURE);
        }

        while(getline(pipe, line))
        {
            for(char &c : line)
            {
                switch(c)
                {
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
