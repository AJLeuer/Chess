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

