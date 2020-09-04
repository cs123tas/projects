/**
 * @file   LinearBrush.cpp
 *
 * Implementation of a brush with a linear mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "LinearBrush.h"

#include <math.h>

LinearBrush::LinearBrush(RGBA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


LinearBrush::~LinearBrush()
{
}

void LinearBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Linear brush here...

}


