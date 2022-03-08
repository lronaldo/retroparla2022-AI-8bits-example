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

#include "math.h"

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// clamp()     : Clamps a value between min and max
// clamp_max() : Clamps only againts max
//
i8 clamp(i8 const value, i8 const min, i8 const max) {
   if       (value < min) return min;
   else if  (value > max) return max;
   return value;
}
u8 clamp_max(u8 const value, u8 const max) {
   u8 v = value;
   if (v > max) v = max;
   return v;
}

//--------------------------------------------------------------------------------
// u8toa() : Converts a u8 value to ascii
// u8toaz() : Converts u8 value to ascii adding zero char at the end8
//
void u8toa_impl(u8 const u8val, char* str, u8 addz) {
   u8 v = u8val; 
   u8 z = 0; 
   if      (v > 199) { *str = '2'; ++str; v -= 200; z=1; }
   else if (v >  99) { *str = '1'; ++str; v -= 100; z=1; }
   if (v > 9) {
      u8 const d = v/10;
      *str = '0' + d; ++str;
      v -= d*10;
   } else if(z != 0) {
      *str = '0'; ++str;
   }
   *str = '0' + v;
   if (addz) { ++str; *str=0; }
}
//--------------------------------------------------------------------------------
// u8toa_2dz() : Converts the 2 right digits of a u8 value into ascii.
//    It ignores the most-significant decimal digit if present, outputing
//    a 2-character zero-terminated string in [00-99].
//
void u8toa_2dz(u8 const u8val, char* str) {
   u8 v = u8val; 
   if      (v > 199) { v -= 200; }
   else if (v >  99) { v -= 100; }
   if (v > 9) {
      u8 const d = v/10;
      *str = '0' + d; ++str;
      v -= d*10;
   } else {
      *str = '0'; ++str;
   }
   *str = '0' + v;
   ++str; *str=0;
}