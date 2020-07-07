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
        std::string content = this->ToUpper(this->ReceiveMessage(GameManager::Sender::GAME).text);
        std::string action = GetValue(content);

        // process input
        if(action == ATTACK)
        {
            // check if enemy is in range
            // roll damage
            // reduce enemy health, if enemy is dead delete him
            // log output
        }

        // M:P1:E
        if(action == MOVE)
        {
            // Get current robot symbol and id
            std::string robotString = this->GetValue(content);

            // get active robot
            Robot *robot = this->GetActiveRobot(robotString);

            if(robot == nullptr)
            {
                this->SendMessage(1, "INFO: Robot not found!", GameManager::Sender::GAME);
                continue;
            }

            std::string oldPos = robot->position.ToString();
            Directions direction = (Directions) GetValue(content)[0];

            // check if move action is possible
            int movementCost = MOVEMENT_COST;
            switch((movementCost = this->CanMove(*robot, direction)))
            {
                case MOVE_BLOCKED:
                    this->SendMessage(1, "INFO: Cannot move there, move is blocked!", GameManager::Sender::GAME);
                    robot = nullptr;
                    continue;

                case NOT_ENOUGH_AP:
                    this->SendMessage(1, "INFO: Not enough AP!", GameManager::Sender::GAME);
                    robot = nullptr;
                    continue;

                default:
                    // set robot position to new position
                    robot->Move(direction);
                    robot->currentActionPoints -= movementCost;
                    std::string newPos = robot->position.ToString();

                    // log output
                    this->WriteToPipe("M:" + robotString
                                              .append(":")
                                              .append(oldPos)
                                              .append(":")
                                              .append(newPos),
                                      GameManager::Sender::LOG);
                    break;
            }
        }

        // S:P1
        if(action == SHOW)
        {
            // SYMBOL|E:ID:SYMBOL:NAME:HEALTH:CURRENT_ACTION_POINTS:ACTION_POINTS:DAMAGE:ATTACK_RADIUS:DESCRIPTION
            Robot *robot = robot = this->GetActiveRobot(this->GetValue(content));
            if(robot == nullptr)
            {
                this->SendMessage(1, "INFO: Robot not found!", GameManager::Sender::GAME);
                continue;
            }
            else
            {
                std::string data;
                data.append(1, robot->symbol).append(":")
                        .append(std::to_string(robot->id)).append(":")
                        .append(1, robot->symbol).append(":")
                        .append(robot->name).append(":")
                        .append(std::to_string(robot->health)).append(":")
                        .append(std::to_string(robot->currentActionPoints)).append(":")
                        .append(std::to_string(robot->actionPoints)).append(":")
                        .append(std::to_string(robot->damage)).append(":")
                        .append(std::to_string(robot->attackRadius)).append(":")
                        .append(robot->description);

                this->WriteToPipe(data, GameManager::Sender::STATS);
            }

            robot = nullptr;
        }

        if(action == HELP)
        {
            // TODO: add manual
            this->PrintManual();
            this->SendMessage(1, "", GameManager::Sender::GAME);
            continue;
        }

        if(action == RETREAT)
        {
            // this->WriteToPipe("R", GameManager::Sender::LOG);
            this->CloseDisplay(GameManager::Sender::LOG);
            this->CloseDisplay(GameManager::Sender::MAP);
            this->CloseDisplay(GameManager::Sender::STATS);
            return;
        }

        if(action == END_ROUND)
        {
            // this->WriteToPipe("E", GameManager::Sender::LOG);
            // reset action points
            this->ResetActionPoints();
            // roundCounter + 1
            // start enemy round
        }

        this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);

        // send message + content
        this->SendMessage(1, "", GameManager::Sender::GAME);
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

std::string GameManager::ToUpper(std::string string)
{
    for(auto &c : string)
    {
        c = std::toupper(c);
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
            description = "";
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

std::string GameManager::GetValue(std::string &line)
{
    int pos = line.find(DELIMITER);
    std::string value = line.substr(0, pos);
    line.erase(0, pos + 1);

    return value;
}

void GameManager::ResetActionPoints()
{
    for(auto &p : this->players)
    {
        p->currentActionPoints = p->actionPoints;
    }

    for(auto &e : this->enemies)
    {
        e->currentActionPoints = e->actionPoints;
    }
}

int GameManager::CanMove(Robot robot, Directions direction)
{
    robot.Move(direction);
    char tile = this->map->GetGrid()[robot.position.x][robot.position.y];
    if(tile == 'M')
    {
        return MOVE_BLOCKED;
    }

    int movementCost = MOVEMENT_COST;
    if(tile == 'W')
    {
        movementCost++;
    }

    if((robot.currentActionPoints - movementCost) < 0)
    {
        return NOT_ENOUGH_AP;
    }

    return movementCost;
}

Robot *GameManager::GetActiveRobot(const std::string &line)
{
    char symbol = line[0];
    int id = stoi(line.substr(1, line.length()), nullptr, 10);

    if(symbol == PLAYER[0])
    {
        for(auto &p : this->players)
        {
            if(p->id == id && p->symbol == symbol)
            {
                return p;
            }
        }
    }
    else
    {
        for(auto &e : this->enemies)
        {
            if(e->id == id && e->symbol == symbol)
            {
                return e;
            }
        }
    }

    return nullptr;
}
