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
// PRIVATE DATA
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// Player template
//
Entity_t const tmpl_player = {
       .cmps = (CMP_ALIVE | CMP_PHYSICS | CMP_RENDER)
   ,   .x = FIXU16(10.0) ,  .y = FIXU16(90.0)
   ,  .vx = FIXI16( 0.0) , .vy = FIXI16( 0.0)
   ,  .max_vx=FIXI16(1.0)
   ,   .w = 2  ,  .h = 16
   ,  .color = cpctm_px2byteM0(1, 1)
   ,  .pdraw = CPCT_VMEM_START
};

//--------------------------------------------------------------------------------
// Enemy template
//
Entity_t const tmpl_enemy = {
       .cmps = (CMP_ALIVE | CMP_PHYSICS | CMP_RENDER)
   ,   .x = FIXU16(40.0) ,  .y = FIXU16(50.0)
   ,  .vx = FIXI16( 0.0) , .vy = FIXI16( 0.0)
   ,  .max_vx=FIXI16(1.0)
   ,  .w = 2  ,  .h = 8
   ,  .color = cpctm_px2byteM0(2, 2)
   ,  .pdraw = CPCT_VMEM_START
   ,  .ai = { .beh=ai_beh_follow, .decision_period=0 }
};

typedef enum {
      GUI_start
   ,  GUI_MaxV
   ,  GUI_DecP
   ,  GUI_end
} GUIElem_t;

#define SPAWN_COOLDOWN  15          // Cycles of cooldown between consecutive spawns
#define BG_SELECTED      6          // Palete colour for selected GUI Element
#define MAXV_STEP       FIXI16(0.1) // Amount to increase MAXV
#define DECP_STEP        1          // Amount to increase DECP
static Entity_t* s_player; // Reference to the player for later usage 
static u8 spawn_countdown; // Count down between spawns
static u8 color;           // Color for each new enemy
static u8 decP;            // Enemy decision period
static u16 maxV;           // MaxV Gui Value
static GUIElem_t selected; // Selected GUI Element

//////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// gui_<ELEMENT>_draw() : Draws a given GUI element
//
static void gui_maxV_draw() {
   u8 * const p = cpctm_screenPtr(CPCT_VMEM_START, 10, 10);
   static char const str[] = "MaxV= .  ";
   u8 bg = (selected == GUI_MaxV) ? BG_SELECTED : 0;
   u8 dec = FIX2U8DEC(maxV);
   u8toa(FIX2U8(maxV), str+5);
   u8toa_2dz(dec, str+7);
   cpct_setDrawCharM0(1, bg);
   cpct_drawStringM0(str, p);
}
static void gui_decP_draw() {
   u8 * const p = cpctm_screenPtr(CPCT_VMEM_START, 50, 10);
   static char const str[] = "DecP=  ";
   u8 bg = (selected == GUI_DecP) ? BG_SELECTED : 0;
   u8toa(decP, str+5);
   cpct_setDrawCharM0(1, bg);
   cpct_drawStringM0(str, p);
}

//--------------------------------------------------------------------------------
// draw_gui() : Draws all GUI elements
//
static void draw_gui() {
   gui_maxV_draw();
   gui_decP_draw();
}

//--------------------------------------------------------------------------------
// select_XXXXX_gui_elem() : Selects next or previous gui element
//
static void select_next_gui_elem() {
   if (++selected == GUI_end)
      selected = GUI_start + 1;
   draw_gui();
}
static void select_prev_gui_elem() {
   if (--selected == GUI_start)
      selected = GUI_end - 1;
   draw_gui();
}
//--------------------------------------------------------------------------------
// increase_gui_elem() : Increases the value of the given gui element
//
static void increase_gui_elem () {
   switch(selected) {
      case GUI_MaxV: maxV += MAXV_STEP; break;
      case GUI_DecP: decP += DECP_STEP; break;
   }
   draw_gui();
}
//--------------------------------------------------------------------------------
// decrease_gui_elem() : Decreases the value of the given gui element
//
static void decrease_gui_elem () {
   switch(selected) {
      case GUI_MaxV: if (maxV > MAXV_STEP) { maxV -= MAXV_STEP; } else { maxV = 0; } break;
      case GUI_DecP: if (decP) { decP -= DECP_STEP; } break;
   }
   draw_gui();
}


//--------------------------------------------------------------------------------
// spawn_enemy() : Spawns a new enemy
//
static void spawn_enemy() {
   Entity_t* enemy  = man_entity_create(&tmpl_enemy);
   u8 const c = (color < 15) ? color + 1 : 2;
   color = c;
   enemy->ai.target_e = s_player;
   enemy->color = cpct_px2byteM0(c, c);
   enemy->ai.decision_period = decP;
   enemy->max_vx = maxV;
   spawn_countdown = SPAWN_COOLDOWN;
}

//--------------------------------------------------------------------------------
// kill_enemies() : Kills all enemies
//
static void kill_enemies() {
   u8 const end = man_entity_size();
   man_entity_forall_range(man_entity_mark_as_dead, 1, end);
}

//--------------------------------------------------------------------------------
// check_keys() : Checks por keypresses and performs desired action
//
typedef struct { enum cpct_e_keyID key; void(*action)(void); } KeyAction_t;
KeyAction_t const ka_table[] ={
      { Key_Space , spawn_enemy           }
   ,  { Key_K     , kill_enemies          }
   ,  { Key_W     , increase_gui_elem     }
   ,  { Key_S     , decrease_gui_elem     }
   ,  { Key_A     , select_prev_gui_elem  }
   ,  { Key_D     , select_next_gui_elem  }
   ,  { 0         , 0                     }
};
static void check_keys() {
   KeyAction_t const* ka = ka_table;
   while (ka->action != 0) {
      if (cpct_isKeyPressed(ka->key)) {
         ka->action();
         spawn_countdown = SPAWN_COOLDOWN;
      }
      ++ka;
   }
}

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// init() : Initializes the entity spawner
//
void sys_spawn_init() { 
   s_player = man_entity_create(&tmpl_player);
   selected = GUI_MaxV;
   maxV     = FIXI16(1.0);
   color    = 2;
   decP     = 0;
   spawn_enemy();
   draw_gui();
}

//--------------------------------------------------------------------------------
// update() : Updates the entity spawner system
//
void sys_spawn_update() { 
   if (spawn_countdown > 0) {
      --spawn_countdown;
   } else {
      check_keys();
   }
}