#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../Vector2D.h"
#include "../Component.h"

class Transform : public Component {
public:
    Transform() = default;

    Transform(float x, float y) {
        Position.x = x;
        Position.y = y;
    }

    Transform(float x, float y, float scaleX, float scaleY) {
        Position.x = x;
        Position.y = y;
        Scale.x = scaleX;
        Scale.y = scaleY;
    }

    Transform(float x, float y, float scaleX, float scaleY, float rotation) {
        Position.x = x;
        Position.y = y;
        Scale.x = scaleX;
        Scale.y = scaleY;
        Rotation = rotation;
    }

    virtual ~Transform() = default;

    Vector2DFloat Position = Vector2DFloat();
    Vector2DFloat Scale = Vector2DFloat(1,1);
    float Rotation = 0.0f;

private:
};

#endif