#include "scrolling_texture.h"

void ScrollingTexture::Move()
{
    _scrollingOffset -= _speed;
    if (_scrollingOffset < -_width)
    {
        _scrollingOffset = 0;
    }
}