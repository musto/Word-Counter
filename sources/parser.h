#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

void parse_words_and_sentence_lengths(FILE* input, void (*process_word)(const char* word), void (*process_sentence)(int length));

#endif

