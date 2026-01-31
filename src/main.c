#include "../include/board.h"
#include "../include/piece.h"

int main(int argc, char* argv[]){
    int playing = 1;
    Board* board = inittializeBoard();
    printBoard(board);
    return 0;
} 