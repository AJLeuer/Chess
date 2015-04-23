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
#include <vector>
#include <list>
#include <array>
#include <tuple>
#include <iterator>



#include "Chess.h"
#include "Piece.h"
#include "Board.h"

#include "../Util/tree.hh"
#include "../Util/Random.hpp"

using namespace std ;

namespace Chess {
	
	
	
//typedef tuple<const Piece *, const Square *, unsigned>  ;
	
	

class Player {
	
protected:
	
	static unsigned long uniqueIDs ;
	
	unsigned long ID ;
	
	string name ;
	
	Chess::Color color ;
	
	Board & board ;
	
	vector<Piece *> findPiecesOnBoard(Board & workingBoard) const ;
	
public:
	
	/* Any other constructors should call this as a delegating constructor */
	explicit Player(Chess::Color color, Board & board) ;
	
	Player(const Player & other) = delete ;
	
	/**
	 * Move constructor
	 */
	Player(Player && other) ;
	
	virtual ~Player() ;
	
	Player & operator = (const Player & other) = delete ;
	
	/**
	 * Move assignment operator
	 */
	Player & operator = (Player && other) ;
	
	void removePiece(Piece * piece) ;
	
	void registerForNotifications() ;
	
	virtual const MoveIntent decideNextMove() const = 0 ;
	
};


class Human : public Player {

public:

	Human(Chess::Color color, Board & board) :
		Player(color, board) {}
	
	const MoveIntent decideNextMove() const override ;
	
};
	
	

class AI : public Player {
	
	
protected:
	
	const MoveIntent findBestMoveForPiece(Piece * piece) const ;
	
	//static
	
	friend class Game ; //debug only
	
public:
	
	AI(Chess::Color color, Board & board) :
		Player(color, board) {}
	
	const MoveIntent decideNextMove() const override ;
	
} ;
	
	
	
void extractHighestValueMoves(vector <MoveIntent> & moves) ;
	
MoveIntent selectMoveAtRandom(const vector <MoveIntent> & moves) ;
	
	
	
	
	
struct StoredMoveIntent {
	
	const Board * board ;
	
	MoveIntent moveIntent ;
	
};

	
}

#endif /* defined(__Chess__Player__) */






