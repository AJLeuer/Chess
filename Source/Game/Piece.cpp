//
//  Piece.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Piece.h"

using namespace std ;

Piece * Piece::init(const string & symbol, const Position * position) {
	Piece * piece ;
	if (symbol == Pawn::symbolWhite) {
		piece = new Pawn(Piece::Color::white, position) ;
	}
	else if (symbol == Pawn::symbolBlack) {
		piece = new Pawn(Piece::Color::black, position) ;
	}
	else if (symbol == Knight::symbolWhite) {
		piece = new Knight(Piece::Color::white, position) ;
	}
	else if (symbol == Knight::symbolBlack) {
		piece = new Knight(Piece::Color::black, position) ;
	}
	else if (symbol == Bishop::symbolWhite) {
		piece = new Bishop(Piece::Color::white, position) ;
	}
	else if (symbol == Bishop::symbolBlack) {
		piece = new Bishop(Piece::Color::black, position) ;
	}
	else if (symbol == Rook::symbolWhite) {
		piece = new Rook(Piece::Color::white, position) ;
	}
	else if (symbol == Rook::symbolBlack) {
		piece = new Rook(Piece::Color::black, position) ;
	}
	else if (symbol == Queen::symbolWhite) {
		piece = new Queen(Piece::Color::white, position) ;
	}
	else if (symbol == Queen::symbolBlack) {
		piece = new Queen(Piece::Color::black, position) ;
	}
	else if (symbol == King::symbolWhite) {
		piece = new King(Piece::Color::white, position) ;
	}
	else if (symbol == King::symbolBlack) {
		piece = new King(Piece::Color::black, position) ;
	}
	else {
		piece = nullptr ;
	}
	return piece ;
}

void Piece::move(const Position to) {
	sendMoveNotification(to) ;
}

void Piece::sendMoveNotification(const Position newPosition) {
	Notification<Piece, Position>::notify(EventType::pieceLeaving, this, *this->position) ;
	Notification<Piece, Position>::notify(EventType::pieceArriving, this, newPosition) ;
}

Pawn::Pawn(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

Pawn::Pawn(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void Pawn::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Knight::Knight(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

Knight::Knight(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void Knight::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Bishop::Bishop(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

Bishop::Bishop(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void Bishop::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Rook::Rook(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

Rook::Rook(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void Rook::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Queen::Queen(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

Queen::Queen(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void Queen::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

King::King(const Color color, const Position * position) :
	Piece((color == Piece::Color::black) ? symbolBlack : symbolWhite, color, position)
{
	
}

King::King(const string & symbol, const Position * position) :
	Piece((symbol == symbolBlack) ? symbolBlack : symbolWhite, (symbol == symbolBlack) ? Piece::Color::black : Piece::Color::white, position)
{
	
}

void King::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}


ostream & operator<< (ostream & out, const Piece & piece) {
	out << piece.getSymbol() ;
	return out ;
}





























