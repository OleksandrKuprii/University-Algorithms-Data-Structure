//
// Created by Dawid Zalewski on 06/12/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "LetterCounter.h"
#include "LangugageRecognizer.h"

void demo(){
    unsigned long counts[26] = {0};
    const char* text = "Alice in Wonderland.";
    (void)countLetters(&counts[0], text);
    printCounts(&counts[0], false, false);
}

unsigned long* processFile(const char* fileName) {

    unsigned long * counts = calloc(sizeof(unsigned long[ALPHABET_SIZE]), sizeof(unsigned long));

    FILE* fp = fopen(fileName, "r");
    unsigned long sum = 0;
    if (fp) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            sum += countLetters(&counts[0], buffer);
        }
        printf("In total counted %ld letters.\n", sum);
    }
    return counts;
}

int main(){
//    unsigned long counts1[26] = {15,3,4,5,16,6,7,8,9,7,6,3,2,11,14,1,2,12,13};
//    unsigned long counts2[26] = {16,4,7,5,20,7,4,3,14,5,9,1,2,18,6,12,9,13,9,15};
//    assert(strcmp("eaosrn", makeSignature(counts1)) == 0);
//    assert(strcmp("enatir", makeSignature(counts2)) == 0);

    unsigned long * counts = processFile("alice3.txt");
    const char * signature = makeSignature(counts);
    const char * language = matchLanguage(signature);

    printf("%s\n%s", signature, language);
}
