#include "riffle.h"
#include "riffle.c"

int main() {

    /* Test ints */
    printf("Testing array of ints: \n");
    int intList[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int intLen = 20;
    int intSize = sizeof(int);


    printf("Before: \n");
    int i;
    for (i = 0; i<intLen; i++){
        printf("%d ", intList[i]);
    }
    
    int checkInt = check_shuffle(intList, intLen, intSize, &cmp_int);

    printf("\nAfter: \n");
    for (i = 0; i<intLen; i++){
        printf("%d ", intList[i]);
    }

    if (checkInt == 1) {
        printf("\nSuccessful shuffle!");
    } else {
        printf("\nUnsuccessful shuffle");
    }
    
    /* Test strings */
    printf("\nTesting array of strings: \n");
    char *greek[] = {"alpha","beta","gamma","delta","epsilon","zeta","eta","theta","iota","kappa","lambda","mu"};
    int greekLen = 12;
    int greekSize = sizeof(char*);

    printf("Before: \n");
    for (i = 0; i<greekLen; i++){
        printf("%s ", greek[i]);
    }
    
    int checkGreek = check_shuffle(greek, greekLen, greekSize, &cmp_string);

    printf("\n After: \n");
    for (i = 0; i<greekLen; i++){
        printf("%s ", greek[i]);
    }
    if (checkGreek == 1) {
        printf("\nSuccessful shuffle!");
    } else {
        printf("\nUnsuccessful shuffle");
    }

}
