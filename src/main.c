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

#include <cpctelera.h>
#include <man/entityman.h>
#include <sys/rendersys.h>
#include <sys/prerendersys.h>
#include <sys/physicssys.h>
#include <sys/aisys.h>
#include <sys/spawnsys.h>
#include <utils/math.h>

// Define macro DEBUGBORDER to enable timing through border colours
#ifdef DEBUGBORDER
 #define B(V) cpct_setBorder((V))
#else
 #define B(V)
#endif

//--------------------------------------------------------------------------------
// main() : Start of the application
//
void main(void) {
   // Initializing
   cpct_disableFirmware();
   man_entity_init();
   sys_ren_init();
   sys_spawn_init();

   // Main Loop
   while (1) {
      B(HW_MAGENTA);      man_entity_update();
      B(HW_GREEN);        sys_spawn_update();
      B(HW_BLUE);         sys_phy_update();
      B(HW_RED);          sys_ai_update();
      B(HW_YELLOW);       sys_preren_update();
      B(HW_BLACK);        cpct_waitVSYNC();
      B(HW_BRIGHT_WHITE); sys_ren_update();
   }
}