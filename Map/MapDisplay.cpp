#include <iostream>
#include <fstream>

int main()
{
    while(true)
    {
        std::string line;
        std::ifstream pipe("../../GameManager/cmake-build-debug/mapPipe");

        if(pipe.is_open())
        {
            while(getline(pipe, line))
            {
                std::cout << line << std::endl << std::flush;
            }
            pipe.close();
        }
        else
        {
            std::cerr << "ERROR: Unable to read from config file";
            std::exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}