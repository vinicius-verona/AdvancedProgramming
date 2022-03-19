#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Represents one field input
 */
typedef struct {
    int rows;
    int columns;
    char** minesweeper;
} Problem;

/**
 * @brief For each minesweeper field, solve the game and print it;
 *
 * @param minesweeper Problem container
 * @param id The field ID. Ex: id = 1 outputs "Field #1:"
 */
void solve(Problem* minesweeper, int id);

/**
 * @brief For a giver element of the minesweeper, find the right value.
 *
 * @param minesweeper Problem container
 * @param row Element's row
 * @param column  Element's column
 *
 * @return The right value for that specific element
 */
int findValue(Problem* minesweeper, int row, int column);

/**
 * @brief Problem: 10189 - Minesweeper
 *
 * @ignore
 * Find at: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=29
 */
int main() {
    int rows = 0;
    int columns = 0;
    int id = 0;

    do {
        // Check if there is one more field
        scanf("%d %d", &rows, &columns);

        if (rows == 0 || columns == 0) break;
        id++;

        Problem* minesweeper = (Problem*)malloc(sizeof(Problem));  // Problem container
        minesweeper->rows = rows;
        minesweeper->columns = columns;
        minesweeper->minesweeper = (char**)malloc(rows * sizeof(char*));

        for (int i = 0; i < rows; i++) {
            minesweeper->minesweeper[i] = (char*)malloc(columns + 1 * sizeof(char));
            scanf("%s", minesweeper->minesweeper[i]);
        }

        solve(minesweeper, id);

        for (int i = 0; i < rows; i++) {
            free(minesweeper->minesweeper[i]);
        }
        free(minesweeper->minesweeper);

    } while (true);

    return 0;
}

void solve(Problem* minesweeper, int id) {
    printf("Field #%d:\n", id);

    for (int i = 0; i < minesweeper->rows; i++) {
        for (int j = 0; j < minesweeper->columns; j++) {
            if (minesweeper->minesweeper[i][j] == '.') {
                printf("%d", findValue(minesweeper, i, j));
            } else {
                printf("%c", minesweeper->minesweeper[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");
}

int findValue(Problem* minesweeper, int row, int column) {
    int value = 0;

    // Vertical boundaries
    int topBoundary = (row - 1) >= 0 ? (row - 1) : row;
    int lowerBoundary = (row + 1) <= minesweeper->rows - 1 ? (row + 1) : row;

    // Horizontal boundaries
    int leftBoundary = (column - 1) >= 0 ? (column - 1) : column;
    int rightBoundary = (column + 1) <= minesweeper->columns - 1 ? (column + 1) : column;

    // Look for mines wihtin the boundary
    for (int i = topBoundary; i <= lowerBoundary; i++) {
        for (int j = leftBoundary; j <= rightBoundary; j++) {
            if (i == row && j == column) continue;
            if (minesweeper->minesweeper[i][j] == '*') value++;
        }
    }

    return value;
}