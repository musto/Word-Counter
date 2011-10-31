#include "parser.h"

#include <ctype.h>

static int is_end_of_sentence(char c)
{
	return c == '.' || c == '!' || c == '?';
}

/*
 * Returns 1, if the given character is a character in the finnish alphabet
 * in latin1 encoding, and 0 otherwise.
 */
static int is_finnish_character(char c)
{
	return c == (char)228 || c == (char)246 || c == (char)196 || c == (char)214;
}

static int is_letter(char c)
{
	return isalpha(c) || is_finnish_character(c);
}

static void check_sentence_end(char c, int* word_count, void (*process_sentence)(int length))
{
	if(is_end_of_sentence(c)) {
		if(*word_count > 0) {
			process_sentence(*word_count);
			*word_count = 0;
		}
	}
}

static void check_word_end(char c, char* word, int* word_length, int* word_count, void (*process_word)(const char* word))
{
	if(is_letter(c)) {
		word[*word_length] = c;
		++*word_length;
	} else {
		if(*word_length >= 2) {
			word[*word_length] = '\0';
			process_word(word);
			++*word_count;
		}
		*word_length = 0;
	}
}

void parse_words_and_sentence_lengths(FILE* input, void (*process_word)(const char* word), void (*process_sentence)(int length))
{
	int ic;
	char c;
	char word[100];
	int word_length = 0;
	int word_count = 0;
	while((ic = fgetc(input)) != EOF) {
		c = ic;
		c = tolower(c);

		check_word_end(c, word, &word_length, &word_count, process_word);
		check_sentence_end(c, &word_count, process_sentence);
	}

	check_word_end('.', word, &word_length, &word_count, process_word);
	check_sentence_end('.', &word_count, process_sentence);
}

