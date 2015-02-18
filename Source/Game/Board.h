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

#include "Util.h"
#include "NotificationSystem.h"
#include "Position.h"
#include "Piece.h"


using namespace std ;


struct Square {
	
protected:
	
	const RankAndFile rankAndFile ;
	
	const Position position ;
	
	Piece * piece ;
	
	friend class Game ;
	
	friend class Board ;
	
public:
	
	Square(const char file, const unsigned rank) ;
	
	Square(Piece * piece, const char file, const unsigned rank) ;
	
	Square(const string & pieceSymbol, const char file, const unsigned rank) ;
	
	void setCurrentPiece(Piece * piece) { this->piece = piece ; this->piece->setCurrentPosition(& this->position) ;}
	
	void clearCurrentPiece(Piece * ignored = nullptr) { this->piece->setCurrentPosition(nullptr) ; this->piece = nullptr ; }
	
	bool isEmpty() const { return piece == nullptr ; }
	
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
	
	friend void runChessGameTests() ;
	
public:
	
	Board() ;
	
	const Square * getSquare(unsigned rank, char file) const ;
	
	const Square * getSquare(unsigned arrIndexX, unsigned arrIndexY) const ;
	
	friend std::ostream & operator << (std::ostream & , const Board &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Board &) ;
} ;

#endif /* defined(__Chess__Board__) */
