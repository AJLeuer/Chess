//
//  Game.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Game.h"

using namespace std ;

namespace Chess {

Game::Game() :
	board(),	/* Note: Must be initialized first */
	player0(new AI(Chess::Color::white, & this->board)), //holds references to pieces at index (0, 0) through (1, 15)
	player1(new AI(Chess::Color::black, & this->board)), //holds references to pieces at index (6, 0) through (7, 7)
	window()
{
	board.game = this ;
	for (auto i = 0 ; i < board.boardRepresentation.size() ; i++) {
		for (auto j = 0 ; j < board.boardRepresentation[i].size() ; j++) {
			auto * piece = board.getSquareMutable({i, j})->getPieceMutable() ;
			if (piece != nullptr) {
				piece->initSpriteTexture() ;
			}
		}
	}
	
}

Game::Game(const Game & other) :
	board(other.board),
	player0(new AI(* other.player0)),
	player1(new AI(* other.player1))
	/* don't create another window. this will usually just create a temporary game to run simulations,
	 so no need for displaying */
{
	board.game = this ;
	/* update players' board pointers */
	player0->board = & board ;
	player1->board = & board ;
}

Game::~Game() {
	if (player0 != nullptr) {
		delete player0 ;
	}
	
	if (player1 != nullptr) {
		delete player1 ;
	}
}


void Game::advanceGame() {
	Player * currentPlayer ;
	
	if ((gameLoops % 2) == 0) {
		currentPlayer = this->player0 ;
	}
	else {
		currentPlayer = this->player1 ;
	}
	
	MoveIntent nextMove = currentPlayer->decideNextMove() ;
	
	commitMove(nextMove) ;

	this_thread::sleep_for(chrono::milliseconds(2000)) ;

}

void Game::advanceGame_Simulated(Player * currentPlayer, bool overrideMoveDecision, MoveIntent * overridingMove) {
	
	if (overrideMoveDecision) {
		
		commitMove(* overridingMove, false) ; //don't waste time recording these simulated moves, there's way too many
		
	}
	else {
		
		MoveIntent nextMove = currentPlayer->decideNextMove() ;
		
		commitMove(nextMove, false) ;
	}
	//and definitely don't sleep
}
	
void Game::commitMove(MoveIntent & move, bool recordMove) {
	
	Piece * movingPiece = move.piece ;
	
	movingPiece->move(move.moveDestination) ;
	
	
	if (recordMove) {
		
		GameRecordEntry record(* movingPiece, move.moveDestination) ;
		
		gameRecord.push_back(record) ;
		
	}
}


void Game::display() {
	
	wstringstream * stream = new wstringstream() ;
	*stream << board ;
	wstring * str = new wstring(stream->str()) ;
	
	vec2<int> windowSize = convertToNativeVectorType<int>(window.getSize()) ;
	auto middle = windowSize / 2 ;

	window.clear(windowBackgroundColor) ;
	
	//commented out for debugging, uncomment
	/*
	for (auto i = 0 ; i < board.boardRepresentation.size() ; i++) {
		for (auto j = 0 ; j < board.boardRepresentation[i].size() ; j++) {
			auto * piece = board.getSquare(i, j)->getPiece() ;
			if (piece != nullptr) {
				window.draw(piece->getSprite()) ;
			}
		}
	} */
	
	window.displayText(*str, windowForegroundColor, middle) ;
	
	window.display() ;
	
	delete stream ;
	delete str ;
}


void Game::playGame() {
	
	monitorMouse() ;
	
	while (true) {
		advanceGame() ;
		display() ;
		gameLoops++ ;
		this_thread::sleep_for(chrono::milliseconds(4)) ;
	}
	
}

void Game::playDebugGame() {
	monitorMouse() ;
	
	while (true) {
		display() ;
		advanceGame() ;
		gameLoops++ ;
		this_thread::sleep_for(chrono::milliseconds(4)) ;
	}
	
}

void Game::monitorMouse() {
	
	auto mouseMonitor = []() -> void {
		while (true) {
			if (Mouse::isButtonPressed(buttonMain)) {
		
				vec2<int> mousePosition = convertToNativeVectorType<int, int>(Mouse::getPosition()) ;
				
				//cout << "Main mouse button pressed." << endl ;
				//cout << "Coordinates: " << mousePosition << endl ;
			}
			this_thread::sleep_for(chrono::microseconds(100)) ;
		}
	} ;
	
	std::thread mouseThread(mouseMonitor) ;
	mouseThread.detach() ;
}


}













