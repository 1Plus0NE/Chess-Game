#include "../include/move.h"

int deltaX(Position* from, Position* to){
    return to -> file - from -> file;
}

int deltaY(Position* from, Position* to){
    return to -> rank - from -> rank;
}

int isMoveDiagonal(Position* from, Position* to){
    return abs(deltaX(from, to)) == abs(deltaY(from, to));
}

int isMoveStraight(Position* from, Position* to){
    int same_file = from -> file == to -> file; // in case of moving in ranks, we have to ensure files arent changed
    int same_rank = from -> rank == to -> rank; // in case of moving in files, we have to ensure ranks arent changed
    int file_change = from -> file != to -> file; // result has to be different than both, meaning that it has moved at least a square within the file
    int rank_change = from -> rank != to -> rank; // result has to be different than both, meaning that it has moved at least a square within the rank

    return (same_file && rank_change) || (same_rank && file_change);
}

int isMoveOutOfBounds(Position* to){
    return (to -> rank > 7 || to -> file > 7);
}

int isPathClearStraight(Board* board, Position* from, Position* to, int dx, int dy){
    // Horizontal move: rank is same, file changes
    if(dy == 0 && dx != 0){
        int step = (dx > 0) ? 1 : -1; // if dx > 0 then increment by 1, else decrement by -1
        for(int f = from -> file + step; f != to -> file; f += step){ // starts at the next square (excluding own), stops before destination
            Piece* p = board -> squares[f][from -> rank];
            if(p -> type != NONE) return 0;
        }
        return 1; // valid
    }
    // Vertical move: file is same, rank changes
    else if(dx == 0 && dy != 0){
        int step = (dy > 0) ? 1 : -1;
        for(int r = from -> rank + step; r != to -> rank; r += step){
            Piece* p = board -> squares[from -> file][r];
            if(p -> type != NONE) return 0;
        }
        return 1; // valid
    }
    return 0; // not a valid straight move path
}

int isPathClearDiagonal(Board* board, Position* from, Position* to, int dx, int dy){
    int rank_step = (dy > 0) ? 1 : -1;
    int file_step = (dx > 0) ? 1 : -1;

    int f = from -> file + file_step;
    int r = from -> rank + rank_step;

    while(f != to -> file && r != to -> rank){ // iterate through the diagonal lines
        Piece* p = board -> squares[f][r];
        if(p -> type != NONE) return 0;
        f += file_step;
        r += rank_step;
    }
    return 1; // valid
}

int isPathClear(Board* board, Position* from, Position* to){
    int dx = deltaX(from, to);   // horizontal difference (left/right)
    int dy = deltaY(from, to);   // vertical difference (up/down)

    if(isMoveStraight(from, to)){
        return isPathClearStraight(board, from, to, dx, dy);
    }
 
    else if(isMoveDiagonal(from, to)){
        return isPathClearDiagonal(board, from, to, dx, dy);
    }
    return 0; // not a straight/diagonal move 
}

int validateQueenMove(Board* board, Move* move){
    if(!isMoveOutOfBounds(move -> to)){
        if(isMoveStraight(move -> from, move -> to) || isMoveDiagonal(move -> from, move -> to)){
            return isPathClear(board, move -> from, move -> to);
        }
        return 0;
    }
    return 0;
}

int validateRookMove(Board* board, Move* move){
    if(!isMoveOutOfBounds(move -> to)){
        if(isMoveStraight(move -> from, move -> to)){
            return isPathClear(board, move -> from, move -> to);
        }
        return 0;
    }
    return 0;
}

int validateBishopMove(Board* board, Move* move){
    if(!isMoveOutOfBounds(move -> to)){
        if(isMoveDiagonal(move -> from, move -> to)){
            return isPathClear(board, move -> from, move -> to);
        }
        return 0;
    }
    return 0;
}

int isMoveLShape(Board* board, Move* move){

    int from_rank = move -> from -> rank;
    int from_file = move -> from -> file;
    int to_rank = move -> to -> rank;
    int to_file = move -> to -> file;

    int dx = abs(to_file - from_file);
    int dy = abs(to_rank - from_rank);

    // Step 1: check if move is an L shape
    if(!((dx == 2 && dy == 1) || (dx == 1 && dy == 2)))
        return 0; // invalid geometry
    
    // Step 2: retrieve pieces
    Piece* from_piece = board->squares[from_file][from_rank];
    Piece* to_piece   = board->squares[to_file][to_rank];

    // Step 3: validate destination
    if(to_piece->type == NONE)
        return 1; // empty square, legal move
    

    if(to_piece->color != from_piece->color) 
        return 1; // capture enemy piece, legal move
    
    // same color piece in destination — illegal
    return 0;

}

int validateKnightMove(Board* board, Move* move){
    if(!isMoveOutOfBounds(move -> to)){
        return isMoveLShape(board, move);
    }
    return 0;
}

int validatePawnMove(Board* board, Move* move){

    int from_rank = move -> from -> rank;
    int from_file = move -> from -> file;
    int to_rank = move -> to -> rank;
    int to_file = move -> to -> file;

    int dx = to_file - from_file;
    int dy = to_rank - from_rank;

    Piece* pawn = board->squares[from_file][from_rank]; // get piece from board
    // if it is white, its direction is positive, from 1 to 8, otherwise it is black and its direction is negative, from 8 to 1
    int dir = (pawn->color == WHITE) ? 1 : -1;
    // get the starting rank of the piece, if it is white it starts in the second position (1), otherwise it is black and starts at the 7th position (6)
    int start_rank = (pawn->color == WHITE) ? 1 : 6;

    // Destination square
    Piece* destination = board->squares[to_file][to_rank];

    // First case: One-square forward move
    if(dx == 0 && dy == dir * 1){
        // Must be empty
        if(destination->type == NONE)
            return 1; 
        else
            return 0; // blocked by a piece
    }

    // Second case: Two-square forward move (only from starting rank)
    if(dx == 0 && dy == dir * 2){
        if(from_rank == start_rank){
            int mid_rank = from_rank + dir; // square in between
            Piece* middle = board->squares[from_file][mid_rank];
            // Both must be empty
            if (middle->type == NONE && destination->type == NONE)
                return 1; 
        }
        return 0; // not from start rank or path blocked
    }

    // Third case: Diagonal capture
    if(abs(dx) == 1 && dy == dir * 1){
        if(destination->type != NONE && destination->color != pawn->color)
            return 1; 
        else
            return 0; // no piece to capture
    }

    // Invalid move
    return 0;

}

int validateKingMove(Board* board, Move* move){
    int from_rank = move -> from -> rank;
    int from_file = move -> from -> file;
    int to_rank = move -> to -> rank;
    int to_file = move -> to -> file;

    int dx = abs(to_file - from_file);
    int dy = abs(to_rank - from_rank);

    return ((dx == 0 && dy == 1) || (dx == 1 && dy == 0) || (dx == 1 && dy == 1));
}

int validateMove(Board* board, Move* move){
    Piece* p = move -> moved_piece;

    switch(p -> type){
        case QUEEN:
            return validateQueenMove(board, move);
            break;
        case ROOK:
            return validateRookMove(board, move);
            break;
        case BISHOP:
            return validateBishopMove(board, move);
            break;
        case KNIGHT:
            return validateKnightMove(board, move);
            break;
        case PAWN:
            return validatePawnMove(board, move);
            break;
        case KING:
            return validateKingMove(board, move);
            break;
        case NONE:
        default:
            return 0;
    }   

}