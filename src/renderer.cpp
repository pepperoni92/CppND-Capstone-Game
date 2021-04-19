#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : kScreenWidth(screen_width),
      kScreenHeight(screen_height),
      kGridWidth(grid_width),
      kGridHeight(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdlWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (_sdlWindow == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    return;
  }

  // Create renderer
  _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
  if (_sdlRenderer == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    return;
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    std::cerr << "SDL_Image cout not be initialized!\n";
    std::cerr << "SDL_Image Error: " << IMG_GetError() << "\n";
    return;
  }

  // load test texture
  _testTexture = loadTexture("../assets/sprites/sprPlayer_Idle_Base.png");
  if (_testTexture == nullptr)
  {
    std::cerr << "Failed to load test texture\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyTexture(_testTexture);
  _testTexture = nullptr;

  SDL_DestroyRenderer(_sdlRenderer);
  _sdlRenderer = nullptr;

  SDL_DestroyWindow(_sdlWindow);
  _sdlWindow = nullptr;

  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = kScreenWidth / kGridWidth;
  block.h = kScreenHeight / kGridHeight;

  // Clear screen
  SDL_SetRenderDrawColor(_sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRenderer);

  // Render test texture to screen
  SDL_RenderCopy(_sdlRenderer, _testTexture, nullptr, nullptr);

  // Render food
  SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(_sdlRenderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdlRenderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(_sdlRenderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdlRenderer, &block);

  // Update Screen
  SDL_RenderPresent(_sdlRenderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdlWindow, title.c_str());
}

SDL_Texture* Renderer::loadTexture(std::string path)
{
  // Final texture
  SDL_Texture* newTexture = nullptr;

  // Load image from path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr)
  {
    std::cerr << "Unable to load image " << path << ". SDL_image Error: " << IMG_GetError() << "\n";
  }
  else
  {
    // create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(_sdlRenderer, loadedSurface);
    if (newTexture == nullptr)
    {
      std::cerr << "Unable to create texture from " << path << ". SDL Error: " << SDL_GetError() << "\n";
    }

    // clear up surface from loaded image
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}