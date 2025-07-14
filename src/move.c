#include "../include/move.h"

int isMoveDiagonal(Position* from, Position* to){
    return abs(to -> rank - from -> rank) == abs(to -> file - from -> file);
}

int isMoveStraight(Position* from, Position* to){
    int same_file = from->file == to->file; // in case of moving in ranks, we have to ensure files arent changed
    int same_rank = from->rank == to->rank; // in case of moving in files, we have to ensure ranks arent changed
    int file_change = from->file != to->file; // result has to be different than both, meaning that it has moved at least a square within the file
    int rank_change = from->rank != to->rank; // result has to be different than both, meaning that it has moved at least a square within the rank

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
    }
    // Vertical move: file is same, rank changes
    else if(dx == 0 && dy != 0){
        int step = (dy > 0) ? 1 : -1;
        for(int r = from -> rank + step; r != to -> rank; r += step){
            Piece* p = board -> squares[from -> file][r];
            if(p -> type != NONE) return 0;
        }
    }
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
}

int isPathClear(Board* board, Position* from, Position* to){
    int dx = to -> file - from -> file;   // horizontal difference (left/right)
    int dy = to -> rank - from -> rank;   // vertical difference (up/down)

    if(isMoveStraight){
        return isPathClearStraight(board, from, to, dx, dy);
    }

    else if(isMoveDiagonal){
        return isPathClearDiagonal(board, from, to, dx, dy);
    }
}


int validateQueenMove(Board* board, Move* move){
    return isPathClear(board, move -> from, move -> to);
}

int validateRookMove(Board* board, Move* move){
    return isPathClearStraight(board, move -> from, move -> to);
}

int validateBishopMove(Board* board, Move* move){
    return isPathClearDiagonal(board, move -> from, move -> to);
}
