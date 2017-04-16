#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0


/** Retrieves all the words stored in wordlist
 * @param wordlist Array where all words will be stored */
void getWords(char* wordlist[]) {
    FILE* fp; // Opened file (wordlist.txt)
    char* line = NULL; // Each line read will be stored here
    size_t len = 0; // Bytes to be read. If len is 0 and line NULL getline will allocate the memory needed to read the lines

    // Opens the file
    fp = fopen("wordlist.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Reads all the lines and store them in variable result
    int i = 0;
    while ((getline(&line, &len, fp)) != -1) {
        // Allocates memory for the string in the array and copies it
        wordlist[i] = malloc(8); // 8 = sizeof(char*)
        strcpy(wordlist[i++], line);
    }

    printf("Total words added to array: %d\n", i + 1);

    // Closes the opened file and frees memory used for reading lines
    fclose(fp);
    if (line)
        free(line);
}


/** Finds the corresponding word in the list for the scrambled word given as argument
 * @param word Scrambled word to search
 * @param wordlist Array of Strings containing every word in the corresponding file
 * @param listLength Length of wordlist */
void findWord(char* word, char* wordlist [], unsigned int listLength){
    size_t wordLength = strlen(word);

    // Iterates over every word in the list
    for (int i = 0; i < listLength - 1; i++) {
        char* currentWord = wordlist[i];
        size_t cWordLength = strlen(currentWord); // Bad

        // Checks if the length of the searched word is equals to the current one
        if (wordLength + 1 == cWordLength){ // +1 cuz of \n
            // Iterates over every character of the scrambled word
            for (int j = 0; j < wordLength; j++){
                bool gotChar = false;

                // Iterates over every character of the current word
                for (int k = 0; k < cWordLength; k++){

                    // Checkes wether the current word has every
                    if (word[j] == currentWord[k]){
                        gotChar = true;
                        break;
                    }
                }

                if (gotChar == false)
                    break;

                // If we got to the end of the word without exiting the loop thats the word we are looking for.
                // Prints it with a ',' at the end
                if (j == wordLength - 1) {
                    printf("%s,", currentWord);
                    break;
                }
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    unsigned int listLength = 1276; // Length of the array
    char* wordlist [listLength]; // Will store every word from the list
    char* token;
    const char delimiter [2] = ",";

    // Scrambled words have to be passed as an argument and comma separated
    // words.js can get them from the page
    if (argc == 2) {
        getWords(wordlist);

        token = strtok(argv[1], delimiter);

        while (token != NULL) {
            findWord(token, wordlist, listLength);
            token = strtok(NULL, ",");
        }
    }

    else
        puts("Usage: <program_name> <comma_separated_scrambled_words>\n");

    return 0;
}
