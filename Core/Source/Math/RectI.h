//
// Created by Dmitry Metelitsa on 2019-11-23.
//

#pragma once

#include "Vector2i.h"

namespace Forge
{
    class RectI
    {
    public:
        static const RectI Zero;

        int x, y, width, height;

        RectI();
        RectI(const Vector2i& min, const Vector2i& max);
        RectI(int x, int y, int width, int height);

        RectI& operator=(const RectI& rhs);
        bool operator==(const RectI& rhs) const;
        bool operator!=(const RectI& rhs) const;

        void set(const RectI& rect);
        void set(int x, int y, int width, int height);
        void set(const Vector2i& min, const Vector2i& max);

        Vector2i center() const;
        Vector2i size() const;

        String toString() const;
    };

}