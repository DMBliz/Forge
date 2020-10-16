//
// Created by Dmitry Metelitsa on 2019-11-23.
//

#include "RectI.h"

namespace Forge
{
    RectI::RectI()
        : x(0), y(0), width(0), height(0)
    {
    }

    RectI::RectI(const Vector2i& min, const Vector2i& max)
        : x(min.x), y(min.y), width(max.x - min.x), height(max.y - max.y)
    {
    }

    RectI::RectI(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height)
    {

    }

    RectI& RectI::operator=(const RectI& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        width = rhs.width;
        height = rhs.height;

        return *this;
    }

    bool RectI::operator==(const RectI& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               width == rhs.width &&
               height == rhs.height;
    }

    bool RectI::operator!=(const RectI& rhs) const
    {
        return x == rhs.x ||
               y == rhs.y ||
               width == rhs.width ||
               height == rhs.height;
    }

    void RectI::set(const RectI& rect)
    {
        *this = rect;
    }

    void RectI::set(const Vector2i& min, const Vector2i& max)
    {
        this->x = min.x;
        this->y = min.y;
        this->width = max.x - min.x;
        this->height = max.y - min.y;
    }

    void RectI::set(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Vector2i RectI::center() const
    {
        return Vector2i(x + width / 2, y + height / 2);
    }

    Vector2i RectI::size() const
    {
        return Vector2i(width, height);
    }

    String RectI::toString() const
    {
        return "(" + String(x) + ", " + String(y) + ", "
               + String(width) + ", " + String(height) + ")\n";
    }
}
