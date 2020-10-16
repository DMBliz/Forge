//
// Created by Dmitry Metelitsa on 2/29/20.
//

#pragma once
#include "Types.h"
#include <vector>

namespace Forge
{
    enum class SystemCursor
    {
        Arrow,
        Hand,
        VerticalResize,
        HorizontalResize,
        Cross,
        IBeam
    };


    class Cursor
    {
    protected:
        SystemCursor systemCursor;
        std::vector<byte> imageData;
        int width, height;
        int xHotSpot, yHotSpot;
    public:
        Cursor(SystemCursor cursor)
            : systemCursor(cursor)
        {
        }

        Cursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot)
            : imageData(imageData), width(width), height(height), xHotSpot(xHotSpot), yHotSpot(yHotSpot)
        {
        }

        ~Cursor()
        {

        }

    };
}