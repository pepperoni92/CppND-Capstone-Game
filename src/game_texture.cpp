#include "game_texture.h"
#include <iostream>
#include <string>

GameTexture::GameTexture()
{
    // Init
    _texture = nullptr;
    _width = 0;
    _height = 0;
}

GameTexture::~GameTexture()
{
    Destroy();
}

void GameTexture::Destroy()
{
  if (_texture != nullptr)
  {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _width = 0;
    _height = 0;
  }
}

bool GameTexture::CreateFromFile(std::string path, SDL_Renderer* sdlRenderer)
{
  std::cout << "Creating texture from " << path << "\n";

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
    std::cout << "image loaded. creating texture\n";
    // create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(sdlRenderer, loadedSurface);
    if (newTexture == nullptr)
    {
      std::cerr << "Unable to create texture from " << path << ". SDL Error: " << SDL_GetError() << "\n";
    }
    else
    {
      std::cout << "Texture size is  " << loadedSurface->w << "x" << loadedSurface->h << "\n";
      std::cout << "Storing height and width\n";
      _width = loadedSurface->w;
      _height = loadedSurface->h;
    }

    std::cout << "Freing up surface\n";
    // clear up surface from loaded image
    SDL_FreeSurface(loadedSurface);
  }

  std::cout << "assigning texture\n";
  _texture = newTexture;
  return _texture != nullptr; // return true if the texture isn't null
}

void GameTexture::Render(int x, int y, SDL_Renderer* sdlRenderer)
{
  SDL_Rect renderQuad = { x, y, _width, _height };
  SDL_RenderCopy(sdlRenderer, _texture, nullptr, &renderQuad);
}

int GameTexture::GetWidth()
{
  return _width;
}

int GameTexture::GetHeight()
{
  return _height;
}