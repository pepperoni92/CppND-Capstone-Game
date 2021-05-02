#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "SDL.h"

class SpritesheetTexture;
class Weapon;

class Player
{
public:
    
    Player() { };
    ~Player();

    void Update();

    void SetCurrentSpeed(float newSpeed) { _currentSpeed = newSpeed; }
    float GetCurrentSpeed() { return _currentSpeed; }
    float GetSpeed() { return _speed; };
    
    float GetX() { return _x; };
    float GetY() { return _y; };

    SDL_Rect GetRect();

    void Jump();

    int GetCurrentHealth() { return _currentHealth; }
    int GetMaxHealth() { return _maxHealth; }

    bool GetIsAttacking() { return _bAttacking; }
    void Attack();

    SpritesheetTexture* GetSpritesheet() { return _spritesheet; }
    void SetSpriteheet(SpritesheetTexture* spritesheet) { _spritesheet = spritesheet; }

    SpritesheetTexture* GetWeaponSpritesheet() { return _weaponSpritesheet; }
    void SetWeaponSpriteheet(SpritesheetTexture* spritesheet) { _weaponSpritesheet = spritesheet; }

    SpritesheetTexture* GetAttackSpritesheet() { return _attackSpritesheet; }
    void SetAttackpriteheet(SpritesheetTexture* spritesheet) { _attackSpritesheet = spritesheet; }

    bool IsAlive() { return _bAlive; }
    void Damage();

    void ResetPlayer();

    bool _moveLeft {false};
    bool _moveRight {false};

    const std::string kTexturePath { "../assets/sprites/sprPlayer_Base.png" };
    const std::string kWeaponTexturePath { "../assets/sprites/sprPlayer_Sword.png" };
    const std::string kAttackTexturePath { "../assets/sprites/sprPlayer_Attacks.png" };
    const int kIdleFrameIndex {0};
    const int kRunFrameStart {1};
    const int kRunFrameEnd {5};

    static const int PLAYER_SIZE {32};

private:
    float _currentSpeed {0.0f};
    float _speed {5.0f};
    float _x {320.0f};
    float _y {264.0f};

    int _maxHealth {1};
    int _currentHealth {_maxHealth};

    float _jumpStartY {0.0f};
    float _jumpStartSpeed {7.5f};
    float _jumpGravity {0.5f};
    float _jumpSpeed {0.0f};

    bool _bAlive {true};
    bool _bRunning {false};
    bool _bJumping{false};
    bool _bAttacking{false};

    SpritesheetTexture* _spritesheet;
    SpritesheetTexture* _weaponSpritesheet;
    SpritesheetTexture* _attackSpritesheet;

    Weapon* _weapon;
};

#endif