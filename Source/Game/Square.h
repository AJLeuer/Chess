//
//  Square.h
//  Chess
//
//  Created by Adam James Leuer on 3/12/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Square_h
#define Chess_Square_h

#include <cassert>

#include "Piece.h"

using namespace std ;

namespace Chess {

/* Forward declaring */
class Board ;

struct Square {
	
protected:
	
	RankAndFile rankAndFile ;
	
	vec2<int> position {0, 0} ;
	
	Board * board ;
	
	Piece * piece = nullptr ;
	
	friend class Game ;
	
	friend class Piece ;
	
	friend class Player ;
	
	friend class AI ;
	
	friend class Board ;
	
	friend class TemporarySquare ;
	
	friend class TemporaryBoard ;
	
	Square() {}
	
	void setCurrentPiece(Piece * pieceMovingTo) ;
	
	void clearCurrentPiece(Piece * toClear) ;
	
	void destroyCurrentPiece() ;
	
	inline Piece * getPieceMutable() { return piece ; } //for debug only, remove later
	
public:
	
	Square(const Square & other) ;
	
	Square(const char file, const unsigned rank, Board * board) ;
	
	Square(Piece * piece, const char file, const unsigned rank, Board * board) ;
	
	Square(const wchar_t pieceSymbol, const char file, const unsigned rank, Board * board) ;
	
	virtual ~Square() ;
	
	virtual Square & operator = (const Square & rhs) ;
	
	void receiveMovingPiece(Piece * pieceMovingTo) ;
	
	inline bool isEmpty() const { return piece == nullptr ; }
	
	inline bool isOccupied() const { return (!(isEmpty())) ; }
	
	const vec2<int> & getPosition() const { return this->position ; }
	
	vec2<int> copyPosition() const { return this->position ; }
	
	const vec2<int> * getPositionPointer() const { return & this->position ; }
	
	inline const Board * getBoard() const { return board ; }
	
	inline const Piece * getPiece() const { return piece ; }
	
	friend std::ostream & operator << (std::ostream & , const Square &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Square &) ;
	
} ;
	
	

	
	
	
	
	
	
	
	
	
	
	
	
}

#endif
