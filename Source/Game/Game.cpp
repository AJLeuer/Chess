//
//  Game_Base.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Game.h"

using namespace std ;

namespace Chess {

Game_Base::Game_Base() :
	board(),	/* Note: Must be initialized first */
	player0(new AI(Chess::Color::white, & this->board)), //holds references to pieces at index (0, 0) through (1, 15)
	player1(new AI(Chess::Color::black, & this->board)) //holds references to pieces at index (6, 0) through (7, 7)
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

Game_Base::Game_Base(const Game_Base & other) :
	board(other.board),
	player0(new AI(* other.player0)),
	player1(new AI(* other.player1))
{
	board.game = this ;
	/* update players' board pointers */
	player0->board = & board ;
	player1->board = & board ;
}

Game_Base::~Game_Base() {
	if (player0 != nullptr) {
		delete player0 ;
	}
	
	if (player1 != nullptr) {
		delete player1 ;
	}
}


void Game_Base::commitMove(MoveIntent & move, bool recordMove) {
	
	Piece * movingPiece = move.piece ;
	
	assert(movingPiece->getSquareMutable()->board->game == this) ;//debug code only
	
	movingPiece->move(move.moveDestination) ;
	
	
	if (recordMove) {
		
		GameRecordEntry record(* movingPiece, move.moveDestination) ;
		
		gameRecord.push_back(record) ;
		
	}
}


MoveIntent Game_Base::tranlateMoveIntent(const Chess::MoveIntent & move) {
	
	MoveIntent copiedMove(move) ;
	
	Piece * equivelentPiece = board.findMatch(move.piece) ;
	
	copiedMove.piece = equivelentPiece ;
	
	return copiedMove ;
}
	
	

	
	
Game::Game() :
	Game_Base(),
	window()
{

}
	

Game::Game(const Game_Base & other) :
	Game_Base(other),
	window()
{
	
}

	
Game::Game(const Game & other) :
	Game_Base(other),
	window()
{
	
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
	
void Game::advanceGame(Player * currentPlayer, bool overrideMoveDecision, MoveIntent * overridingMove) {

	if ((gameLoops % 2) == 0) {
		currentPlayer = this->player0 ;
		
		/* Below is debug code only */
		auto allMoves = currentPlayer->findAllMoves() ;
	}
	else {
		currentPlayer = this->player1 ;
	}
	
	MoveIntent nextMove = currentPlayer->decideNextMove() ;
	
	commitMove(nextMove) ;
	
	this_thread::sleep_for(chrono::milliseconds(2000)) ;
	
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
	
	
	
	
SimulatedGame::SimulatedGame() :
	Game_Base()
{
	
}

	
SimulatedGame::SimulatedGame(const Game_Base & other) :
	Game_Base(other)
{
	
}

SimulatedGame::SimulatedGame(const SimulatedGame & other) :
	Game_Base(other)
{
	
}
	
void SimulatedGame::playGame() {

	while (true) {
		advanceGame() ;
		gameLoops++ ;
	}
}

void SimulatedGame::playDebugGame() {

	while (true) {
		advanceGame() ;
		gameLoops++ ;

	}
}
	
void SimulatedGame::advanceGame(Player * currentPlayer, bool overrideMoveDecision, MoveIntent * overridingMove) {
	
	if (overrideMoveDecision) {
		
		commitMove(* overridingMove, false) ; //don't waste time recording these simulated moves, there's way too many
		
	}
	else {
		
		MoveIntent nextMove = currentPlayer->decideNextMove() ;
		
		commitMove(nextMove, false) ;
	}
	//and definitely don't sleep
}
	
	
	
	
	
}













