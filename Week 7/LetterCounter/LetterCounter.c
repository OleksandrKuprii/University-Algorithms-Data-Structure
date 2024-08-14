//
// Created by Dawid Zalewski on 06/12/2020.
//

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "LetterCounter.h"

unsigned long countLetters(unsigned long counts[static 26], const char* str){
    unsigned long count = 0;

    for (unsigned long i = 0; i < strlen(str); i++) {
        if (isalpha(str[i])) {
            counts[tolower(str[i]) - 'a']++;
            count++;
        }
    }

    return count;
}

const char* makeSignature(unsigned long counts[static 26]){
    static char signature[7];

    // Loop 6 times to find 6 characters
    for (int i = 0; i < 6; i++) {
        unsigned long max = 0; // save the maximum count
        int index_max; // save the position of the maximum count in the array

        // For every character count in counts
        for (int j = 0; j < 26; j++) {
            if (counts[j] > max) {  // If the count is bigger than the current maximum
                bool flag = true;

                // Check if this character is not already in signature
                for (int k = 0; k < i; k++) {
                    if (signature[k] == (char)('a' + j)) {
                        // The character is already in the signature
                        flag = false;
                    }
                }

                // Update the variables if the character was not found in the signature
                if (flag) {
                    max = counts[j];
                    index_max = j;
                }
            }
        }

        // Add the character to the signature
        signature[i] = (char) ('a' + index_max);
    }

    signature[6] = '\0';
    return &signature[0];
}


static inline unsigned long sumAllCounts(unsigned long counter[static 26]) {
    unsigned long sum = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        sum += counter[i];
    }
    return sum;
}

int cmpLetterCounts(const void* a, const void* b){
    // compare ignoring the first 8 bits
    unsigned long aa = (*(const unsigned long*)b << 8);
    unsigned long bb = (*(const unsigned long*)a << 8);
    return (aa > bb) ? 1 : ((aa < bb)? -1 : 0);
}

// internal function for sorting the counts - used in printCounts
static size_t sortedCounts(unsigned long counts[static 26], unsigned long sorted_counts[static 26]){

    const size_t shift = 8 * (sizeof(unsigned long) - 1);
    for (int i = 0; i < ALPHABET_SIZE; ++i){
        sorted_counts[i] = counts[i] | ((unsigned long)('a' + i) << shift);
    }

    qsort(sorted_counts, ALPHABET_SIZE, sizeof(unsigned long), cmpLetterCounts);
    return shift;
}

void printCounts(unsigned long counts[static 26], bool sorted, bool asFrequencies){

    const double sum = 100.0 /  (double)sumAllCounts(counts);

    if (sorted) {
        unsigned long* sorted_counts = malloc(sizeof (unsigned long) * ALPHABET_SIZE);
        const size_t shift = sortedCounts(counts, sorted_counts);

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            char letter = (char)(sorted_counts[i] >> shift);
            unsigned int count = (unsigned int)((sorted_counts[i] << 8) >> 8);
            if (asFrequencies){
                printf("%c: %u\n", letter, count);
            }
            else {
                printf("%c: %0.2f%%\n", letter, (double)count * sum);
            }
        }
        free(sorted_counts);

    }
    else{
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (asFrequencies){
                printf("%c: %ld\n", 'a' + i, counts[i]);
            }
            else {
                printf("%c: %0.2f%%\n", 'a' + i, (double)counts[i] * sum);
            }
        }
    }
}




