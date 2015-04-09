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
#include <chrono>
#include <thread>

#include <SFML/Window/Mouse.hpp>

#include "../Util/Config.h"
#include "../Util/Random.hpp"

#include "Board.h"
#include "Player.h"

#include "../View/Window.h"

using namespace std ;

class Game {
	
protected:
	
	unsigned long gameLoops = 0 ;
	
	/** Note: Must be initialized first */
	Board board ;
	
	Player * player0 ;
	Player * player1 ;
	
	ChessWindow window ;
	
	void display() ;
	
	void updateGameState() ;
	
	/**
	 * Purely for development and debugging
	 */
	void testAndDebug() ;
	
	void monitorMouse() ;
		
public:
	
	Game() ;
	
	Game(const Game & other) = delete ;
	
	~Game() ;
	
	Game & operator = (const Game & other) = delete ;
	
	void playGame() ;
	
	/**
	 * For development and debugging
	 */
	void playDebugGame() ;
	
};


#endif /* defined(__Chess__Game__) */
