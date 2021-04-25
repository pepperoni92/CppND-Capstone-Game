#ifndef SPRITESHEET_TEXTURE_H
#define SPRITESHEET_TEXTURE_H

#include "game_texture.h"
#include <vector>
#include "SDL.h"

class SpritesheetTexture : public GameTexture
{
public:
    SpritesheetTexture();
    ~SpritesheetTexture();
    bool CreateFromFile(std::string path, SDL_Renderer* sdlRenderer, int spriteSize);
    void Render(int x, int y, SDL_Renderer* sdlRenderer, double deltaTime, int spriteIndex = 0);
    bool PlayAnimation(int startFrameIndex, int endFrameIndex, double fps = 60.0);
    void StopAnimation();
    bool IsAnimating() { return _bAnimating; }

private:
    std::vector<SDL_Rect> _spriteClips;
    GameTexture _spriteTexture;

    bool _bAnimating;
    int _animationCurrentFrame;
    int _animationStartFrame;
    int _animationEndFrame;
    double _animationFrameLength;
    double _currentFrameTime;
};

#endif