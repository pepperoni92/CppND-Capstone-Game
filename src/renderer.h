#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"

class Enemy;
class Player;
class GameTexture;
class SpritesheetTexture;
class ScrollingTexture;

class Renderer {
 public:
  Renderer(const std::size_t screenWidth, const std::size_t screenHeight);
  ~Renderer();

  void LoadTextures(Player* player);

  void Render(Player* const player, std::vector<Enemy*> const enemies);
  void UpdateWindowTitle(int score, int fps);

 private:

  const std::size_t kScreenWidth;
  const std::size_t kScreenHeight;

  SDL_Window* _sdlWindow;
  SDL_Renderer* _sdlRenderer;

  ScrollingTexture* _background;
  ScrollingTexture* _foreground;

  double _lastFrameTime;

  SDL_Texture* loadTexture(std::string path);
  double UpdateLastFrameTime();
};

#endif