#include "test.h"
#include "parser.h"

FILE* create_tmp_file(const char* contents)
{
    FILE* fptr = tmpfile();
    if(!fptr) {
        perror("tmpfile");
        assertNotNull(fptr);
    }
    fprintf(fptr, "%s", contents);
    rewind(fptr);

    return fptr;
}

int current_word = 0;
int word_count = 0;
const char* const* expected_words = NULL;

void word_tester(const char* word)
{
/*
    printf("Parsed word '%s'\n", word);
*/

    if(current_word >= word_count) {
        printf("Error, got word '%s', didn't expect more words\n", word);
    } else {
        assertStringEquals(expected_words[current_word], word);
    }
    ++current_word;
}

int current_sentence = 0;
int sentence_count = 0;
const int* expected_sentence_lengths = NULL;

void sentence_tester(int length)
{
/*
    printf("Parsed length '%d'\n", length);
*/

    if(current_sentence >= sentence_count) {
        printf("Error, got sentence length'%d', didn't expect more sentences\n", length);
    } else {
        assertIntEquals(expected_sentence_lengths[current_word], length);
    }
    ++current_sentence;
}

void test_hello()
{
    FILE* fptr = create_tmp_file("Hello, small world. hello internet.");

    current_sentence = 0;
    sentence_count = 2;
    int sentence_lengths[] = {3, 2};
    expected_sentence_lengths = sentence_lengths;

    current_word = 0;
    word_count = 5;
    const char* words[] = { "hello", "small", "world", "hello", "internet" };
    expected_words = words;

    parse_words_and_sentence_lengths(fptr, word_tester, sentence_tester);

    assertIntEquals(current_word, word_count);
    assertIntEquals(current_sentence, sentence_count);

    fclose(fptr);
}

void test_punctuation()
{
    FILE* fptr = create_tmp_file("a!b,c.d?aa bb cc, dd ee. ff gg hh... y. ii. jj.aa bb cc");

    int sentence_lengths[] = {5, 3, 1, 1, 3};
    sentence_count = 5;
    current_sentence = 0;
    expected_sentence_lengths = sentence_lengths;

    const char* words[] = { "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "aa" "bb", "cc" };
    word_count = 13;
    current_word = 0;
    expected_words = words;

    parse_words_and_sentence_lengths(fptr, word_tester, sentence_tester);

    assertIntEquals(current_word, word_count);
    assertIntEquals(current_sentence, sentence_count);

    fclose(fptr);
}

int main(void)
{
    test_hello();
    test_punctuation();

    return 0;
}

