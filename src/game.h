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
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration, int screenWidth, int screenHeight);
  int GetScore() const;
  int GetHighScore() const;

private:
  Player* _player;
  std::vector<Enemy*> _enemies;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _randomEnemyPlacement;
  std::uniform_int_distribution<int> _randomEnemyHeight;

  int _score{0};
  int _highScore{0};

  int _screenWidth{0};
  int _screenHeight{0};

  void Update();
  void SpawnEnemy(float x, float y);

  bool CheckCollision(SDL_Rect a, SDL_Rect b);

  void ResetGame();
};

#endif