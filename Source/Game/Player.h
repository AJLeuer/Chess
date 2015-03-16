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
#include <list>
#include <array>
#include <iterator>

#include "Board.h"

using namespace std ;

struct MoveIntent {
	Piece * piece ;
	Square * destination ;
} ;

class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	list<Square> squaresWithPieces ;
	
	unsigned long ID ;
	
	string name ;
	
public:
	
	template <typename Iterator>
	Player(Iterator squares_start, Iterator squares_end) :
		squaresWithPieces(squares_start, squares_end),
		ID(uniqueIDs++),
		name("Player " + to_string(ID))
	{
		
	}
	
	virtual MoveIntent decideNextMove() ;
	
};


class Human : public Player {

public:

	template <typename Iterator>
	Human(Iterator squares_start, Iterator squares_end) :
		Player(squares_start, squares_end) {}
	
	MoveIntent decideNextMove() ;
	
};

class AI : public Player {
	
public:
	
	template <typename Iterator>
	AI(Iterator squares_start, Iterator squares_end) :
		Player(squares_start, squares_end) {}
	
	MoveIntent decideNextMove() ;
	
	void runSearchAlgorithm() ;
	
} ;

#endif /* defined(__Chess__Player__) */






