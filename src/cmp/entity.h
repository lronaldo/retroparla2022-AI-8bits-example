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
#include <types.h>

// Behaviour function type
struct Entity;
typedef u8(BehaviourFunc_t)(struct Entity*);

// AI Information structure
typedef struct AI {
   BehaviourFunc_t* beh;
   struct Entity* target_e;
   u8 decision_count, decision_period;
} AI_t;

// Entity Components & Status
typedef enum {
      CMP_ALIVE   = 0x80
   ,  CMP_PHYSICS = 0x40
   ,  CMP_RENDER  = 0x20
} Component_t;

// Entity Structure
typedef struct Entity {
   u8     cmps;   // Components
   u16   x,  y;   // Fixed 8.8 
   i16  vx, vy;   // Fixed 8.8
   i16  max_vx;   // Fixed 8.8
   u8    w,  h;
   u8   color;
   u8   *perase, *pdraw;
   AI_t  ai;      // All AI information
} Entity_t;