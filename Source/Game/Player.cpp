//
//  Player.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Player.h"

using namespace std ;

namespace Chess {

unsigned long Player::uniqueIDs = 1 ;


list <Piece *> Player::initPieces(Chess::Color playerColor, const Board & board) {
	
	list<Piece *> pieces ;
	
	if (playerColor == Chess::Color::black) { //grab black's squares at their starting positions
		
		for (auto x = 0 ; x < board.boardRepresentation.size() ; x++) {
			
			for (auto y = 7 ; y >= 6 ; y--) {
				
				const Square * square = & (board.boardRepresentation[x][y]) ;
				
				Piece * piece = square->piece ;
				
				pieces.push_front(piece) ;

			}
		}
	}
	
	else /* if (playerColor == Chess::Color::white) */ { //grab white's squares at their starting positions
		
		for (auto x = 0 ; x < board.boardRepresentation.size() ; x++) {
			
			for (auto y = 0 ; y <= 1 ; y++) {
				
				const Square * square = & (board.boardRepresentation[x][y]) ;
				
				Piece * piece = square->piece ;
				
				pieces.push_front(piece) ;
				
			}
		}
	}
	
	return pieces ;
}


Player::Player(Chess::Color color, Board * board) :
	ID(uniqueIDs++),
	name("Player " + to_string(ID)),
	color(color),
	board(board),
	startingPieces(initPieces(color, * board)),
	remainingPieces()
{
	remainingPieces = startingPieces ;
	registerForNotifications() ;
}


Player::Player(Player && other) :
	ID(other.ID),
	name(std::move(other.name)),
	color(std::move(other.color)),
	startingPieces(std::move(other.startingPieces)),
	remainingPieces(std::move(other.remainingPieces))
{
	other.ID = 0 ;
}

Player & Player::operator = (Player && other) {

	this->ID = std::move(other.ID) ;
	this->name = std::move(other.name) ;
	this->color = std::move(other.color) ;
	this->startingPieces = std::move(other.startingPieces) ;
	this->remainingPieces = std::move(other.remainingPieces) ;
		
	other.ID = 0 ;
	
	return * this ;
}
	
vector<const Piece *> Player::copyCurrentPieces(const Board & workingBoard) {
	
	vector<const Piece *> workingPieces ;
	
	for (auto out = this->remainingPieces.begin() ; out != remainingPieces.end() ; out++) {
		Piece * p = * out ;
		const Piece * workingPiece = workingBoard.getSquare(* p->getPosition())->getPiece() ;
		workingPieces.push_back(workingPiece) ;
	}
	
	return workingPieces ;
}

void Player::removePiece(Piece * piece) {
	bool pieceNotFound = true ; //debug var, remove
	
	for (auto pieceIterator = remainingPieces.begin(); pieceIterator != remainingPieces.end() ; pieceIterator++) {
		if (* pieceIterator == piece) {
			this->remainingPieces.erase(pieceIterator) ;
			pieceNotFound = false ;
		}
	}
	
	//debug code
	if (pieceNotFound) {
		cerr << "Unexpected behavior in Player::removePiece(). Could not find a match for the given argument in remainingPieces" << endl ;
	}
	
}

void Player::registerForNotifications() {
	using namespace std::placeholders ;
	//The major use of notifications is to keep our remainingPieces() updated
	
	//Register to be notified when one of our pieces is captured...
	for (auto pieceIterator = startingPieces.begin() ; pieceIterator != startingPieces.end() ; pieceIterator++) {
		
		Piece * piece = *(pieceIterator) ;
		auto removeP = std::bind(& Player::removePiece, this, _1) ;
		Notification<Piece> pieceCapturedNotification(EventType::pieceSpecifiedByIDWasCaptured, removeP, {board->getID(), piece->getID()}) ;
		pieceCapturedNotification.registerForCallback() ;
	
		//.. we may need to be notified of other events as well, add them here:
	}
}

void Human::decideNextMove() {
	//todo: implement
}


void AI::decideNextMove() {
	
	Board testingBoard(* board) ; //copy current gamestate, testingBoard will serve as a scratchpad to compute the optimal next move
	
	vector<const Piece *> workingPieces = copyCurrentPieces(testingBoard) ;
	

	
	

}

void AI::findBestMoveForPiece(const Piece * piece, const Board & board) {
	auto possibleMoves = piece->getAllPossibleLegalMoves() ;
	
	unsigned highestMoveValue = 0 ; 
	for (auto i = 0 ; i < possibleMoves.size() ; i++) {
		
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}