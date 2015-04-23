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
#include <memory>
#include <functional>
#include <string>
#include <exception>
#include <vector>
#include <valarray>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Chess.h"

#include "../Util/Config.h"
#include "../Util/Util.h"
#include "../Util/Util.hpp"
#include "../Util/Vect.h"

namespace Chess {

using namespace std ;

struct Symbols {
	const wchar_t black ;
	const wchar_t white ;
} ;

struct ImageFiles {
	const string black ;
	const string white ;
};
	
	
class Board ;

class Square ;
	
	
class Piece {
	
public:
	
	/* Note to the standards committee - C++ needs nested enums */
	enum class Type {
		GenericPiece,
		Pawn,
		Knight,
		Bishop,
		Rook,
		Queen,
		King
	} ;
	
	
protected:
	
	static unsigned long iDs ;
	

	Type type ;
	
	const unsigned long iD ;
	
	wchar_t symbol ;
	
	Chess::Color color ;
	
	unsigned movesMade = 0 ;
	
	string spriteImageFilePath ;

	sf::Texture spriteTexture ;
	
	sf::Sprite sprite ;
	
	Square * square ;
	
	bool deleted = false ; //debug variable only

	Piece(Type type, const wchar_t symbol, const string & spriteImageFilePath,
		  const Chess::Color color, Square *square) ;
	
	
	//Square * & getSquareMutable() { return square ; }
	
	friend class TemporaryPiece ;
	
	friend class Square ;
	
	friend class Player ;
	
	friend class AI ;
	
	friend void runTests() ;
	
	friend int main(int, const char **) ; //for debug and devel only, remove
	
	
public:
	

	static Piece * init(const wchar_t symbol, Square * square) ;
	
	static Piece * initCopy(const Piece & piece) ;
	
	Piece (const Piece & other) ;
	
	
	virtual ~Piece() {
		square = nullptr ;
		if (deleted) { //debug code
		
		}
		deleted = true ;
	} ; 
	
	virtual Piece & operator = (const Piece & rhs) ;
	
	/**
	 * Returns true if there exists at least one Square that this Piece can legally move to,
	 * false otherwise
	 */
	virtual const bool canMove() const ;
	
	/**
	 * @return a std::vector that is either filled with the Squares this Piece can legally move to, or, if there are
	 * no such Squares, empty
	 */
	virtual vector<vec2<int>> getAllPossibleLegalMoves() const ;

	/**
	 * Moves the piece to it's new square, and notifies both the Square object
	 * at its last location the and Square at its new, current location
	 */
	virtual void move(const vec2<int> to) ;//inheriting pieces will define
	
	
	const unsigned long getID() const { return iD ; }
	
	inline const Chess::Color getColor() const { return color ; }
	
	const wchar_t & getSymbol() const { return symbol ; }
	
	const sf::Sprite & getSprite() const { return sprite ; }
	
	const vec2<int> * getPosition() const ;
	
	virtual const unsigned int getValue() const = 0 ;
	
	virtual const vector<Direction> getLegalMovementDirections() const = 0 ;
	
	Square * const & getSquare() const { return square ; }
	
	/**
	 * Called before any drawing is done. Initializes texture object
	 */
	void initSpriteTexture() ;
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Piece &) ;
	
	friend int main(int argc, const char * argv[]) ;

};



class Pawn : virtual public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;

	Pawn(const Piece & other) :
		Piece(other) {}
	
	Pawn(const Chess::Color color, Square * square) ;
	
	Pawn(const wchar_t symbol, Square * square) ;
	
	virtual ~Pawn() {}
	
	const unsigned int getValue() const override { return 1 ; }
	
	/**
	 * @return a std::vector that is either filled with the Squares this Pawn can legally move to, or, if there are
	 * no such Squares, empty
	 */
	virtual vector<vec2<int>> getAllPossibleLegalMoves() const override ;
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	const vector<Direction> getLegalCaptureDirections() const ;
	
	Direction getLegalMovementDirectionToEmptySquares() const ;
	
	void move(const vec2<int> to) override ;
	
	const bool canMove() const override ;
	
} ;

class Knight : virtual public Piece {

	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Knight(const Piece & other) :
		Piece(other) {}
	
	Knight(const Chess::Color color, Square * square) ;
	
	Knight(const wchar_t symbol, Square * square) ;
	
	virtual ~Knight() {}
	
	const unsigned int getValue() const override { return 3 ; }
	
	/**
	 * @return a std::vector that is either filled with the Squares this Knight can legally move to, or, if there are
	 * no such Squares, empty
	 */
	virtual vector<vec2<int>> getAllPossibleLegalMoves() const override ;
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const vec2<int> to) override ;
	
};

class Bishop : virtual public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Bishop(const Piece & other) :
		Piece(other) {}

	Bishop(const Chess::Color color, Square * square) ;
	
	Bishop(const wchar_t symbol, Square * square) ;
	
	virtual ~Bishop() {}
	
	const unsigned int getValue() const override { return 3 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const vec2<int> to) override ;
	
};


class Rook : virtual public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Rook(const Piece & other) :
		Piece(other) {}

	Rook(const Chess::Color color, Square * square) ;
	
	Rook(const wchar_t symbol, Square * square) ;
	
	virtual ~Rook() {}
	
	const unsigned int getValue() const override { return 5 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const vec2<int> to) override ;

};

class Queen : virtual public Piece {
	
public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	Queen(const Piece & other) :
		Piece(other) {}
	
	Queen(const Chess::Color color, Square * square) ;
	
	Queen(const wchar_t symbol, Square * square) ;
	
	virtual ~Queen() {}
	
	const unsigned int getValue() const override { return 9 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const vec2<int> to) override ;
	
};

class King : virtual public Piece {

public:
	
	static Symbols symbols ;
	
	static ImageFiles imageFiles ;
	
	King(const Piece & other) :
		Piece(other) {}
	
	King(const Chess::Color color, Square * square) ;
	
	King(const wchar_t symbol, Square * square) ;
	
	virtual ~King() {}
	
	/**
	 * Equal to the combined values of all other Pieces, plus 1
	 */
	const unsigned int getValue() const override { return 40 ; }
	
	const vector<Direction> getLegalMovementDirections() const override ;
	
	void move(const vec2<int> to) override ;
	
};
	
	
	
	
	
	
	
struct MoveIntent {
	
	/**
	 * Whether is possible for piece to move
	 */
	bool canMove ;
	
	Piece * piece ;
	
	vec2<int> moveDestination ;
	
	int moveValue ;
	
} ;





}

#endif /* defined(__Chess__Piece__) */
