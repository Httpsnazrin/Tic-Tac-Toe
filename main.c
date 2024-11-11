#include <stdio.h>

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

int choice;
int player = 1; // Player 1 starts
int row, column;
char mark;
int player_moves[2][9]; // Store moves for each player, maximum 9 moves each

void printBoard() {
    printf("\n\n Tic-Tac-Toe Board \n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n\n");
}

int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }

    return 0;
}

void deleteFirstMove(int player) {
    int firstMove = player_moves[player - 1][0];  // Get the first move of the player
    row = (firstMove - 1) / 3;
    column = (firstMove - 1) % 3;

    // Reset the first move to its original number
    board[row][column] = '0' + firstMove;
    printf("First move of Player %d has been deleted!\n", player);

    // Also reset the neighboring cell (right or down, depending on the position)
    if (column < 2) {
        // If it's not the last column, reset the right neighbor
        board[row][column + 1] = '0' + (firstMove + 1);  // Right neighbor
    } else if (row < 2) {
        // If it's the last column, check downwards
        board[row + 1][column] = '0' + (firstMove + 3);  // Bottom neighbor
    }
}

int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0; // There are still moves left
            }
        }
    }
    return 1; // Draw
}

int main() {
    printf("Tic-Tac-Toe Game!\n");
    printBoard();

    while (1) {
        printf("Player %d, enter a number (1-9): ", player);
        scanf("%d", &choice);

        // Convert choice to row and column
        row = (choice - 1) / 3;
        column = (choice - 1) % 3;

        if (board[row][column] != 'X' && board[row][column] != 'O') {
            mark = (player == 1) ? 'X' : 'O';
            board[row][column] = mark;
            player_moves[player - 1][choice - 1] = choice; // Save the move of the player
            printBoard();

            if (checkWin()) {
                printf("Player %d wins!\n", player);
                break;
            }

            // If the game ends in a draw, delete the first move of the current player and continue the game
            if (checkDraw()) {
                printf("It's a draw, but we continue playing!\n");
                deleteFirstMove(player); // Delete the first move of the current player
            }

            // Switch player
            player = (player == 1) ? 2 : 1;
        } else {
            printf("Cell already taken, try again.\n");
        }
    }

    return 0;
}
