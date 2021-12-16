// Copyright [2021] <Yuxuan Li>
// Import libraries needed to compile.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "SpellChecker.h"

#define MAX_WORD_SIZE 128
#define DEFAULT_DICT_SIZE (1 << 16)  // same as 2^16, an arbitrary starting size

size_t build_dictionary(char* filename, Dictionary* dict_result) {
  // allocate space for the dictionary
  size_t dict_size = DEFAULT_DICT_SIZE;
  // change the malloc size from 'dict_size' to 'dict_size*sizeof(char*)'
  // dict is char**, which is a array of string
  // malloc size should be numOfString*stringTypeSize
  Dictionary dict = (Dictionary) malloc(dict_size*sizeof(char*));

  // create a buffer to store the lines
  // change the malloc size
  // from 'MAX_WORD_SIZE' to 'MAX_WORD_SIZE*sizeof(char*)'
  char* buffer = (char*) malloc(MAX_WORD_SIZE*sizeof(char*));
  size_t buffer_len = MAX_WORD_SIZE;

  // open the file for reading
  FILE* input = fopen(filename, "r");
  if (!input) {
    return 0;
  }

  size_t word_count = 0;
  char* line = fgets(buffer, buffer_len, input);
  size_t word_len = strlen(buffer);
  // needs to check for \n at the end because fgets reads in \n as well
  if (buffer[word_len - 1] == '\n') {
    // Remove the newline from the word
    buffer[word_len - 1] = '\0';
    word_len--;
  }
  char* word;
  while (line) {  // line is not NULL
    // double the dictionary size if it's full
    if (word_count == dict_size) {
      dict_size *= 2;
      // realloc malloc size also need to multiply 'sizeof(char*)'
      dict = (Dictionary) realloc(dict, dict_size*sizeof(char*));
    }
    // save the word in a new allocated space and put it into the dictionary
    word = malloc(sizeof(char) * (word_len + 1));
    strncpy(word, buffer, word_len + 1);
    dict[word_count] = word;

    // go to the next line
    line = fgets(buffer, buffer_len, input);
    word_len = strlen(buffer);
    if (buffer[word_len - 1] == '\n') {
      word_len--;
      buffer[word_len] = '\0';
    }
    // no need to free(word), word pointer has been assigned to dict[i]
    word_count++;
  }

  // assign to output parameter
  *dict_result = dict;

  // clean up
  // and fclose and files opened
  fclose(input);
  free(buffer);
  return word_count;
}

void free_dictionary(Dictionary dict, size_t size) {
  // To free the dictionary, we need to free the block allocated to every word
  for (size_t i = 0; i < size; i++) {
    free(dict[i]);
  }
  free(dict);
}

int check_spelling(Dictionary dict, size_t size, char* word) {
  int lo = 0, hi = size - 1;
  int mid;
  int cmp_result;

  // typical binary search
  do {
    mid = (lo + hi) / 2;
    cmp_result = strcmp(word, dict[mid]);
    if (cmp_result == 0) {
      return 1;
    } else if (cmp_result > 0) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  } while (lo <= hi);

  // didn't find a match
  return 0;
}
