//
//  Player.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Player.h"

using namespace std ;

unsigned long Player::uniqueIDs = 0 ;


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

