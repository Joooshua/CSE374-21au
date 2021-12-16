// Copyright [2021] <Ruoqi Zhang, Yinuo Chen, Yuxuan Li (Alphabetical Order)>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 502
#define MAX_PATTERN 101

bool ignore_flag = false;
bool number_flag = false;
// Copies a string (up to max length)
// Optionally converts the copied string to lowercase
// Params:
//  - copy_to:    The string/buffer to copy to
//  - copy_from:  The null-terminated string to copy from
//  - max_length: The max characters to copy over (including null terminator)
//  - lowercase:  Whether to convert to lowercase after copying
void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase);

// Prints all lines in a file that match the pattern
// Params:
//  - file:              the file to check for results
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_matches_in_file(FILE *file, char *pattern,
                           bool ignore_case, bool print_line_number);

// Loops through a list of files and prints matches to the pattern for each
// Params:
//  - num_files:         number of files in the list
//  - filename_list:     list of filenames to check
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number);
// Print the usage of the program
// Params:
//  - program_name: the name of the program being run (argv[0])
void usage(char *program_name);

// Main entry point of the function
// Parses the input into flags, pattern, and files
// Params:
//  - argc: The number of arguments provided
//  - argv: The list of arguments provided
// Returns the exit status
int main(int argc, char **argv);


void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase) {
}

void print_matches_in_file(FILE *file, char *pattern, bool ignore_case,
                           bool print_line_number) {
    // copy pattern into the Pattern, copy string in txt into the tmp
    char res[MAX_LENGTH];
    char tmp[MAX_LENGTH];
    char Pattern[MAX_PATTERN];
    // if '-i' appears, loew the case of pattern
    if (ignore_case) {
        for (int i = 0; i < MAX_PATTERN; i++)
            Pattern[i] = tolower(pattern[i]);
    } else {
        strncpy(Pattern, pattern, MAX_PATTERN);
    }
    int i = 1;
    // load file into 'res'
    while ( fgets(res, sizeof(res), file) ) {
        // if '-i' appears, lower the case of txt
        if (ignore_case) {
            for (int i = 0; i < MAX_LENGTH; i++)
                tmp[i] = tolower(res[i]);
        } else {
            strncpy(tmp, res, MAX_LENGTH);
        }
        if (strstr(tmp, Pattern) != NULL) {
            // if '-n' appears, also print out the line number
            if (print_line_number == 1) {
                printf("(%d) %s", i, res);
            } else {
            printf("%s", res);
            }
        }
        i++;
    }
}


void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number) {
    // traversing through the file set
    for (int i = 0; i < num_files; i++) {
        FILE *file;
        if ((file = fopen(filename_list[i], "r")) == NULL) {
            fprintf(stderr, "Could not open file: %s\n", filename_list[i]);
        } else {
            printf("%s:\n", filename_list[i]);
            char res[MAX_LENGTH];
            char tmp[MAX_LENGTH];
            char Pattern[MAX_PATTERN];
            // if '-i' appears, lower the case of patterns
            if (ignore_case) {
                for (int i = 0; i < MAX_PATTERN; i++)
                    Pattern[i] = tolower(pattern[i]);
            } else {
            strncpy(Pattern, pattern, MAX_PATTERN);
            }
            int i = 1;
            // load file into 'res'
            while ( fgets(res, sizeof(res), file) ) {
                // if '-i' appears, lower the case the txt
                if (ignore_case) {
                    for (int i = 0; i < MAX_LENGTH; i++)
                        tmp[i] = tolower(res[i]);
                } else {
                    strncpy(tmp, res, MAX_LENGTH);
                }

                if (strstr(tmp, Pattern) != NULL) {
                    // if '-n' appears, also print out the line number
                    if (print_line_number == 1) {
                        printf("(%d) %s", i, res);
                    } else {
                        printf("%s", res);
                    }
                }
                i++;
            }
        }
    }
}


void usage(char *program_name) {
    printf("Usage: %s [OPTIONS] pattern file...\n", program_name);
}

int main(int argc, char **argv) {
    // main function
    char* pattern = NULL;
    char** filename_list[MAX_LENGTH];
    int j = 0;
    int numberOfFlag = 0;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-i", 2) == 0) {
            ignore_flag = true;
            numberOfFlag++;
        } else if (strncmp(argv[i], "-n", 2) == 0) {
            number_flag = true;
            numberOfFlag++;
        } else if (pattern == NULL) {
            pattern = argv[i];
        } else {
            filename_list[j++]=argv[i];
        }
    }
    // if the number of input file is more than one, use 'print_all_matches'
    // if the number of input file is equal to one, use 'print_matches_in_file'
    if (argc <= numberOfFlag+2) {
        usage("myfgrep.c");
        return(EXIT_FAILURE);
    } else if (j > 1) {
        print_all_matches(j, filename_list, pattern, ignore_flag, number_flag);
    } else {
        FILE *file;
        if ((file = fopen(filename_list[0], "r")) == NULL) {
            fprintf(stderr, "Could not open file: %s\n", filename_list[0]);
        } else {
            printf("%s:\n", filename_list[0]);
            print_matches_in_file(file, pattern, ignore_flag, number_flag);
        }
    }
}
