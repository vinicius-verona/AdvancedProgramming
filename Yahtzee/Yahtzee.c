#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROUND 5

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
 * ->[1,2,3,4,5]
 * @return The sum of each dice if the round matches the category criteria (for
 * 1 <= n <= 4) and 50 (n = 5), and 0 otherwise.
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

    if (sequenceLength < 4) return 0;
    if (n == 5 && sequenceLength == 5)
        return 35;
    else if (n == 4 && sequenceLength == 4)
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
        valueCounter[round[i]] += 1;
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
 * @brief Problem: 10149 - Yahtzee
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=30
 */
int main() {
    do {
    } while (true);

    return 0;
}

/**
 * Aparentemente, para cada categoria
 * é necessário colocar o valor da soma referente
 * à rodada escolhida para receber aquela categoria
 *
 */