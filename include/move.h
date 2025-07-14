#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "piece.h"
#include "board.h"

#ifndef MOVE_H
#define MOVE_H

typedef struct position{
    int rank;
    int file;
}Position;

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

int validateQueenMove(Board* board, Move move);
int validateRookMove(Board* board, Move move);
int validateBishopMove(Board* board, Move move);
int validateKnightMove(Board* board, Move move);
int validatePawnMove(Board* board, Move move);
int validateKingMove(Board* board, Move move);

int validateMove(Board* board, Move move);


#endif