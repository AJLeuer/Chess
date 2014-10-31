//
//  Piece.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Piece.h"

using namespace std ;

Pawn::Pawn(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

Pawn::Pawn(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void Pawn::move() {
	
}

Knight::Knight(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

Knight::Knight(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void Knight::move() {
	
}

Bishop::Bishop(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

Bishop::Bishop(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void Bishop::move() {
	
}

Rook::Rook(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

Rook::Rook(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void Rook::move() {
	
}

Queen::Queen(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

Queen::Queen(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void Queen::move() {
	
}

King::King(const Color color) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color)
{
	
}

King::King(const string & symbol) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white)
{
	
}

void King::move() {
	
}


ostream & operator<< (ostream & out, const Piece & piece) {
	out << piece.getSymbol() ;
	return out ;
}

































