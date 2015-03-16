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

#include <SFML/Graphics/Image.hpp>

#include "Config.h"
#include "Util.h"
#include "Color.h"
#include "NotificationSystem.h"
#include "Position.h"

using namespace std ;

struct Symbols {
	const wstring black ;
	const wstring white ;
} ;

struct ImageFiles {
	const string black ;
	const string white ;
};

class Piece {
	
protected:
	
	wstring symbol ;
	
	const string spriteImageFile ;
	
	sf::Image sprite ;
	
	const Position * position ;
	
	void sendMoveNotification(const Position newPosition) ;
	
	void setCurrentPosition(const Position * position) { this->position = position ; }
	
	friend class Square ;
	
	friend void runTests() ;
	
public:
	
	static Piece * init(const wstring & symbol, const Position * position) ;
	
	virtual ~Piece() {} ;
	
	Piece & operator = (const Piece & rhs) ;
	
	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) ;//inheriting pieces will define
	
	const Color getColor() const { return color ; }
	
	const wstring & getSymbol() const { return symbol ; }
	
	const Position * getPosition() const { return position ; }
	
	virtual const float getValue() const = 0 ;
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Piece &) ;
	
	friend int main(int argc, const char * argv[]) ;
	
protected:
	
	Color color ;
	
	Position * getPosition() { return new Position{0, 0} ; } //todo implement
	
	Piece(const wstring & symbol, const string & spriteImageFile, const Color color, const Position * position) :
		symbol(symbol),
		spriteImageFile(spriteImageFile),
		color(color),
		position(position)
	{
		bool loadedOK = sprite.loadFromFile(spriteImageFile) ;
	}
	
};



class Pawn : public Piece {

protected:
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Pawn(const Color color, const Position * position) ;
	
	Pawn(const wstring & symbol, const Position * position) ;
	
	~Pawn() {}
	
	virtual const float getValue() const override ;
	
	void move(const Position to) override ;

} ;

class Knight : public Piece {
	
protected:
	
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Knight(const Color color, const Position * position) ;
	
	Knight(const wstring & symbol, const Position * position) ;
	
	~Knight() {}
	
	virtual const float getValue() const override { return 2 ; }
	
	void move(const Position to) override ;
	
};

class Bishop : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;

	Bishop(const Color color, const Position * position) ;
	
	Bishop(const wstring & symbol, const Position * position) ;
	
	~Bishop() {}
	
	virtual const float getValue() const override { return 4 ; }
	
	void move(const Position to) override ;

};


class Rook : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;

	Rook(const Color color, const Position * position) ;
	
	Rook(const wstring & symbol, const Position * position) ;
	
	~Rook() {}
	
	virtual const float getValue() const override { return 6 ; }
	
	void move(const Position to) override ;
	
};

class Queen : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Queen(const Color color, const Position * position) ;
	
	Queen(const wstring & symbol, const Position * position) ;
	
	~Queen() {}
	
	virtual const float getValue() const override { return 10 ; }
	
	void move(const Position to) override ;
	
};

class King : public Piece {
	
protected:
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	King(const Color color, const Position * position) ;
	
	King(const wstring & symbol, const Position * position) ;
	
	~King() {}
	
	virtual const float getValue() const override { return 48 ; }
	
	void move(const Position to) override ;
	
};




#endif /* defined(__Chess__Piece__) */
