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

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////
i8 clamp(i8 const value, i8 const min, i8 const max);
u8 clamp_max(u8 const value, u8 const max);
void u8toa_impl(u8 const u8val, char* str, u8 addz);
#define u8toa(V,C)  u8toa_impl((V), (C), 0)
#define u8toaz(V,C) u8toa_impl((V), (C), 1)
void u8toa_2dz(u8 const u8val, char* str);

//////////////////////////////////////////////////////////////////////////////////
// PUBLIC MACROS
//////////////////////////////////////////////////////////////////////////////////
#define M_CLAMP_MIN(VAL, MIN)  ((VAL) < (MIN) ? (MIN) : (VAL))
#define M_CLAMP_MAX(VAL, MAX)  ((VAL) > (MAX) ? (MAX) : (VAL))
#define M_CLAMP(VAL, MIN, MAX) M_CLAMP_MIN(M_CLAMP_MAX((VAL), (MAX)), (MIN))

// Fixed Point Arithmetic
#define FIX_SCALE    256   // Scale for fixed point arithmetic 8.8 (*256)
#define FIX2U8(V)    ((u8)(((V)/FIX_SCALE)&0x00FF))
#define FIX2U8DEC(V) ((u8)(((V)%FIX_SCALE)*10/26)) // Just an approximation, but useful
#define FIX2I8(V)    ((i8)((V)/FIX_SCALE))
#define U82FIX(V)    ((u16)((V)*FIX_SCALE))
#define I82FIX(V)    ((i16)((V)*FIX_SCALE))
#define FIXU16(V)    ((u16)((V)*FIX_SCALE))
#define FIXI16(V)    ((i16)((V)*FIX_SCALE))
