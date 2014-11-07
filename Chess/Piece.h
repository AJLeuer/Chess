//
//  Piece.h
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Piece__
#define __Chess__Piece__

#include <iostream>
#include <functional>

#include "NotificationSystem.h"
#include "Position.h"

using namespace std ;

//class Square ;

class Piece {
	
protected:
	
	const string symbol ;
	
	const Position * position ;
	
	void sendMoveNotification(const Position newPosition) ;
	
	void setCurrentPosition(const Position * position) { this->position = position ; }
	
	friend class Square ;
	
	friend void runChessGameTests() ;
	
public:
	
	enum class Color {
		black,
		white
	} ;
	
	friend class Square ;
	
	virtual ~Piece() {} ;
	
	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) = 0 ;//inheriting pieces will define
	
	const string & getSymbol() const { return symbol ; }
	
	const Position * getPosition() const { return position ; }
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
protected:
	
	Color color ;
	
	Position * getPosition() { return new Position{0, 0} ; } //todo implement
	
	Piece(const string & symbol, const Color color, const Position * position) : symbol(symbol), color(color), position(position) {}
	
};



class Pawn : public Piece {

protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♟"} ;
	
	static constexpr char * symbolWhite {(char *)"♙"} ;
	
	Pawn(const Color color, const Position * position) ;
	
	Pawn(const string & symbol, const Position * position) ;
	
	~Pawn() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;

} ;

class Knight : public Piece {
	
protected:
	
	
public:
	
	static constexpr char * symbolBlack {(char *)"♞"} ;
	
	static constexpr char * symbolWhite {(char *)"♘"} ;

	Knight(const Color color, const Position * position) ;
	
	Knight(const string & symbol, const Position * position) ;
	
	~Knight() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;
	
};

class Bishop : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♝"} ;
	
	static constexpr char * symbolWhite {(char *)"♗"} ;
	
	Bishop(const Color color, const Position * position) ;
	
	Bishop(const string & symbol, const Position * position) ;
	
	~Bishop() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;
	
};


class Rook : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♜"} ;
	
	static constexpr char * symbolWhite {(char *)"♖"} ;

	Rook(const Color color, const Position * position) ;
	
	Rook(const string & symbol, const Position * position) ;
	
	~Rook() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;
	
};

class Queen : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♛"} ;
	
	static constexpr char * symbolWhite {(char *)"♕"} ;
	
	Queen(const Color color, const Position * position) ;
	
	Queen(const string & symbol, const Position * position) ;
	
	~Queen() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;
	
};

class King : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♚"} ;
	
	static constexpr char * symbolWhite {(char *)"♔"} ;
	
	King(const Color color, const Position * position) ;
	
	King(const string & symbol, const Position * position) ;
	
	~King() {}
	
	void move(const Position to) ;
	
	const string & symbol() const ;
	
};


/**
 * Initializes piece by inferring its type (i.e. Pawn, Queen, etc.) from the
 * string argument symbol
 *
 * @param symbol The string from which the particular type of Piece * piece is inferred
 */
Piece * initPiece(const string & symbol, const Position * position) ;





#endif /* defined(__Chess__Piece__) */
