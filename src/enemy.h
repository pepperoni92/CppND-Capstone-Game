#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() { }
    
    Enemy (float x, float y) {
        _x = x;
        _y = y;
    }

    ~Enemy() { }

    bool IsAlive() { return _bAlive; }
    void IsAlive(bool value) { _bAlive = value; }

    float GetX() { return _x; }
    float GetY() { return _y; }

private:
    bool _bAlive {true};
    float _x {0.0f};
    float _y {0.0f};
};

#endif