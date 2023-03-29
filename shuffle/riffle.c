#include "riffle.h"


/**
 * This function shuffles an array using the riffle method.
 * @param L pointer to head of array to be shuffled.
 * @param len length of array to be shuffled
 * @param size size (bytes) of array element
 * @param work void array to be used as workspace
*/
void riffle_once(void *L, int len, int size, void *work) {
    /* Void pointer to the midpoint of the array */
    void *mid = L + (len / 2) * size;

    /* Counters that keep track of how many elements have been added to the shuffled array from each half */
    int left = 0;
    int right = 0;

    /* Generate a psuedo-random seed */
    srand(time(NULL));

    while (left + right < len) {
        /* Choose side of the array to be added, remainder 0 = left, right = 1 */
        int side = rand() % 2;

        /* If a side is at mid point -> add from other side */
        if (left == len / 2) { 
            side = 1;
        } else if (right == len / 2) {
            side = 0;
        }

        /* Move the elements */
        if (side == 0) {
            memcpy(work + (left + right) * size, L + left * size, size);
            left++;
        } else {
            memcpy(work + (left + right) * size, mid + right * size, size);
            right++;
        }
    }

    memcpy(L, work, len * size);
}



/**
 * Shuffles an array using the riffle method.
 * Performs N shuffle iterations on the array.
 * @param L pointer to head of array to be shuffled
 * @param len length of array to be shuffled
 * @param size size (bytes) of array element
 * @param N number of times array will be shuffled
*/
void riffle(void *L, int len, int size, int N) {

    /* Allocate memory for temporary workspace */
    void *work = malloc(len * size); 


    /* For loop that calls riffle_once N times */
    int i;
    for (i = 0; i < N; i++){
        riffle_once(L, len, size, work);
    }

    free(work);
}

/**
 * Function that checks if array contains the same elements as before the riffle.
 * Checks are done both ways to ensure no elements were added or removed.
 * @param L pointer to head of array to be shuffled
 * @param len length of array to be shuffled
 * @param size size (bytes) of array element
 * @param cmp comparison function
 * @return 1 if valid shuffle, 0 if not
*/
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)){

    /* Copy of original elements */
    void *original = malloc(len * size);
    memcpy(original, L, len * size);

    /* Perform 5 riffles */
    riffle(L, len, size, 5);

    void *checkOriginal = original;
    void *checkAfter = L;
    int valid = 1;
    int i;
    int j;
    int present = 1;

    /* Check every element in Original is a member of After */
    for (i = 0; i < len; i ++){ /* every element in Original */
        present = 1;
        checkAfter = L;
        for (j = 0; j < len; j++){
            if (cmp(checkOriginal, checkAfter) == 0){ /* every element in After */
                present = 0;
                j = len;
            }
            checkAfter += size;
        }
        /* Not found */
        if (present == 1){
            free(original);
            return valid = 0;
        }
    }

    /* Check every element in After is a member of Original */
    for (i = 0; i < len; i ++){ /* every element in After */
        present = 1;
        checkOriginal = original;
        for (j = 0; j < len; j++){
            if (cmp(checkOriginal, checkAfter) == 0){ /* every element in Original */
                present = 0;
                j = len;
            }
            checkOriginal += size;
        }
        /* Not found */
        if (present == 1){
            free(original);
            return valid = 0;
        }
    }

    free(original);
    return valid;

}

/**
 * Compares integers.
 * @param first int
 * @param second int
 * @return 0 if equal, 1 if x > y, -1 if y > x.
*/
int cmp_int(void *x, void *y){
    int a = *(int *)x;
    int b = *(int *)y;

    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

/**
 * Compares strings.
 * @param first string
 * @param second string
 * @return 0 if equal, 1 if x > y, -1 if y > x.
*/
int cmp_string(void *x, void *y){
    return strcmp(x, y);
}


/**
 * Evaluates how well an array was shuffled.
 * 0.5 is the ideal shufufle quality.
 * @param numbers shuffled array
 * @param len length of shuffled array
 * @return quality measurement between 0 and 1
*/
float quality(int *numbers, int len){
    int qualityCounter = 0;
    int i;
    for (i = 0; i < len-1; i++){
        if (numbers[i+1] > numbers[i]){
            qualityCounter++;
        }
    }
    return (float)qualityCounter / (len - 1);
}


/**
 * Measures quality of multiple shuffles on array.
 * 0.5 is the ideal shufufle quality.
 * @param N length of array
 * @param shuffles number of times to shuffle
 * @param trials number of trials to perform
 * @return quality measurement between 0 and 1
*/
float average_quality(int N, int shuffles, int trials){

    float qualitySum;
    float averageQuality;

    /* Loop for every trial */
    int i;
    for (i = 0; i < trials; i++){

        /* Create array */
        int *array = malloc(N * sizeof(int));
        int j;
        for (j = 0; j < N;j++){
            array[j] = j;
        }

        riffle(array, N, sizeof(int), shuffles);
        float qualityNum = quality(array, N);
        qualitySum += qualityNum;
        free(array);
    }

    averageQuality = qualitySum / trials;
    return averageQuality;
}