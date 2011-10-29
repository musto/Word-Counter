#include "parser.h"

void parse_words_and_sentence_lengths(FILE* input, void (*process_word)(const char* word), void (*process_sentence)(int length))
{
	int c;
	char letter[2] = { 'a', '\0' };
	while((c = fgetc(input)) != EOF) {
		letter[0] = c;

		/* TODO: write me! */

		process_word(letter);

		if(c == '.') {
			process_sentence(3);
		}
	}
}

