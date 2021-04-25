#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class SpritesheetTexture;

class Player
{
public:
    enum class Direction { kUp, kDown, kLeft, kRight };
    
    Player() { };
    ~Player();

    void Update();

    void SetCurrentSpeed(float newSpeed) { _currentSpeed = newSpeed; }
    float GetCurrentSpeed() { return _currentSpeed; }
    float GetSpeed() { return _speed; };
    float GetX() { return _x; };
    float GetY() { return _y; };
    int GetCurrentHealth() { return _currentHealth; }
    int GetMaxHealth() { return _maxHealth; }

    bool _moveLeft {false};
    bool _moveRight {false};

    const std::string kTexturePath { "../assets/sprites/sprPlayer_Base.png" };
    const int kIdleFrameIndex {0};
    const int kRunFrameStart {1};
    const int kRunFrameEnd {5};

    SpritesheetTexture* _spritesheet;

private:
    float _currentSpeed {0.0f};
    float _speed {5.0f};
    float _x {320.0f};
    float _y {500.0f};
    int _maxHealth {100};
    int _currentHealth {_maxHealth};
    bool _bAlive {true};
    bool _bRunning {false};
};

#endif