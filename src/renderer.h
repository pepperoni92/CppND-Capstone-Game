#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
           const std::size_t gridWidth, const std::size_t gridHeight);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window* _sdlWindow;
  SDL_Renderer* _sdlRenderer;

  const std::size_t kScreenWidth;
  const std::size_t kScreenHeight;
  const std::size_t kGridWidth;
  const std::size_t kGridHeight;
};

#endif