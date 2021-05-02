#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"

class Player;
class Enemy;

class Game
{
public:
  Game();
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

private:
  Player* _player;
  std::vector<Enemy*> _enemies;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _randomW;
  std::uniform_int_distribution<int> _randomH;

  int _score{0};

  void Update();
  void SpawnEnemy(float x, float y);

  bool CheckCollision(SDL_Rect a, SDL_Rect b);
};

#endif