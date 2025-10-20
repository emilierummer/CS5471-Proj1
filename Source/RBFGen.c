#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashUtils.h"

/**
 * Initialize the RBF to default values
 * - Set bits to either 0 or 1 based on the hash mod 2 value
 * - Only store the first row of the RBF
 */
int *initRBF(int m) {
    // Initialize array
    int *rbf = malloc(m * sizeof(int));
    if (rbf == NULL) {
        printf("Error: Could not allocate memory for RBF\n");
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        // Hash column index with key 0 and mod 2
        int row = getRbfRow(i);
        rbf[i] = row;
    }
    // Return a pointer to the array
    return rbf;
}

/**
 * Insert an IP address into the RBF
 */
void insertIP(int *rbf, char ip[], int m) {
    for (int i = 1; i <= NUM_HASHES; i++) {
        // Get which column we're setting
        int rbfCol = hashWithKey(i, ip, m);

        // Check if we should be using the first or second row of the bloom filter
        int row = getRbfRow(rbfCol);
        rbf[rbfCol] = (row == 0) ? 1 : 0;
    }
}

/**
 * Creates text file with the first row of the RBF
 *
 * Inputs:
 * - m (number)
 * - output file name (string)
 */
int main(int argc, char *argv[]) {
    // Process command line arguments
    if (argc != 3) {
        printf("Usage: %s <m> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int m = atoi(argv[1]);
    if (m <= 0) {
        printf("Error: m must be a positive integer\n");
        return EXIT_FAILURE;
    }
    char *outputFileName = argv[2];

    // Initialize RBF and add IP addresses
    int *rbf = initRBF(m);
    if (!rbf) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 10; i++) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                for (int z = 0; z < 10; z++) {
                    char ip[16];
                    snprintf(ip, sizeof(ip), "192.168.%d.%d%d%d", i, x, y, z);
                    insertIP(rbf, ip, m);
                }
            }
        }
    }

    // Create output file (or clear it if it already exists)
    FILE *file = fopen(outputFileName, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", outputFileName);
        return EXIT_FAILURE;
    }

    // Write RBF to file 
    for (int i = 0; i < m; i++) {
        fprintf(file, "%d", rbf[i]);
    }

    // Cleanup
    free(rbf);
    fclose(file);
    return EXIT_SUCCESS;
}

