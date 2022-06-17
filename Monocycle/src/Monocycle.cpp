/*
 * Used reference: https://github.com/morris821028/UVa/blob/master/volume100/10047%20-%20The%20Monocycle.cpp (BFS exit
 * condition)
 */

#include <iostream>
#include <string.h>

#include <list>
#include <vector>

using namespace std;

#define MAX_INSTANCE_LENGTH 25
#define COLORS              5
#define DIRS                4

#define GREEN 0
#define NORTH 0

// INFO:
// Dirs => 0 = North, 1 = East, 2 = South, 3 = West
// Colors => 0 = Green, 1 = Black, 2 = Red, 3 = Blue, 4 = White

struct Vertex {
    int row;       // Current row in the grid
    int column;    // Current column in the grid
    int color;     // Current color
    int direction; // Current direction
    int steps;     // Current number of steps taken

    Vertex(int _row, int _column, int _color, int _direction, int _steps)
        : row(_row), column(_column), color(_color), direction(_direction), steps(_steps) {}
};

// Used to traverse and execute BFS storing the time taken from S to the current point
int grid[MAX_INSTANCE_LENGTH][MAX_INSTANCE_LENGTH][COLORS][DIRS];

// Grid provided by the problem instance
char problemGrid[MAX_INSTANCE_LENGTH][MAX_INSTANCE_LENGTH];

// Instance size
int prows, pcolumns, cases;

// Move forward
int forwardRow(int currentRow, int currentDirection) {
    if (currentDirection == 0) { // Facing North
        return currentRow -= 1;
    }
    if (currentDirection == 2) { // Facing South
        return currentRow += 1;
    }

    // East or West
    return currentRow;
}

int forwardColumn(int currentColumn, int currentDirection) {
    if (currentDirection == 1) { // Facing East
        return currentColumn += 1;
    }
    if (currentDirection == 3) { // Facing West
        return currentColumn -= 1;
    }

    // North or South
    return currentColumn;
}

/**
 * @brief For the given grid, traverse using BFS and display the minimum amount
 * of time necessary for the cyclist to reach the target position.
 *
 * @ignore
 * In order to complete the task we must verify if the target position is
 * reachable with the green region of the monocycle facing the ground. If it is
 * reachable, we must display the minimum amount of time the cyclist will take
 * from S to T.
 *
 * Executing BFS will automatically complete both tasks once we can verify if
 * the graph is either connected or not. Besides, as BFS analyzes the graph in
 * depth level, the first time we reach the target point with the green region
 * facing the ground will be the minimum amount of time the cyclist take from S
 * to T.
 *
 * PS: 1 Step = 1 second
 */
void solve(int startingRow, int startingColumn, int targetRow, int targetColumn) {

    cases += 1;
    int timeTaken = -1;
    memset(grid, -1, sizeof(grid)); // -1 means unvisitied vertex
    grid[startingRow][startingColumn][GREEN][NORTH] = 0;

    // Start BFS list
    list<Vertex> visiting_vertices;

    // Mark initial vertex as visited
    Vertex vertex(startingRow, startingColumn, GREEN, NORTH, 0);
    visiting_vertices.push_back(vertex);

    while (!visiting_vertices.empty()) {

        vertex = visiting_vertices.front();
        visiting_vertices.pop_front();

        // If reached target with green segment facing the ground, eixt BFS;
        if (vertex.row == targetRow && vertex.column == targetColumn && vertex.color == GREEN) {
            timeTaken = vertex.steps;
            break;
        }

        // Possible steps: rotate left, go forward, rotate right
        // The following code blocks checks for walls grid limits and if possible follow the steps in order mentioned

        int nrow = vertex.row, ncol = vertex.column, color = vertex.color, dir = vertex.direction;

        if (grid[nrow][ncol][color][(dir + 3) % DIRS] == -1) {
            grid[nrow][ncol][color][(dir + 3) % DIRS] = vertex.steps + 1;

            Vertex auxiliarVertex(nrow, ncol, color, (dir + 3) % DIRS, (vertex.steps + 1));
            visiting_vertices.push_back(auxiliarVertex);
        }

        nrow  = forwardRow(vertex.row, vertex.direction);
        ncol  = forwardColumn(vertex.column, vertex.direction);
        color = vertex.color;
        dir   = vertex.direction;

        if (nrow >= 0 && nrow < prows && ncol >= 0 && ncol < pcolumns && problemGrid[nrow][ncol] != '#') {
            if (grid[nrow][ncol][(color + 1) % COLORS][dir] == -1) {
                grid[nrow][ncol][(color + 1) % COLORS][dir] = vertex.steps + 1;

                Vertex auxiliarVertex(nrow, ncol, (color + 1) % COLORS, dir, (vertex.steps + 1));
                visiting_vertices.push_back(auxiliarVertex);
            }
        }

        nrow  = vertex.row;
        ncol  = vertex.column;
        color = vertex.color;
        dir   = vertex.direction;

        if (grid[nrow][ncol][color][(dir + 1) % DIRS] == -1) {
            grid[nrow][ncol][color][(dir + 1) % DIRS] = vertex.steps + 1;

            Vertex auxiliarVertex(nrow, ncol, color, (dir + 1) % DIRS, (vertex.steps + 1));
            visiting_vertices.push_back(auxiliarVertex);
        }
    }

    if (cases != 1) cout << endl;
    cout << "Case #" << cases << endl;

    if (timeTaken > 0)
        cout << "minimum time = " << timeTaken << " sec" << endl;
    else
        cout << "destination not reachable" << endl;
}

/**
 * @brief Problem: 10047 - The Monocycle
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=40&page=show_problem&problem=988
 */
int main() {

    int rows = 0, cols = 0;
    cases = 0;

    while (cin >> rows >> cols) {
        if (rows == 0 || cols == 0) return 0;

        prows = rows, pcolumns = cols;
        int sRow = 0, sCol = 0, tRow = 0, tCol = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> problemGrid[i][j];
                if (problemGrid[i][j] == 'S') {
                    sRow = i;
                    sCol = j;
                }
                if (problemGrid[i][j] == 'T') {
                    tRow = i;
                    tCol = j;
                }
            }
        }

        solve(sRow, sCol, tRow, tCol);
    }

    return 0;
}