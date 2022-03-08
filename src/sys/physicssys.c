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
#include "physicssys.h"
#include <cpctelera.h>
#include <man/entityman.h>
#include <utils/math.h>

//////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// check_input() : Checks input keyboard and modifies entity attributes
//
static void check_input(Entity_t * const e) {
   u8 const on_floor = (FIX2U8(e->y) + e->h) == FLOOR_Y;
   e->vx = 0;
   cpct_scanKeyboard_f();
   if       (on_floor && cpct_isKeyPressed(Key_CursorUp))   e->vy = FIXI16(-3.0);
   if       (cpct_isKeyPressed(Key_CursorRight))            e->vx = FIXI16( 1.0);
   else if  (cpct_isKeyPressed(Key_CursorLeft))             e->vx = FIXI16(-1.0);
}

//--------------------------------------------------------------------------------
// move_entity() : Move one entity according to its physics
//
static void move_entity(Entity_t * const e) { 
   { // Apply gravity
      i16 const v = e->vy + G_YVAL;
      e->vy = M_CLAMP(v, -MAX_VY, MAX_VY);
   }
   { // Clamp VX
      i16 const max = e->max_vx;
      e->vx = M_CLAMP(e->vx, -max, max);
   }
   { // X Axis
      u16 const x     = e->x + e->vx;
      u16 const max_x = MAX_X - U82FIX(e->w);
      e->x = M_CLAMP(x, MIN_X, max_x);
   }
   { // Y Axis
      u16 const y     = e->y + e->vy;
      u16 const max_y = U82FIX((FLOOR_Y - e->h));
      e->y = M_CLAMP_MAX(y, max_y);
   }
}

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// update() : Move all entities
//
void sys_phy_update() { 
   man_entity_forall_range(check_input, 0, 1);
   man_entity_forall(move_entity); 
}