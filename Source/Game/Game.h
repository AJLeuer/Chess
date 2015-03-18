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
#include <string>
#include <sstream>
#include <thread>

#include <SFML/Window/Mouse.hpp>

#include "Config.h"
#include "Random.hpp"
#include "Board.h"
#include "Player.h"
#include "Window.h"

class Game {
	
protected:
	
	/** Note: Must be initialized first */
	Board board ;
	
	Player * player0 ;
	Player * player1 ;
	
	ChessWindow window ;
		
public:
	
	Game() ;
	
	Game(const Game & other) = delete ;
	
	~Game() ;
	
	Game & operator = (const Game & other) = delete ;
	
	void updateGameState() ;
	
	void display() ;
	
	void runTests() ;
	
	void monitorMouse() ;
};


#endif /* defined(__Chess__Game__) */
