//
//  Piece.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Piece.h"
#include "Square.h"
#include "Board.h"


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

ImageFiles Rook::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Rook.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Rook.png" } ;

ImageFiles Queen::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Queen.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Queen.png" } ;

ImageFiles King::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ King.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ King.png" } ;




Piece * Piece::init(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) {
	Piece * piece ;
	if (symbol == Pawn::symbols.white) {
		piece = new Pawn(Color::white, position, board, square) ;
	}
	else if (symbol == Pawn::symbols.black) {
		piece = new Pawn(Color::black, position, board, square) ;
	}
	else if (symbol == Knight::symbols.white) {
		piece = new Knight(Color::white, position, board, square) ;
	}
	else if (symbol == Knight::symbols.black) {
		piece = new Knight(Color::black, position, board, square) ;
	}
	else if (symbol == Bishop::symbols.white) {
		piece = new Bishop(Color::white, position, board, square) ;
	}
	else if (symbol == Bishop::symbols.black) {
		piece = new Bishop(Color::black, position, board, square) ;
	}
	else if (symbol == Rook::symbols.white) {
		piece = new Rook(Color::white, position, board, square) ;
	}
	else if (symbol == Rook::symbols.black) {
		piece = new Rook(Color::black, position, board, square) ;
	}
	else if (symbol == Queen::symbols.white) {
		piece = new Queen(Color::white, position, board, square) ;
	}
	else if (symbol == Queen::symbols.black) {
		piece = new Queen(Color::black, position, board, square) ;
	}
	else if (symbol == King::symbols.white) {
		piece = new King(Color::white, position, board, square) ;
	}
	else if (symbol == King::symbols.black) {
		piece = new King(Color::black, position, board, square) ;
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
	position(other.position),
	board(other.board),
	square(other.square),
	color(other.color)
	/* add any other newer members here */
{
	
}

Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		this->symbol = rhs.symbol ;
		this->spriteImageFilePath = rhs.spriteImageFilePath ;
		this->spriteImage = rhs.spriteImage ;
		this->sprite = rhs.sprite ;
		this->position = rhs.position ;
		this->board = rhs.board ;
		this->square = rhs.square ;
		this->color = rhs.color ;
		/* add any other newer members here */
	}
	return * this ;
}

void Piece::move(const Position to) {
	sendMoveNotification(to) ;
}

bool Piece::canMove() {
	//debug code, this should never be called (always overriden)
	throw exception() ;
}

void Piece::sendMoveNotification(const Position newPosition) {
	
	//debug code
	if (this->position == nullptr) {
		throw std::exception() ;
	}
	
	Notification<Piece, Position>::notify(EventType::pieceLeaving, this, *this->position) ;
	Notification<Piece, Position>::notify(EventType::pieceArriving, this, newPosition) ;
}

Pawn::Pawn(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	sprite.setPosition(50, 50) ;
}

Pawn::Pawn(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
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

bool Pawn::canMove() {
	Position start = *this->position ;
	
	auto checkForEmptySquares = [] (vector<const Square *> & squares) -> bool {
		
		for (auto i = 0 ; i < squares.size() ; i++) {
			if (squares.at(i)->isEmpty()) {
				return true ;
			}
		}
		return false ;
	} ;
	
	vector<Direction> directions ;
	
	if (this->color == Color::black) {
		directions.push_back(Direction::down) ;
		directions.push_back(Direction::downLeft) ;
		directions.push_back(Direction::downRight) ;
	}
	
	else { /* if (this->color == Color::white) */
		directions.push_back(Direction::up) ;
		directions.push_back(Direction::upLeft) ;
		directions.push_back(Direction::upRight) ;
	}
	
	(*board)->runSearchFunction<bool>(checkForEmptySquares, *this->position, directions, 2) ;
	
	return true ;
}

Knight::Knight(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Knight::Knight(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
{
	
}

void Knight::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

bool Knight::canMove() {
	Position start = *this->position ;
	
	
	
	
	
	
	return true ;
}

Bishop::Bishop(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Bishop::Bishop(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
{
	
}

void Bishop::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

bool Bishop::canMove() {
	Position start = *this->position ;
	
	
	
	
	
	
	return true ;
}

Rook::Rook(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Rook::Rook(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
{
	
}

void Rook::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

bool Rook::canMove() {
	Position start = *this->position ;
	
	
	
	
	
	
	return true ;
}

Queen::Queen(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Queen::Queen(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
{
	
}

void Queen::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

bool Queen::canMove() {
	Position start = *this->position ;
	
	
	
	
	
	
	return true ;
}

King::King(const Color color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == Color::black) ? symbols.black : symbols.white,
		  (color == Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

King::King(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Color::black : Color::white,
		  position,
		  board,
		  square)
{
	
}

void King::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

bool King::canMove() {
	Position start = *this->position ;
	
	
	
	
	
	
	return true ;
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





























