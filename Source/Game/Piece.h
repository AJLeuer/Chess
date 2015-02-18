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
#include <string>

#include "Util.h"
#include "NotificationSystem.h"
#include "Position.h"

using namespace std ;


class Piece {
	
protected:
	
	wstring symbol ;
	
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
	
	struct Symbols {
		const wstring black ;
		const wstring white ;
	} ;
	
	
	static Piece * init(const wstring & symbol, const Position * position) ;
	
	virtual ~Piece() {} ;
	
	Piece & operator = (const Piece & rhs) ;
	
	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) ;//inheriting pieces will define
	
	const wstring & getSymbol() const { return symbol ; }
	
	const Position * getPosition() const { return position ; }
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Piece &) ;
	
	friend int main(int argc, const char * argv[]) ;
	
protected:
	
	Color color ;
	
	Position * getPosition() { return new Position{0, 0} ; } //todo implement
	
	Piece(const wstring & symbol, const Color color, const Position * position) : symbol(symbol), color(color), position(position) {}
	
};



class Pawn : public Piece {

protected:
	
public:
	
	static Symbols symbols ;
	
	Pawn(const Color color, const Position * position) ;
	
	Pawn(const wstring & symbol, const Position * position) ;
	
	~Pawn() {}
	
	void move(const Position to) override ;

} ;

class Knight : public Piece {
	
protected:
	
	
public:
	
	static Symbols symbols ;
	
	Knight(const Color color, const Position * position) ;
	
	Knight(const wstring & symbol, const Position * position) ;
	
	~Knight() {}
	
	void move(const Position to) override ;
	
};

class Bishop : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;

	Bishop(const Color color, const Position * position) ;
	
	Bishop(const wstring & symbol, const Position * position) ;
	
	~Bishop() {}
	
	void move(const Position to) override ;

};


class Rook : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;

	Rook(const Color color, const Position * position) ;
	
	Rook(const wstring & symbol, const Position * position) ;
	
	~Rook() {}
	
	void move(const Position to) override ;
	
};

class Queen : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	Queen(const Color color, const Position * position) ;
	
	Queen(const wstring & symbol, const Position * position) ;
	
	~Queen() {}
	
	void move(const Position to) override ;
	
};

class King : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	King(const Color color, const Position * position) ;
	
	King(const wstring & symbol, const Position * position) ;
	
	~King() {}
	
	void move(const Position to) override ;
	
};




#endif /* defined(__Chess__Piece__) */
