#include "pig.h"


/**
 * Checks if the character is a vowel or y | [a,e,i,o,u,y].
 * Returns True if its a vowel, false if its a consonant.
 * @param x The character being checked
 * @return 1 if it is a vowel, 0 if not
*/
int is_vowel(char x){
    x = tolower(x);
    if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' || x == 'y'){
        return 1;
    } else {
        return 0;
    }
}


/**
 * Translates a word into pig latin.
 * If the first letter is a vowel or 'y', add 'way' to the end of it.
 * If the first letter is a consonant, add 'ay' to the end of it.
 * @param word A pointer to the first letter of the word to translate
 * @return A pointer to the first letter of the pig latin word
*/
char * pig(char * word){
    char * pigWord;
    char firstLetter = tolower(word[0]);


    /* If first letter is a vowel and not 'y' */
    if (is_vowel(word[0]) == 1 && firstLetter != 'y'){
        
        /* Allocate memory to fit word + 'way' */
        pigWord = malloc(sizeof(word) + sizeof(char) * 3);

        /* Add "way" to the end of the pig word */
        strcpy(pigWord, word);
        strcat(pigWord, "way");


    } else { /* If first letter is a consonant */
        
        /* Allocate memory to fit word + 'ay' */
        pigWord = malloc(sizeof(word) + sizeof(char) * 2);

        int i = 0;
        int pigWordIndex = 0;


        /* If first letter is 'y' -> treat it as consonant  */
        if (firstLetter == 'y'){
            i++;
        } 

        /* skip first cluster of consonants, or if there are no vowels, skip the whole word.*/
        while (is_vowel(word[i]) == 0 && word[i] != '\0'){
            i++;
        }

        /* Construct the pig latin word */
        strcpy(pigWord, word + i);
        strncat(pigWord, word, i);
        strcat(pigWord, "ay");
    }

    return pigWord;
}


