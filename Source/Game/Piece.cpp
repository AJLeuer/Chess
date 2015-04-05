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
using namespace Directions ;


Symbols Pawn::symbols {/* black */ L"♟", /* white */ L"♙"} ;


Symbols Knight::symbols {/* black */ L"♞", /* white */ L"♘"} ;


Symbols Bishop::symbols {/* black */ L"♝", /* white */ L"♗"} ;


Symbols Rook::symbols {/* black */ L"♜", /* white */ L"♖"} ;


Symbols Queen::symbols {/* black */ L"♛", /* white */ L"♕"} ;


Symbols King::symbols {/* black */ L"♚", /* white */ L"♔"} ;


ImageFiles Pawn::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Pawn.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Pawn.png" } ;

ImageFiles Knight::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Knight.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Knight.png" } ;

ImageFiles Bishop::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black Pawn.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Bishop.png" } ;

ImageFiles Rook::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Rook.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Rook.png" } ;

ImageFiles Queen::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ Queen.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ Queen.png" } ;

ImageFiles King::imageFiles {/* black */ "./Assets/Bitmaps\ \&\ Vectors/Black\ King.png", /* white */ "./Assets/Bitmaps\ \&\ Vectors/White\ King.png" } ;




Piece * Piece::init(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) {
	Piece * piece ;
	if (symbol == Pawn::symbols.white) {
		piece = new Pawn(ChessColor::white, position, board, square) ;
	}
	else if (symbol == Pawn::symbols.black) {
		piece = new Pawn(ChessColor::black, position, board, square) ;
	}
	else if (symbol == Knight::symbols.white) {
		piece = new Knight(ChessColor::white, position, board, square) ;
	}
	else if (symbol == Knight::symbols.black) {
		piece = new Knight(ChessColor::black, position, board, square) ;
	}
	else if (symbol == Bishop::symbols.white) {
		piece = new Bishop(ChessColor::white, position, board, square) ;
	}
	else if (symbol == Bishop::symbols.black) {
		piece = new Bishop(ChessColor::black, position, board, square) ;
	}
	else if (symbol == Rook::symbols.white) {
		piece = new Rook(ChessColor::white, position, board, square) ;
	}
	else if (symbol == Rook::symbols.black) {
		piece = new Rook(ChessColor::black, position, board, square) ;
	}
	else if (symbol == Queen::symbols.white) {
		piece = new Queen(ChessColor::white, position, board, square) ;
	}
	else if (symbol == Queen::symbols.black) {
		piece = new Queen(ChessColor::black, position, board, square) ;
	}
	else if (symbol == King::symbols.white) {
		piece = new King(ChessColor::white, position, board, square) ;
	}
	else if (symbol == King::symbols.black) {
		piece = new King(ChessColor::black, position, board, square) ;
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


const bool Piece::canMove() const {

	auto checkForEmptySquares = [] (vector<const Square *> & squares) -> bool {
		
		for (auto i = 0 ; i < squares.size() ; i++) {
			if (squares.at(i)->isEmpty()) {
				return true ;
			}
		}
		return false ;
	} ;
	
	return (*board)->runSearchFunction<bool>(checkForEmptySquares, *this->position, getLegalMovementDirections(), 2) ;
}

void Piece::sendMoveNotification(const Position newPosition) {
	
	//debug code
	if (this->position == nullptr) {
		throw std::exception() ;
	}

	Notification<Piece, size_t>::notify(EventType::pieceLeaving, this, hashTwoVector(*this->position)) ;
	Notification<Piece, size_t>::notify(EventType::pieceArriving, this, hashTwoVector(newPosition)) ;
}

Pawn::Pawn(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
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
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
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

const vector<Direction> Pawn::getLegalMovementDirections() const {
	
	if (this->color == ChessColor::black) {
		return vector<Direction> { down, downLeft, downRight } ;
	}
	else /* if (this->color == ChessColor::white) */ {
		return vector<Direction> { up, upLeft, upRight } ;
	}
}

void Pawn::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}


Knight::Knight(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Knight::Knight(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> Knight::getLegalMovementDirections() const {
	
	vector<Direction> directions ;
	
	for (int v = -2 ; v <= 2 ; v++) { //primarily vertical movement
		for (int h = -1 ; h <= 1 ; h++) {
			directions.push_back(Direction(h, v)) ;
		}
	}
	
	for (int h = -2 ; h <= 2 ; h++) { //primarily horizontal movement
		for (int v = -1 ; v <= 1 ; v++) {
			directions.push_back(Direction(h, v)) ;
		}
	}
	
	return directions ;
}


void Knight::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Bishop::Bishop(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Bishop::Bishop(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> Bishop::getLegalMovementDirections() const {
	return vector<Direction> { Directions::upLeft, Directions::upRight, Directions::downLeft, Directions::downRight } ;
}

void Bishop::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}


Rook::Rook(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Rook::Rook(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> Rook::getLegalMovementDirections() const {
	return vector<Direction> { Directions::up, Directions::down, Directions::left, Directions::right } ;
}

void Rook::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Queen::Queen(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Queen::Queen(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> Queen::getLegalMovementDirections() const {
	return vector<Direction> { Directions::up, Directions::down, Directions::left, Directions::right,
		Directions::upLeft, Directions::upRight, Directions::downLeft, Directions::downRight } ;
}

void Queen::move(const Position to) {
	//todo add move legality checking
	Piece::move(to) ;
}


King::King(const ChessColor color, const Position * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

King::King(const wstring & symbol, const Position * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> King::getLegalMovementDirections() const {
	return vector<Direction> { Directions::up, Directions::down, Directions::left, Directions::right,
		Directions::upLeft, Directions::upRight, Directions::downLeft, Directions::downRight } ;
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





























