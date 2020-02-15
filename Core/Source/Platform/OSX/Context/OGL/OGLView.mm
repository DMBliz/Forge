//
// Created by Дмитрий Метелица on 2019-07-06.
//

#include "OGLView.h"

@implementation OGLView
{
    NSOpenGLContext* openGLContext;
}

-(void)setOpenGLContext:(NSOpenGLContext *)context
{
    openGLContext = context;
}

-(void)setLayer:(CALayer*)layer
{
    [super setLayer:layer];

    [openGLContext update];
}

@end