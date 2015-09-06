//
//  Player.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Player.h"
#include "Game.h"

using namespace std ;

namespace Chess {

unsigned long Player::uniqueIDs = 1 ;


Player::Player(Chess::Color color, Board * board) :
	ID(uniqueIDs++),
	name("Player " + to_string(ID)),
	color(color),
	board(board)
{
	registerForNotifications() ;
}
	
Player::Player(const Player & other) :
	ID(uniqueIDs++),
	name("Player " + to_string(ID)),
	color(other.color),
	board(nullptr)
{
		
}
	


Player::Player(Player && other) :
	ID(other.ID),
	name(std::move(other.name)),
	color(std::move(other.color)),
	board(other.board)
{
	other.ID = 0 ;
}
	
Player::~Player() {}


	
vector<Piece *> Player::findOwnPiecesOnBoard(const Board & workingBoard) const {
	
	vector<Piece *> workingPieces ;
	
	for (auto i = 0 ; i < workingBoard.boardRepresentation.size() ; i++) {
		for (auto j = 0 ; j < workingBoard.boardRepresentation[i].size() ; j++) {
			if (workingBoard.boardRepresentation[i][j].piece != nullptr) {
				if (workingBoard.boardRepresentation[i][j].piece->getColor() == this->color) {
					workingPieces.push_back(workingBoard.boardRepresentation[i][j].piece) ;
				}
			}
		}
	}
	
	return workingPieces ;
}

void Player::removePiece(Piece * piece) {
	bool pieceNotFound = true ; //debug var, remove
	
	//debug code
	if (pieceNotFound) {
		cerr << "Unexpected behavior in Player::removePiece(). Could not find a match for the given argument in remainingPieces" << endl ;
	}
	
}

void Player::registerForNotifications() {
	using namespace std::placeholders ;
	//The major use of notifications is to keep our remainingPieces() updated
	
	//Register to be notified when one of our pieces is captured...
}

const MoveIntent Human::decideNextMove() const {
	throw exception() ; //todo implement
}


const MoveIntent AI::decideNextMove() const {
	
	Board temporaryBoard(* this->board) ;
	
	AI simulatedOpponent(getOpposite(this->color), & temporaryBoard) ;
	
	const MoveIntent move = chooseBestMove(temporaryBoard) ;
	
	//todo finish
	return move ;
}
	
void AI::findMoveSequence(unsigned int maxSearchDepth, unsigned int currentDepth) {
	Game simulation(* this->board->game) ;
	
	vector<Piece *> workingPieces = findOwnPiecesOnBoard(* board) ;
}
	
	
tree<MoveIntent>  AI::computeAllMoves(Game & game, vector<Piece *> & piecesToSearchForMoves, vector<MoveIntent> & movesToCheck,
										unsigned piecesSearchedThisDepth, unsigned currentDepth, unsigned maxSearchDepth)
{
	
	tree<MoveIntent> searchTree ;
	

	if (currentDepth == maxSearchDepth) {
		
		if (piecesToSearchForMoves.empty()) {
			
			return searchTree ;
		}
		
		Piece * piece = piecesToSearchForMoves.back() ;
		
		searchTree = piece->getPossibleLegalMovesTree() ;
		
		piecesToSearchForMoves.pop_back() ;
		
		return searchTree ;
		
	}
	
	else {
		
		MoveIntent & move = movesToCheck.back() ;
		
		game.advanceGame_Simulated(game.getMatchingPlayer(* this), true, & move) ;
		
		game.advanceGame_Simulated(game.getOpponentPlayer(* this), false, nullptr) ;
	}


	
	//auto allMoves = (*currentPiece)->getAllPossibleLegalMovePositions() ;

	throw exception() ;
}
	
const MoveIntent AI::chooseBestMove(Board & board) const {
	vector<MoveIntent> highValueMoveOptions = computeBestMoves(board) ;
	
	MoveIntent move = selectMoveAtRandom(highValueMoveOptions) ;
	
	//get the actual live piece matching the one in mv, and swap it out for its stand-in
	Piece * original = this->board->getSquareMutable(*move.piece->getPosition())->getPieceMutable() ;
	move.piece = original ;
	
	return move ;
}
	
vector<MoveIntent> AI::computeBestMoves(Board & board) const {
	vector<Piece *> workingPieces = findOwnPiecesOnBoard(board) ;
	
	vector<MoveIntent> moveOptions ;
	
	for (auto i = 0 ; i < workingPieces.size() ; i++) {
		MoveIntent moveOption = findBestMoveForPiece(workingPieces.at(i)) ;
		assert(moveOption.piece == workingPieces.at(i)) ; //debug code only
		
		if (moveOption.canMove) {
			moveOptions.push_back(moveOption) ;
		}
	}
	vector<MoveIntent> highValueMoveOptions = extractHighestValueMoves(moveOptions) ;
	
	return highValueMoveOptions ;
}

const MoveIntent AI::findBestMoveForPiece(Piece * piece) const {
	
	/* don't change the state of Piece's original board */
	const Board * originalBoard = piece->getSquare()->getBoard() ;
	
	auto possibleMoves = piece->getAllPossibleLegalMovePositions() ;
	
	
	if (possibleMoves.size() > 0) {
		
		/* instead copy it each time the piece moves, and compare the board values after each move */
		Board testBoard(*originalBoard) ;
		
		Piece * testPiece = testBoard.getSquareMutable(*piece->getPosition())->getPieceMutable() ;
		
		
		testPiece->move(possibleMoves.at(0)) ;
		
		int highestMoveValue = testBoard.evaluate(piece->getColor()) ;
		
		vector <MoveIntent> optimalMoves ;
		
		MoveIntent currentBestMove { true, piece, *testPiece->getPosition(), highestMoveValue } ;
		
		optimalMoves.push_back(currentBestMove) ;
		
		/* test all possible moves for this piece on a copy of the game state, so we don't disrupt the *actual*
		 	game state */
		for (auto i = 1 ; i < possibleMoves.size() ; i++) {
			
			Board testBoard(*originalBoard) ;
			
			testPiece = testBoard.getSquareMutable(*piece->getPosition())->getPieceMutable() ;
			
			if (testPiece->deleted) { //debug code
				;
			}
			
			testPiece->move(possibleMoves.at(i)) ;
			
			int currentMoveValue = testBoard.evaluate(piece->getColor()) ;
			
			
			if (currentMoveValue >= highestMoveValue) {
				
				highestMoveValue = currentMoveValue ;
				
				MoveIntent currentBestMove { true, piece, *testPiece->getPosition(), highestMoveValue } ;
				
				optimalMoves.push_back(currentBestMove) ;
				
			}
			
		}
		
		/* Take out all but the highest-valued moves */
		extractHighestValueMoves(optimalMoves) ;
		
		/* The remaining moves all have equally beneficial outcomes, so choose one at random */
		return selectMoveAtRandom(optimalMoves) ;
		
	}
	else { /* then it's impossible for this Piece to move */
		
		MoveIntent noMove { false, piece, vec2<int>{0, 0}, 0 } ;
		
		return noMove ;
	}
}
	
	
	
	
vector <MoveIntent> extractHighestValueMoves(const vector <MoveIntent> & moves) {
	
	vector<MoveIntent> optimalMoves ;
	
	if (moves.size() == 0) {
		std::exit(0) ;
	}
	
	int highestValue = moves[0].moveValue ;
	
	for (auto i = 1 ; i < moves.size() ; i++) {
		if (moves[i].moveValue > highestValue) {
			highestValue = moves[i].moveValue ;
		}
	}
	
	for (auto i = 0 ; i < moves.size() ; i++) {
		if (moves[i].moveValue == highestValue) {
			optimalMoves.push_back(moves[i]) ;
		}
	}
	
	return optimalMoves ;
}
	
	
MoveIntent selectMoveAtRandom(const vector <MoveIntent> & moves) { return chooseRandomElement(moves) ; }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}