#include <stdio.h>
#include <stdlib.h>
// TODO: Import SHA256 from openssl

/** 
 * Hash an IP using a key and SHA256
 */
int hashWithKey(char key[], char ip[]) {

}

/**
 * Initialize the RBF to default values
 * - Set bits to either 0 or 1 based on the hash mod 2 value
 * - Only store the first row of the RBF
 */
void initRBF(FILE *file, int m) {

}

/**
 * Insert an IP address into the RBF
 */
void insertIP(char ip[]) {
    
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
        return 1;
    }
    int m = atoi(argv[1]);
    if(m <= 0) {
        printf("Error: m must be a positive integer\n");
        return 1;
    }
    char* outputFileName = argv[2];

    // Create output file (or clear it if it already exists)
    // TODO: check that this works correctly
    FILE *file = fopen(outputFileName, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", outputFileName);
        return 1;
    }

    // Initialize RBF and add IP addresses
    initRBF(file, m);
    // TODO: set up for loop
    insertIP("ip");

    // Close file
    fclose(file);
	return 0;
}

