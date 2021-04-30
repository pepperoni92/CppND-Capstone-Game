#ifndef SCROLLING_TEXTURE_H
#define SCROLLING_TEXTURE_H

#include "game_texture.h"

class ScrollingTexture : public GameTexture
{
public:
    void SetSpeed(float value) { _speed = value; }
    float GetScrollingOffset() { return _scrollingOffset; };
    void Move();
private:
    float _speed {1.0f};
    float _scrollingOffset {0.0f};
};

#endif