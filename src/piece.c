#include "../include/piece.h";

/* --- Memory Allocation ---*/
Piece* inittializePiece(PieceType type, Color color, int file, int rank){
    Piece* p = (Piece*)malloc(sizeof(Piece));
    if(!p){
        perror("Error alocating memory for the chess piece.");
        exit(EXIT_FAILURE);
    }
    
    p -> type = type;
    p -> color = color;
    p -> file = file;
    p -> rank = rank;

    return p;
}

/* --- Getters ---*/

PieceType getPieceType(Piece* p){
    return p -> type;
}

Color getPieceColor(Piece* p){
    return p -> color;
}

int getPieceFile(Piece* p){
    return p -> file;
}

int getPieceRank(Piece* p){
    return p -> rank;
}

/* --- Setters ---*/

void setPieceType(Piece* p, PieceType type){
    p -> type = type;
}

void setPieceColor(Piece* p){
    p -> color = NO_COLOR;
}

void setPieceFile(Piece* p, int file){
    p -> file = file;
}

void setPieceRank(Piece* p, int rank){
    p -> rank = rank;
}

/* --- Memory Deallocation ---*/
void freePiece(Piece* p){
    free(p);
}