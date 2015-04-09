//
//  Game.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Game.h"

using namespace std ;

Game::Game() :
	board(),	/* Note: Must be initialized first */
	player0(new AI(ChessColor::white, this->board)), //holds references to pieces at index (0, 0) through (1, 15)
	player1(new Human(ChessColor::black, this->board)) //holds references to pieces at index (6, 0) through (7, 7)
{
	
}

Game::~Game() {
	if (player0 != nullptr) {
		delete player0 ;
	}
	
	if (player1 != nullptr) {
		delete player1 ;
	}
}


void Game::updateGameState() {
	//todo
}

void Game::testAndDebug() {
	//all for debugging
	static Piece * pawn  ;
	
	if (gameLoops == 0) {
		pawn = this->board(0, 1)->getPieceUnsafe() ;
	}
	
	bool canMove = pawn->canMove() ;
	Position pos = *(pawn->getPosition()) ;
	pos.y++ ;
	pawn->move({pos.x, pos.y}) ;
	
	this_thread::sleep_for(chrono::milliseconds(2000)) ;
	
	short val = board.evaluate(pawn->getColor()) ;
	auto i = 1 ;
}

void Game::display() {
	
	wstringstream * stream = new wstringstream() ;
	*stream << board ;
	wstring * str = new wstring(stream->str()) ;
	
	vec2<int> windowSize = convertToNativeVectorType<int>(window.getSize()) ;
	vec2<int> middle = windowSize / 2 ;
	
	window.clear(sf::Color(0, 202, 255, 128)) ;
	window.displayText(*str, middle) ;
	
	window.display() ;
	
	delete stream ;
	delete str ;
}


void Game::playGame() {
	
	monitorMouse() ;
	
	while (true) {
		updateGameState() ;
		display() ;
		gameLoops++ ;
		this_thread::sleep_for(chrono::milliseconds(4)) ;
	}
	
}

void Game::playDebugGame() {
	monitorMouse() ;
	
	while (true) {
		testAndDebug() ;
		display() ;
		gameLoops++ ;
		this_thread::sleep_for(chrono::milliseconds(4)) ;
	}
	
}

void Game::monitorMouse() {
	
	auto mouseMonitor = []() -> void {
		while (true) {
			if (Mouse::isButtonPressed(buttonMain)) {
		
				Position mousePosition = convertToNativeVectorType<int, int>(Mouse::getPosition()) ;
				
				//cout << "Main mouse button pressed." << endl ;
				//cout << "Coordinates: " << mousePosition << endl ;
			}
			this_thread::sleep_for(chrono::microseconds(100)) ;
		}
	} ;
	
	std::thread mouseThread(mouseMonitor) ;
	mouseThread.detach() ;
}
















