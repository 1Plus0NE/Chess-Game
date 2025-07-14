#include "../include/board.h"
#include "../include/piece.h"

int main(int argc, char* argv[]){

    Board* board = inittializeBoard();
    printBoard(board);
    return 0;
} 