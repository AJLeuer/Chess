//
//  Board.h
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Board__
#define __Chess__Board__

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <initializer_list>

#include "Piece.h"

using namespace std ;

struct Square {
	
protected:
	
	Piece * piece ;
	
	const string file ;
	
	const unsigned rank ;
	
	friend class Board ;
	
	void initPiece(const string &) ;
	
public:
	
	Square(const string & file, const unsigned rank) ;
	
	Square(const string & pieceSymbol, const string & file, const unsigned rank) ;
	
	Square(Piece * piece, const string & file, const unsigned rank) ;
	
	
	bool isEmpty() const { return piece == nullptr ; }
	
	const Piece * getPiece() const { return piece ; }
	
	friend std::ostream & operator<< (std::ostream & , const Square &) ;
	
} ;

class Board {
	
protected:
	
	/**
	 * The number of rows on the chessboard
	 */
	static constexpr unsigned ranks = 8 ;
	
	/**
	 * The number of columns on the chessboard
	 */
	static constexpr unsigned files = 8 ;
	
	array<array<Square, files>, ranks> boardRepresentation ;
	
public:
	
	Board() ;
	
	const Square * getSquare(unsigned rank, char file) const ;
	
	const Square * getSquare(unsigned arrIndexX, unsigned arrIndexY) const ;
	
	friend std::ostream & operator<< (std::ostream & , const Board &) ;
} ;

#endif /* defined(__Chess__Board__) */
