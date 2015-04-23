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

namespace Chess {

Symbols Pawn::symbols {/* black */ L'♟', /* white */ L'♙'} ;

Symbols Knight::symbols {/* black */ L'♞', /* white */ L'♘'} ;

Symbols Bishop::symbols {/* black */ L'♝', /* white */ L'♗'} ;

Symbols Rook::symbols {/* black */ L'♜', /* white */ L'♖'} ;

Symbols Queen::symbols {/* black */ L'♛', /* white */ L'♕'} ;

Symbols King::symbols {/* black */ L'♚', /* white */ L'♔'} ;


ImageFiles Pawn::imageFiles {/* black */ "./Assets/Bitmaps/BlackPawn.png", /* white */ "./Assets/Bitmaps/WhitePawn.png" } ;

ImageFiles Knight::imageFiles {/* black */ "./Assets/Bitmaps/BlackKnight.png", /* white */ "./Assets/Bitmaps/WhiteKnight.png" } ;

ImageFiles Bishop::imageFiles {/* black */ "./Assets/Bitmaps/BlackPawn.png", /* white */ "./Assets/Bitmaps/WhiteBishop.png" } ;

ImageFiles Rook::imageFiles {/* black */ "./Assets/Bitmaps/BlackRook.png", /* white */ "./Assets/Bitmaps/WhiteRook.png" } ;

ImageFiles Queen::imageFiles {/* black */ "./Assets/Bitmaps/BlackQueen.png", /* white */ "./Assets/Bitmaps/WhiteQueen.png" } ;

ImageFiles King::imageFiles {/* black */ "./Assets/Bitmaps/BlackKing.png", /* white */ "./Assets/Bitmaps/WhiteKing.png" } ;


unsigned long Piece::iDs = 0 ;


Piece * Piece::init(const wchar_t symbol, Square * square) {
	Piece * piece ;
	if (symbol == Pawn::symbols.white) {
		piece = new Pawn(Chess::Color::white, square) ;
	}
	else if (symbol == Pawn::symbols.black) {
		piece = new Pawn(Chess::Color::black, square) ;
	}
	else if (symbol == Knight::symbols.white) {
		piece = new Knight(Chess::Color::white, square) ;
	}
	else if (symbol == Knight::symbols.black) {
		piece = new Knight(Chess::Color::black, square) ;
	}
	else if (symbol == Bishop::symbols.white) {
		piece = new Bishop(Chess::Color::white, square) ;
	}
	else if (symbol == Bishop::symbols.black) {
		piece = new Bishop(Chess::Color::black, square) ;
	}
	else if (symbol == Rook::symbols.white) {
		piece = new Rook(Chess::Color::white, square) ;
	}
	else if (symbol == Rook::symbols.black) {
		piece = new Rook(Chess::Color::black, square) ;
	}
	else if (symbol == Queen::symbols.white) {
		piece = new Queen(Chess::Color::white, square) ;
	}
	else if (symbol == Queen::symbols.black) {
		piece = new Queen(Chess::Color::black, square) ;
	}
	else if (symbol == King::symbols.white) {
		piece = new King(Chess::Color::white, square) ;
	}
	else if (symbol == King::symbols.black) {
		piece = new King(Chess::Color::black, square) ;
	}
	else {
		piece = nullptr ;
	}
	return piece ;
}
	
Piece * Piece::initCopy(const Chess::Piece & piece) {
	
	switch (piece.type) {
			
		case Type::Pawn: {
			return new Pawn(piece) ;
			break;
		}
		case Type::Knight: {
			return new Knight(piece) ;
			break;
		}
		case Type::Bishop: {
			return new Bishop(piece) ;
			break;
		}
		case Type::Rook: {
			return new Rook(piece) ;
			break;
		}
		case Type::Queen: {
			return new Queen(piece) ;
			break;
		}
		case Type::King: {
			return new King(piece) ;
			break;
		}
		default: {
			throw std::exception() ; //debug code, remove
			break;
		}
	}
}

Piece::Piece(Type type, const wchar_t symbol, const string & spriteImageFilePath,
			 const Chess::Color color, Square * square) :
	
	type(type),
	iD(iDs++),
	symbol(symbol),
	color(color),
	/* movesMade init to 0 */
	spriteImageFilePath(spriteImageFilePath),
	/* Don't initialize the actual texture/sprite data. Too
	 expensive - we only init it when we need it */
	square(square)
{

}

Piece::Piece (const Piece & other) :
	type(other.type),
	iD(iDs++), //Pieces resulting from copies have their own, unique IDs
	symbol(other.symbol),
	color(other.color),
	/* movesMade init to 0 */
	spriteImageFilePath(other.spriteImageFilePath)
	
	/* Don't initialize the actual texture/sprite data. Too
	 expensive - we only init it when we need it */
	
	/* Don't copy other's square references: we don't know if we're owned
	 by a new board or still held by the same, and if we are on the new square/or board,
	 they'll have to update our references */
{
	
}

Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		/* Keeps it's own ID */
		assert(this->type == rhs.type) ; //debug code only
		this->symbol = rhs.symbol ;
		this->color = rhs.color ;
		/* Keeps own movesMade count */
		this->spriteImageFilePath = rhs.spriteImageFilePath ;
		/* Don't copy the actual texture/sprite data. Too
		 expensive - we only init it when we need it */
		/* Don't copy other's square references: we don't know if we're owned
		 by a new board or still held by the same, and if we are on the new square or board,
		 they'll have to update our references */
	}
	return * this ;
}
	
const vec2<int> * Piece::getPosition() const { return square->getPositionPointer() ; }

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
	
	vector<const Square *> squares = square->getBoard()->getSpecifiedSquares(* getPosition(), getLegalMovementDirections(), 1, getOpposite(this->getColor()), this->getColor()) ;
	
	return checkForAvailableSquares(squares) ;
}

vector<vec2<int>> Piece::getAllPossibleLegalMoves() const {
	
	vector<vec2<int>> legalMoves ;
	
	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(), this->getLegalMovementDirections(),
										 getOpposite(getColor()), getColor()) ;
	
	for (auto i = 0 ; i < squares.size() ; i++) {
		legalMoves.push_back(squares.at(i)->copyPosition()) ;
	}
	
	return legalMoves ;
}

void Piece::move(const vec2<int> to){
	Board * board = square->board ;
	
	this->square->clearCurrentPiece(this) ;
	
	Square * destination = board->getSquareMutable(to) ;
	destination->receiveMovingPiece(this) ;
	
	movesMade++ ;
}

	
void Piece::initSpriteTexture() {
	spriteTexture.loadFromFile(spriteImageFilePath) ;
	this->sprite = sf::Sprite(this->spriteTexture) ;
}

Pawn::Pawn(const Chess::Color color, Square * square) :
	Piece(Type::Pawn,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	sprite.setPosition(50, 50) ;
}

Pawn::Pawn(const wchar_t symbol, Square * square) :
	Piece(Type::Pawn,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
		  square)
{
	
}
	
vector<vec2<int>> Pawn::getAllPossibleLegalMoves() const {
	
	vector<const Square *> emptySquares = square->getBoard()->getSpecifiedSquares(* getPosition(),
		{getLegalMovementDirectionToEmptySquares()}, (movesMade == 0) ? 2 : 1, getOpposite(getColor()), getColor()) ;
	
	
	vector<const Square *> captureSquares = square->getBoard()->getSpecifiedSquares(* getPosition(),
		{getLegalCaptureDirections()}, 1, getOpposite(getColor()), getColor()) ;
	
	auto squares = emptySquares + captureSquares ;
	
	vector<vec2<int>> legalMoves ;
	
	for (auto i = 0 ; i < squares.size() ; i++) {
		legalMoves.push_back(squares.at(i)->copyPosition()) ;
	}
	
	return legalMoves ;
}

const vector<Direction> Pawn::getLegalMovementDirections() const {
	return getLegalCaptureDirections() + getLegalMovementDirectionToEmptySquares() ;
}

const vector<Direction> Pawn::getLegalCaptureDirections() const {
	if (this->color == Chess::Color::black) {
		return vector<Direction> { downLeft, downRight } ;
	}
	else /* if (this->color == Chess::Color::white) */ {
		return vector<Direction> { upLeft, upRight } ;
	}
}

Direction Pawn::getLegalMovementDirectionToEmptySquares() const {
	if (this->color == Chess::Color::black) {
		return down ;
	}
	else /* if (this->color == Chess::Color::white) */ {
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
	
	vector<const Square *> emptySquares = square->getBoard()->getSpecifiedSquares(*getPosition(), {getLegalMovementDirectionToEmptySquares()}, (movesMade == 0) ? 2 : 1, getOpposite(getColor()), getColor()) ;

	
	vector<const Square *> captureSquares = square->getBoard()->getSpecifiedSquares(*getPosition(), {getLegalCaptureDirections()}, 1, getOpposite(getColor()), getColor()) ;
	
	bool canMoveToEmptySquare = checkForEmptyMoveableSquares(emptySquares) ;
	bool canCapture = checkForCapturableSquares(captureSquares) ;
	
	return (canMoveToEmptySquare || canCapture) ;
}


Knight::Knight(const Chess::Color color, Square * square) :
	Piece(Type::Knight,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

Knight::Knight(const wchar_t symbol, Square * square) :
	Piece(Type::Knight,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
		  square)
{
	
}
	
vector<vec2<int>> Knight::getAllPossibleLegalMoves() const {
	
	vector<vec2<int>> legalMoves ;
	
	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(),
				   this->getLegalMovementDirections(), 1, getOpposite(getColor()), getColor()) ;
	
	for (auto i = 0 ; i < squares.size() ; i++) {
		legalMoves.push_back(squares.at(i)->copyPosition()) ;
	}
	
	return legalMoves ;
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

Bishop::Bishop(const Chess::Color color, Square * square) :
	Piece(Type::Bishop,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

Bishop::Bishop(const wchar_t symbol, Square * square) :
	Piece(Type::Bishop,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
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


Rook::Rook(const Chess::Color color, Square * square) :
	Piece(Type::Rook,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

Rook::Rook(const wchar_t symbol, Square * square) :
	Piece(Type::Rook,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
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

Queen::Queen(const Chess::Color color, Square * square) :
	Piece(Type::Queen,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

Queen::Queen(const wchar_t symbol, Square * square) :
	Piece(Type::Queen,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
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


King::King(const Chess::Color color, Square * square) :
	Piece(Type::King,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

King::King(const wchar_t symbol, Square * square) :
	Piece(Type::King,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
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
	






	
	
	
	
	
}
