//
//  Game.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Game.h"

void Game::runTests() {
	
	wstringstream * stream = new wstringstream() ;
	*stream << board ;
	cout << board ;
	wstring * str = new wstring(stream->str()) ;
	
	auto open = window.isOpen() ;
	
	//more tests
	auto sq = board.getSquare((unsigned)0, (unsigned)1) ;
	Piece * piece = sq->piece ;
	piece->move({1, 3}) ;
	
	while (true) {
		window.clear() ;
		window.draw("│ ♖ │ ♘ │ ♗ │ ♕ │ ♚ │ ♗ │ ♘ │ ♖ ││") ;
		window.display() ;
		this_thread::sleep_for(chrono::milliseconds(4)) ;
	}
}
