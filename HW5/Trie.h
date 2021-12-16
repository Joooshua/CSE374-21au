// Copyright [2021] <Yuxuan Li>
#ifndef TRIE_H
#define TRIE_H

#define NUM_CHILDREN 10

typedef struct TrieNode {
    char* word;
    struct TrieNode *children[NUM_CHILDREN];
} TrieNode;

typedef struct Trie {
    TrieNode *root;
} Trie;

TrieNode* makeNode(char* word);
void insertTrie(TrieNode* root, char* word);
char* searchTrie(TrieNode* root, char* word);
void freeTrie(TrieNode* root);
int letterToDigit(char letter);
int wordToDigit(char* word);
#endif  // TRIE_H
