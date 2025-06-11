#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

#ifndef BOARD_H
#define BOARD_H

#define WHITE 0
#define BLACK 1

/**
 * Structure to represent the chess board
 */
typedef struct board{
    Piece* squares[8][8];
    int playing;
}Board;

/**
 * Places white or black pieces (excluding pawns) in the board
 * 
 * @param board The pointer to the chess board structure
 * @param color The color of the pieces
 * @param rank The rank of the pieces
 */
void placePieceRow(Board* board, Color color, int rank);

/**
 * Places white or black pawns in the board
 * 
 * @param board The pointer to the chess board structure
 * @param color The color of the pawns
 * @param rank The rank of the pawns
 */
void placePawnRow(Board* board, Color color, int rank);

/**
 * Places empty pieces in the board
 * 
 * @param board The pointer to the chess board structure
 */
void placeEmptyPieceRows(Board* board);

/**
 * Inittialiazes the chess board
 */
Board* inittializeBoard();

#endif