#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char** initBoard();
void printBoard(char** board);
void playerMove(char** board);
int smartComputerMove(char** board);
void computerMove(char** board);
int checkWinner(char** board);
int checkFreeSpaces(char** board);

int main() {
    char** board = initBoard();

    do{
        printBoard(board);
        playerMove(board);
        printBoard(board);
        if( !smartComputerMove(board))
            computerMove(board);

    }while(checkFreeSpaces(board) == 0 || checkWinner(board) == 0);

    printBoard(board);

    free(board);
    return 0;
}

char** initBoard() {
    char** newBoard = (char**)malloc(3 * sizeof(char*));
    for(int i = 0; i < 3; i++)
        newBoard[i] = (char*)malloc(3 * sizeof(char*));

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            newBoard[i][j] = ' ';

    return newBoard;
}

void printBoard(char** board) {
    /*
        | X |   |   |
        -------------
        |   | X |   |
        -------------
        |   |   | X |
     */

    for(int i = 0; i < 5; i++) {
        if(i % 2){
            printf("-------------\n");
        }
        else {
            if(i == 0)
                printf("| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
            else if(i == 2)
                printf("| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
            else
                printf("| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);
        }
    }
}

void playerMove(char** board)
{
    int x, y;

    do {
        printf("\nEnter your move:\n x = ");
        scanf("%d", &x);
        printf("\n y = ");
        scanf("%d", &y);
        if(board[x][y] != ' ' || x > 2 || y > 2)
            printf("\nPosition not available!\n");
    } while(board[x][y] != ' ' || x > 2 || y > 2);

    board[x][y] = 'X';
}

int smartComputerMove(char** board) {
    int x, y;

    // try winning if close
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == 'O' && board[i][2] == 'O' && board[i][1] == ' ') {
            board[i][1] = 'O';
            printf("\nComputer move: x = %d y = %d\n", i, 1);
            return 1;
        }
        if(board[0][i] == 'O' && board[2][i] == 'O' && board[1][i] == ' ') {
            board[1][i] = 'O';
            printf("\nComputer move: x = %d y = %d\n", 1, i);
            return 1;
        }
    }

    // check diagonals

    if(((board[0][0] == 'O' && board[2][2] == 'O') || (board[0][2] == 'O' && board[2][0] == 'O')) && board[1][1] == ' ') {
        board[1][1] = 'O';
        printf("\nComputer move: x = %d y = %d\n", 1, 1);
        return 1;
    }

    // try blocking user if is about to win
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == 'X' && board[i][2] == 'X' && board[i][1] == ' ') {
            board[i][1] = 'O';
            printf("\nComputer move: x = %d y = %d\n", i, 1);
            return 1;
        }
        if(board[0][i] == 'X' && board[2][i] == 'X' && board[1][i] == ' ') {
            board[1][i] = 'O';
            printf("\nComputer move: x = %d y = %d\n", 1, i);
            return 1;
        }
    }

    // check diagonals
    if(((board[0][0] == 'X' && board[2][2] == 'X') || (board[0][2] == 'X' && board[2][0] == 'X')) && board[1][1] == ' ') {
        board[1][1] = 'O';
        return 1;
    }

    return 0;
}

void computerMove(char** board) {
    int x, y;

    do {
        srand(time(0));
        x = rand() % 3;
        y = rand() % 3;
    } while(board[x][y] != ' ');

    printf("\nComputer move: x = %d y = %d\n", x, y);

    board[x][y] = 'O';
}

int checkWinner(char** board) {
    //  check rows

    if(board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
        if (board[0][0] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[0][0] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    if(board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
        if (board[1][0] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[1][0] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    if(board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
        if (board[2][0] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[2][0] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    // check columns

    if(board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
        if (board[0][0] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[0][0] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    if(board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
        if (board[0][1] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[0][1] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    if(board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
        if (board[0][2] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        } else if (board[0][2] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    // check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if(board[0][0] == 'X'){
            printf("\nPlayer wins!\n");
            return 1;
        }
        if(board[0][0] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if(board[0][2] == 'X') {
            printf("\nPlayer wins!\n");
            return 1;
        }
        if(board[0][2] == 'O') {
            printf("\nComputer wins!\n");
            return 1;
        }
    }

    // no winner found
    return 0;
}

int checkFreeSpaces(char** board) {
    int freeSpaces = 0;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == ' ')
                freeSpaces += 1;

    return freeSpaces;
}