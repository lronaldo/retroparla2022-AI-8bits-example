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
#include "rendersys.h"
#include <cpctelera.h>
#include <man/entityman.h>

//////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// render_entity() : Renders one entity
//
static void render_entity(Entity_t const * const e) {
   u8 const w = e->w;
   u8 const h = e->h;
   cpct_drawSolidBox(e->perase, 0, w, h);          // Erase entity
   if (e->cmps & CMP_ALIVE)
      cpct_drawSolidBox(e->pdraw , e->color, w, h);// Redraw entity (only when alive)
}

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// init() : Initializes the render system
//
void sys_ren_init() {
   cpct_setVideoMode(0);
   cpct_setBorder(HW_BLACK);

   // Draw floor
   {
      u8 const* p = cpctm_screenPtr(CPCT_VMEM_START,  0, 180);
      u8 const  c = cpctm_px2byteM0(6, 8);
      cpct_drawSolidBox(p +  0, c, 40, 20);
      cpct_drawSolidBox(p + 40, c, 40, 20);
   }
}

//--------------------------------------------------------------------------------
// update() : Renders all entities
//
void sys_ren_update() { man_entity_forall(render_entity); }