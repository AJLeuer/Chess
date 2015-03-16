//
//  Piece.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Piece.h"


using namespace std ;


Symbols Pawn::symbols {/* black */ L"♟", /* white */ L"♙"} ;


Symbols Knight::symbols {/* black */ L"♞", /* white */ L"♘"} ;


Symbols Bishop::symbols {/* black */ L"♝", /* white */ L"♗"} ;


Symbols Rook::symbols {/* black */ L"♜", /* white */ L"♖"} ;


Symbols Queen::symbols {/* black */ L"♛", /* white */ L"♕"} ;


Symbols King::symbols {/* black */ L"♚", /* white */ L"♔"} ;


ImageFiles Pawn::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Pawn.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Pawn.png" } ;

ImageFiles Knight::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Knight.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Knight.png" } ;

ImageFiles Bishop::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Pawn.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Bishop.png" } ;

ImageFiles Rook::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Rook.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Rook.jpg" } ;

ImageFiles Queen::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Queen.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Queen.png" } ;

ImageFiles King::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ King.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ King.png" } ;




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

Piece::Piece (const Piece & other) :
	symbol(other.symbol),
	spriteImageFilePath(other.spriteImageFilePath),
	spriteImage(other.spriteImage),
	sprite(other.sprite),
	color(other.color),
	position(other.position)
{
	
}

Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		this->symbol = rhs.symbol ;
		this->spriteImageFilePath = rhs.spriteImageFilePath ;
		this->spriteImage = rhs.spriteImage ;
		this->sprite = rhs.sprite ;
		this->color = rhs.color ;
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
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	sprite.setPosition(50, 50) ;
}

Pawn::Pawn(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
{
	
}

const float Pawn::getValue() const  {
	constexpr float pawnValue = 1 ;
	auto rank = position->x ;
	auto adjustedRank = (rank / 8) ;
	return (pawnValue + adjustedRank) ;
}

void Pawn::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Knight::Knight(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	
}

Knight::Knight(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
{
	
}

void Knight::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Bishop::Bishop(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	
}

Bishop::Bishop(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
{
	
}

void Bishop::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Rook::Rook(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	
}

Rook::Rook(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
{
	
}

void Rook::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Queen::Queen(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	
}

Queen::Queen(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
{
	
}

void Queen::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

King::King(const Color color, const Position * position) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position)
{
	
}

King::King(const wstring & symbol, const Position * position) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position)
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





























