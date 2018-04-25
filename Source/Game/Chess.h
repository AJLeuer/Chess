//
//  Chess.h
//  Chess
//
//  Created by Adam James Leuer on 3/12/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#pragma once

#include "../Util/Color.h"

namespace Chess {
	
/**
 * The number of rows on the chessboard
 */
static constexpr unsigned ranks = 8 ;

/**
 * The number of columns on the chessboard
 */
static constexpr unsigned files = 8 ;
	
static constexpr TrueColor windowBackgroundColor {0x00, 0x00, 0x00, 160} ; // NOLINT
static constexpr TrueColor windowForegroundColor {0x9D, 0xFF, 0x00, 254} ; // NOLINT

enum class Color {
	black,
	white
} ;
	
inline constexpr Color getOpposite(Color color) {
	if (color == Color::black) {
		return Color::white ;
	}
	else /* if (color == Color::white) */ {
		return Color::black ;
	}
}
	

	
}



