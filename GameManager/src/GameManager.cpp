#include <algorithm>
#include "../include/GameManager.h"
#include "../../MessageManager/include/ConfigManager.h"
#include "../../MapDisplay/include/TileTypes.h"


GameManager::GameManager()
{
    this->playerCount = 0;
    this->enemyCount = 0;
    this->map = nullptr;

    this->LoadPictures();
    this->Initialize();
}

GameManager::~GameManager()
{
    this->DeleteRobots();
    this->CloseDisplay(GameManager::Sender::LOG);
    this->CloseDisplay(GameManager::Sender::MAP);
    this->CloseDisplay(GameManager::Sender::STATS);
    delete this->map;
}

void GameManager::Run()
{
    this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);
    int turnCounter = 1;

    while(true)
    {
        if(playerCount == 0)
        {
            this->WriteToPipe("L:", GameManager::Sender::LOG);
        }
        if(enemyCount == 0)
        {
            this->WriteToPipe("W:", GameManager::Sender::LOG);
        }

        if(turnCounter % 2 == 0)
        {
            this->Wait(100000);
            // enemy make decision -> move -> attack
            this->WriteToPipe(this->ToString('E').append(1, ':')
                                      .append(std::to_string(turnCounter)),
                              GameManager::Sender::LOG);
            this->ResetActionPoints();
            turnCounter++;
        }

        std::string content = this->ToUpper(this->ReceiveMessage(GameManager::Sender::GAME).text);
        char action = GetValue(content)[0];

        // process input
        switch(action)
        {
            case ATTACK: // A:P1:E2:DMG
            {
                Robot *robot = this->GetActiveRobot(this->GetValue(content));
                Robot *enemy = this->GetActiveRobot(this->GetValue(content));
                if(robot == nullptr || enemy == nullptr)
                {
                    this->WriteToPipe("I:Robot not found!", GameManager::Sender::LOG);
                    break;
                }

                if(robot->currentActionPoints <= 0)
                {
                    this->WriteToPipe("I:Not enough AP!", GameManager::Sender::LOG);
                    break;
                }

                int damage;
                // switch(damage = robot->Attack(enemy))
                switch(damage = this->CanAttack(robot, enemy))
                {
                    case ERR_ATTACK_IS_BLOCKED:
                        this->WriteToPipe("I:Cannot attack robot, robot is blocked!", GameManager::Sender::LOG);
                        break;

                    case ERR_OUT_OF_RANGE:
                        this->WriteToPipe("I:Enemy not in range!", GameManager::Sender::LOG);
                        break;

                    default:
                        robot->currentActionPoints = 0;
                        robot->Attack(enemy, damage);
                        if(enemy->currentHealth <= 0)
                        {
                            this->DeleteRobot(enemy->symbol, enemy->id);
                            robot->currentActionPoints = 0;
                            // D:E1
                            this->WriteToPipe(
                                    "A:" + this->ToString(robot->symbol).append(std::to_string(robot->id)).append(":")
                                            .append(this->ToString(enemy->symbol)).append(std::to_string(enemy->id))
                                            .append(":").append(std::to_string(damage)),
                                    GameManager::Sender::LOG);
                            this->WriteToPipe("D:" + this->ToString(enemy->symbol).append(std::to_string(enemy->id)),
                                              GameManager::Sender::LOG);
                        }
                        else
                        {
                            this->WriteToPipe(
                                    "A:" + this->ToString(robot->symbol).append(std::to_string(robot->id)).append(":")
                                            .append(this->ToString(enemy->symbol)).append(std::to_string(enemy->id))
                                            .append(":").append(std::to_string(damage)),
                                    GameManager::Sender::LOG);
                        }

                        this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);
                        break;
                }

                break;
            }
            case MOVE: // M:P1:E
            {
                Robot *robot = this->GetActiveRobot(this->GetValue(content));
                if(robot == nullptr)
                {
                    this->WriteToPipe("I:Robot not found!", GameManager::Sender::LOG);
                    break;
                }

                Directions direction = (Directions) GetValue(content)[0];
                if(direction != Directions::NORTH && direction != Directions::EAST && direction != Directions::SOUTH &&
                   direction != Directions::WEST)
                {
                    this->WriteToPipe("I:Invalid direction!", GameManager::Sender::LOG);
                    break;
                }

                int movementCost;
                std::string oldPos = robot->position.ToString();
                switch((movementCost = this->CanMove(*robot, direction)))
                {
                    case ERR_MOVE_BLOCKED:
                        this->WriteToPipe("I:Cannot move there, move is blocked!", GameManager::Sender::LOG);
                        break;

                    case ERR_NOT_ENOUGH_AP:
                        this->WriteToPipe("I:Not enough AP!", GameManager::Sender::LOG);
                        break;

                    default:
                        robot->Move(direction, movementCost);
                        this->WriteToPipe(this->ToString(action).append(":")
                                                  .append(this->ToString(robot->symbol)
                                                                  .append(std::to_string(robot->id))).append(":")
                                                  .append(oldPos).append(":")
                                                  .append(robot->position.ToString()),
                                          GameManager::Sender::LOG);
                        this->WriteToPipe(this->DrawMap(), GameManager::Sender::MAP);
                        break;
                }

                break;
            }

            case SHOW: // S:P1
            {
                Robot *robot = this->GetActiveRobot(this->GetValue(content));
                if(robot == nullptr)
                {
                    this->WriteToPipe("I:Robot not found!", GameManager::Sender::LOG);
                    break;
                }

                // SYMBOL|E:ID:SYMBOL:NAME:CURRENT_HEALTH:HEALTH:CURRENT_ACTION_POINTS:ACTION_POINTS:DAMAGE:ATTACK_RADIUS:POSITION:DESCRIPTION
                this->WriteToPipe(this->ToString(robot->symbol).append(":")
                                          .append(robot->picture).append(":")
                                          .append(std::to_string(robot->id)).append(":")
                                          .append(this->ToString(robot->symbol)).append(":")
                                          .append(robot->name).append(":")
                                          .append(std::to_string(robot->currentHealth)).append(":")
                                          .append(std::to_string(robot->health)).append(":")
                                          .append(std::to_string(robot->currentActionPoints)).append(":")
                                          .append(std::to_string(robot->actionPoints)).append(":")
                                          .append(std::to_string(robot->damage)).append(":")
                                          .append(std::to_string(robot->attackRadius)).append(":")
                                          .append(robot->position.ToString()).append(":")
                                          .append(robot->description),
                                  GameManager::Sender::STATS);
                break;
            }

            case HELP:
                // TODO: add manual
                this->PrintManual();
                break;

            case RETREAT: // R:
                this->WriteToPipe(this->ToString(action).append(":"), GameManager::Sender::LOG);
                this->Wait(1000000);
                return;

            case END_TURN: // E:TURN
                this->WriteToPipe(this->ToString(action).append(":")
                                          .append(std::to_string(turnCounter)),
                                  GameManager::Sender::LOG);
                this->ResetActionPoints();
                turnCounter++;
                break;

            default:
                this->WriteToPipe("I:Invalid command!", GameManager::Sender::LOG);
                break;
        }

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
    ScreenManager::ShowFightMenu();

    this->LoadRobots(PLAYER);
    this->LoadRobots(ENEMY);

    this->SendMessage(1, "", GameManager::Sender::GAME);
}

void GameManager::ShowConfiguration() const
{
    std::cout << "Map Path: " << this->path << std::endl;
    std::cout << "Number of players: ";
    if(this->playerCount > 0 && this->playerCount < 10)
    {
        std::cout << this->playerCount;
    }

    std::cout << std::endl << "Number of enemies: ";
    if(this->enemyCount > 0 && this->enemyCount < 10)
    {
        std::cout << this->enemyCount;
    }

    std::cout << std::endl;
}

std::string GameManager::DrawMap()
{
    std::vector<std::vector<char>> grid = this->map->GetGrid();
    if(!this->players.empty())
    {
        for(auto &p : this->players)
        {
            grid[p->position.y][p->position.x] = p->symbol;
        }
    }

    if(!this->enemies.empty())
    {
        for(auto &e : this->enemies)
        {
            grid[e->position.y][e->position.x] = e->symbol;
        }
    }

    return this->ToString(grid);
}

void GameManager::DeleteRobots()
{
    if(!this->players.empty())
    {
        for(auto &r : this->players)
        {
            delete r;
        }

        this->players.clear();
    }

    if(!this->enemies.empty())
    {
        for(auto &r : this->enemies)
        {
            delete r;
        }

        this->enemies.clear();
    }
}

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

    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, this->robotPictures.size() - 1);

    while(getline(robots, line))
    {
        int pos = 0;
        line = ConfigManager::RemoveNewLine(line);

        if(counter == this->playerCount)
        {
            break;
        }

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
                                               description, this->map->playerSpawnPoints[counter],
                                               this->robotPictures[distribution(generator)]));
        }

        if(identifier == ENEMY)
        {
            this->enemies.push_back(new Enemy(id, symbol, name, health, actionPoints, damage, attackRadius,
                                              description, this->map->enemySpawnPoints[counter],
                                              this->robotPictures[distribution(generator)]));
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
    robot.Move(direction, 0);
    char tile = this->map->GetGrid()[robot.position.y][robot.position.x];
    if(tile == (char) TileTypes::MOUNTAIN)
    {
        return ERR_MOVE_BLOCKED;
    }

    int movementCost = MOVEMENT_COST;
    if(tile == (char) TileTypes::WATER)
    {
        movementCost++;
    }

    if((robot.currentActionPoints - movementCost) < 0)
    {
        return ERR_NOT_ENOUGH_AP;
    }

    return movementCost;
}

Robot *GameManager::GetActiveRobot(const std::string &line)
{
    char symbol;
    int id;

    try
    {
        symbol = line[0];
        id = stoi(line.substr(1, line.length()), nullptr, 10);
    }
    catch(const std::exception &e)
    {
        return nullptr;
    }

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

std::string GameManager::ToString(char c) const
{
    std::string s;
    s = c;
    return s;
}

void GameManager::DeleteRobot(char symbol, int id)
{
    if(symbol == PLAYER[0])
    {
        for(int i = 0; i < (int) this->players.size(); i++)
        {
            if(this->players[i]->id == id && this->players[i]->symbol == symbol)
            {
                this->players.erase(this->players.begin() + i);
                this->playerCount--;
            }
        }
    }
    else
    {
        for(int i = 0; i < (int) this->enemies.size(); i++)
        {
            if(this->enemies[i]->id == id && this->enemies[i]->symbol == symbol)
            {
                this->enemies.erase(this->enemies.begin() + i);
                this->enemyCount--;
            }
        }
    }
}

int GameManager::CanAttack(Robot *robot, Robot *enemy)
{
    int damage = robot->GetDamage();
    Point point = Point(0, 0);
    for(int i = 1; i <= robot->attackRadius; i++)
    {
        if(this->IsInRange(robot->position + Point(0, i), enemy->position))
        {
            return this->IsAttackBlocked(robot->position, enemy->position, Point(0, 1))
                   ? ERR_ATTACK_IS_BLOCKED
                   : damage;
        }

        if(this->IsInRange(robot->position + Point(i, 0), enemy->position))
        {
            return this->IsAttackBlocked(robot->position, enemy->position, Point(1, 0))
                   ? ERR_ATTACK_IS_BLOCKED
                   : damage;
        }

        if(this->IsInRange(robot->position + Point(0, -i), enemy->position))
        {
            return this->IsAttackBlocked(robot->position, enemy->position, Point(0, -1))
                   ? ERR_ATTACK_IS_BLOCKED
                   : damage;
        }

        if(this->IsInRange(robot->position + Point(-i, 0), enemy->position))
        {
            return this->IsAttackBlocked(robot->position, enemy->position, Point(-1, 0))
                   ? ERR_ATTACK_IS_BLOCKED
                   : damage;
        }
    }

    return ERR_OUT_OF_RANGE;
}

bool GameManager::IsAttackBlocked(Point robotPosition, Point enemyPosition, Point point)
{
    Point currentPoint = robotPosition;
    while(currentPoint != enemyPosition)
    {
        if(this->map->GetGrid()[currentPoint.y][currentPoint.x] == (char) TileTypes::MOUNTAIN)
        {
            return true;
        }

        currentPoint += point;
    }

    return false;
}

bool GameManager::IsInRange(Point robotPosition, Point enemyPosition)
{
    return robotPosition == enemyPosition;
}

void GameManager::LoadPictures()
{
    std::fstream pictures(ConfigManager().picturePath);

    if(!pictures.is_open())
    {
        std::cerr << "ERROR: Unable to open .picture file" << std::endl << std::flush;
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    std::string picture;
    while(getline(pictures, line))
    {
        if((line = ConfigManager::RemoveNewLine(line)).empty())
        {
            std::replace(picture.begin(), picture.end(), ':', ';');
            this->robotPictures.push_back(picture);
            picture = "";
            continue;
        }

        picture += line;
        picture += "\t";
    }
}