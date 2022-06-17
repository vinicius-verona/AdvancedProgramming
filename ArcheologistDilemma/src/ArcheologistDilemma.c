#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG10 log2l(10)

/**
 * @brief Problem: 701 - The Archeologists' Dilemma
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=33&page=show_problem&problem=642
 */
int main() {
    long double leftHandNumber = 0;
    long double D = 0;

    while (scanf("%Lf\n", &leftHandNumber) == 1) {
        /*
         * We are looking for a number K such that:
         * input = 2^K / 10^D, where D equals is the difference (2^K) - getNumberOfDigits(input)
         * if input = 2^K / 10^D then:
         *  - input <= 2^K / 10^D < input + 1 is true
         *  - input * 10^D <= 2^K < (input + 1) * 10^D is true
         *  - log2(input * 10^D) <= K < log2((input + 1) * 10^D) is true
         *  - log2(input) + D * log2(10) <= K < log2(input + 1) + D * log2(10) is true
         */
        D = floorl(log10l(leftHandNumber)) + 1;  // log10l(n) + 1 takes number of digits of n
        D *= 2;

        while (1) {
            long double lowerBound = ceill(log2l(leftHandNumber) + D * LOG10);
            long double upperBound = floorl(log2l(leftHandNumber + 1) + D * LOG10);

            if ((long double)(pow(2, lowerBound)) < 0) {
                printf("no power of 2\n");
                break;
            }

            if (abs(upperBound - lowerBound) < 1) {
                printf("%.0Lf\n", lowerBound);
                break;
            }

            D += 1;
        }
    }

    return 0;
}