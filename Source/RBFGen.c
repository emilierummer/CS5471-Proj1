#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/**
 * Hash an IP using a key and SHA256
 */
int hashWithKey(int key, const char *ip, int m) {
    // Combine key and IP into a single string
    char combined[16];
    snprintf(combined, sizeof(combined), "%d%s", key, ip);

    // Hash the combined string
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)combined, strlen(combined), hash);

    // Get the least significant 24 bits of the hash
    unsigned int finalHash = 0;
    for (int i = SHA256_DIGEST_LENGTH - 3; i < SHA256_DIGEST_LENGTH; i++) {
        finalHash = (finalHash << 8) | hash[i];
    }
    // Keep only the least significant 20 bits
    finalHash = finalHash & 0xFFFFF;

    // Mod the result with m and return
    return finalHash % m;
}

/**
 * Initialize the RBF to default values
 * - Set bits to either 0 or 1 based on the hash mod 2 value
 * - Only store the first row of the RBF
 */
int *initRBF(int m) {
    // Initialize array
    int *rbf = malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        // Hash column index with key 0 and mod 2
        char colAsString[2];
        snprintf(colAsString, sizeof(colAsString), "%d", i);
        rbf[i] = hashWithKey(2, colAsString, 2);
    }
    // Return a pointer to the array
    return rbf;
}

/**
 * Insert an IP address into the RBF
 */
void insertIP(char ip[], int m) {
    printf("Inserting IP: %s\n", ip);
    for (int i = 1; i <= 8; i++) {
        printf("\tHash with key %d: %d\n", i, hashWithKey(i, ip, m));
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
        return 1;
    }
    int m = atoi(argv[1]);
    if (m <= 0) {
        printf("Error: m must be a positive integer\n");
        return 1;
    }
    char *outputFileName = argv[2];

    // Initialize RBF and add IP addresses
    int *rbf = initRBF(m);

    // for(int i = 0; i < 10; i++) {
    //     for(int x = 0; x < 10; x++) {
    //         for(int y = 0; y < 10; y++) {
    //             for(int z = 0; z < 10; z++) {
    //                 char ip[16];
    //                 snprintf(ip, sizeof(ip), "192.168.%d.%d%d%d", i, x, y, z);
    //                 insertIP(ip);
    //             }
    //         }
    //     }
    // }
    insertIP("192.168.0.000", m);
    insertIP("192.168.0.001", m);

    // Create output file (or clear it if it already exists)
    FILE *file = fopen(outputFileName, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", outputFileName);
        return 1;
    }

    // Write RBF to file 
    for (int i = 0; i < m; i++) {
        fprintf(file, "%d", rbf[i]);
    }

    // Close file
    fclose(file);
    return 0;
}

