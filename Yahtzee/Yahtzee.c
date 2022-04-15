#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROUND      5
#define CATEGORIES 13

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
 * @brief Problem: 10149 - Yahtzee
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=30
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
                if (scanf("%d", &dices[j]) != 1 &&
                    (dices[j] > 6 || dices[j] < 1)) {
                    return 0;
                }
            }

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

        for (int i = 0; i < CATEGORIES; i++) {
            for (int j = 0; j < CATEGORIES; j++) {
                printf("%2d ", game[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    } while (true);

    return 0;
}

/**
 * Aparentemente, para cada categoria
 * é necessário colocar o valor da soma referente
 * à rodada escolhida para receber aquela categoria
 *
 */