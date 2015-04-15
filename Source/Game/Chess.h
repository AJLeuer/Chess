//
//  Chess.h
//  Chess
//
//  Created by Adam James Leuer on 3/12/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#pragma once

namespace Chess {
	
enum class Color {
	black,
	white
} ;
	
inline Color getOpposite(Color color) {
	if (color == Color::black) {
		return Color::white ;
	}
	else /* if (color == Color::white) */ {
		return Color::black ;
	}
}
	

	
}



