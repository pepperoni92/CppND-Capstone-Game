#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "snake.h"

class Player;
class GameTexture;
class SpritesheetTexture;
class ScrollingTexture;

class Renderer {
 public:
  Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
           const std::size_t gridWidth, const std::size_t gridHeight);
  ~Renderer();

  void LoadTextures(Player* player);

  void Render(Snake const snake, SDL_Point const &food, Player* const player);
  void UpdateWindowTitle(int score, int fps);

 private:

  const std::size_t kScreenWidth;
  const std::size_t kScreenHeight;
  const std::size_t kGridWidth;
  const std::size_t kGridHeight;

  SDL_Window* _sdlWindow;
  SDL_Renderer* _sdlRenderer;

  ScrollingTexture* _background;
  ScrollingTexture* _foreground;

  double _lastFrameTime;

  SDL_Texture* loadTexture(std::string path);
  double UpdateLastFrameTime();
};

#endif