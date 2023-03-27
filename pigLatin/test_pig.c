#include "pig.h"
#include "pig.c"


/**
 * Test function that checks if the pig function works as expected.
 * The words tested are: "happy", "duck", "glove", "evil", "eight", "yowler" and "crystal".
*/
int main() {
    /* Test cases */
    char *testWords[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    char *expected[] = {"appyhay", "uckday", "oveglay", "evilway", "eightway", "owleryay", "ystalcray"};

    /* Loop through each test case */
    int i;
    for (int i = 0; i < 7; i++) {
        char *result = pig(testWords[i]);

        /* Check if result is equal to expected */
        assert(strcmp(result, expected[i]) == 0);

        /* Print test result */
        printf("%s -> %s\n", testWords[i], result);

        /* Free memory allocated for result */
        free(result);
    }

    printf("All tests passed successfully.\n");
    return 0;
}