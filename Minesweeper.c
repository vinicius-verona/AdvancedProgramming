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
 * @param minesweeper - Problem container
 */
void solve(Problem* minesweeper);

/**
 * @brief Problem: 10189 - Minesweeper
 *
 * @ignore
 * Find at: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=29
 */
int main() {
    int rows = 0;
    int columns = 0;

    do {
        // Check if there is one more field
        scanf("%d %d", &rows, &columns);

        if (rows == 0 && columns == 0) break;
        printf("Rows: %d | Columns: %d\n", rows, columns);

        // Problem minesweeper;  // Problem container
        Problem* minesweeper = (Problem*)malloc(sizeof(Problem));  // Problem container
        minesweeper->rows = rows;
        minesweeper->columns = columns;
        minesweeper->minesweeper = (char**)malloc(rows * sizeof(char*));

        for (int i = 0; i < rows; i++) {
            minesweeper->minesweeper[i] = (char*)malloc(columns + 1 * sizeof(char));
            scanf("%s", minesweeper->minesweeper[i]);
        }

        solve(minesweeper);

        for (int i = 0; i < rows; i++) {
            free(minesweeper->minesweeper[i]);
        }
        free(minesweeper->minesweeper);

    } while (true);

    return 0;
}

void solve(Problem* minesweeper) {
}