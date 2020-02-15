//
// Created by Дмитрий Метелица on 2019-07-06.
//

#pragma once


#import <AppKit/AppKit.h>
#import "Platform/OSX/OSXView.h"

@interface OGLView: OSXView

-(void)setOpenGLContext: (NSOpenGLContext*)context;
@end