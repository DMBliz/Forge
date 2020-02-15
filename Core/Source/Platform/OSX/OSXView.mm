//
// Created by Дмитрий Метелица on 2019-07-06.
//

#import "OSXView.h"
#import <Carbon/Carbon.h>

@implementation OSXView

-(BOOL)isOpaque
{
    return YES;
}

-(BOOL)mouseDownCanMoveWindow
{
    return YES;
}

-(BOOL)isFlipped
{
    return YES;
}

-(BOOL)acceptsFirstResponder
{
    return YES;
}

-(BOOL)acceptsFirstMouse:(__unused NSEvent*)event
{
    return YES;
}


-(void)resetCursorRects
{
    [super resetCursorRects];
    //TODO: process input for mac os
}

#if !defined(__MAC_10_12) || __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_10_12
enum
{
    kVK_RightCommand = 0x36
};
#endif


@end