/*
 * Used reference: https://tausiq.wordpress.com/2010/04/14/uva-846/
 */

#include <iostream>

using namespace std;

/**
 * @brief For the given initial and final steps, calculate the number of steps taken from initial to final step
 *
 * @ignore
 * The main idea is to insert the greater amount of steps on both extremes of an array. For example, we first insert
 * in the left extreme and then, if possible, to the right extreme with the same length as the one previously inserted.
 * As we do not need to display the steps, it is easier to start by calculating the maximum amount of of steps possible
 * to take from the first to the last step (ignoring all constraints).
 *
 * Example:
 * First step: 45
 * Last step : 50
 * Max steps: 5
 *
 * As stated by the problem, both first and last step must have value 1. Therefore we remove start with 1, insert the step,
 * check if it possible to insert in the opposite extreme, insert with value one, and increase the length in one
 *
 * Difference: 50 - 45 = 5
 * Insert step of length 1 in the left extreme -> Difference = 4
 * Insert step of length 1 in the right extreme -> Difference = 3
 *   Increase step in 1
 * Insert step of length 2 in the left extreme -> Difference = 1
 * Insert step of length 2 in the right extreme -> Difference = -1
 *
 * As the difference is less than or equal to 0, we can stop trying to insert more steps
 *
 *
 * Instead of using an array to store the value, as proposed by the reference, we can use a boolean flag
 * to switch from extremes and simply store the value in a counter.
 */
void solve(int start, int end) {

    int steps = 1;
    int stepsDifference = end - start;
    int stepsCounter = 0;
    bool oppositeExtreme = false;
    
    while(stepsDifference > 0) {
        stepsDifference -= steps;
        stepsCounter += 1;
        
        if (oppositeExtreme) steps += 1;

        oppositeExtreme = !oppositeExtreme;
    }
    
    cout << stepsCounter << endl;

}

/**
 * @brief Problem: 846 - Steps
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=787
*/
int main() {

    int cases = 0;
    cin >> cases;


    for (int i = 0; i < cases; i++) {
    
        int start = 0;
        int end = 0;
        cin >> start >> end;

        solve(start, end);

    }

    return 0;
}
