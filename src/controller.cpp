#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "player.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Player *player) const
{
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
      case SDLK_w:
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        player->Jump();
        break;

      case SDLK_DOWN:
      case SDLK_s:
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
      case SDLK_a:
        ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
        player->_moveLeft = true;
        break;

      case SDLK_RIGHT:
      case SDLK_d:
        ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
        player->_moveRight = true;
        break;

      case SDLK_SPACE:
        player->Attack();
        break;
      }
    }
    else if (e.type == SDL_KEYUP)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_LEFT:
      case SDLK_a:
        ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
        player->_moveLeft = false;
        break;

      case SDLK_RIGHT:
      case SDLK_d:
        ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
        player->_moveRight = false;
        break;
      }
    }
  }
}