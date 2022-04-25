// Used references:
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1199
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define FAULT        20
#define CONSTESTANTS 100
#define PROBLEMS     9

typedef struct _contestant {
    int order;       // Contestant order
    int contestant;  // Contestant id
    int penalty;     // Time penalty accumulated
    int correct;     // Time for correct submission
    int solved;      // Number of problems solved
    bool submitted;

    /**
     * @brief Compare two contestants according to the contest rules.
     * @param a Any contestant
     * @param b Any contestant
     * @note Comparison rule:
     *  - First comes those contestants with more solved problems
     *  - Then comes those contestants with more total penalty time
     *  - Finally in submission order
     */
    bool operator<(const _contestant& submission) const {
        if (solved != submission.solved) {
            return solved > submission.solved;
        } else if (penalty + correct != submission.penalty + submission.correct) {
            return penalty + correct < submission.penalty + submission.correct;
        } else {
            return contestant < submission.contestant;
        }
    }
} Contestant;

/**
 * @brief Problem: 10258 - Contest Scoreboard
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1199
 */
int main() {
    int cases;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        vector<Contestant> submissions(CONSTESTANTS, Contestant());
        int problems[CONSTESTANTS][2 * PROBLEMS] = {0};

        for (int j = 0; j < CONSTESTANTS; j++) {
            submissions[j].order = INT_MAX;
            submissions[j].contestant = INT_MAX;
            submissions[j].penalty = 0;
            submissions[j].correct = 0;
            submissions[j].solved = 0;
            submissions[j].submitted = false;
        }

        size_t buffersize = 12;
        char* buffer = (char*)malloc(12 * sizeof(char));

        int contestant = 0, prob = 0, time = 0, cidx = 0;
        char status;

        // Read and update counters
        do {
            int read = getline(&buffer, &buffersize, stdin);

            if (read >= 4) {
                sscanf(buffer, "%d %d %d %c", &contestant, &prob, &time, &status);
                if (status == 'C' && problems[contestant - 1][prob - 1] != 1) {
                    submissions[contestant - 1].correct += time;
                    submissions[contestant - 1].solved += 1;
                    problems[contestant - 1][prob - 1] = 1;
                } else if (status == 'I' && problems[contestant - 1][prob - 1] != 1) {
                    problems[contestant - 1][prob - 1 + 9] += FAULT;
                }

                // Update counters to show
                if (!submissions[contestant - 1].submitted) {
                    submissions[contestant - 1].order = cidx;
                    submissions[contestant - 1].submitted = true;
                    submissions[contestant - 1].contestant = contestant;
                    cidx++;
                }

            } else {
                break;
            }
        } while (true);

        // Sort scoreboard
        for (int j = 0; j < CONSTESTANTS; j++) {
            int probsSolved = 0;
            int index = j;
            int timePenalty = 0;

            if (index == -1) break;

            for (int k = 0; k < PROBLEMS; k++) {
                if (problems[index][k]) {
                    probsSolved += 1;
                    timePenalty += problems[index][k + 9];
                }
            }

            submissions[index].penalty = timePenalty;
        }

        sort(submissions.begin(), submissions.end());

        // Print scoreboard
        for (int j = 0; j < CONSTESTANTS; j++) {
            int index = j;

            if (index == -1) continue;
            if (submissions[index].submitted) {
                printf("%d %d %d\n", submissions[index].contestant, submissions[index].solved,
                       submissions[index].correct + submissions[index].penalty);
            }
        }
        if (i < cases - 1) printf("\n");
        free(buffer);
    }

    return 0;
}
