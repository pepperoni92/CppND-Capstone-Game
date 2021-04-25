#include "spritesheet_texture.h"
#include <vector>
#include <iostream>
#include <chrono>


SpritesheetTexture::SpritesheetTexture() 
{
    _animationCurrentFrame = 0;
    _animationStartFrame = 0;
    _animationEndFrame = 0;
    _currentFrameTime = 0.0;
}

SpritesheetTexture::~SpritesheetTexture() {}

bool SpritesheetTexture::CreateFromFile(std::string path, SDL_Renderer* sdlRenderer, int spriteSize)
{
    if (!GameTexture::CreateFromFile(path, sdlRenderer))
    {
        return false;
    }

    int spriteRows = _height / spriteSize;
    int spriteCols = _width / spriteSize;

    for (int row = 0; row < spriteRows; row++)
    {
        for (int col = 0; col < spriteCols; col++)
        {
            SDL_Rect spriteRect;
            spriteRect.w = spriteSize;
            spriteRect.h = spriteSize;
            spriteRect.x = col * spriteSize;
            spriteRect.y = row * spriteSize;
            _spriteClips.push_back(spriteRect);
        }
    }

    return true;
}

void SpritesheetTexture::Render(int x, int y, SDL_Renderer* sdlRenderer, double deltaTime, int spriteIndex)
{
    if (spriteIndex > _spriteClips.size())
    {
        std::cerr << "spriteIndex of " << spriteIndex << " is out of bounds. There are only " << _spriteClips.size() << " sprites in this sheet.\n";
    }

    SDL_Rect renderQuad = { x, y, _width, _height };
    SDL_Rect* currentClip;

    if (_bAnimating)
    {
        _currentFrameTime += deltaTime;
        if (_currentFrameTime >= _animationFrameLength)
        {
            _animationCurrentFrame++;

            if (_animationCurrentFrame > _animationEndFrame)
            {
                _animationCurrentFrame = _animationStartFrame;
            }

            // std::cout << "New frame! Frametime was " << _currentFrameTime << ". New frame is " << _animationCurrentFrame << "\n";

            _currentFrameTime = 0.0;
        }

        currentClip = &_spriteClips[_animationCurrentFrame];
        renderQuad.w = _spriteClips[_animationCurrentFrame].w;
        renderQuad.h = _spriteClips[_animationCurrentFrame].h;
        // std::cout << "Playing frame at " << currentClip->x << ", " << currentClip->y << "\n";
    }
    else
    {
        currentClip = &_spriteClips[spriteIndex];
        renderQuad.w = _spriteClips[spriteIndex].w;
        renderQuad.h = _spriteClips[spriteIndex].h;
    }

    SDL_RenderCopy(sdlRenderer, _texture, currentClip, &renderQuad);
}

bool SpritesheetTexture::PlayAnimation(int startFrameIndex, int endFrameIndex, double fps)
{
    if (startFrameIndex == endFrameIndex)
    {
        std::cerr << "startFrameIndex and endFrameIndex are the same. Cannot start an animation with a single frame\n";
        _bAnimating = false;
        return false;
    }

    _bAnimating = true;
    _animationStartFrame = startFrameIndex;
    _animationEndFrame = endFrameIndex;
    _animationFrameLength = 1/fps;

    return true;
}

void SpritesheetTexture::StopAnimation()
{
    _animationStartFrame = 0;
    _animationEndFrame = 0;
    _bAnimating = false;
}