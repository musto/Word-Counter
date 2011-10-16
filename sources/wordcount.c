#include <stdio.h>
#include <stdlib.h>

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

    int c = fgetc(input);
    while(c != EOF){
        fprintf(output, "%c", c);
        c = fgetc(input);
    }





    if (argc > 1) {
        fclose(input);
    }
    if (argc > 2) {
        fclose(output);
    }
    return (EXIT_SUCCESS);
}

