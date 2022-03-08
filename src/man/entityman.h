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

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA
//////////////////////////////////////////////////////////////////////////////////
#define MAX_ENTITIES 5
typedef void(EntityProcessFunc_t)(Entity_t* e) ;

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////
void        man_entity_init();
Entity_t*   man_entity_new();
Entity_t*   man_entity_create(Entity_t const * const template);
void        man_entity_delete(Entity_t const * const e);
void        man_entity_forall(EntityProcessFunc_t* process);
void        man_entity_forall_range(EntityProcessFunc_t* process, u8 const idxbegin, u8 const idxend);
void        man_entity_mark_as_dead(Entity_t * const e);
void        man_entity_update();
u8          man_entity_size();