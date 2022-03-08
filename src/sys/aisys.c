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

#include "aisys.h"
#include <cpctelera.h>
#include <utils/math.h>
#include <man/entityman.h>

//////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// process_entity_ai() : Process AI for one entity
//
static void process_entity_ai(Entity_t * const e) {
   AI_t * const ai = &e->ai;
   u8 cnt = ai->decision_count;
   if (cnt == 0) {
      BehaviourFunc_t* beh_func = ai->beh;
      if (beh_func)
         beh_func(e);
      cnt = ai->decision_period;
   } else {
      --cnt;
   }
   ai->decision_count = cnt;
}

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// ai_beh_follow() : Moves following a given target entity
//
u8 ai_beh_follow(Entity_t * const e) {
   Entity_t* tgt = e->ai.target_e;
   e->vx = 0;
   if (tgt) {
      if      ( e->x < tgt->x ) e->vx = FIXI16( 1);
      else if ( e->x > tgt->x ) e->vx = FIXI16(-1);
   }
   return 0;
}

//--------------------------------------------------------------------------------
// update() : Process AI for all entities
//
void sys_ai_update() { man_entity_forall(process_entity_ai); }