#include "obstacles.h"


Obstacles::~Obstacles()
{
    for (auto item : this->obstacles) 
    {
        delete item;
    }
}

void Obstacles::AddObstacle(Snake const &snake, SDL_Point const &food)
{
    SDL_Point *obs = new SDL_Point();
    int x, y;
    bool obs_placed = false;
    while (!obs_placed) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item or food item before placing
        if (!snake.SnakeCell(x, y) && !(food.x == x && food.y == y) && !ObstacleCell(x, y)) {
            obs->x = x;
            obs->y = y;
            obs_placed = true;
            size++;
        }
    }
    obstacles.emplace_back(obs);
}

void Obstacles::RemoveObstacle()
{
    if(!obstacles.empty())
    {
        SDL_Point *tmp;
        std::uniform_int_distribution<int> random_item(0,size-1);
        size_t item = size_t(random_item(engine));
        tmp = obstacles.at(item);
        obstacles.erase(obstacles.begin() + item);
        delete tmp;
        size--;
    }
}

bool Obstacles::ObstacleCell(int x, int y)
{
    for (auto const &item : this->obstacles) 
    {
        if (x == item->x && y == item->y) 
        {
            return true;
        }
    }
    return false;
}