// Copyright [2021] <Yinuo Chen>
#include "Trie.h"
#define MAX_WORD_SIZE 16
#define MAXLINE 50


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
    // ============================get dictionary=======================
    char* input_filename = argv[1];
    // open the input text file
    FILE* text = fopen(input_filename, "r");
    if (!text) {
    fprintf(stderr, "Failed to open %s for input.\n", input_filename);
    return EXIT_FAILURE;
    }

    // ============================insert trie=======================
    /*TrieNode* root;
    root = makeNode(NULL);
    // create buffer for each line with MAX_WORD_SIZE
    char* buffer = (char*) malloc(MAX_WORD_SIZE*sizeof(char));
    size_t buffer_len = 81;
    char* line = fgets(buffer, buffer_len, text);
    while (line) {
        insertTrie(root, line);
        line = fgets(buffer, buffer_len, text);
    }*/
    TrieNode* root;
    root = makeNode(NULL);
    // create buffer for each line with MAX_WORD_SIZE
    char* buffer = (char*) malloc(MAX_WORD_SIZE*sizeof(char));
    char* word;
    size_t buffer_len = 81;
    char* line = fgets(buffer, buffer_len, text);
    while (line) {
        int word_len = strlen(line);
        word = (char*) malloc((word_len + 1) * sizeof(char));
        snprintf(word, word_len, "%s", line);
        insertTrie(root, word);
        line = fgets(buffer, buffer_len, text);
    }


    // ============================read command line=======================
    char input[MAXLINE+1];
    char lastInput[MAXLINE+1];
    printf("Enter \"exit\" to quit.\n");

    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        scanf("%s", input);
        if (strncmp(input, "#", 1) == 0) {
            int len = sizeof(lastInput + strlen(lastInput));
            snprintf(lastInput + strlen(lastInput), len + 1, "#");
            printf("'%s'\n", lastInput);
            printf("'%s'\n", searchTrie(root, lastInput));
        } else {
            if (strncmp(input, "exit", 4) == 0) {
                break;
            } else {
                printf("'%s'\n", searchTrie(root, input));
            }
            snprintf(lastInput, strlen(input)+1, "%s", input);
        }
    }
    // ============================free memory=======================
    free(buffer);
    freeTrie(root);
    fclose(text);
    return EXIT_SUCCESS;
}
