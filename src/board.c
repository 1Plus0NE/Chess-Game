#include "../include/board.h"

void placePieceRow(Board* board, Color color, int rank){
    board -> squares[0][rank] = inittializePiece(ROOK, color, 0, rank);
    board -> squares[1][rank] = inittializePiece(KNIGHT, color, 1, rank);
    board -> squares[2][rank] = inittializePiece(BISHOP, color, 2, rank);
    board -> squares[3][rank] = inittializePiece(QUEEN, color, 3, rank);
    board -> squares[4][rank] = inittializePiece(KING, color, 4, rank);
    board -> squares[5][rank] = inittializePiece(BISHOP, color, 5, rank);
    board -> squares[6][rank] = inittializePiece(KNIGHT, color, 6, rank);
    board -> squares[7][rank] = inittializePiece(ROOK, color, 7, rank);
}

void placePawnRow(Board* board, Color color, int rank){
    for(int file = 0; file < 8; file++){
        Piece* pawn = inittializePiece(PAWN, color, file, rank);
        board -> squares[file][rank] = pawn;
    }
}

void placeEmptyPieceRows(Board* board){
    for(int rank = 2; rank < 6; rank++){
        for(int file = 0; file < 8; file++){
            Piece* none = inittializePiece(NONE, NO_COLOR, file, rank);
            board -> squares[file][rank] = none;
        }
    }
}

Board* inittializeBoard(){
    Board* board = (Board*)malloc(sizeof(Board));
    if(!board){
        perror("Error alocating memory for the chess board.");
        exit(EXIT_FAILURE);
    }

    placePawnRow(board, WHITE, 1); // place white pawns
    placePieceRow(board, WHITE, 0); // place white pieces
    placePawnRow(board, BLACK, 6); // place black pawns
    placePieceRow(board, BLACK, 7); // place black pieces
    placeEmptyPieceRows(board);

    board -> playing = WHITE;

    return board;
}