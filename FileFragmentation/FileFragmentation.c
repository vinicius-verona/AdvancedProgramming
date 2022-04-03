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

typedef struct {
    int fragmentSize;
    char* fragment;
} FileFragment;
typedef struct {
    int fileSize;
    int numberOfFiles;
    char* bitPattern;

    FileFragment** smallest;
    FileFragment** biggest;
    FileFragment** fragments;
} Problem;

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
 * @param problem problem data
 * @return file's size
 */
int calculateFileSize(Problem* problem);

/**
 * @brief For the given fragments, try to find bit pattern.
 *
 * @param problem problem data
 */
void findBitPattern(Problem* problem);

int main() {
    int cases = 0;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        Problem* problem = malloc(sizeof(Problem));
        problem->fragments = malloc(ROWS * sizeof(FileFragment*));

        // Read and store fragmented files
        FileFragment* fragmentation = malloc(sizeof(FileFragment));
        fragmentation->fragment = malloc(COLS * sizeof(char));

        int fragmentCounter = 0;
        size_t fragmentTotalSize = COLS;

        // Read fragment
        while (getline(&fragmentation->fragment, &fragmentTotalSize, stdin) != -1) {
            if (fragmentation->fragment[0] == '\n' || fragmentation->fragment[0] == '\0') break;

            FileFragment* fragment = malloc(sizeof(FileFragment));
            fragment->fragment = malloc(COLS * sizeof(char));

            // problem->fragments[fragmentCounter] = malloc(COLS * sizeof(char));
            strcpy(fragment->fragment, fragmentation->fragment);
            int len = strlen(fragment->fragment);
            fragment->fragment[len - 1] = '\0';

            problem->fragments[fragmentCounter] = fragment;
            fragment->fragmentSize = len - 1;
            fragmentCounter++;
        }

        // for (int j = 0; j < fragmentCounter; j++) {
        //     printf("- %d len in pattern %s\n", problem->fragments[j]->fragmentSize, problem->fragments[j]->fragment);
        // }

        problem->smallest = malloc(fragmentCounter * sizeof(FileFragment*));
        problem->biggest = malloc(fragmentCounter * sizeof(FileFragment*));

        // Calculate number of files and file size
        problem->numberOfFiles = calculateNumberOfFiles(fragmentCounter);
        problem->fileSize = calculateFileSize(problem);

        // Find pattern
        findBitPattern(problem);
        printf("%s\n", problem->bitPattern);

        // Free memory
        for (int j = 0; j < fragmentCounter; j++) {
            free(problem->fragments[j]->fragment);
            free(problem->fragments[j]);
            problem->fragments[j] = NULL;
        }
        free(fragmentation->fragment);
        free(fragmentation);
        free(problem->fragments);
        free(problem->smallest);
        free(problem->biggest);
        free(problem);
    }

    return 0;
}

int calculateNumberOfFiles(int totalFragments) {
    return totalFragments / 2;
}

int calculateFileSize(Problem* problem) {
    int minSize = INT_MAX, maxSize = 0;
    FileFragment** fragments = problem->fragments;

    int smallestCounter = 0;
    int biggestCounter = 0;

    for (int i = 0; i < ROWS; i++) {
        if (fragments[i] == NULL) break;

        int size = fragments[i]->fragmentSize;

        if (size < minSize) {
            minSize = size;
            problem->smallest[0] = fragments[i];

            // Remove previously inserted fragments
            int auxCounter = 1;
            while (auxCounter <= smallestCounter) {
                problem->smallest[auxCounter] = NULL;
                auxCounter++;
            }
            smallestCounter = 0;

        } else if (size == minSize) {
            smallestCounter += 1;
            problem->smallest[smallestCounter] = fragments[i];
        }

        if (size > maxSize) {
            maxSize = size;
            problem->biggest[0] = fragments[i];

            // Remove previously inserted fragments
            int auxCounter = 1;
            while (auxCounter <= biggestCounter) {
                problem->biggest[auxCounter] = NULL;
                auxCounter++;
            }
            biggestCounter = 0;

        } else if (size == maxSize) {
            biggestCounter += 1;
            problem->biggest[biggestCounter] = fragments[i];
        }
    }

    return minSize + maxSize;
}

void findBitPattern(Problem* problem) {
    char leftPattern[300];   // small fragment + big fragment
    char rightPattern[300];  // big fragment + small fragment
    int patternCounter = 0;

    while (problem->smallest[patternCounter] != NULL) {
        strcpy(leftPattern, problem->smallest[patternCounter]->fragment);

        // For each of the biggest fragments, create a new pattern.
        int fi = 0;  // fragment i
        while (problem->biggest[fi] != NULL) {
            strcpy(leftPattern, problem->smallest[patternCounter]->fragment);
            strcat(leftPattern, problem->biggest[fi]->fragment);
            strcpy(rightPattern, problem->biggest[fi]->fragment);
            strcat(rightPattern, problem->smallest[patternCounter]->fragment);
            int rightPatternMatch = 0;
            int leftPatternMatch = 0;

            // Try to find the same pattern between others fragments
            for (int i = 0; i < ROWS; i++) {
                if (problem->fragments[i] == NULL) break;

                for (int j = 0; j < ROWS; j++) {
                    if (problem->fragments[j] == NULL) break;

                    if (i != j && problem->fragments[i]->fragmentSize + problem->fragments[j]->fragmentSize == problem->fileSize) {
                        char npattern[300];
                        strcpy(npattern, problem->fragments[i]->fragment);
                        strcat(npattern, problem->fragments[j]->fragment);

                        if (strcmp(npattern, leftPattern) == 0) {
                            leftPatternMatch++;
                        }
                        if (strcmp(npattern, rightPattern) == 0) {
                            rightPatternMatch++;
                        }
                    }
                }
            }

            if (leftPatternMatch >= problem->numberOfFiles) {
                problem->bitPattern = leftPattern;
                return;
            }

            if (rightPatternMatch >= problem->numberOfFiles) {
                problem->bitPattern = rightPattern;
                return;
            }
            fi++;
        }

        patternCounter++;
    }
}