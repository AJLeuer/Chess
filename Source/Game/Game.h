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
#include "../Util/Util.h"
#include "../Util/Random.hpp"

#include "Support.h"
#include "Board.h"
#include "Player.h"

#include "../View/Window.h"

using namespace std ;

int main(int, char **) ;

namespace Chess {

class Game {
	
protected:
	
	
	unsigned long gameLoops = 0 ;
	
	/** Note: Must be initialized first */
	Board board ;
	
	Player * player0 ;
	Player * player1 ;
	
	ChessWindow window ;
	
	void display() ;
	
	void advanceGame() ;
	
	void advanceGame_Simulated(Player * currentPlayer, bool overrideMoveDecision, MoveIntent * overridingMove) ;
	
	void commitMove(MoveIntent & move, bool recordMove = true) ;
	
	void monitorMouse() ;
	
	vector<GameRecordEntry> gameRecord ;
	
	friend class AI ;
	
	friend int ::main(int, char **) ; //for debug only
	
		
public:
	
	Game() ;
	
	/**
	 * Copy constructor. Right now, the only use is createing temporary games to run simulations
	 */
	Game(const Game & other) ;
	
	~Game() ;
	
	Game & operator = (const Game & other) = delete ;
	
	void playGame() ;
	
	/**
	 * For development and debugging
	 */
	void playDebugGame() ;
	
	/**
	 * @return The Player with the same color as the Player * passed in as an argument
	 */
	Player * getMatchingPlayer(const Player & player) { return (player.getColor() == player0->getColor()) ? player0 : player1 ;  }
	
	/**
	 * @return The Player with the color opposite the Player * passed in as an argument
	 */
	Player * getOpponentPlayer(const Player & player) { return (player.getColor() != player0->getColor()) ? player0 : player1 ;  }
	
};
	
}


#endif /* defined(__Chess__Game__) */
