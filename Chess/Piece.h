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

using namespace std ;

template<typename N>
using vec2 = N __attribute__((ext_vector_type(2))) ;

typedef vec2<unsigned> Position ;


class Piece {
	
protected:
	
	const string symbol ;
	
public:
	
	enum class Color {
		black,
		white
	} ;
	
	friend class Square ;
	
	virtual ~Piece() {} ;
	
	virtual void move() = 0 ;//inheriting pieces will define
	
	const string & getSymbol() const { return symbol ; }
	
	friend ostream & operator<< (ostream & , const Piece &) ;
	
protected:
	
	Color color ;
	
	Position position ;
	
	Piece(const string & symbol, const Color color) : symbol(symbol), color(color) {}
	
};



class Pawn : public Piece {

protected:
	
public:
	
	static constexpr char * symbolBlack {"♟"} ;
	
	static constexpr char * symbolWhite {"♙"} ;
	
	Pawn(const Color color) ;
	
	Pawn(const string & symbol) ;
	
	~Pawn() {}
	
	void move() ;
	
	const string & symbol() const ;

} ;

class Knight : public Piece {
	
protected:
	
	
public:
	
	static constexpr char * symbolBlack {(char *)"♞"} ;
	
	static constexpr char * symbolWhite {(char *)"♘"} ;

	Knight(const Color color) ;
	
	Knight(const string & symbol) ;
	
	~Knight() {}
	
	void move() ;
	
	const string & symbol() const ;
	
};

class Bishop : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♝"} ;
	
	static constexpr char * symbolWhite {(char *)"♗"} ;
	
	Bishop(const Color color) ;
	
	Bishop(const string & symbol) ;
	
	~Bishop() {}
	
	void move() ;
	
	const string & symbol() const ;
	
};


class Rook : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♜"} ;
	
	static constexpr char * symbolWhite {(char *)"♖"} ;

	Rook(const Color color) ;
	
	Rook(const string & symbol) ;
	
	~Rook() {}
	
	void move() ;
	
	const string & symbol() const ;
	
};

class Queen : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♛"} ;
	
	static constexpr char * symbolWhite {(char *)"♕"} ;
	
	Queen(const Color color) ;
	
	Queen(const string & symbol) ;
	
	~Queen() {}
	
	void move() ;
	
	const string & symbol() const ;
	
};

class King : public Piece {
	
protected:
	
public:
	
	static constexpr char * symbolBlack {(char *)"♚"} ;
	
	static constexpr char * symbolWhite {(char *)"♔"} ;
	
	King(const Color color) ;
	
	King(const string & symbol) ;
	
	~King() {}
	
	void move() ;
	
	const string & symbol() const ;
	
};








#endif /* defined(__Chess__Piece__) */
