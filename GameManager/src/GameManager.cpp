#include "../include/GameManager.h"
#include "../../MessageManager/include/ConfigManager.h"


GameManager::GameManager()
{
    this->playerCount = 0;
    this->enemyCount = 0;
    this->map = nullptr;

    this->Initialize();
}

GameManager::~GameManager()
{
    this->DeleteRobots();
    delete this->map;
}

void GameManager::Run()
{
    this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);
    //this->SendMessage(1, "dere", GameManager::Sender::GAME);

    while(true)
    {
        std::string content = this->ReceiveMessage(GameManager::Sender::GAME).text;

        // process input
        // Get current player
        if(content == ATTACK)
        {
            // check if enemy is in range
            // roll damage
            // reduce enemy health, if enemy is dead delete him
            // log output
        }

        if(content == MOVE)
        {
            // get active player
            // check if move action is possible
            // set robot position to new position
            // log output
            std::string oldPos = players[0]->position.ToString();
            this->players[0]->Move(Directions::EAST);
            this->WriteToPipe("M:P1:" + oldPos + ":" + this->players[0]->position.ToString(), GameManager::Sender::LOG);
        }

        if(content == HELP)
        {
            // TODO: add manual
            this->PrintManual();
            this->SendMessage(1, "", GameManager::Sender::GAME);
            continue;
        }

        if(content == RETREAT)
        {
            // this->WriteToPipe("R", GameManager::Sender::LOG);
            this->CloseDisplay(GameManager::Sender::LOG);
            this->CloseDisplay(GameManager::Sender::MAP);
            this->CloseDisplay(GameManager::Sender::STATS);
            return;
        }

        this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);

        // send message + content
        this->SendMessage(1, content, GameManager::Sender::GAME);
    }
}

std::string GameManager::ToLower(std::string string)
{
    for(auto &c : string)
    {
        c = std::tolower(c);
    }

    return string;
}

void GameManager::Initialize()
{
    Sender::Wait(25000);
    std::string errorMessage;
    this->GetMessageQueue(GameManager::Sender::GAME);

    ScreenManager::ShowFightScreen();

    while(true)
    {
        this->SendMessage(1, errorMessage + "Enter a valid path to your map\n", GameManager::Sender::GAME);
        std::fstream file(this->path = this->ReceiveMessage(GameManager::Sender::GAME).text);

        if(file.is_open())
        {
            this->map = new Map(this->path);
            errorMessage = "";
            break;
        }

        errorMessage = "ERROR: Invalid path\n\n";
    }

    this->enemyCount = this->map->enemyCount;
    this->playerCount = this->map->playerCount;

    ScreenManager::ShowFightScreen();
    this->ShowConfiguration();

    this->LoadRobots(PLAYER);
    this->LoadRobots(ENEMY);

    this->SendMessage(1, "", GameManager::Sender::GAME);
}

void GameManager::ShowConfiguration() const
{
    std::cout << "Map Path: " << this->path << std::endl;
    std::cout << "Number of Players: ";
    if(this->playerCount > 1 && this->playerCount < 10)
    {
        std::cout << this->playerCount;
    }

    std::cout << std::endl << "Number of Players: ";
    if(this->enemyCount > 1 && this->enemyCount < 10)
    {
        std::cout << this->enemyCount;
    }

    std::cout << std::endl;
}

std::string GameManager::DrawMap()
{
    std::vector<std::vector<char>> grid = this->map->GetGrid();
    for(auto &p : this->players)
    {
        grid[p->position.y][p->position.x] = p->symbol;
    }

    for(auto &e : this->enemies)
    {
        grid[e->position.y][e->position.x] = e->symbol;
    }

    return this->ToString(grid);
}

void GameManager::DeleteRobots()
{
    for(auto &robot : this->players)
    {
        delete robot;
    }

    this->players.clear();

    for(auto &robot : this->enemies)
    {
        delete robot;
    }

    this->enemies.clear();
}

// TODO: refactor
void GameManager::LoadRobots(const std::string &identifier)
{
    std::string robotsPath;

    if(identifier == PLAYER)
    {
        robotsPath = ConfigManager().playerRobotsPath;
    }

    if(identifier == ENEMY)
    {
        robotsPath = ConfigManager().enemyRobotsPath;
    }

    std::fstream robots(robotsPath);

    if(!robots.is_open())
    {
        std::cerr << "ERROR: Unable to open .save file" << std::endl << std::flush;
        std::exit(EXIT_FAILURE);
    }

    int id;
    int health;
    int damage;
    int actionPoints;
    int attackRadius;
    int counter = 0;

    char symbol;

    std::string name;
    std::string description;
    std::string line;


    while(getline(robots, line))
    {
        int pos = 0;
        line = ConfigManager::RemoveNewLine(line);

        if(line == "ROBOT" || line.empty())
        {
            continue;
        }

        std::string attribute = line.substr(0, (pos = line.find(DELIMITER)));
        line = line.substr((pos + 1), line.length());

        if(attribute == ID)
        {
            id = stoi(line, nullptr, 10);
            continue;
        }

        if(attribute == SYMBOL)
        {
            symbol = line[0];
            continue;
        }

        if(attribute == NAME)
        {
            name = line;
            continue;
        }

        if(attribute == HEALTH)
        {
            health = stoi(line, nullptr, 10);
            continue;
        }

        if(attribute == ACTION_POINTS)
        {
            actionPoints = stoi(line, nullptr, 10);
            continue;
        }

        if(attribute == DAMAGE)
        {
            damage = stoi(line, nullptr, 10);
            continue;
        }

        if(attribute == ATTACK_RADIUS)
        {
            attackRadius = stoi(line, nullptr, 10);
            continue;
        }

        if(attribute == DESCRIPTION)
        {
            while(getline(robots, line))
            {
                line = ConfigManager::RemoveNewLine(line);
                if(line == "-")
                {
                    break;
                }

                description += line;
            }
        }

        if(identifier == PLAYER)
        {

            this->players.push_back(new Player(id, symbol, name, health, actionPoints, damage, attackRadius,
                                               description, this->map->playerSpawnPoints[counter]));
        }

        if(identifier == ENEMY)
        {
            this->enemies.push_back(new Enemy(id, symbol, name, health, actionPoints, damage, attackRadius,
                                              description, this->map->enemySpawnPoints[counter]));
        }

        counter++;
    }
}

void GameManager::CloseDisplay(const std::string &display) const
{
    this->WriteToPipe(SHUTDOWN, display);
}

std::string GameManager::ToString(const std::vector<std::vector<char>> &grid)
{
    std::string gridString;
    for(auto &row : grid)
    {
        for(auto &c : row)
        {
            gridString += c;
        }
        gridString += "\n";
    }

    return gridString;
}

void GameManager::PrintManual() const
{
    std::cout << "HELP" << std::endl << std::flush;
}
