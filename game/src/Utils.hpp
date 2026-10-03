#pragma once
#include <raylib.h>
#include <vector>
#include <cstdint>

namespace Utils
{

typedef struct IVector2
{
    int32_t x;
    int32_t y;
} IVector2;

static inline Vector2 ToVector2(const IVector2& ivector)
{
    Vector2 vector = 
    {
        .x = static_cast<float>(ivector.x), 
        .y = static_cast<float>(ivector.y)
    };

    return vector;
}

static inline IVector2 ToIVector2(const Vector2& vector)
{
    IVector2 ivector;
    ivector.x = static_cast<int32_t>(vector.x);
    ivector.y = static_cast<int32_t>(vector.y);
    return ivector;
}

}
