#include "HashUtils.h"
#include <string.h>
#include <openssl/sha.h>

/**
 * Hash an IP using a key and SHA256
 */
int hashWithKey(int key, const char *ip, int m) {
    // Combine key and IP into a single string
    char combined[64];
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
 * Get which row of the RBF to use based on the hash mod 2 value
 */
int getRbfRow(int col) {
    char colAsString[32];
    snprintf(colAsString, sizeof(colAsString), "%d", col);
    return hashWithKey(0, colAsString, 2);
}

