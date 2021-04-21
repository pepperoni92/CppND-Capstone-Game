#include "renderer.h"
#include <iostream>
#include <string>
#include "game_texture.h"

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

  std::cout << "SDL Window Created\n";

  // Create renderer
  _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
  if (_sdlRenderer == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    return;
  }

  std::cout << "SDL Renderer created\n";

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    std::cerr << "SDL_Image cout not be initialized!\n";
    std::cerr << "SDL_Image Error: " << IMG_GetError() << "\n";
    return;
  }

  std::cout << "SDL Image Create\n";

  // load test texture
  _testTexture = new GameTexture();
  _testTexture->CreateFromFile("../assets/sprites/sprPlayer_Idle_Base.png", _sdlRenderer);
  if (_testTexture == nullptr)
  {
    std::cerr << "Failed to load test texture\n";
  }
  std::cout << "Texture loaded successfully\n";
}

Renderer::~Renderer() {
  // _testTexture->Destroy();
  // _testTexture = nullptr;

  SDL_DestroyRenderer(_sdlRenderer);
  _sdlRenderer = nullptr;

  SDL_DestroyWindow(_sdlWindow);
  _sdlWindow = nullptr;

  IMG_Quit();
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
  _testTexture->Render(200, 200, _sdlRenderer);

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