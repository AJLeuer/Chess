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
		}
		case Type::Knight: {
			return new Knight(piece) ;
		}
		case Type::Bishop: {
			return new Bishop(piece) ;
		}
		case Type::Rook: {
			return new Rook(piece) ;
		}
		case Type::Queen: {
			return new Queen(piece) ;
		}
		case Type::King: {
			return new King(piece) ;
		}
		default: {
			throw std::exception() ; //debug code, remove
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
	square(square),
	startingPosition(square->copyPosition())
{

}

Piece::Piece (const Piece & other) :
	type(other.type), //commented for debug, uncomment later
	iD(iDs++), //Pieces resulting from copies have their own, unique IDs
	symbol(other.symbol),
	color(other.color),
	/* movesMade is already init to 0 */
	spriteImageFilePath(other.spriteImageFilePath),
	startingPosition(other.startingPosition) 
	
	/* Don't initialize the actual texture/sprite data. Too
	 expensive - we only init it when we need it */
	
	/* Don't copy other's square references: we don't know if we're owned
	 by a new board or still held by the same, and if we are on the new square/or board,
	 they'll have to update our references */
{
	
}

/*
Piece & Piece::operator = (const Piece & rhs) {
	if (this != & rhs) {
		assert(this->type == rhs.type) ; //debug code only
		// Keeps it's own ID
		this->symbol = rhs.symbol ;
		this->color = rhs.color ;
		// Keeps own movesMade count
		this->spriteImageFilePath = rhs.spriteImageFilePath ;
		this->startingPosition = rhs.startingPosition ; // *must* copy startingPosition from other
		// Don't copy the actual texture/sprite data. Too
		 expensive - we only init it when we need it
	
		// Don't copy other's square references: we don't know if we're owned
		// by a new board or still held by the same, and if we are on the new square or board,
		// they'll have to update our references
	}
	return * this ;
} */
	
const vec2<int> * Piece::getPosition() const { return square->getPositionPointer() ; }

	
const bool Piece::canMove() const {
	
	auto moves = this->getAllPossibleLegalMovePositions() ;
	
	const bool canMove = (moves.empty() == false) ;
	
	return canMove ;
}

vector<vec2<int>> Piece::getAllPossibleLegalMovePositions() const {
	
	vector<vec2<int>> legalMoves ;
	
	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(), this->getLegalMovementDirections(),
														   SafeBoolean::t, getOpposite(getColor())) ;
	
	for (auto & square : squares) {
		legalMoves.push_back(square->copyPosition()) ;
	}
	
	return legalMoves ;
}

vector<MoveIntent> Piece::getAllPossibleLegalMoves() {
	
	vector<MoveIntent> legalMoves ;
	
	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(), this->getLegalMovementDirections(),
														   SafeBoolean::t, getOpposite(getColor())) ;
	
	for (auto & square : squares) {
		
		vec2<int> moveDestination = square->copyPosition() ;
        
        union MoveIntent::BoardOrPiece pc {this};
		
		legalMoves.push_back(MoveIntent(true, pc, moveDestination, this->square->getBoard()->evaluateAfterHypotheticalMove(this, moveDestination))) ;
	}
	
	return legalMoves ;
}
	
tree<MoveIntent> Piece::getPossibleLegalMovesTree() {
	
	tree<MoveIntent> legalMoves ;

	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(), this->getLegalMovementDirections(),
														   SafeBoolean::t, getOpposite(getColor())) ;
	
	tree<MoveIntent>::sibling_iterator currentTreePos = legalMoves.begin() ;
	
	for (auto i = 0 ; i < squares.size() ; i++) {
		
		vec2<int> moveDestination = squares.at(i)->copyPosition() ;
        
        union MoveIntent::BoardOrPiece borp {this};
		
		currentTreePos = legalMoves.insert(currentTreePos, MoveIntent(true, borp, moveDestination,
																	  this->square->getBoard()->evaluateAfterHypotheticalMove(this, moveDestination))) ;
		
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
	updateSpritePosition() ;
}

Pawn::Pawn(const Chess::Color color, Square * square) :
	Piece(Type::Pawn,
		  (color == Chess::Color::black) ? symbols.black : symbols.white,
		  (color == Chess::Color::black) ? imageFiles.black : imageFiles.white,
		  color,
		  square)
{
	
}

Pawn::Pawn(const wchar_t symbol, Square * square) :
	Piece(Type::Pawn,
		  (symbol == symbols.black) ? symbols.black : symbols.white,
		  (symbol == symbols.black) ? imageFiles.black : imageFiles.white,
		  (symbol == symbols.black) ? Chess::Color::black : Chess::Color::white,
		  square)
{
	
}
	
vector<vec2<int>> Pawn::getAllPossibleLegalMovePositions() const {
	
	vector<const Square *> emptySquares = square->getBoard()->getSpecifiedSquares(* getPosition(),
										  {getLegalMovementDirectionToEmptySquares()},
										  (square->copyPosition() == startingPosition) ? 2 : 1, //if this is the pawn's first move, it can move 2 squares
										  SafeBoolean::f, Color::black) ; //last argument should be ignored
	
	vector<const Square *> captureSquares ;
	vector<const Square *> captureSquares_temporary = square->getBoard()->getSpecifiedSquares(* getPosition(),
													 {getLegalCaptureDirections()}, 1, SafeBoolean::t, getOpposite(getColor())) ;
	
	/* Only take the squares in capture directions if they hold pieces */
	for (auto i = 0 ; i < captureSquares_temporary.size() ; i++) {
		if (captureSquares_temporary[i]->isOccupied()) {
			if (captureSquares_temporary[i]->getPiece()->getColor() != this->getColor()) {
    			captureSquares.push_back(captureSquares_temporary[i]) ;
			}
		}
	}
	
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
	
vector<vec2<int>> Knight::getAllPossibleLegalMovePositions() const {
	
	vector<vec2<int>> legalMoves ;
	
	auto squares = square->getBoard()->getSpecifiedSquares(* getPosition(),
				   this->getLegalMovementDirections(), 1, SafeBoolean::t, getOpposite(getColor())) ;
	
	for (auto i = 0 ; i < squares.size() ; i++) {
		legalMoves.push_back(squares.at(i)->copyPosition()) ;
	}
	
	return legalMoves ;
}
	
const vector<Direction> Knight::getLegalMovementDirections() const {
	
	vector<Direction> directions ;
	
	for (int h = -1 ; h <= 1 ; h += 2) {
		for (int v = -2 ; v <= 2 ; v += 4) {
			directions.push_back(Direction(h, v)) ;
		}
	}
	
	for (int h = -2 ; h <= 2 ; h += 4) { 
		for (int v = -1 ; v <= 1 ; v += 2) {
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
	
MoveIntent::MoveIntent(const MoveIntent & other) :
    sentinel(other.sentinel),
    canMove(other.canMove),
    boardOrPiece(other.boardOrPiece),
	moveDestination(other.moveDestination),
    moveValue(other.moveValue)
{
	
}


MoveIntent::MoveIntent(MoveIntent && other) noexcept :
    sentinel(other.sentinel),
    canMove(other.canMove),
    boardOrPiece(other.boardOrPiece),
	moveDestination(std::move(other.moveDestination)),
    moveValue(other.moveValue)
{
    other.boardOrPiece = BoardOrPiece{(Board *)nullptr} ;
}
	
MoveIntent MoveIntent::createPieceSentinel(Piece * piece) {
	BoardOrPiece thePiece(piece);
	MoveIntent mv(false, thePiece, {0, 0}, 0);
    mv.sentinel = {true, Sentinel::piece} ;
	return mv ;
}
    
MoveIntent MoveIntent::createBoardSentinel(Board * board) {
	BoardOrPiece theBoard(board);
    MoveIntent mv(false, theBoard, {0, 0}, 0);
    mv.sentinel = {true, Sentinel::board};
    return mv ;
}

MoveIntent & MoveIntent::operator = (const MoveIntent & other) {
	if (this != & other) {
		canMove = other.canMove ;
		boardOrPiece = other.boardOrPiece;
		moveDestination = other.moveDestination ;
		moveValue = other.moveValue ;
	}
	return * this ;
}
	
MoveIntent & MoveIntent::operator = (MoveIntent && other) noexcept {
	if (this != & other) {
		canMove = other.canMove ;
		boardOrPiece = other.boardOrPiece;
		moveDestination = std::move(other.moveDestination) ;
		moveValue = other.moveValue ;
		
		other.boardOrPiece = BoardOrPiece((Board *)nullptr);
	}
	
	return * this ;
}
	
bool operator == (const MoveIntent & mv1, const MoveIntent & mv2) {
	return (& mv1 == & mv2) ;
}
	
bool operator != (const MoveIntent & mv1, const MoveIntent & mv2) {
	return (& mv1 != & mv2) ;
}
	
}
