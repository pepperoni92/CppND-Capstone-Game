#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

void Controller::HandleInput(bool &running, Player *player) const
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
        player->Jump();
        break;

      case SDLK_DOWN:
      case SDLK_s:
        break;

      case SDLK_LEFT:
      case SDLK_a:
        player->_moveLeft = true;
        break;

      case SDLK_RIGHT:
      case SDLK_d:
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
        player->_moveLeft = false;
        break;

      case SDLK_RIGHT:
      case SDLK_d:
        player->_moveRight = false;
        break;
      }
    }
  }
}