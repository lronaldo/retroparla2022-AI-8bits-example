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
#include "entityman.h"
#include <cpctelera.h>

//////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
//////////////////////////////////////////////////////////////////////////////////
#define  CAPACITY_   MAX_ENTITIES   // Capacity of the entity array
Entity_t entities_[CAPACITY_];      // Entity array
u8       size_;                     // Current number of entities

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// init() : Initialize the manager
//
void man_entity_init() {
   size_ = 0;
}

//--------------------------------------------------------------------------------
// new() : Reserves space for a new entity
//
Entity_t* man_entity_new() {
   Entity_t* new_e = entities_ + size_;
   ++size_;
   return new_e;
}

//--------------------------------------------------------------------------------
// create() : Asks for a new entity and fills it up copying values from a template
//
Entity_t* man_entity_create(Entity_t const * const template) {
   Entity_t* new_e = man_entity_new();
   cpct_memcpy(new_e, template, sizeof(Entity_t));
   return new_e;
}

//--------------------------------------------------------------------------------
// delete() : Frees up the espace of a previously used entity
//
void man_entity_delete(Entity_t const * const e) {
   // If there is only one entity to delete
   if (size_ > 1) {
      // Check if we want to delete the last one
      Entity_t const* last_e = entities_ + size_ - 1;
      if (e != last_e) {
         // Delete one in the middle, copying the last one over
         cpct_memcpy(e, last_e, sizeof(Entity_t));
      }
   }
   // Remove one from the array
   --size_;
}

//--------------------------------------------------------------------------------
// mark_as_dead() : Marks an entity as dead, to be deleted next frame
//
void man_entity_mark_as_dead(Entity_t * const e) {
   e->cmps &= ~CMP_ALIVE;  // Remove Alive bit from entity
}

//--------------------------------------------------------------------------------
// forall_range() : Does some operation to all entities in a given range
//
void man_entity_forall_range(EntityProcessFunc_t const* process, u8 const idxbegin, u8 const idxend) {
   Entity_t*        it = entities_ + idxbegin;
   Entity_t const* end = entities_ + idxend;
   while(it < end) {
      process(it);
      ++it;
   }
}

//--------------------------------------------------------------------------------
// forall() : Does some operation to all entities
//
void man_entity_forall(EntityProcessFunc_t const* process) { man_entity_forall_range(process, 0, size_); }

//--------------------------------------------------------------------------------
// update() : Removes all entities marked as dead
//
void man_entity_update() {
   u8 i = 0;
   while (i < size_) {
      Entity_t * const e = entities_ + i;
      if ( (e->cmps & CMP_ALIVE) == 0 ) {
         man_entity_delete(e);
         continue;
      }
      ++i;
   }
}

//--------------------------------------------------------------------------------
// size() : Get current size of entity vector
//
u8 man_entity_size() { return size_; }
