#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


void riffle_once(void*, int, int, void*);
void riffle(void*, int, int, int);
int check_shuffle(void*, int, int, int (*)(void *, void *));
int cmp_string(void*, void*);
int cmp_int(void*, void*);
float quality(int *, int);
float average_quality(int, int, int);