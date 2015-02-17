//
//  Game.h
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Game__
#define __Chess__Game__

#include <iostream>
#include <sstream>
#include <thread>

#include "Board.h"
#include "Player.h"
#include "Window.h"

class Game {
	
protected:
	
	Player player0 ;
	Player player1 ;
	
	Board board ;
	
	ChessWindow window ;
	
public:
	
	Game() {}
	
	void runTests() ;
};


#endif /* defined(__Chess__Game__) */