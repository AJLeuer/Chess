//
//  Game.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Game.h"

Game::Game() :
	board(),	/* Note: Must be initialized first */
	player0(new AI(& board.boardRepresentation[0][0], & board.boardRepresentation[1][8])), //holds references to pieces at index (0, 0) through (1, 15)
	player1(new Human(& board.boardRepresentation[6][0], & board.boardRepresentation[7][8])) //holds references to pieces at index (6, 0) through (7, 7)
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
	
	auto sq = board.getSquare((unsigned)0, (unsigned)1) ;
	Piece * piece = sq->piece ;
	
	//piece->move({1, 3}) ;
}

void Game::display() {
	
	wstringstream * stream = new wstringstream() ;
	*stream << board ;
	wstring * str = new wstring(stream->str()) ;
	
	vec2<int> windowSize = convertToNativeVectorType<int>(window.getSize()) ;
	vec2<int> middle = windowSize / 2 ;
	
	window.clear(sf::Color(0, 202, 255, 128)) ;
	window.displayText(*str, middle) ;
	
	FastRand<unsigned> randm_x_1(0, 1) ;
	FastRand<unsigned> randm_x_2(6, 7) ;
	FastRand<unsigned> randm_y(0, 7) ;
	
	auto x = chooseAtRand(randm_x_1(), randm_x_2()) ;
	auto y = randm_y() ;
	
	auto pc = this->board.getSquare(unsigned(1), unsigned(0))->getPiece() ;
	auto spr = pc->getSprite() ;
	
	x = 1200 ;
	y = 700 ;
	
	spr.setPosition(x, y) ;
	window.draw(spr) ;
	
	window.display() ;
	
	delete stream ;
	delete str ;
}


void Game::runTests() {
	
	monitorMouse() ;
	
	while (true) {
		updateGameState() ;
		display() ;
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
















