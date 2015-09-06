//
//  Color.h
//  Chess
//
//  Created by Adam James Leuer on 4/23/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Color_h
#define Chess_Color_h

#include <iostream>
#include <array>
#include <cstdint>

using namespace std ;

typedef uint8_t byte ;

struct TrueColor {
	
	array<byte, 4> RGBA ;
	
	inline constexpr TrueColor(byte R, byte G, byte B, byte A) : RGBA({R, G, B, A}) {}
	
	inline constexpr operator array<byte, 4>() const { return this->RGBA ; }
	
	template <typename ColorType>
	inline constexpr operator ColorType() const { return ColorType { R(), G(), B(), A()} ; }
	
	inline constexpr byte R() const { return RGBA[0] ; }
	
	inline constexpr byte G() const { return RGBA[1] ; }
	
	inline constexpr byte B() const { return RGBA[2] ; }
	
	inline constexpr byte A() const { return RGBA[3] ; }
	
	inline constexpr float R_float() const { return (float)(RGBA[0] + 1) / 256 ; }
	
	inline constexpr float G_float() const { return (float)(RGBA[1] + 1) / 256 ; }
	
	inline constexpr float B_float() const { return (float)(RGBA[2] + 1) / 256 ; }
	
	inline constexpr float A_float() const { return (float)(RGBA[3] + 1) / 256 ; }
	
};


#endif
