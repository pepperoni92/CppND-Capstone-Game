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

bool SpritesheetTexture::CreateFromFile(std::string path, SDL_Renderer* sdlRenderer, int spriteWidth, int spriteHeight)
{
    if (!GameTexture::CreateFromFile(path, sdlRenderer))
    {
        return false;
    }

    int spriteRows = _height / spriteHeight;
    int spriteCols = _width / spriteWidth;

    for (int row = 0; row < spriteRows; row++)
    {
        for (int col = 0; col < spriteCols; col++)
        {
            SDL_Rect spriteRect;
            spriteRect.w = spriteWidth;
            spriteRect.h = spriteHeight;
            spriteRect.x = col * spriteWidth;
            spriteRect.y = row * spriteHeight;
            _spriteClips.push_back(spriteRect);
        }
    }

    return true;
}

void SpritesheetTexture::Render(int x, int y, SDL_Renderer* sdlRenderer, double deltaTime)
{
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

            // check for looping
            if (_animationCurrentFrame == _animationStartFrame) // did the loop start over?
            {
                _loopCount++;

                if (_loops > -1 && _loopCount >= _loops)  // are completed all loops?
                {
                    StopAnimation();
                    _loops = 0;
                    _loopCount = 0;
                }
            }
        }

        currentClip = &_spriteClips[_animationCurrentFrame];
        renderQuad.w = _spriteClips[_animationCurrentFrame].w;
        renderQuad.h = _spriteClips[_animationCurrentFrame].h;
        // std::cout << "Playing frame at " << currentClip->x << ", " << currentClip->y << "\n";
    }
    else
    {
        currentClip = &_spriteClips[_frameIndex];
        renderQuad.w = _spriteClips[_frameIndex].w;
        renderQuad.h = _spriteClips[_frameIndex].h;
    }

    SDL_RendererFlip flip = _bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderCopyEx(sdlRenderer, _texture, currentClip, &renderQuad, 0.0, NULL, flip);
}

bool SpritesheetTexture::PlayAnimation(int startFrameIndex, int endFrameIndex, double fps, int loops)
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

    _loops = loops;
    _loopCount = -1;

    return true;
}

void SpritesheetTexture::StopAnimation()
{
    _animationStartFrame = 0;
    _animationEndFrame = 0;
    _bAnimating = false;
}

void SpritesheetTexture::SetFrameIndex(int frame)
{
    if (frame > _spriteClips.size())
    {
        std::cerr << "Frame Index " << frame << " is ou of bounds. Max frame index is " << _spriteClips.size() - 1 << "\n";
        _frameIndex = 0;
    }
    else
    {
        _frameIndex = frame;
    }


}