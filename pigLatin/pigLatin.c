#include "pig.h"
#include "pig.c"


/**
 * Repeatedly asks the user for an English input, outputs pig latin.
 * Stops running when an empty line is received.
*/
int main() {
    char input[500];
    char* words[520];
    int numWords = 0;

    printf("Pig Latin Translator \n\n"); 
    printf("Enter English to translate: "); 
    while (fgets(input, sizeof(input), stdin)){

        /* If the user enters an empty line -> break */
        if (strcmp(input, "\n") == 0){
            break;
        } 

        /* Remove the newline charecter at the end */
        input[strcspn(input, "\n")] = '\0';

        printf("\n%s => ", input);
        
        /* Add translated words to array */
        char *word;
        char *rest = input;
        while ((word = strtok_r(rest, " ", &rest))) {
            char * pigTranslation = pig(word);
            words[numWords] = pigTranslation;
            numWords++;
        }

        /* Print translation */
        int i;
        for (i = 0; i < numWords; i++){
            printf("%s ", words[i]);
            free(words[i]); /* Free the memory allocated for each word */
        }
        numWords = 0;
        printf("\nEnter English to translate (empty line to exit): ");
    }
    return 0;
}

