#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() { }
    
    Enemy (float x, float y, int width, int height) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
    }

    ~Enemy() { }

    bool IsAlive() { return _bAlive; }
    void IsAlive(bool value) { _bAlive = value; }

    float GetX() { return _x; }
    float GetY() { return _y; }

    int GetWidth() { return _width; }
    int GetHeight() { return _height; }

    static const int ENEMY_SIZE {16};

private:
    bool _bAlive {true};
    float _x {0.0f};
    float _y {0.0f};
    int _height {16};
    int _width {16};
};

#endif