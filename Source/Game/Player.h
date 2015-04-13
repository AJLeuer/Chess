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

#include "Color.h"
#include "Board.h"

using namespace std ;


class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	static list <Piece *> initPieces(ChessColor playerColor, const Board & board) ;
	
	unsigned long ID ;
	
	string name ;
	
	ChessColor color ;
	
	list <Piece *> startingPieces ;
	list <Piece *> remainingPieces ;
	
public:
	
	/* Any other constructors should call this as a delegating constructor */
	explicit Player(ChessColor color, const Board & board) ;
	
	Player(const Player & other) = delete ;
	
	/**
	 * Move constructor
	 */
	Player(Player && other) ;
	
	virtual ~Player() {}
	
	Player & operator = (const Player & other) = delete ;
	
	/**
	 * Move assignment operator
	 */
	Player & operator = (Player && other) ;
	
	void removePiece(Piece * piece) ;
	
	void registerForNotifications() ;
	
	virtual Piece::Move decideNextMove() = 0 ;
	
};


class Human : public Player {

public:

	Human(ChessColor color, const Board & board) :
		Player(color, board) {}
	
	Piece::Move decideNextMove() override ;
	
};

class AI : public Player {
	
public:
	
	AI(ChessColor color, const Board & board) :
		Player(color, board) {}
	
	Piece::Move decideNextMove() override ;
	
	void runSearchAlgorithm() ;
	
} ;

#endif /* defined(__Chess__Player__) */






