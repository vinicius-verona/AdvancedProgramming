/**
 * @file FileFragmentation.cpp
 * Find N -> number of substrings / 2
 * Find the size of a complete string -> (biggest substring + smallest substring)
 *
 * For one of the fragments iterate through the matching fragmentations creating bit patterns
 * Selected a pattern, try to join the rest of the matching fragmentations to create the same pattern as
 * the one created with the matching fragmentation.
 *
 * A matching fragment is the one that complete the substring in matter of size
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 144
#define COLS 257

/**
 * @brief Calculate the total amount of files given an amount of fragments
 *
 * @param totalFragments number of fragments read
 * @return number of files fragmented
 */
int calculateNumberOfFiles(int totalFragments);

/**
 * @brief Calculate the total size of a file given all the fragments read.
 *
 * @param fragmentations fragments read
 * @return file's size
 */
int calculateFileSize(char** fragmentations);

int main() {
    int cases = 0;

    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        // Read and store fragmented files
        char** fragmentations = malloc(ROWS * sizeof(char*));
        char* fragment = malloc(COLS * sizeof(char));
        int fragmentCounter = 0;
        size_t fragmentTotalSize = COLS;

        // Read fragment
        while (getline(&fragment, &fragmentTotalSize, stdin) != -1) {
            if (fragment[0] == '\n' || fragment[0] == '\0') break;

            fragmentations[fragmentCounter] = malloc(COLS * sizeof(char));
            strcpy(fragmentations[fragmentCounter], fragment);
            fragmentCounter++;
        }

        // Calculate number of files and file size
        int nfiles = calculateNumberOfFiles(fragmentCounter);
        int fileSize = calculateFileSize(fragmentations);

        printf("Number of files: %d\n", nfiles);
        printf("File size: %d\n\n", fileSize);

        // Free memory
        for (int r = 0; r < fragmentCounter; r++) {
            free(fragmentations[r]);
        }

        free(fragment);
    }

    return 0;
}

int calculateNumberOfFiles(int totalFragments) {
    return totalFragments / 2;
}

int calculateFileSize(char** fragmentations) {
    int minSize = INT_MAX, maxSize = 0;

    for (int i = 0; i < ROWS; i++) {
        if (fragmentations[i] == NULL) break;

        int size = 0;
        while (fragmentations[i][size] != '\n' && fragmentations[i][size] != '\0') size++;

        if (size < minSize) minSize = size;
        if (size > maxSize) maxSize = size;
    }

    return minSize + maxSize;
}