#include "renderer.h"
#include <iostream>
#include <string>
#include <chrono>
#include "game_texture.h"
#include "spritesheet_texture.h"
#include "scrolling_texture.h"
#include "player.h"
#include "enemy.h"

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height) : kScreenWidth(screen_width), kScreenHeight(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdlWindow = SDL_CreateWindow("Fight Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (_sdlWindow == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    return;
  }

  // Create renderer
  _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

  std::cout << "SDL Image Create\n";
}

Renderer::~Renderer() {

  SDL_DestroyRenderer(_sdlRenderer);
  _sdlRenderer = nullptr;

  SDL_DestroyWindow(_sdlWindow);
  _sdlWindow = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void Renderer::LoadTextures(Player* player)
{
  _background = new ScrollingTexture();
  _background->CreateFromFile("../assets/sprites/background_dark.png", _sdlRenderer);

  _foreground = new ScrollingTexture();
  _foreground->CreateFromFile("../assets/sprites/sprGround_Full.png", _sdlRenderer);

  SpritesheetTexture* playerSpritesheet = new SpritesheetTexture();
  playerSpritesheet->CreateFromFile(player->kTexturePath, _sdlRenderer, 32, 32);
  player->SetSpriteheet(std::move(playerSpritesheet));

  SpritesheetTexture* weaponSpritesheet = new SpritesheetTexture();
  weaponSpritesheet->CreateFromFile(player->kWeaponTexturePath, _sdlRenderer, 32, 32);
  player->SetWeaponSpriteheet(std::move(weaponSpritesheet));

  SpritesheetTexture* attackSpritesheet = new SpritesheetTexture();
  attackSpritesheet->CreateFromFile(player->kAttackTexturePath, _sdlRenderer, 64, 32);
  player->SetAttackpriteheet(std::move(attackSpritesheet));
}

double Renderer::UpdateLastFrameTime()
{
  auto currentTime = std::chrono::steady_clock::now();
  auto currentTimeSeconds = std::chrono::duration<double>(currentTime.time_since_epoch()).count();
  double deltaTime =  currentTimeSeconds - _lastFrameTime;
  _lastFrameTime = currentTimeSeconds;
  return deltaTime;
}

void Renderer::Render(Player* const player, std::vector<Enemy*> const enemies) {
  double deltaTime = UpdateLastFrameTime();

  // Clear screen
  SDL_SetRenderDrawColor(_sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRenderer);

  // Render background
  _background->Move(player->GetX());
  _background->Render(_background->GetScrollingOffset(), -120, _sdlRenderer);
  _background->Render(_background->GetScrollingOffset() + _background->GetWidth(), -120, _sdlRenderer);

  // Render ground
  _foreground->Move(player->GetX());
  _foreground->Render(_foreground->GetScrollingOffset(), 296, _sdlRenderer);
  _foreground->Render(_foreground->GetScrollingOffset() + _foreground->GetWidth(), 296, _sdlRenderer);

  if (player->GetIsAttacking())
  {
    // render attacking sprite
    player->GetAttackSpritesheet()->Render(320-16, player->GetY(), _sdlRenderer, deltaTime);
  }
  else
  {
    player->GetSpritesheet()->Render(320, player->GetY(), _sdlRenderer, deltaTime);

    // Render weapon
    player->GetWeaponSpritesheet()->Render(320, player->GetY(), _sdlRenderer, deltaTime);
  }

  // render enemies
  for (Enemy* enemy : enemies)
  { 
    int enemyX = enemy->GetX() - player->GetX();
    int enemyY = enemy->GetY();

    SDL_Rect enemyRect = { enemyX, enemyY, 16, 16 };
    SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(_sdlRenderer, &enemyRect);
  }

  // // Render food
  // SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xCC, 0x00, 0xFF);
  // block.x = food.x * block.w;
  // block.y = food.y * block.h;
  // SDL_RenderFillRect(_sdlRenderer, &block);

  // // Render snake's body
  // SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  // for (SDL_Point const &point : snake.body) {
  //   block.x = point.x * block.w;
  //   block.y = point.y * block.h;
  //   SDL_RenderFillRect(_sdlRenderer, &block);
  // }

  // // Render snake's head
  // block.x = static_cast<int>(snake.head_x) * block.w;
  // block.y = static_cast<int>(snake.head_y) * block.h;
  // if (snake.alive) {
  //   SDL_SetRenderDrawColor(_sdlRenderer, 0x00, 0x7A, 0xCC, 0xFF);
  // } else {
  //   SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
  // }
  // SDL_RenderFillRect(_sdlRenderer, &block);

  // Update Screen
  SDL_RenderPresent(_sdlRenderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdlWindow, title.c_str());
}