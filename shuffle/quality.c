#include "riffle.h"
#include "riffle.c"

/**
 * Tests quality and average_quality on an array of length 50.
 * Performs 30 trials of 1 -> 15 shuffles.
*/
int main(){
    int i;
    for(i=1; i < 16; i++){
        float averageQuality = average_quality(50, i, 30);
        printf("\nShuffles: %d | Average Quality: %.5f", i, averageQuality);
    }
}