#include "../../include/graphics/rectangle.h"

#include "../../include/system/core.h"

/// @brief Create a new Rectangle at co-ordinates (0,0) with a width and height of 0
Rectangle::Rectangle()
{
    position = new Vector2(0, 0);
    width = 0;
    height = 0;
}

/// @brief Create a new Rectangle at the given co-ordinates, width and height
/// @param x The x co-ordinate
/// @param y The y co-ordinate
/// @param w The width
/// @param h The height
Rectangle::Rectangle(int x, int y, int w, int h)
{
    position = new Vector2(x, y);
    width = w;
    height = h;
}

/// @brief Create a new Rectangle using another rectangle as the source.
/// @param rectangle The source rectangle.
Rectangle::Rectangle(SDL_Rect rectangle)
{
    position = new Vector2(rectangle.x, rectangle.y);
    width = rectangle.w;
    height = rectangle.h;
}

/// @brief Destructor.
Rectangle::~Rectangle()
{
    delete position;
}

/// @brief Get the x co-ordinate
/// @return The x co-ordinate
int Rectangle::X()
{
    return position->X();
}

/// @brief Get the y co-ordinate
/// @return The y co-ordinate
int Rectangle::Y()
{
    return position->Y();
}

/// @brief Get the width
/// @return The width
int Rectangle::Width()
{
    return width;
}

/// @brief Get the height
/// @return The height
int Rectangle::Height()
{
    return height;
}

/// @brief Get whether a point is inside the rectangle
/// @param point The point
/// @return true if inside, false if not
bool Rectangle::Contains(Vector2* point)
{
    float pointX = point->X() * SCREEN_TOUCH_MULTIPLIER;
    float pointY = point->Y() * SCREEN_TOUCH_MULTIPLIER;

    delete point;

    return pointX >= X() && pointX <= X() + width
            && pointY >= Y() && pointY <= Y() + height;
}

/// @brief Move the rectangle to the position.
/// @param position The position.
void Rectangle::Move(Vector2* position)
{
    this->position->Move(position->X(), position->Y());

    delete position;
}