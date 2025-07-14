#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "piece.h"
#include "board.h"

#ifndef MOVE_H
#define MOVE_H

/**
 * Structure to represent a position of a chess piece
 */
typedef struct position{
    int rank;
    int file;
}Position;

/**
 * Structure to represent a chess move, having:
 * From current rank/file
 * To rank/file
 * 
 * Checking the moved piece, used later for history
 * Captured piece
 * 
 * Flags to determine special moves
 */
typedef struct move{
    Position* from;
    Position* to;
    Piece* moved_piece;
    Piece* captured_piece;
    bool is_castling;
    bool is_en_passant;
    bool is_promotion;
    bool is_check;
}Move;

/**
 * Helper function that determines if a move is diagonal
 * 
 * Verifies if the absolute difference between "to position" and "from position" are equal within their ranks/files
 * 
 * @param from  The pointer of the position structure, representing current position
 * @param to    The pointer of the position structure, representing desisered position
 * 
 * @return 1 if the move is diagonal, 0 otherwise
 */
int isMoveDiagonal(Position* from, Position* to);

/**
 * Helper function that determines if a move is straight
 * 
 * Verifies if the move is either horizontal or vertical
 * 
 * @param from  The pointer of the position structure, representing current position
 * @param to    The pointer of the position structure, representing the next position 
 * 
 * @return 1 if the move is straight, 0 otherwise
 */
int isMoveStraight(Position* from, Position* to); 

/**
 * Helper function that determines if a move is out of bounds,
 * meaning that a chess piece cannot leave the chess board
 * 
 * @param to The pointer of the position structure, representing the next position
 * 
 * @return 1 if the move is out of bounds, 0 otherwise
 */
int isMoveOutOfBounds(Position* to);

/**
 * Function that determines if the path is clear for a straight move, wether it is horizontal or vertical
 * Checks if all squares are empty in order to make it possible
 * This function does not handle/verify the last position, since that will be verified by another function
 * 
 * @param board The pointer of the chess board
 * @param from  The pointer of the position structure, representing the current position
 * @param to    The pointer of the position structure, representing the next position
 * @param dx    The horizontal difference used to determine which direction its moving (left/right)
 * @param dy    The vertical difference used to determine which direction its moving (up/down)
 * 
 * @return 1 if the path is clear, 0 otherwise
 */
int isPathClearStraight(Board* board, Position* from, Position* to, int dx, int dy);

/**
 * Function that determines if the path is clear for a diagonal move
 * Checks if all squares are empty in order to make it valid
 * This function does not handle/verify the last position, since that will be covered by another function
 * 
 * @param board The pointer of the chess board
 * @param from  The pointer of the position structure, representing the current position
 * @param to    The pointer of the position structure, representing the next position
 * @param dx    The horizontal difference used to determine the direction its moving (left/right)
 * @param dy    The vertical difference used to determine the direction its moving (up/down)
 * 
 * @return 1 if the path is clear, 0 otherwise
 */
int isPathClearDiagonal(Board* board, Position* from, Position* to, int dx, int dy);

/**
 * Function that determines if the path is clear
 * Checks if all squares are empty in order to make it valid
 * 
 * @param board The pointer of the chess board structure, used to check if a square is empty (NONE)
 * @param from  The pointer of the position structure, representing the current position
 * @param to    The pointer of the position structure, representing the next position
 * 
 * @return 1 if the path is clear, 0 otherwise
 */
int isPathClear(Board* board, Position* from, Position* to);

/**
 * Validates a Queen Move
 * Checks if the move is valid and does not go through chess pieces 
 * 
 * @param board The pointer to the chess board 
 * @param move The pointer to the chess move
 * 
 * @return 1 if the move is valid, 0 otherwise
 */
int validateQueenMove(Board* board, Move* move);

// TO DO

int validateRookMove(Board* board, Move* move);
int validateBishopMove(Board* board, Move* move);
int validateKnightMove(Board* board, Move* move);
int validatePawnMove(Board* board, Move* move);
int validateKingMove(Board* board, Move* move);

int validateMove(Board* board, Move* move);


#endif