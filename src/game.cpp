#include "game.h"
#include <iostream>
#include "SDL.h"
#include "player.h"
#include "enemy.h"

Game::Game() : _engine(_dev()){
  _player = new Player();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {

  renderer.LoadTextures(_player);

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // INPUT
    controller.HandleInput(running, _player);

    // UPDATE
    Update();

    // RENDER
    renderer.Render(_player, _enemies);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    //std::cout << "Frame " << frame_count << "\n";

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (!_player->IsAlive()) return;

  _player->Update();
  int playerX = _player->GetX();

  // spawn an enemy every 100 units
  if (playerX % 100 == 0)
  {
    SpawnEnemy(playerX + 640, _player->GetY());
  }

  std::vector<int> enemiesToKill;
  int iterator = 0;

  // check for collision with enemies
  for (Enemy* enemy : _enemies)
  {
    int enemyX = enemy->GetX() - _player->GetX();
    int enemyY = enemy->GetY();

    SDL_Rect enemyRect = { enemyX, enemyY, 16, 16 };
    if (CheckCollision(enemyRect, _player->GetRect()))
    {
      // player is colliding with enemy, check if they are attacking
      if (_player->GetIsAttacking())
      {
        enemy->IsAlive(false);
        enemiesToKill.push_back(iterator);
      }
      else // else the player dies here
      {
        _player->Damage();
      }
    }

    iterator++;
  }

  for (int i : enemiesToKill)
  {
    _enemies.erase(_enemies.begin() + i);
  }
}


void Game::SpawnEnemy(float x, float y)
{
  bool bEmptyPosition = true;

  // check existing enemies to make sure one is not in this x position
  for (Enemy* enemy : _enemies)
  {
    if (x == enemy->GetX())
    {
      bEmptyPosition = false;
      break;
    }
  }

  if (bEmptyPosition)
  {
    Enemy* enemy = new Enemy(x, y + 16);
    _enemies.push_back(std::move(enemy));
  }
}

bool Game::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB ) return false;

    if( topA >= bottomB ) return false;

    if( rightA <= leftB ) return false;

    if( leftA >= rightB ) return false;

    // No sides from A are outside B
    return true;
}

int Game::GetScore() const { return _score; }