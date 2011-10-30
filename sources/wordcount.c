#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "parser.h"
#include "int_counts.h"

static void process_word(const char* word);
static void process_sentence_length(int length);
static void process(FILE* input, FILE* output);

int main(int argc, char* argv[]) {
    FILE* input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    } else {
        input = stdin;
    }

    FILE* output;
    if (argc > 2) {
        output = fopen(argv[2], "w");
        if (output == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    } else {
        output = stdout;
    }

    process(input, output);

    if (argc > 1) {
        fclose(input);
    }
    if (argc > 2) {
        fclose(output);
    }
    return (EXIT_SUCCESS);
}

static struct avl_tree_node* words;
static struct int_counts* sentence_lengths;
static FILE* output;

static void process_word(const char* word)
{
#if 0
	printf("Read word '%s'\n", word);
#endif
	avl_tree_increase(words, word);
}

static void process_sentence_length(int length)
{
#if 0
    printf("Sentence had %d words\n", length);
#endif
	int_counts_add(sentence_lengths, length);
}

static void print_word_and_count(const char* word, int count)
{
	fprintf(output, "%s %d\n", word, count);
}

static void process(FILE* input, FILE* out)
{
	output = out;
	words = avl_tree_create();
	sentence_lengths = int_counts_create();

	parse_words_and_sentence_lengths(input, process_word, process_sentence_length);

	avl_tree_for_each(words, print_word_and_count);

	fprintf(output, "\n");
	fprintf(output, "sentences: %d\n", int_counts_total(sentence_lengths));
	int min = int_counts_min(sentence_lengths);
	int max = int_counts_max(sentence_lengths);
	for(int i = min; i <= max; ++i) {
		int count = int_counts_get(sentence_lengths, i);
		fprintf(output, "%d word sentences: %d\n", i, count);
	}

	int_counts_destroy(sentence_lengths);
	avl_tree_destroy(words);
}

