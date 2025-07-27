#pragma once
#include <raylib.h>

typedef struct IVector2
{
    int x;
    int y;
} IVector2;

static inline Vector2 ToVector2(const IVector2& ivector)
{
    Vector2 vector;
    vector.x = static_cast<float>(ivector.x);
    vector.y = static_cast<float>(ivector.y);
    return vector;
}

static inline IVector2 ToIVector2(const Vector2& vector)
{
    IVector2 ivector;
    ivector.x = static_cast<int>(vector.x);
    ivector.y = static_cast<int>(vector.y);
    return ivector;
}
