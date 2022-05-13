#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

bool Controller::HandleInput(bool &running, Snake &snake, bool game_paused) const {
  bool inactive = game_paused;
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          if(!inactive)
          {
            ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          }
          break;

        case SDLK_DOWN:
          if(!inactive)
          {
            ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          }
          break;

        case SDLK_LEFT:
          if(!inactive)
          { 
            ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          }
          break;

        case SDLK_RIGHT:
          if(!inactive)
          {
            ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          }
          break;
        case SDLK_SPACE:
          if(inactive)
            inactive = false;
          else
            inactive = true;
          break;
      }
    }
  }
  return inactive;
}