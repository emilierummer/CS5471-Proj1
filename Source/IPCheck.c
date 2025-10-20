#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashUtils.h"

/**
 * Gets the size of the RBF from the file
 */
int getRbfSize(FILE *file) {
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking to end of file");
        return -1;
    }
    long fileSize = ftell(file);
    if (fileSize == -1l) {
        perror("Error getting file size");
        return -1;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error seeking to beginning of file");
        return -1;
    }
    return (int)fileSize;
}

/**
 * Reads the RBF from a file
 */
int *readRbf(FILE *file, int rbfSize) {
    // Allocate memory for RBF
    int *rbf = malloc(rbfSize * sizeof(int));
    if (rbf == NULL) {
        perror("Error allocating memory for RBF");
        return NULL;
    }

    // Read RBF from file
    for (int i = 0; i < rbfSize; i++) {
        int ch = fgetc(file);
        if (ch == EOF) {
            printf("Error: Unexpected end of file while reading RBF\n");
            free(rbf);
            return NULL;
        }
        rbf[i] = ch - '0';  // Convert char to int
    }
    return rbf;
}

/**
 * Checks if an IP is in the RBF
 * Returns: 0 for false and 1 for true
 */
int checkIp(int m, int *rbf, char ip[]) {
    for (int i = 1; i <= NUM_HASHES; i++) {
        // Get which column we're checking
        int rbfCol = hashWithKey(i, ip, m);

        // Check if we should be using the first or second row of the bloom filter
        int row = getRbfRow(rbfCol);

        // If the bit is 0, the IP is definitely not in the RBF
        int bit = rbf[rbfCol];
        if ((row == 0 && bit == 0) || (row == 1 && bit == 1)) {
            return 0;
        }
    }
    return 1;
}


/**
 * Checks if an IP is in the RBF
 *
 * Inputs:
 * - input file name (string)
 * - IP to check (string)
 *
 * Output:
 * - "pass" or "block"
 */
int main(int argc, char *argv[]) {
    // Process command line arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <IP to check>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *inputFileName = argv[1];
    char *ipToCheck = argv[2];

    // Read RBF from file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Error: Could not open input file %s\n", inputFileName);
        return EXIT_FAILURE;
    }
    int m = getRbfSize(file);
    if (m < 0) {
        fclose(file);
        return EXIT_FAILURE;
    }
    int *rbf = readRbf(file, m);
    if (rbf == NULL) {
        free(rbf);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Check if the IP is in the RBF
    int result = checkIp(m, rbf, ipToCheck);
    if (result) {
        printf("block\n");
    } else {
        printf("pass\n");
    }

    // Cleanup
    free(rbf);
    fclose(file);
    return EXIT_SUCCESS;
}
