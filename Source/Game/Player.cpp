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

Player::Player() :
	ID(uniqueIDs++),
	name("Player " + to_string(ID))
{
	
}
