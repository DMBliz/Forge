//
// Created by Dmitry Metelitsa on 2019-07-06.
//

#pragma once


#import <AppKit/AppKit.h>
#import "Platform/MacOS/MacOSView.h"

@interface OGLView: MacOSView

-(void)setOpenGLContext: (NSOpenGLContext*)context;
@end