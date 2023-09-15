#include <readaline.h>
#include <except.h>
#include <stdio.h>
#include <stdlib.h>

size_t readline(FILE *inputfd, char **datapp);

int main (int argc, char*argv[]){
    if (argc != 2){
        printf("must specify a file");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *line  = NULL;

    size_t line_len = readaline(file, &line);
    while ((line_len = readaline(file, &line)) != 0){
      printf("%s", line);
      free(line);   
    }

    
    
    fclose(file);

    return 0;
}


size_t readaline(FILE *inputfd, char **datapp){
    char *line = NULL; 
    size_t len = 0;
    size_t cap = 1;
    char ch;

    while ((ch = fgetc(inputfd)) != EOF && ch != '\n'){
        if (len + 2 >= cap){
            cap *= 3;
            line = (char *)realloc(line, cap);
            if (line == NULL){
                perror("reallocating memory error");
                exit(EXIT_FAILURE);
            }
        }

        line[len++] = ch;

    }

    
    
    if (len == 0){
        *datapp = NULL;
        return 0;
    }

    line[len] = '\n';
    *datapp = line;

    return len;

}