#include <stdio.h>
#include <stdlib.h>

#ifndef PIECE_H
#define PIECE_H

/**
 * Structure to represent a type of a chess piece
*/
typedef enum{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NONE // used to represent empty space in the board
}PieceType;

/**
 * Structure to represent a color of a chess piece
 */
typedef enum{
    WHITE,
    BLACK,
    NO_COLOR // used when a piece's type is NONE
}Color;

/**
 * Structure to represent a chess piece
 */
typedef struct piece{
    PieceType type;
    Color color;
    int file; // 0 .. 7 || a .. h in chess notation 
    int rank; // 0 .. 7 || 1 .. 8 in chess notation
}Piece;

/**
 * Creates a chess piece
 * 
 * @param type  The type of the piece
 * @param color The color of the piece
 * @param file  The file of the piece
 * @param rank  The rank of the piece 
 * 
 * @return The created chess piece
 */
Piece* inittializePiece(PieceType type, Color color, int file, int rank);

/**
 * Returns the type of the chess piece
 * 
 * @param p The pointer to the chess piece structure
 * 
 * @return The type of the chess piece
 */
PieceType getPieceType(Piece* p);

/**
 * Returns the color of the chess piece
 * 
 * @param p The pointer to the chess piece structure
 * 
 * @return The color of the chess piece
 */
Color getPieceColor(Piece* p);

/**
 * Returns the current file position of the chess piece
 * 
 * @param p The pointer to the chess piece structure
 * 
 * @return The current file of the chess piece
 */
int getPieceFile(Piece* p);

/**
 * Returns the current rank position of the chess piece
 * 
 * @param p The pointer to the chess piece structure
 * 
 * @return The current rank of the chess piece
 */
int getPieceRank(Piece* p);

/**
 * Changes the type of the chess piece
 * This function is used whenever a piece is captured or a pawn is promoted
 * 
 * @param p     The pointer to the chess piece structure
 * @param type  The new type of the chess piece
 */
void setPieceType(Piece* p, PieceType type);

/**
 * Changes the color of the chess piece
 * This function is used when a piece is captured
 * 
 * @param p The pointer to the chess piece structure
 */
void setPieceColor(Piece* p);

/**
 * Changes the file of the chess piece
 * 
 * @param p     The pointer to the chess piece structure
 * @param file  The new file of the chess piece
 */
void setPieceFile(Piece* p, int file);

/**
 * Changes the rank of the chess piece
 * 
 * @param p     The pointer to the chess piece structure
 * @param rank  The new rank of the chess piece
 */
void setPieceRank(Piece* p, int rank);

/**
 * Frees the memory allocated from a chess piece
 * 
 * @param p The pointer to the chess piece structure
 */
void freePiece(Piece* p);

#endif