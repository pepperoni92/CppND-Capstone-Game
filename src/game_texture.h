#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"

class GameTexture {
public:
    GameTexture();
    ~GameTexture();

    bool CreateFromFile(std::string path, SDL_Renderer* sdlRenderer);
    void Destroy();
    void Render(int x, int y, SDL_Renderer* sdlRenderer);
    int GetWidth();
    int GetHeight();
    

private:
    SDL_Texture* _texture;
    int _width;
    int _height;
};

#endif