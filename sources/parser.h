#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

/*
 * Parse function does the following:
 *
 * For each word it calls the given function pointer (process_word). Parameter for this function call is the word.
 * 
 * For each sentence it calls the given function pointer (process_sentence). Parameter for this function call is the sentences length.
 */

void parse_words_and_sentence_lengths(FILE* input, void (*process_word)(const char* word), void (*process_sentence)(int length));

#endif

