//
//  Player.h
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Player__
#define __Chess__Player__

#include <iostream>
#include <string>

using namespace std ;

class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	unsigned long ID ;
	
	string name ;
	
public:
	
	Player() ;
	
};

#endif /* defined(__Chess__Player__) */
