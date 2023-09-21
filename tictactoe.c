#include <stdio.h>
#include <ctype.h>

typedef enum {
    NO_PLAYER,
    X_PLAYER,
    O_PLAYER,
} Player;

typedef struct {
    int x;
    int y;
    Player player;
} BoardSlot;

BoardSlot initSlot(int x, int y) {
    BoardSlot slot = {
        .x = x,
        .y = y,
        .player = NO_PLAYER
    };
    return slot;
}

char player(BoardSlot slot) {
    Player player = slot.player;
    if (player == NO_PLAYER) {
        return '-';
    } else if (player == X_PLAYER) {
        return 'X';
    } else {
        return 'O';
    }
}

void printBoard(BoardSlot board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", player(board[i][j]));
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
    }
}

void cleanBoard(BoardSlot board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = initSlot(i, j);
        }
    }
}

void executeTurn(Player turn, BoardSlot board[3][3]){
    int x;
    int y;
    printf("Player %d, input your square.\n", turn);
    int valid_turn = 0;
    
    while (valid_turn < 1) {
        char input[500];
        fgets(input, 500, stdin);
        char c = input[0];
        if (!isdigit(c)) {
            printf("Input not numerical. Try again, player %d.\n", turn);
            continue;
        }
        sscanf(input, "%d %d", &x, &y);
        printf("x: %d, y: %d\n", x, y);
        if (x > 2 || y > 2) {
            printf("Invalid input. Try again, player %d.\n", turn);
        } else
        if (board[x][y].player != NO_PLAYER) {
            printf("Square occupied. Try again, player %d.\n", turn);
        } else {
            board[x][y].player = turn;
            valid_turn = 1;
        }
    }
}

Player checkBoard(BoardSlot board[3][3]) {
    //diagonals
    int LR = 4;
    int RL = 2;
    BoardSlot* center = &board[1][1];
    if (center->player != NO_PLAYER) {
        if (center->player == (center - LR)->player && center->player == (center + LR)->player) {
            return center->player;
        } else
        if (center->player == (center - RL)->player && center->player == (center + RL)->player) {
            return center->player;
        }
    }
    //columns
    for (int i = 0; i < 3; i++) {
        BoardSlot* pivot = &board[1][i];
        if (pivot->player != NO_PLAYER) {
            if (pivot->player == (pivot-3)->player && pivot->player == (pivot+3)->player) {
                return pivot->player;
            }
        }
    }
    //rows
    for (int i = 0; i < 3; i++) {
        BoardSlot* pivot = &board[i][0];
        if (pivot->player != NO_PLAYER) {
            if (pivot->player == (pivot+1)->player && pivot->player == (pivot+2)->player) {
                return pivot->player;
            }
        }
    }
    return NO_PLAYER;
}

int is_board_full(BoardSlot board[3][3]){
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y].player == NO_PLAYER) {
                return 0;
            }
        }
    }
    return 1;
}


int main() {
    BoardSlot board[3][3];
    int keep_going = 1;
    while (keep_going == 1) {
        cleanBoard(board);
        printBoard(board);
        Player victor = NO_PLAYER;
        Player turn = X_PLAYER;
        while (!is_board_full(board) && victor == NO_PLAYER) {
            executeTurn(turn, board);
            printBoard(board);
            
            if (turn == X_PLAYER) {
                turn = O_PLAYER;
            } else {
                turn = X_PLAYER;
            }
            victor = checkBoard(board);
        }
        keep_going = 0;
        if (victor != NO_PLAYER) {
            printf("Player %d won.\n", victor);
        } else if(is_board_full(board)){
            printf("The game ended in a draw.\n");
        }
        printf("Press 1 to restart game. Otherwise, the script will terminate itself.\n");
        char keep_going_str[3];
        fgets(keep_going_str, 3, stdin);
        sscanf(keep_going_str, "%d", &keep_going);
    }
    printf("Thank you for playing.");
    return 0;
}