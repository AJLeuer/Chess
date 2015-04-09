//
//  Square.h
//  Chess
//
//  Created by Adam James Leuer on 3/12/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Square_h
#define Chess_Square_h

#include "Piece.h"

using namespace std ;

//namespace Chess {

/* Forward declaring */
class Board ;

struct Square {
	
protected:
	
	RankAndFile rankAndFile ;
	
	Position position ;
	
	const Board * board ;
	
	Piece * piece = nullptr ;
	
	friend class Game ;
	
	friend class Board ;
	
public:
	
	Square(const Square & other) ;
	
	Square(const char file, const unsigned rank, const Board * board) ;
	
	Square(Piece * piece, const char file, const unsigned rank, const Board * board) ;
	
	Square(const string & pieceSymbol, const char file, const unsigned rank, const Board * board) ;
	
	~Square() { if (piece != nullptr) { delete piece ; } ; }
	
	Square & operator = (const Square & rhs) ;
	
	void setCurrentPiece(Piece * piece) { this->piece = piece ; this->piece->setCurrentPosition(& this->position) ;}
	
	void clearCurrentPiece(Piece * ignored = nullptr) ;
	
	bool isEmpty() const { return piece == nullptr ; }
	
	bool isOccupied() const { return isEmpty() == false ; }
	
	const Position & getPosition() const { return this->position ; }
	
	const Piece * getPiece() const { return piece ; }
	
	/**
	 * Registers this Square to be notified when a Piece moves to it
	 * or leaves it.
	 */
	void registerForPieceMovement() ;
	
	friend std::ostream & operator<< (std::ostream & , const Square &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Square &) ;
	
} ;
	
//}

#endif
