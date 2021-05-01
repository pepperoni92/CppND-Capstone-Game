#pragma once

#include <iostream>

template <typename T>
struct Vector2D {

    T x, y;

    Vector2D() {
        this->x = 0;
        this->y = 0;
    }

    Vector2D(T x, T y) {
        this->x = x;
        this->y = y;
    }

    // v1 + v2
    inline Vector2D<T> operator+(const Vector2D<T>& v2) const {
        return Vector2D<T>(x + v2.x, y + v2.y);
    }

    // v1 += v2
    inline friend Vector2D<T>& operator+=(Vector2D<T>& v1, const Vector2D<T>& v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    // v1 - v2
    inline Vector2D<T> operator-(const Vector2D<T>& v2) const {
        return Vector2D<T>(x - v2.x, y - v2.y);
    }

    // v1 -= v2
    inline friend Vector2D<T>& operator-=(Vector2D<T>& v1, const Vector2D<T>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    // v * f
    inline Vector2D<T> operator*(const T scalar) const {
        return Vector2D<T>(x*scalar, y*scalar);
    }

    // v / d
    inline Vector2D<T> operator/(const T d) const {
        return (d != 0) ? Vector2D<T>(x/d, y/d) : Vector2D<T>();
    }

    inline Vector2D<T>& Zero() {
        this->x = 0;
        this->y = 0;
        return *this;
    }

    inline Vector2D<T>& One() {
        this->x = 1;
        this->y = 1;
        return *this;
    }

    inline friend std::ostream& operator<<(std::ostream& stream, const Vector2D<T>& v) {
        stream << "(" << v.x << "," << v.y << ")";
        return stream;
    }
};

using Vector2DInt = Vector2D<int>;
using Vector2DUInt = Vector2D<unsigned int>;
using Vector2DFloat = Vector2D<float>;
using Vector2DLongFloat = Vector2D<double>;