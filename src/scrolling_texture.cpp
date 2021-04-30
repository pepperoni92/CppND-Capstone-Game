#include "scrolling_texture.h"

void ScrollingTexture::Move(int playerPosition)
{
    _scrollingOffset = (-playerPosition % _width);
}