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


class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	list<Square> squaresWithPieces ;
	
	unsigned long ID ;
	
	string name ;
	
public:
	
	Player(const Player & other) = delete ;
	
	/**
	 * Move constructor
	 */
	Player(Player && other) ;
	
	template <typename SquareIterator>
	Player(SquareIterator squares_start, SquareIterator squares_end) :
		squaresWithPieces(squares_start, squares_end),
		ID(uniqueIDs++),
		name("Player " + to_string(ID))
	{
		
	}
	
	virtual ~Player() {}
	
	Player & operator = (const Player & other) = delete ;
	
	/**
	 * Move assignment operator
	 */
	Player & operator = (Player && other) ;
	
	virtual Piece::Move decideNextMove() ;
	
};


class Human : public Player {

public:

	template <typename SquareIterator>
	Human(SquareIterator squares_start, SquareIterator squares_end) :
		Player(squares_start, squares_end) {}
	
	Piece::Move decideNextMove() override ;
	
};

class AI : public Player {
	
public:
	
	template <typename SquareIterator>
	AI(SquareIterator squares_start, SquareIterator squares_end) :
		Player(squares_start, squares_end) {}
	
	Piece::Move decideNextMove() override ;
	
	void runSearchAlgorithm() ;
	
} ;

#endif /* defined(__Chess__Player__) */






