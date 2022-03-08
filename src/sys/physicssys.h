//------------------------------------------------------------------------------------------------------------------------------
// MIT License 
//   This file is part of AI-parla, an AI example demonstrating Decision Period shown at RetroParla 2022
//   Copyright © 2022 Francisco J. Gallego-Durán (@FranGallegoBR, Profesor Retroman, fjgallego@ua.es)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//------------------------------------------------------------------------------------------------------------------------------
#pragma once

#include <cmp/entity.h>

#define MAX_VY    FIXI16( 4.00)   // Maximum VY down velocity
#define MAX_VX    FIXI16( 2.00)   // Maximum VX right velocity
#define G_YVAL    FIXI16( 0.25)   // Amount of VY increment per gravity application
#define FLOOR_Y   ((u8)180)       // X where the floor starts
#define MIN_X     FIXU16( 2.00)   // Minimum X value for an entity
#define MAX_X     FIXU16(78.00)   // Maximum X value for an entity

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////
void sys_phy_update();