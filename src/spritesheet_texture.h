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
    bool CreateFromFile(std::string path, SDL_Renderer* sdlRenderer, int spriteWidth, int spriteHeight);
    void Render(int x, int y, SDL_Renderer* sdlRenderer, double deltaTime);
    bool PlayAnimation(int startFrameIndex, int endFrameIndex, double fps = 60.0, int loops = -1);
    void StopAnimation();
    bool IsAnimating() { return _bAnimating; }
    void SetFlipped(bool flipped) { _bFlipped = flipped; }
    void SetFrameIndex(int frame);
    int GetCurrentAnimationFrame() { return _animationCurrentFrame; }

private:
    std::vector<SDL_Rect> _spriteClips;
    GameTexture _spriteTexture;

    int _frameIndex = 0;

    bool _bFlipped {false};
    bool _bAnimating;
    int _animationCurrentFrame;
    int _animationStartFrame;
    int _animationEndFrame;
    int _loops {-1};
    int _loopCount {0};
    double _animationFrameLength;
    double _currentFrameTime;
};

#endif