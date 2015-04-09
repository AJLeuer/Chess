//
//  Player.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Player.h"

using namespace std ;

unsigned long Player::uniqueIDs = 1 ;


list <const Square *> Player::initSquares(ChessColor playerColor, const Board & board) {
	
	list<const Square *> squares ;
	
	if (playerColor == ChessColor::black) { //grab black's squares at their starting positions
		
		for (auto x = 0 ; x < board.boardRepresentation.size() ; x++) {
			
			for (auto y = 7 ; y >= 6 ; y--) {
				
				const Square * squarePointer = & (board.boardRepresentation[x][y]) ;
				
				squares.push_front(squarePointer) ;

			}
		}
	}
	
	else /* if (playerColor == ChessColor::white) */ { //grab white's squares at their starting positions
		
		for (auto x = 0 ; x < board.boardRepresentation.size() ; x++) {
			
			for (auto y = 0 ; y <= 1 ; y++) {
				
				const Square * squarePointer = & (board.boardRepresentation[x][y]) ;
				
				squares.push_front(squarePointer) ;
				
			}
		}
	}
	
	return squares ;
}


Player::Player(Player && other) :
	squaresWithPieces(std::move(other.squaresWithPieces)),
	ID(other.ID),
	name(std::move(other.name))
{
	other.ID = 0 ;
}

Player & Player::operator = (Player && other) {
	this->squaresWithPieces = std::move(other.squaresWithPieces) ;
	this->ID = std::move(other.ID) ;
	this->name = std::move(other.name) ;
	
	other.ID = 0 ;
	return * this ;
}

Piece::Move Player::decideNextMove() {
	return Piece::Move() ;
}


Piece::Move Human::decideNextMove() {
	return Piece::Move() ; //todo: implement
}


Piece::Move AI::decideNextMove() {
	
	for (auto square = squaresWithPieces.begin() ; square != squaresWithPieces.end() ; square++) {
		const Piece * piece = (*square)->getPiece() ;
		piece->canMove() ;
	}
	return Piece::Move() ; //todo: implement
}

void AI::runSearchAlgorithm() {
	
}

