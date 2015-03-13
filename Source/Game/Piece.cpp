//
//  Piece.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Piece.h"


using namespace std ;


Piece::Symbols Pawn::symbols {/* black */ L"♟", /* white */ L"♙"} ;


Piece::Symbols Knight::symbols {/* black */ L"♞", /* white */ L"♘"} ;


Piece::Symbols Bishop::symbols {/* black */ L"♝", /* white */ L"♗"} ;


Piece::Symbols Rook::symbols {/* black */ L"♜", /* white */ L"♖"} ;


Piece::Symbols Queen::symbols {/* black */ L"♛", /* white */ L"♕"} ;


Piece::Symbols King::symbols {/* black */ L"♚", /* white */ L"♔"} ;



Piece * Piece::init(const wstring & symbol, const Position * position) {
	Piece * piece ;
	if (symbol == Pawn::symbols.white) {
		piece = new Pawn(Color::white, position) ;
	}
	else if (symbol == Pawn::symbols.black) {
		piece = new Pawn(Color::black, position) ;
	}
	else if (symbol == Knight::symbols.white) {
		piece = new Knight(Color::white, position) ;
	}
	else if (symbol == Knight::symbols.black) {
		piece = new Knight(Color::black, position) ;
	}
	else if (symbol == Bishop::symbols.white) {
		piece = new Bishop(Color::white, position) ;
	}
	else if (symbol == Bishop::symbols.black) {
		piece = new Bishop(Color::black, position) ;
	}
	else if (symbol == Rook::symbols.white) {
		piece = new Rook(Color::white, position) ;
	}
	else if (symbol == Rook::symbols.black) {
		piece = new Rook(Color::black, position) ;
	}
	else if (symbol == Queen::symbols.white) {
		piece = new Queen(Color::white, position) ;
	}
	else if (symbol == Queen::symbols.black) {
		piece = new Queen(Color::black, position) ;
	}
	else if (symbol == King::symbols.white) {
		piece = new King(Color::white, position) ;
	}
	else if (symbol == King::symbols.black) {
		piece = new King(Color::black, position) ;
	}
	else {
		piece = nullptr ;
	}
	return piece ;
}

Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		this->symbol = rhs.symbol ;
		this->position = rhs.position ;
		//add any other newer members here
	}
	return * this ;
}

void Piece::move(const Position to) {
	sendMoveNotification(to) ;
}

void Piece::sendMoveNotification(const Position newPosition) {
	Notification<Piece, Position>::notify(EventType::pieceLeaving, this, *this->position) ;
	Notification<Piece, Position>::notify(EventType::pieceArriving, this, newPosition) ;
}

Pawn::Pawn(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

Pawn::Pawn(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void Pawn::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Knight::Knight(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

Knight::Knight(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void Knight::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Bishop::Bishop(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

Bishop::Bishop(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void Bishop::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Rook::Rook(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

Rook::Rook(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void Rook::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Queen::Queen(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

Queen::Queen(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void Queen::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

King::King(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white, color, position)
{
	
}

King::King(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white, (symbol == symbols.black) ? Color::black : Color::white, position)
{
	
}

void King::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}


ostream & operator << (ostream & out, const Piece & piece) {
	auto bytes = stringConverter.to_bytes(piece.getSymbol()) ;
	out << bytes ;
	return out ;
}

basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> & out, const Piece & piece) {
	out << piece.getSymbol() ;
	return out ;
}





























