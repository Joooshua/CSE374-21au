// Copyright [2021] <Yuxuan Li>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"

// create a TrieNode whose "word" is the argument "word"
TrieNode* makeNode(char* word) {
    TrieNode *n = (TrieNode*) malloc(sizeof(TrieNode));
    n->word = word;
    for (int i = 0; i < NUM_CHILDREN; i++) {
        n->children[i] = NULL;
    }
    return n;
}

// convert letter into digit
int letterToDigit(char letter) {
    if (letter == 'a' || letter == 'b' || letter == 'c') {
    return 2;
  } else if (letter == 'd' || letter == 'e' || letter == 'f') {
    return 3;
  } else if (letter == 'g' || letter == 'h' || letter == 'i') {
    return 4;
  } else if (letter == 'j' || letter == 'k' || letter == 'l') {
    return 5;
  } else if (letter == 'm' || letter == 'n' || letter == 'o') {
    return 6;
  } else if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') {
    return 7;
  } else if (letter == 't' || letter == 'u' || letter == 'v') {
    return 8;
  } else if (letter == 'w' || letter == 'x' || letter == 'y' || letter == 'z') {
    return 9;
  } else if (letter == '#') {
    return 10;
  }
  return -1;
}

void insertTrie(TrieNode *root, char *word) {
  int digit;
  // use "cur" to traverse through the Trie
  TrieNode* cur = root;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] == '\0' || word[i] == '\n') break;
    digit = letterToDigit(word[i]);
    if (digit == -1) {
        return;
    } else {
        if (cur->children[digit-2] == NULL) {
            cur->children[digit-2] = makeNode(NULL);
        }
        cur = cur->children[digit-2];
    }
  }

  if (cur->word == NULL) {
    cur->word = word;
  } else {
    while (cur->children[8] != NULL) {
      cur = cur->children[8];
    }
    cur->children[8] = makeNode(word);
  }
}

char* searchTrie(TrieNode *root, char* input) {
  if (root == NULL || input[0] == '#') return "Not a valid input";
  TrieNode* cur = root;
  int key;          // input key

  while (*input != '\0' && *input != '\n') {
    if (*input == '#') {
      if (cur->children[8] == NULL) {
        return "There are no more word";
      }
      cur = cur->children[8];
    } else {
      key = *input - '0' - 2;

      if (key < 0 || key > 7) {
        return "Input out of range";
      }

      if (cur->children[key] == NULL) {
        return "Word not found in Dictionary";
      }
      cur = cur->children[key];
    }
    input++;
  }
  if (cur->word == NULL) {
    return "Word not found in Dictionary";
  }
  return cur->word;
}

void freeTrie(TrieNode* root) {
  for (int i = 0; i < NUM_CHILDREN; i++) {
    if (root->children[i] != NULL) {
      freeTrie(root->children[i]);
    }
  }
  free(root->word);
  free(root);
}


int wordToDigit(char* word) {
  int res = 0;
  while (*word) {
    res = res * 10 + letterToDigit(*word);
    word++;
  }
  return res;
}
