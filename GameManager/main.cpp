#include <iostream>
#include <getopt.h>

#include "Header/GameManager.h"

const struct option longOptions[] =
        {
                {"help",   no_argument,       0, 'h'},
                {"width",  required_argument, 0, 'x'},
                {"height", required_argument, 0, 'y'},
                {"player", required_argument, 0, 'p'},
                {"enemy",  required_argument, 0, 'e'}
        };

void PrintUsage()
{
    fprintf(stderr, "Usage: gridserver –x NUM –y NUM\n");
    std::cout << "Usage: robotcommander -x NUM -y NUM -p NUM -e NUM" << std::endl;
    std::cout << "\t-x, --width\t\tset width" << std::endl;
    std::cout << "\t-y, --height\tset height" << std::endl;
    std::cout << "\t-p, --player\tset number of player robots max. 9" << std::endl;
    std::cout << "\t-e, --enemy\t\tset number of enemy robots max. 9" << std::endl;
    std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c = 0;
    int optionXCounter = 0;
    int optionYCounter = 0;
    int optionPCounter = 0;
    int optionECounter = 0;

    int width = 0;
    int height = 0;
    int playerCount = 0;
    int enemyCount = 0;

    int optionIndex = 0;

    while((c = getopt_long(argc, argv, "hx:y:p:e:", longOptions, &optionIndex)) != EOF)
    {
        switch(c)
        {
            case 'h':
                PrintUsage();
                break;

            case 'x':
                if(optionXCounter)
                {
                    PrintUsage();
                }
                optionXCounter++;
                width = std::stoi(optarg, nullptr, 10);
                break;

            case 'y':
                if(optionYCounter)
                {
                    PrintUsage();
                }
                optionYCounter++;
                height = std::stoi(optarg, nullptr, 10);
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

    if(optind != 9 || argc != 9)
    {
        PrintUsage();
    }

    auto *gameManager = new GameManager(new Map(width, height), playerCount, enemyCount);

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
