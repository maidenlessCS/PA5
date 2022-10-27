#include "tetris.h"

int main() {

    char board[20][10];

    initializeBoard(board, '-');

    displayBoard(board);

    return 0;

}