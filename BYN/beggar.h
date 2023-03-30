#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../shuffle/riffle.c"

typedef struct player_struct {
	int id;
	int handSize;
	int* hand;
} Player;

typedef struct pile_struct {
	int pileSize;
	int* pile;
} Pile;

int finished(Player*, int);
int card_penalty(int);
int remove_top(Player*);
int next_player(int, int);
int previous_player(int, int);
int* split_cards(int);
void add_to_pile(Pile*, int);
struct pile_struct* take_turn(Player*, Pile*);
int beggar(int, int*, int);