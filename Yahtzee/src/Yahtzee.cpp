/** Used References
 * https://blog.csdn.net/metaphysis/article/details/6432286
 * https://karatos.com/art?id=b080d332-3878-4f66-8a5f-f8d7d7ee9bd9
 * https://codingstrife.wordpress.com/2013/07/10/solution-uva10149-pc110208-yahtzee/
 */

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
#define ROUND       5
#define CATEGORIES  13
#define BONUS       35
#define LIMIT_BONUS 63
#define DEBUG       false  // Used to display recursions

int RECURSIVE_COUNTER = 0;

/*
 * For each pair<int,int> in MEMO there is a vector of combinations where the position CATEGORIES+1
 * is the total result for that combination.
 */
map<pair<int, int>, vector<int>> MEMO;
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

void printGame(int game[CATEGORIES][CATEGORIES]) {
    for (int i = 0; i < CATEGORIES; i++) {
        for (int j = 0; j < CATEGORIES; j++) {
            printf("%2d ", game[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

string toBinary(int n, int len) {
    string binary;
    for (unsigned i = (1 << (len - 1)); i > 0; i = i / 2) {
        binary += (n & i) ? "1" : "0";
    }

    return binary;
}

/**
 * @brief With the usage of Dynamic Programming find the best possible combination of categorization.
 * Each of the 2^13 (due to bitmask used on the first element of each MEMO key) possible combinations are stored
 * on a (map<pair<int, int>> MEMO).
 *
 * @skip
 * This method was adapted from https://codingstrife.wordpress.com/2013/07/10/solution-uva10149-pc110208-yahtzee/ for
 * educational purposes. The solution idea belongs to the author of the article.
 */
vector<int> dpMemoSolver(int nCategories, int unusedRounds, int game[CATEGORIES][CATEGORIES]) {
    int krow = nCategories, kcol = unusedRounds;

    if (DEBUG) RECURSIVE_COUNTER += 1;

    vector<int> bestSolution(CATEGORIES + 1, 0);
    vector<int> localSolution(CATEGORIES + 1, 0);
    pair<int, int> memoKey(krow, kcol);

    bestSolution[CATEGORIES] = -1;

    if (DEBUG) cout << "\nCALL: " << RECURSIVE_COUNTER << endl;

    auto solution = MEMO.find(memoKey);

    // If the scoreing combination has already beem calculated, return it
    if (solution != MEMO.end()) return solution->second;

    // Recursion base case -> no category left to be used
    if (!nCategories) {
        // Access the column in the position where the only uncategorized round is located
        int cidx = (int)(log(unusedRounds) / log(2));

        if (DEBUG) cout << "RETURN from " << nCategories << " categories - cidx: " << cidx << endl;

        bestSolution[nCategories] = game[nCategories][cidx];
        bestSolution[CATEGORIES] = game[nCategories][cidx];
        return bestSolution;
    }

    // For a given category, check solution for each available round as if it was assigned to the given category
    for (int i = 0; i < CATEGORIES; i++) {
        if (DEBUG) {
            cout << "CALL: " << RECURSIVE_COUNTER << " unusedRounds -> " << toBinary(unusedRounds, 13) << endl;
            cout << "unusedRounds AND -> " << toBinary(unusedRounds & (int)pow(2, i), 13)
                 << " i = " << toBinary(pow(2, i), 13) << " - " << i << endl;
        }

        if (unusedRounds & (int)pow(2, i))   // Check if round was selected
            unusedRounds ^= (int)pow(2, i);  // Select round
        else
            continue;

        if (DEBUG) {
            cout << "unusedRounds XOR 1 -> " << toBinary(unusedRounds, 13) << " i = " << toBinary(pow(2, i), 13)
                 << " - " << i << endl;
        }

        // Recursive call to solve smalled instances
        localSolution = dpMemoSolver(nCategories - 1, unusedRounds, game);

        // Assign current category to current round
        localSolution[nCategories] = game[nCategories][i];
        localSolution[CATEGORIES] += game[nCategories][i];

        // Check Bonus score when category is 5
        if (nCategories == 5 && localSolution[CATEGORIES] >= LIMIT_BONUS) localSolution[CATEGORIES] += BONUS;

        // If found solution is better than the current best solution, replace solution
        if (localSolution[CATEGORIES] > bestSolution[CATEGORIES]) bestSolution = localSolution;
        unusedRounds ^= (int)pow(2, i);

        if (DEBUG) {
            cout << "unusedRounds XOR 2 -> " << toBinary(unusedRounds, 13) << " i = " << toBinary(pow(2, i), 13)
                 << " - " << i << endl;
            cout << "\n";
        }
    }

    if (DEBUG) cout << "RETURN solution and insert in MEMO" << endl;

    MEMO[memoKey] = bestSolution;
    return bestSolution;
}

/**
 * @brief Using Dynamic Programming with memoization hashtable, find maximum possible values for the given Yahtzee
 * scoreboard. It tests each possible combination of rounds categorization using bitmask as auxiliars to avoid re-
 * calculating all possibilities.
 *
 * @param game - The calculated scoreboard for the game.
 */
void solve(int game[CATEGORIES][CATEGORIES]) {
    MEMO.clear();
    if (DEBUG) RECURSIVE_COUNTER = 0;
    vector<int> scores = dpMemoSolver(CATEGORIES - 1, pow(2, CATEGORIES) - 1, game);

    // Sum the scores in order to check if the game gets the bonus score or not.
    int firstSix = 0;
    int bonus = 0;

    for (int i = 0; i < CATEGORIES; i++) {
        if (i < 6) firstSix += scores[i];
        printf("%d ", scores[i]);
    }

    if (firstSix >= LIMIT_BONUS) {
        bonus = BONUS;
    }
    printf("%d %d\n", bonus, scores[CATEGORIES]);
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
