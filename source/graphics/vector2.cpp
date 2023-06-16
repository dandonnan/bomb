#include "../../include/graphics/vector2.h"

/// @brief Create a Vector2 with co-ordinates (0, 0)
Vector2::Vector2()
{
    x = 0;
    y = 0;
}

/// @brief Create a Vector2 with the given co-ordinates
/// @param x The x co-ordinate
/// @param y The y co-ordinate
Vector2::Vector2(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2::~Vector2()
{
}

/// @brief Get the x co-ordinate
/// @return The x co-ordinate
int Vector2::X()
{
    return x;
}

/// @brief Get the y co-ordinate
/// @return The y co-ordinate
int Vector2::Y()
{
    return y;
}

/// @brief Move the position to the new co-ordinates.
/// @param x The x co-ordinate.
/// @param y The y co-ordinate.
void Vector2::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}