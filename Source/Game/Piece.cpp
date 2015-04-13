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


ImageFiles Pawn::imageFiles {/* black */ "./Assets/Bitmaps/BlackPawn.png", /* white */ "./Assets/Bitmaps/WhitePawn.png" } ;

ImageFiles Knight::imageFiles {/* black */ "./Assets/Bitmaps/BlackKnight.png", /* white */ "./Assets/Bitmaps/WhiteKnight.png" } ;

ImageFiles Bishop::imageFiles {/* black */ "./Assets/Bitmaps/BlackPawn.png", /* white */ "./Assets/Bitmaps/WhiteBishop.png" } ;

ImageFiles Rook::imageFiles {/* black */ "./Assets/Bitmaps/BlackRook.png", /* white */ "./Assets/Bitmaps/WhiteRook.png" } ;

ImageFiles Queen::imageFiles {/* black */ "./Assets/Bitmaps/BlackQueen.png", /* white */ "./Assets/Bitmaps/WhiteQueen.png" } ;

ImageFiles King::imageFiles {/* black */ "./Assets/Bitmaps/BlackKing.png", /* white */ "./Assets/Bitmaps/WhiteKing.png" } ;


unsigned long Piece::iDs = 0 ;

sf::Texture & Piece::initSpriteTexture(sf::Texture & spriteTexture, const string & spriteImageFilePath) {
	spriteTexture.loadFromFile(spriteImageFilePath) ;
	return spriteTexture ;
}


Piece * Piece::init(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) {
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

Piece::Piece(const wstring & symbol, const string & spriteImageFilePath, const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	iD(iDs++),
	symbol(symbol),
	color(color),
	position(position),
	/* movesMade init to 0 */
	spriteImageFilePath(spriteImageFilePath),
	spriteTexture(initSpriteTexture(spriteTexture, spriteImageFilePath)),
	sprite(spriteTexture),
	board(board),
	square(square)
{

}

Piece::Piece (const Piece & other) :
	iD(iDs++), //Pieces resulting from copies have their own, unique IDs
	symbol(other.symbol),
	color(other.color),
	position(other.position),
	/* movesMade init to 0 */
	spriteImageFilePath(other.spriteImageFilePath),
	spriteTexture(sf::Texture(other.spriteTexture)),
	sprite(this->spriteTexture),
	board(other.board),
	square(other.square)
{
	
}

Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		/* Keeps it's own ID */
		this->symbol = rhs.symbol ;
		this->color = rhs.color ;
		this->position = rhs.position ;
		/* Keeps own movesMade count */
		this->spriteImageFilePath = rhs.spriteImageFilePath ;
		this->spriteTexture = rhs.spriteTexture ;
		this->sprite = sf::Sprite(this->spriteTexture) ;
		this->board = rhs.board ;
		this->square = rhs.square ;
	}
	return * this ;
}

const bool Piece::canMove() const {
	
	auto checkForAvailableSquares = [this] (vector<const Square *> & squares) -> bool {
		
		for (auto i = 0 ; i < squares.size() ; i++) { //true if there's a square we can move to that's empty...
			if (squares.at(i)->isEmpty()) {
				return true ;
			}
			else if ((squares.at(i)->getPiece() != nullptr) && (squares.at(i)->getPiece()->color != this->color)) { //... or that has an opponent piece
				return true ;
			}
		}
		return false ;
	} ;
	
	return (*board)->runSearchFunction<bool>(checkForAvailableSquares, *this->position, getLegalMovementDirections(), 1) ;
}

vector<const Square *> Piece::getAllPossibleLegalMoves() const {
	
	vector<vec2<int>> legalMoves ;
	
	return (*board)->getSpecifiedSquares(*this->position, this->getLegalMovementDirections(), true) ;
}

void Piece::move(const vec2<int> to) {
	sendMoveNotification(to) ;
	movesMade++ ;
}


void Piece::sendMoveNotification(const vec2<int> newPosition) {
	
	//debug code, remove
	if (this->position == nullptr) {
		throw std::exception() ;
	}

	Notification<Piece>::notify(EventType::pieceLeavingPositionSpecifiedByPositionID, this, generateID<int>(*(this->position))) ;
	Notification<Piece>::notify(EventType::pieceArrivingAtPositionSpecifiedByPositionID, this, generateID<int>(newPosition)) ;
}

Pawn::Pawn(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	sprite.setPosition(50, 50) ;
}

Pawn::Pawn(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? ChessColor::black : ChessColor::white,
		  position,
		  board,
		  square)
{
	
}

const vector<Direction> Pawn::getLegalMovementDirections() const {
	return getLegalCaptureDirections() + getLegalMovementDirectionToEmptySquares() ;
}

const vector<Direction> Pawn::getLegalCaptureDirections() const {
	if (this->color == ChessColor::black) {
		return vector<Direction> { downLeft, downRight } ;
	}
	else /* if (this->color == ChessColor::white) */ {
		return vector<Direction> { upLeft, upRight } ;
	}
}

Direction Pawn::getLegalMovementDirectionToEmptySquares() const {
	if (this->color == ChessColor::black) {
		return down ;
	}
	else /* if (this->color == ChessColor::white) */ {
		return up ;
	}
}

void Pawn::move(const vec2<int> to) {
	//todo add move legality checking
	Piece::move(to) ;
}

const bool Pawn::canMove() const {
	
	auto checkForEmptyMoveableSquares = [this] (vector<const Square *> & squares) -> bool {
		for (auto i = 0 ; i < squares.size() ; i++) { //true if there's a square we can move to that's empty...
			if (squares.at(i)->isEmpty()) {
				return true ;
			}
		}
		return false ;
	} ;
	
	auto checkForCapturableSquares = [this] (vector<const Square *> & squares) -> bool {
		
		for (auto i = 0 ; i < squares.size() ; i++) { //true if there's a square we can move to that's empty...
			if ((squares.at(i)->getPiece() != nullptr) && (squares.at(i)->getPiece()->getColor() != this->color)) { //... or that has an opponent piece
				return true ;
			}
		}
		return false ;
	} ;
	
	
	bool canMoveToEmptySquare = (*board)->runSearchFunction<bool>(checkForEmptyMoveableSquares, *this->position, {getLegalMovementDirectionToEmptySquares()}, (movesMade == 0) ? 2 : 1) ; //check 2x as far at beginning of game
	
	bool canCapture = (*board)->runSearchFunction<bool>(checkForCapturableSquares, *this->position, getLegalCaptureDirections(), 1) ;
	
	return (canMoveToEmptySquare || canCapture) ;
}


Knight::Knight(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Knight::Knight(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
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


void Knight::move(const vec2<int> to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Bishop::Bishop(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Bishop::Bishop(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
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

void Bishop::move(const vec2<int> to) {
	//todo add move legality checking
	Piece::move(to) ;
}


Rook::Rook(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Rook::Rook(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
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

void Rook::move(const vec2<int> to) {
	//todo add move legality checking
	Piece::move(to) ;
}

Queen::Queen(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

Queen::Queen(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
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

void Queen::move(const vec2<int> to) {
	//todo add move legality checking
	Piece::move(to) ;
}


King::King(const ChessColor color, const vec2<int> * position, const Board * const * board, const Square * square) :
	Piece((color == ChessColor::black) ? symbols.black : symbols.white,
		  (color == ChessColor::black) ? imageFiles.black : imageFiles.white,
		  color,
		  position,
		  board,
		  square)
{
	
}

King::King(const wstring & symbol, const vec2<int> * position, const Board * const * board, const Square * square) :
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

void King::move(const vec2<int> to) {
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





