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

    if (_weaponSpritesheet != nullptr)
    {
        _weaponSpritesheet->Destroy();
        _weaponSpritesheet = nullptr;
    }
}

void Player::Jump()
{
    if (!_bJumping)
    {
        _jumpStartY = _y;
        _bJumping = true;
        _jumpSpeed = _jumpStartSpeed;
        _spritesheet->StopAnimation();
    }
}

void Player::Update()
{
    if (_spritesheet == nullptr)
    {
        std::cerr << "Player spritesheet is null. Skipping Update.\n";
        return;
    }

    std::cout << "Player::Update - Current speed = " << _currentSpeed << "\n";

    _currentSpeed = 0.0f;
    
    if (_moveLeft)
    {
        _currentSpeed--;
        _spritesheet->SetFlipped(true);
    }

    if (_moveRight)
    {
        _currentSpeed++;
        _spritesheet->SetFlipped(false);
    }

    if (_bJumping)
    {
        _jumpSpeed -= _jumpGravity;

        // Change frame to jump or fall based on current speed
        if (_jumpSpeed > 0.0f)
        {
            _spritesheet->SetFrameIndex(6);
        }
        else
        {
            _spritesheet->SetFrameIndex(7);
        }

        if (_y > _jumpStartY) // check if we've landed back on the groud
        {
            _y = _jumpStartY;
            _jumpSpeed = 0.0f;
            _bJumping = false;
            _spritesheet->SetFrameIndex(0);
        }
        else
        {
            _y -= _jumpSpeed;
        }
    }
    else // Not jumping - regular run
    {
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
    }

    _x += _currentSpeed * _speed;
    //std::cout << "Player x = " << _x << "\n";
}