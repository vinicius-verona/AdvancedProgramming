#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROUND       5
#define CATEGORIES  13
#define BONUS       35
#define LIMIT_BONUS 63

int ROUNDS[CATEGORIES][ROUND];

/**
 * @brief Value of the round for the chosen category.
 *
 * @param round The numbers of each of the 5 dices
 * @param category The chosen category -> [1,2,3,4,5,6]
 * @return The sum of all values equal to 'category' within the round
 */
int sumValues(int round[ROUND], int category) {
    int sum = 0;

    for (int i = 0; i < ROUND; i++) {
        if (round[i] == category) sum += category;
    }
    return sum;
}

/**
 * @brief Scored value for the round if category chosen is 'Chance'.
 *
 * @param round The numbers of each of the 5 dices
 * @return The sum of each dice
 */
int scoreChance(int round[ROUND]) {
    int sum = 0;

    for (int i = 0; i < ROUND; i++) {
        sum += round[i];
    }

    return sum;
}

/**
 * @brief Scored value for the round if category chosen is 'N of a Kind'.
 *
 * @param round The numbers of each of the 5 dices
 * @param n The number of occurrence of the same value in order to score.
 * ->[3,4,5]
 * @return The sum of each dice if the round matches the category criteria (for
 * 3 <= n <= 4) and 50 (n = 5), and 0 otherwise.
 */
int scoreNOAK(int round[ROUND], int n) {
    bool matches = false;
    int occurrence = 0;

    for (int i = 0; i < ROUND; i++) {
        occurrence = 0;

        for (int j = 0; j < ROUND; j++) {
            if (round[i] == round[j]) occurrence += 1;
        }

        if (occurrence >= n) {
            matches = true;
            break;
        }
    }

    if (!matches) return 0;
    if (n == 5) return 50;

    int sum = 0;
    for (int i = 0; i < ROUND; i++) {
        sum += round[i];
    }

    return sum;
}

/**
 * @brief Scored value for the round if category chosen is 'Short Straight' or
 * 'Long Straight'.
 *
 * @param round The numbers of each of the 5 dices
 * @param n The category chosen (4 for 'Short' and 5 for 'Long')
 * @return 25 if the dices forms a sequence of 4 numbers and 'n' equals 4, 35 if
 * a sequence of five numbers and 'n' equals 5 and 0 if round does not match
 * criteria.
 */
int scoreStraight(int round[ROUND], int n) {
    int sequenceLength = 0;

    for (int i = 1; i < ROUND; i++) {
        if (round[i] == round[i - 1] + 1) sequenceLength += 1;
    }

    if (sequenceLength < 3) return 0;
    if (n == 5 && sequenceLength >= 4)
        return 35;
    else if (n == 4 && sequenceLength >= 3)
        return 25;
    else
        return 0;
}

/**
 * @brief Scored value for the round if category chosen is 'Full House'.
 *
 * @param round The numbers of each of the 5 dices
 * @return 40 if three of the dices are equal and the other two dices are also
 * equal, and 0 if round does not match criteria.
 */
int scoreFullHouse(int round[ROUND]) {
    bool matchForTwo = false;
    bool matchForThree = false;
    bool matchForFive = false;
    int valueCounter[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < ROUND; i++) {
        valueCounter[round[i] - 1] += 1;
    }

    for (int i = 0; i < 6; i++) {
        if (valueCounter[i] == 2) matchForTwo = true;
        if (valueCounter[i] == 3) matchForThree = true;
        if (valueCounter[i] == 5) matchForFive = true;
    }

    if ((matchForTwo && matchForThree) || matchForFive)
        return 40;
    else
        return 0;
}

/**
 * @brief Create an integer matrix Aij where i,j = 13,13
 *
 * @return 13 by 13 integer matrix.
 */
void createMatrix(int matrix[13][13]) {
    for (int i = 0; i < CATEGORIES; i++) {
        for (int j = 0; j < CATEGORIES; j++) {
            matrix[i][j] = 0;
        }
    }
}

/**
 * @brief Calculate the assignment score.
 *
 * @param game The score table
 * @param assignment - The round assigned to each category
 * @return Total score for the given assignment
 */
int gameScore(int game[CATEGORIES][CATEGORIES], int assignment[CATEGORIES]) {
    int sum = 0;
    int firstSix = 0;

    for (int i = 0; i < CATEGORIES; i++) {
        int round = assignment[i];
        sum += game[i][round];

        if (i < 6) firstSix += game[i][round];
    }

    if (firstSix >= LIMIT_BONUS) {
        sum += BONUS;
    }

    return sum;
}

void solve(int game[CATEGORIES][CATEGORIES]) {
    int scores[CATEGORIES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int assignedCategories[CATEGORIES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int assignedRounds[CATEGORIES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 1 - Find the maximum element within the scoreboard
    // 2 - Add to `scores` the assignment, remove its column and row
    // 3 - Back to 1
    for (int i = 0; i < CATEGORIES; i++) {
        int maxVal = 0;
        int maxRow = 0;
        int maxCol = 0;

        for (int j = 0; j < CATEGORIES; j++) {
            for (int k = 0; k < CATEGORIES; k++) {
                if (assignedCategories[j]) break;
                if (assignedRounds[k]) continue;
                if (game[j][k] > maxVal) {
                    maxVal = game[j][k];
                    maxRow = j;
                    maxCol = k;
                }
            }
        }

        if (scores[maxRow] == 0) {
            scores[maxRow] = maxVal;
            assignedRounds[maxCol] = 1;
            assignedCategories[maxRow] = 1;
        }
    }

    // Sum the scores in order to check if the game gets the bonus score or not.
    int firstSix = 0;
    int sum = 0;
    int bonus = 0;
    for (int i = 0; i < CATEGORIES; i++) {
        if (i < 6) firstSix += scores[i];
        sum += scores[i];
        printf("%d ", scores[i]);
    }

    if (firstSix >= LIMIT_BONUS) {
        bonus = BONUS;
        sum += BONUS;
    }
    printf("%d %d\n", bonus, sum);
}

void printGame(int game[CATEGORIES][CATEGORIES]) {
    for (int i = 0; i < CATEGORIES; i++) {
        for (int j = 0; j < CATEGORIES; j++) {
            printf("%2d ", game[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief Problem: 10149 - Yahtzee
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=30&page=show_problem&problem=1090
 */
int main() {
    // bool exit = false;
    int game[CATEGORIES][CATEGORIES];
    int dices[ROUND] = {0, 0, 0, 0, 0};

    do {
        createMatrix(game);

        for (int i = 0; i < CATEGORIES; i++) {
            dices[0] = 0;
            dices[1] = 0;
            dices[2] = 0;
            dices[3] = 0;
            dices[4] = 0;

            for (int j = 0; j < 5; j++) {
                if (scanf("%d", &dices[j]) != 1 && (dices[j] > 6 || dices[j] < 1)) {
                    return 0;
                }
            }

            ROUNDS[i][0] = dices[0];
            ROUNDS[i][1] = dices[1];
            ROUNDS[i][2] = dices[2];
            ROUNDS[i][3] = dices[3];
            ROUNDS[i][4] = dices[4];

            game[0][i] = sumValues(dices, 1);
            game[1][i] = sumValues(dices, 2);
            game[2][i] = sumValues(dices, 3);
            game[3][i] = sumValues(dices, 4);
            game[4][i] = sumValues(dices, 5);
            game[5][i] = sumValues(dices, 6);
            game[6][i] = scoreChance(dices);
            game[7][i] = scoreNOAK(dices, 3);
            game[8][i] = scoreNOAK(dices, 4);
            game[9][i] = scoreNOAK(dices, 5);
            game[10][i] = scoreStraight(dices, 4);
            game[11][i] = scoreStraight(dices, 5);
            game[12][i] = scoreFullHouse(dices);
        }

        solve(game);
    } while (true);

    return 0;
}