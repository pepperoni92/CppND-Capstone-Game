#ifndef SCROLLING_TEXTURE_H
#define SCROLLING_TEXTURE_H

#include "game_texture.h"

class ScrollingTexture : public GameTexture
{
public:
    float GetScrollingOffset() { return _scrollingOffset; };
    void Move(int playerPosition);
private:
    float _scrollingOffset {0.0f};
};

#endif