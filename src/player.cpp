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

    if (_attackSpritesheet != nullptr)
    {
        _attackSpritesheet->Destroy();
        _attackSpritesheet = nullptr;
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

void Player::Attack()
{
    if (!_bAttacking)
    {
        _bAttacking = true;
        _attackSpritesheet->PlayAnimation(0, 2, 15.0, 0);
    }
}

void Player::Update()
{
    if (_spritesheet == nullptr)
    {
        std::cerr << "Player spritesheet is null. Skipping Update.\n";
        return;
    }

    if (!_bAlive) return;

    _currentSpeed = 0.0f;
    
    if (_moveLeft)
    {
        _currentSpeed--;
        _spritesheet->SetFlipped(true);
        _weaponSpritesheet->SetFlipped(true);
        _attackSpritesheet->SetFlipped(true);
    }

    if (_moveRight)
    {
        _currentSpeed++;
        _spritesheet->SetFlipped(false);
        _weaponSpritesheet->SetFlipped(false);
        _attackSpritesheet->SetFlipped(false);
    }

    if (_bAttacking)
    {
        if (!_attackSpritesheet->IsAnimating())
        {
            _bAttacking = false;
        }
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

    if (!_bJumping) // Not jumping - regular run
    {
        if (_currentSpeed != 0.0f)
        {
            if (!_spritesheet->IsAnimating())
            {
                _bRunning = true;
                _spritesheet->PlayAnimation(kRunFrameStart, kRunFrameEnd, 30.0);
                _weaponSpritesheet->PlayAnimation(kRunFrameStart, kRunFrameEnd, 30.0);
            }
        }
        else
        {
            _bRunning = false;
            _spritesheet->StopAnimation();
            _weaponSpritesheet->StopAnimation();
        }
    }

    _x += _currentSpeed * _speed;

    if (_x <= 32) // if player is on the far left of the map, stop them from moving further left
    {
        _x = 32;
    }
    //std::cout << "Player x = " << _x << "\n";
}

SDL_Rect Player::GetRect()
{
    int rectWidth = _bAttacking ? 48 : 32;
    SDL_Rect rect = { 320, (int)_y, rectWidth, 32 };
    return rect;
}

void Player::Damage()
{
    _currentHealth--;

    if(_currentHealth <= 0)
    {
        _spritesheet->StopAnimation();
        _spritesheet->SetFrameIndex(9);
        _weaponSpritesheet->StopAnimation();
        _weaponSpritesheet->SetFrameIndex(9);
        _bAlive = false;

        if (_bAttacking)
        {
            _bAttacking = false;
            _attackSpritesheet->StopAnimation();
        }
    }
}

void Player::ResetPlayer()
{
    _x = 320.0f;
    _y = 264.0f;
    _currentHealth = _maxHealth;
    _currentSpeed = 0.0f;
    _spritesheet->SetFrameIndex(0);
    _weaponSpritesheet->SetFrameIndex(0);
    _bAlive = true;
}