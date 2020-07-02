#include <iostream>
#include <getopt.h>

#include "include/GameManager.h"

const struct option longOptions[] =
        {
                {"help", no_argument, nullptr, 'h'},
                {"map", required_argument, nullptr, 'm'},
                {"player", required_argument, nullptr, 'p'},
                {"enemy", required_argument, nullptr, 'e'}
        };

void PrintUsage()
{
    fprintf(stderr, "Usage: gridserver –x NUM –y NUM\n");
    std::cout << "Usage: robotcommander -x NUM -y NUM -p NUM -e NUM" << std::endl;
    std::cout << "\t-m, --map\t\trelative or absolute path to the .map file" << std::endl;
    std::cout << "\t-p, --player\tset number of player robots max. 9" << std::endl;
    std::cout << "\t-e, --enemy\t\tset number of enemy robots max. 9" << std::endl;
    std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c = 0;
    int optionMCounter = 0;
    int optionPCounter = 0;
    int optionECounter = 0;

    std::string path;
    int playerCount = 0;
    int enemyCount = 0;

    int optionIndex = 0;

    while((c = getopt_long(argc, argv, "hm:p:e:", longOptions, &optionIndex)) != EOF)
    {
        switch(c)
        {
            case 'h':
                PrintUsage();
                break;

            case 'm':
                if(optionMCounter)
                {
                    PrintUsage();
                }
                optionMCounter++;
                path = optarg;
                break;

            case 'p':
                if(optionPCounter)
                {
                    PrintUsage();
                }
                optionPCounter++;
                playerCount = std::stoi(optarg, nullptr, 10);
                break;

            case 'e':
                if(optionECounter)
                {
                    PrintUsage();
                }
                optionECounter++;
                enemyCount = std::stoi(optarg, nullptr, 10);
                break;

            default:
                PrintUsage();
                break;
        }
    }

    if(optind != 7 || argc != 7)
    {
        PrintUsage();
    }

    auto *gameManager = new GameManager(new Map(path), playerCount, enemyCount);

    int input = 0;
    while(true)
    {
        std::cin >> input;
        if((int) input == 0)
        {
            break;
        }
        std::string string;
        std::cin >> string;
        gameManager->Input(string);
    }

    delete gameManager;
    return EXIT_SUCCESS;
}
