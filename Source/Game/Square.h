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
	
	const Board * board ;
	
	Piece * piece = nullptr ;
	
	friend class Game ;
	
	friend class Player ;
	
	friend class Board ;
	
	friend class TemporarySquare ;
	
	friend class TemporaryBoard ;
	
	Square() {}
	
	void setCurrentPiece(Piece * pieceMovingTo) ;
	
	void clearCurrentPiece(Piece * toClear) ;
	
	void destroyCurrentPiece() ;
	
	void handlePieceCapture(Piece * pieceCapturing) ;
	
	Piece * getPieceMutable() const { return piece ; } //for debug only, remove later
	
public:
	
	Square(const Square & other) ;
	
	Square(const char file, const unsigned rank, const Board * board) ;
	
	Square(Piece * piece, const char file, const unsigned rank, const Board * board) ;
	
	Square(const wchar_t pieceSymbol, const char file, const unsigned rank, const Board * board) ;
	
	virtual ~Square() { if (piece != nullptr) { delete piece ; } ; }
	
	virtual Square & operator = (const Square & rhs) ;
	
	void receiveMovingPiece(Piece * pieceMovingTo) ;
	
	inline bool isEmpty() const { return piece == nullptr ; }
	
	inline bool isOccupied() const { return (!(isEmpty())) ; }
	
	const vec2<int> & getPosition() const { return this->position ; }
	
	inline const Piece * getPiece() const { return piece ; }
	
	/**
	 * Registers this Square to be notified when a Piece moves to it
	 * or leaves it.
	 */
	void registerForPieceMovement() ;
	
	friend std::ostream & operator << (std::ostream & , const Square &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Square &) ;
	
} ;
	
	

	
	
	
	
	
	
	
	
	
	
	
	
}

#endif
