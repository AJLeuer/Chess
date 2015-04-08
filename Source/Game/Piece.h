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
#include <vector>
#include <valarray>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Color.h"

#include "../Util/Config.h"
#include "../Util/Util.h"
#include "../Util/Util.hpp"
#include "../Util/Position.h"
#include "../Util/NotificationSystem.h"



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
	
	static unsigned long iDs ;
	
	unsigned long iD ;
	
	wstring symbol ;
	
	string spriteImageFilePath ;
	
	sf::Image spriteImage ;
	
	sf::Sprite sprite ;
	
	const Position * position = nullptr ;
	
	const Board * const * board ;
	
	const Square * square ;
	
	unsigned movesMade = 0 ;
	
	auto getBoard() const { return board ; }
	
	void sendMoveNotification(const Position newPosition) ;
	
	void setCurrentPosition(const Position * position) { this->position = position ; }
	
	friend class Square ;
	
	friend void runTests() ;
	
public:
	
	struct Move {
		Piece * piece ;
		Square * destination ;
	} ;
	
	static Piece * init(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	Piece (const Piece & other) ;
	
	virtual ~Piece() {} ; //position isn't ours, don't delete it
	
	Piece & operator = (const Piece & rhs) ;

	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const Position to) ;//inheriting pieces will define
	
	const unsigned long getID() const { return iD ; }
	
	/**
	 * Returns true if there exists at least one Square that this Piece can move to,
	 * false otherwise
	 */
	virtual const bool canMove() const ;
	
	const ChessColor getColor() const { return color ; }
	
	const wstring & getSymbol() const { return symbol ; }
	
	const sf::Sprite & getSprite() const { return sprite ; }
	
	const Position * getPosition() const { return position ; }
	
	virtual const float getValue() const = 0 ;
	
	virtual const vector<Direction> getLegalMovementDirections() const = 0 ;
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Piece &) ;
	
	friend int main(int argc, const char * argv[]) ;
	
protected:
	
	ChessColor color ;

	Piece(const wstring & symbol, const string & spriteImageFilePath, const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
		iD(iDs++),
		symbol(symbol),
		spriteImageFilePath(spriteImageFilePath),
		color(color),
		position(position),
		board(board),
		square(square)
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
	
	Pawn(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	Pawn(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Pawn() {}
	
	Pawn & operator = (const Pawn & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	const float getValue() const override { return 1 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	const vector<Direction> getLegalCaptureDirections() const ;
	
	Direction getLegalMovementDirectionToEmptySquares() const ;
	
	void move(const Position to) override ;
	
	const bool canMove() const override ;
	
} ;

class Knight : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Knight(const Knight & other) :
		Piece(other) {}
	
	Knight(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	Knight(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Knight() {}
	
	Knight & operator = (const Knight & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	const float getValue() const override { return 3 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const Position to) override ;
	
};

class Bishop : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Bishop(const Bishop & other) :
		Piece(other) {}

	Bishop(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	Bishop(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Bishop() {}
	
	Bishop & operator = (const Bishop & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 3 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const Position to) override ;
	
};


class Rook : public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Rook(const Rook & other) :
		Piece(other) {}

	Rook(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	Rook(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Rook() {}
	
	Rook & operator = (const Rook & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 5 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const Position to) override ;

};

class Queen : public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Queen(const Queen & other) :
		Piece(other) {}
	
	Queen(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	Queen(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~Queen() {}
	
	Queen & operator = (const Queen & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	virtual const float getValue() const override { return 9 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const Position to) override ;
	
};

class King : public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	King(const King & other) :
		Piece(other) {}
	
	King(const ChessColor color, const Position * position, const Board * const * board, const Square * square) ;
	
	King(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) ;
	
	~King() {}
	
	King & operator = (const King & other) {
		if (this != & other) {
			this->Piece::operator=(other) ;
		}
		return * this ;
	}
	
	/**
	 * Equal to the combined values of all other Pieces, plus 1
	 */
	virtual const float getValue() const override { return 40 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const Position to) override ;
	
};




#endif /* defined(__Chess__Piece__) */
