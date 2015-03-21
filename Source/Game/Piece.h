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
#include <exception>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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

class Board ;

class Square ;

class Piece {
	
protected:
	
	wstring symbol ;
	
	string spriteImageFilePath ;
	
	sf::Image spriteImage ;
	
	sf::Sprite sprite ;
	
	const Position * position = nullptr ;
	
	const Board * const * board ;
	
	const Square * square ;
	
	void sendMoveNotification(const Position newPosition) ;
	
	void setCurrentPosition(const Position * position) { this->position = position ; }
	
	friend class Square ;
	
	friend void runTests() ;
	
public:
	
	static Piece * init(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	Piece (const Piece & other) ;
	
	virtual ~Piece() {} ; //position isn't ours, don't delete it
	
	Piece & operator = (const Piece & rhs) ;
	
	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) ;//inheriting pieces will define
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	virtual bool canMove() ;
	
	const Color getColor() const { return color ; }
	
	const wstring & getSymbol() const { return symbol ; }
	
	const sf::Sprite & getSprite() const { return sprite ; }
	
	const Position * getPosition() const { return position ; }
	
	virtual const float getValue() const = 0 ;
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Piece &) ;
	
	friend int main(int argc, const char * argv[]) ;
	
protected:
	
	Color color ;

	Piece(const wstring & symbol, const string & spriteImageFilePath, const Color color, const Position * position, const Board * const * board, const Square * square) :
		symbol(symbol),
		spriteImageFilePath(spriteImageFilePath),
		color(color),
		position(position)
	{
		bool loadedImageOK = spriteImage.loadFromFile(spriteImageFilePath) ;
		sf::Texture texture ;
		texture.loadFromImage(spriteImage) ;
		sprite.setTexture(texture) ;
	}
	
};



class Pawn : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Pawn(const Pawn & other) :
		Piece(other) {}
	
	Pawn(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	Pawn(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Pawn() {}
	
	Pawn & operator = (const Pawn & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override ;
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;

} ;

class Knight : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Knight(const Knight & other) :
		Piece(other) {}
	
	Knight(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	Knight(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Knight() {}
	
	Knight & operator = (const Knight & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 2 ; }
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;
	
};

class Bishop : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Bishop(const Bishop & other) :
		Piece(other) {}

	Bishop(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	Bishop(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Bishop() {}
	
	Bishop & operator = (const Bishop & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 4 ; }
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;

};


class Rook : public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Rook(const Rook & other) :
		Piece(other) {}

	Rook(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	Rook(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Rook() {}
	
	Rook & operator = (const Rook & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 6 ; }
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;
	
};

class Queen : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Queen(const Queen & other) :
		Piece(other) {}
	
	Queen(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	Queen(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Queen() {}
	
	Queen & operator = (const Queen & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 10 ; }
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;
	
};

class King : public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	King(const King & other) :
		Piece(other) {}
	
	King(const Color color, const Position * position, const Board * const * board, const Square * square) ;
	
	King(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~King() {}
	
	King & operator = (const King & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 48 ; }
	
	void move(const Position to) override ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	bool canMove() override ;
	
};




#endif /* defined(__Chess__Piece__) */
