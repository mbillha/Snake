#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <vector>
#include <random>
#include "SDL.h"
#include "snake.h"

class Obstacles {
 public:
  Obstacles(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        engine(dev()),
        random_w(0, static_cast<int>(grid_width - 1)),
        random_h(0, static_cast<int>(grid_height - 1)) 
        {}
  ~Obstacles();

  bool ObstacleCell(int x, int y);
  void AddObstacle(Snake const &snake, SDL_Point const &food);
  void RemoveObstacle();

  
  int size{0};
  std::vector<SDL_Point *> obstacles;

 private:
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int grid_width;
  int grid_height;
};

#endif