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

MoveIntent Player::decideNextMove() {
	return MoveIntent() ;
}


MoveIntent Human::decideNextMove() {
	return MoveIntent() ; //todo: implement
}


MoveIntent AI::decideNextMove() {
	return MoveIntent() ; //todo: implement
}

void AI::runSearchAlgorithm() {
	
}

