//
// Created by Dawid Zalewski on 06/12/2020.
//

#include "LangugageRecognizer.h"
#include "string.h"

typedef struct{
    const char* langCode;
    const char* signature;
} LangSignature;

static LangSignature signatures[] = {
    {"en", "etaoin"},
    {"fr", "esaitn"},
    {"de", "ensria"},
    {"es", "eaosrn"},
    {"pt", "aeosri"},
    {"it", "eaioln"},
    {"se", "eanrts"},
    {"pl", "aioezn"},
    {"nl", "enatir"},
    {"dk", "erntai"},
    {"fi", "aintes"}
};

static const int _size = sizeof(signatures) / sizeof(signatures[0]);

extern const char* matchLanguage(const char* signature){

    int best_score = 100;
    const char* best_match = NULL;
    const int length = (int)strlen(signature);

    for (int i = 0; i < _size; ++i){
        int score = 0;
        for (int j = 0; j < length; ++j){
            // add 1 to the score for any mismatch in the signature
            score += (signatures[i].signature[j] == signature[j])? 0 : 1;
        }
        if (score < best_score){
            best_score = score;
            best_match = signatures[i].langCode;
        }
    }
    return best_match;
}
