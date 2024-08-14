//
// Created by Dawid Zalewski on 06/12/2020.
//

#ifndef WORDS_COUNTING_LETTERCOUNTER_H
#define WORDS_COUNTING_LETTERCOUNTER_H

#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE ('Z' - 'A' + 1)

/// Counts letters in a string, and updates character counts accordingly
/// \param counts The array of character counts, with a minimum size of 26
/// \param str The string in which characters must be counted
/// \return The number of characters in the string
extern unsigned long countLetters(unsigned long counts[static 26], const char* str);

/// Returns a string of length six, which contains the six characters that have the highest frequency,
/// ordered by their frequencies, from high to low
/// \param counts the array of length (at least) 26 that contains character counts
/// \return the signature based on the counts. This signature must not be freed
extern const char* makeSignature(unsigned long counts[static 26]);

// prints the counts of letters in a nice way
extern void printCounts(unsigned long counts[static 26], bool sorted, bool asFrequencies);

#endif //WORDS_COUNTING_LETTERCOUNTER_H
