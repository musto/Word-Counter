#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "parser.h"
#include "int_counts.h"
/*
 * Wordcount is the programs main file. It handles the inputs and the outputs, uses the 
 * data structures and the parser. It has the following functions: main, process_word, 
 * process_sentence, print_word_and_count and process. 
 *
 * First it reads either the file or text from stdin. When the input is read, it checks
 * whether output should be written in a file or in stdout. The main function then calls 
 * process function. Process creates AVL tree and int counts datastructures.
 * Process then calls parser, which reads words and sentences using wordcounts methods 
 * process_word and process_sentence. After the words are read, printing words is done using 
 * AVLs for-each function. Then the sentences are printed using int_counts_get function.
 * 
 * Both datastructures are deleted after the printing is done.
 */

static void process_word(const char* word);
static void process_sentence_length(int length);
static void process(FILE* input, FILE* output);

/*
 * Main function checks whether input is taken from stdin or from a file, and whether output is done 
 * using stdout or file. It then calls process function with the correct input/outputs.
 */

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

/*
 * Process_word reads a word passed as a parameter into the AVL tree. If the word
 * exists, it increases the value by one.
 */

static void process_word(const char* word)
{
#if 0
	printf("Read word '%s'\n", word);
#endif
	words = avl_tree_increase(words, word);
}

/*
 * Process_sentence adds a sentence of set length into the int counts data structure. If 
 * a sentence of the current length is already added, it increases its value by one. 
 * Parameter is the length of the sentence.
 */
static void process_sentence_length(int length)
{
#if 0
    printf("Sentence had %d words\n", length);
#endif
	int_counts_add(sentence_lengths, length);
}
/*
 * Print_word_and_count is used with avl_tree_for_each to print a word.
 * Parameters are the word and the amount of its appearances in the text.
 */
static void print_word_and_count(const char* word, int count)
{
	fprintf(output, "%s %d\n", word, count);
}

/* 
 * Process function has two parameters: the input and output. They can be done using 
 * stdin/stdout or files. First process creates AVL tree and int counts datastructures.
 * Process then calls parser, which reads words and sentences using wordcounts methods 
 * process_word and process_sentence. After the words are read, printing words is done using 
 * AVLs for-each function. Then the sentences are printed using int_counts_get function.
 * Finally the data structures are destroyed.
 */
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
		fprintf(output, "%2d word sentences: %d\n", i, count);
	}

	int_counts_destroy(sentence_lengths);
	avl_tree_destroy(words);
}

