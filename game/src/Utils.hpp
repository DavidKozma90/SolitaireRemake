#pragma once
#include <raylib.h>
#include <vector>
#include <cstdint>

namespace Utils
{

#define DEFAULT_CTOR(ClassName)     ClassName() = default;

#define DEFAULT_DTOR(ClassName)     ~ClassName() = default;

#define DEFAULT_COPY(ClassName)     ClassName(const ClassName&) = default; \
                                    ClassName& operator=(const ClassName&) = default;

#define DEFAULT_MOVE(ClassName)     ClassName(ClassName&&) noexcept = default; \
                                    ClassName& operator=(ClassName&&) noexcept = default;

#define COPY_DISABLED(ClassName)    ClassName(const ClassName&) = delete; \
                                    ClassName& operator=(const ClassName&) = delete;

#define MOVE_DISABLED(ClassName)    ClassName(ClassName&&) noexcept = delete; \
                                    ClassName& operator=(ClassName&&) noexcept = delete;
typedef struct IVector2
{
    int32_t x;
    int32_t y;
} IVector2;

static inline Vector2 ToVector2(const IVector2& ivector)
{
    return 
    {
        .x = static_cast<float>(ivector.x), 
        .y = static_cast<float>(ivector.y)
    };
}

static inline IVector2 ToIVector2(const Vector2& vector)
{
    return 
    {
        .x = static_cast<int32_t>(vector.x),
        .y = static_cast<int32_t>(vector.y)
    };
}

}
