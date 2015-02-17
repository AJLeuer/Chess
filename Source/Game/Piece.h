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
#include <locale>
#include <codecvt>
#include <string>

#include "NotificationSystem.h"
#include "Position.h"

using namespace std ;

//class Square ;

class Piece {
	
protected:
	
	const wstring symbol ;
	
	const Position * position ;
	
	
	void sendMoveNotification(const Position newPosition) ;
	
	void setCurrentPosition(const Position * position) { this->position = position ; }
	
	friend class Square ;
	
	friend void runTests() ;
	
public:
	
	enum class Color {
		black,
		white
	} ;
	
	static Piece * init(const string & symbol, const Position * position) ;
	
	virtual ~Piece() {} ;
	
	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) ;//inheriting pieces will define
	
	const wstring & getSymbol() const { return symbol ; }
	
	const Position * getPosition() const { return position ; }
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
protected:
	
	Color color ;
	
	Position * getPosition() { return new Position{0, 0} ; } //todo implement
	
	Piece(const wstring & symbol, const Color color, const Position * position) : symbol(symbol), color(color), position(position) {}
	
};



class Pawn : public Piece {

protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♟"} ;
	
	static constexpr char * symbolWhite {(char *)"♙"} ;
	
	Pawn(const Color color, const Position * position) ;
	
	Pawn(const string & symbol, const Position * position) ;
	
	~Pawn() {}
	
	void move(const Position to) override ;

} ;

class Knight : public Piece {
	
protected:
	
	
public:
	
	static constexpr char * symbolBlack {(char *)"♞"} ;
	
	static constexpr char * symbolWhite {(char *)"♘"} ;

	Knight(const Color color, const Position * position) ;
	
	Knight(const string & symbol, const Position * position) ;
	
	~Knight() {}
	
	void move(const Position to) override ;
	
};

class Bishop : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♝"} ;
	
	static constexpr char * symbolWhite {(char *)"♗"} ;
	
	Bishop(const Color color, const Position * position) ;
	
	Bishop(const string & symbol, const Position * position) ;
	
	~Bishop() {}
	
	void move(const Position to) override ;

};


class Rook : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♜"} ;
	
	static constexpr char * symbolWhite {(char *)"♖"} ;

	Rook(const Color color, const Position * position) ;
	
	Rook(const string & symbol, const Position * position) ;
	
	~Rook() {}
	
	void move(const Position to) override ;
	
};

class Queen : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♛"} ;
	
	static constexpr char * symbolWhite {(char *)"♕"} ;
	
	Queen(const Color color, const Position * position) ;
	
	Queen(const string & symbol, const Position * position) ;
	
	~Queen() {}
	
	void move(const Position to) override ;
	
};

class King : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♚"} ;
	
	static constexpr char * symbolWhite {(char *)"♔"} ;
	
	King(const Color color, const Position * position) ;
	
	King(const string & symbol, const Position * position) ;
	
	~King() {}
	
	void move(const Position to) override ;
	
};




#endif /* defined(__Chess__Piece__) */
