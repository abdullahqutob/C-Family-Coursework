#include "beggar.h"
#include "beggar.c"

int main(int argc, char* argv[])
{
	if (argc == 2) {

		/* Create deck */
		int deck[] = {2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14};

		/* Riffle shuffle deck */
		riffle(deck, 52, sizeof(int), 8)	

		/* Play Game */
		if (atoi(argv[1])) {
			int players = atoi(argv[1]);
			beggar(players, deck, 1);
			return 0;
		}

		printf("Error: Invalid arguments!\n");
		return 1;
	}
}