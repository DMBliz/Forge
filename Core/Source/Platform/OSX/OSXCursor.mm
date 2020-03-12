//
// Created by Дмитрий Метелица on 3/11/20.
//

#include "OSXCursor.h"

namespace Forge
{

    OSXCursor::OSXCursor(const std::vector<byte>& imageData, int width, int height, int xHotSpot, int yHotSpot)
            : Cursor(imageData, width, height, xHotSpot, yHotSpot)
    {
        @autoreleasepool {
        if (imageData.empty())
            return;

        byte* rgba = this->imageData.data();

        NSImage* image = [[[NSImage alloc] initWithSize:NSMakeSize(width, height)] autorelease];
        NSBitmapImageRep* imageRep = [[[NSBitmapImageRep alloc]
                                        initWithBitmapDataPlanes:&rgba
                                                      pixelsWide:width
                                                      pixelsHigh:height
                                                   bitsPerSample:8
                                                 samplesPerPixel:4
                                                        hasAlpha:YES
                                                        isPlanar:NO
                                                  colorSpaceName:NSCalibratedRGBColorSpace
                                                    bitmapFormat:NSBitmapFormatAlphaNonpremultiplied
                                                     bytesPerRow:this->width * 4
                                                    bitsPerPixel:32] autorelease];

        [image addRepresentation:imageRep];
        cursor = [[NSCursor alloc] initWithImage:image
                                         hotSpot:NSMakePoint(xHotSpot, yHotSpot)];

        [image release];
        [imageRep release];


        }
    }

    OSXCursor::OSXCursor(SystemCursor cursor)
            : Cursor(cursor)
    {
        switch (systemCursor)
        {
            default:
            case SystemCursor::Arrow:
                this->cursor = [NSCursor arrowCursor];
                break;
            case SystemCursor::Hand:
                this->cursor = [NSCursor openHandCursor];
                break;
            case SystemCursor::HorizontalResize:
                this->cursor = [NSCursor resizeLeftRightCursor];
                break;
            case SystemCursor::VerticalResize:
                this->cursor = [NSCursor resizeUpDownCursor];
                break;
            case SystemCursor::Cross:
                this->cursor = [NSCursor crosshairCursor];
                break;
            case SystemCursor::IBeam:
                this->cursor = [NSCursor IBeamCursor];
                break;
        }

        if(this->cursor)
            [this->cursor retain];
    }

    NSCursorPtr OSXCursor::getNativeCursor()
    {
        return cursor;
    }
}