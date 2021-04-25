#include "player.h"
#include <iostream>
#include "spritesheet_texture.h"

Player::~Player()
{
    if (_spritesheet != nullptr)
    {
        _spritesheet->Destroy();
        _spritesheet = nullptr;
    }
}

void Player::Update()
{
    std::cout << "Player::Update - Current speed = " << _currentSpeed << "\n";

    _currentSpeed = 0.0f;
    
    if (_moveLeft)
        _currentSpeed--;

    if (_moveRight)
        _currentSpeed++;

    if (_currentSpeed != 0.0f)
    {
        if (!_spritesheet->IsAnimating())
        {
            _bRunning = true;
            _spritesheet->PlayAnimation(kRunFrameStart, kRunFrameEnd);
        }
    }
    else
    {
        _bRunning = false;
        _spritesheet->StopAnimation();
    }

    _x += _currentSpeed * _speed;
    //std::cout << "Player x = " << _x << "\n";
}