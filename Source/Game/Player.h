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
#include <tuple>
#include <iterator>

#include "Chess.h"
#include "Board.h"

using namespace std ;

namespace Chess {
	
	
	
typedef tuple<const Piece *, const Square *, unsigned> MoveIntent ;
	
	

class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	static list <Piece *> initPieces(Chess::Color playerColor, const Board & board) ;
	
	unsigned long ID ;
	
	string name ;
	
	Chess::Color color ;
	
	Board * board ;
	
	list <Piece *> startingPieces ;
	list <Piece *> remainingPieces ;
	
	vector<const Piece *> copyCurrentPieces(const Board & workingBoard) ;
	
public:
	
	/* Any other constructors should call this as a delegating constructor */
	explicit Player(Chess::Color color, Board * board) ;
	
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
	
	virtual void decideNextMove() = 0 ;
	
};


class Human : public Player {

public:

	Human(Chess::Color color, Board * board) :
		Player(color, board) {}
	
	void decideNextMove() override ;
	
};

class AI : public Player {
	
	void findBestMoveForPiece(const Piece * piece, const Board & board) ;
	
public:
	
	AI(Chess::Color color, Board * board) :
		Player(color, board) {}
	
	void decideNextMove() override ;
	
	
	
} ;

	
}

#endif /* defined(__Chess__Player__) */






