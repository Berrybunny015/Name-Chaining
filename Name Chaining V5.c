#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define any global variables
#define maxLetters 21

int isPretty(char perm[][maxLetters], int numLines); //find the pretty phrase from the permutations
int handlePerm(char handles[][maxLetters], char perm[][maxLetters], int line, int numLines, int* used); //create permutations

int isPretty(char perm[][maxLetters], int numLines) {
    int numLetters; //to help find the last letter of a word in a permutation

    for (int i = 0; i < numLines - 1; i++) {
        numLetters = strlen(perm[i]);

        if(perm[i][numLetters - 1] != perm[i + 1][0]) { //if the permutation isn't a pretty phrase throughout, then it's not pretty yet
            return 0;
        }
    }

    return 1; //if the permutation is a pretty phrase throughout, then it's pretty
}


int handlePerm(char handles[][maxLetters], char perm[][maxLetters], int line, int numLines, int* used) {
    int numLetters, i;

    if (line == numLines) { //base case
        if(isPretty(perm, numLines) == 1) { //if the permutation is pretty, then it'll be printed
            for(i = 0; i < numLines; i++) {
                printf("%s ", perm[i]);
            }

            printf("\n");
            return 1;
        }

        return 0; //if the permutation is not pretty, the program will continue running
    }

    //look at every possible spot in the handles array and create the different permutations
    for (i = 0; i < numLines; i++) {

        if (used[i] == 0) {
            strcpy(perm[line], handles[i]); //store in the permutation
            used[i] = 1; //use the index to create new permutation

            numLetters = strlen(perm[i]);

            //if(perm[line][numLetters - 1] == perm[line + 1][0]) {
            //    line = line + 1;
            //}

            if (handlePerm(handles, perm, line + 1, numLines, used) == 1) {
                do {
                    return 1;
                } while (perm[i][numLetters - 1] == perm[i + 1][0]);
            }

            used[i] = 0; //unuse the index and permit future permutations
        }
    }

    return 0;
}


int main() {
    int numLines, line;

    scanf("%d", &numLines); //takes in number of handles

    char handles[numLines][maxLetters]; //hold the handles in their original orientation
    char perm[numLines][maxLetters]; //hold the handles' permutations
    int used[numLines]; //keep track of where to make the upcoming permutation(s)

    for (line = 0; line < numLines; line++) {
        scanf("%s", handles[line]); //take in the handles
        used[line] = 0; //initialize the used array
    }

    handlePerm(handles, perm, 0, numLines, used); //create the permutations and find the pretty phrase

    return 0;
}
