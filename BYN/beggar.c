#include "beggar.h"
#include "../shuffle/riffle.c"


/**
 * Checks if current game state is a finished game
 * @param players Players of the game
 * @param Nplayers Number of players
 * @return 1 if one player has all the cards, else return 0
*/
int finished(Player* players, int Nplayers) {
	int finishedStatus = 0;
    int i;
    for (i = 0; i < Nplayers; i++) {
		if (players[i].handSize == 52) { /* Whole deck */
			finishedStatus = 1;
		} else {
			return 0;
		}
	}
	
	if (finishedStatus == 1) {
		return 1;	
	}

	return 0;
}

/**
 * Checks if a card is a penalty card
 * @param cardNum value of the card
 * @return number of penalty turns
*/
int card_penalty(int cardNum) {
	if (cardNum > 10) {
		return 1;	
	} else {
		return 0;
	}
}

/**
 * Remove top element of the pile and return its value.
 * @param player Player to remove card from
 * @return Value of removed top element
*/
int remove_top(Player* player) {
	int topValue = player->hand[0]; /* Get value of the top element */
    int i;
    for (i = 0; i < player->handSize; i++) {
		if (i == player->handSize-1) {
			player->hand[i] = 0;	
		} else {
			player->hand[i] = player->hand[i+1]; /* Shift pile elements one position to the left */
		}
	}
	player->handSize --; /* Update handSize to reflect the removal of the top element */
	return topValue;
}

/**
 * Function that gets the index of the next player.
 * @param current current player
 * @param Nplayers number of players in the game
 * @return Index of next player
*/
int next_player(int currentPlayer, int Nplayers) {
	if (currentPlayer < Nplayers-1) {
		return currentPlayer ++;	
	} else {
		return 0;
    }
}

/**
 * Function that gets the index of the previous player.
 * @param current current player
 * @param Nplayers number of players in the game
 * @return Index of previous player
*/
int previous_player(int currentPlayer, int Nplayers) {
	if (currentPlayer == 0) {
		return Nplayers--;
	} else {
		return currentPlayer--;
	}
}

/**
 * Determines the number of cards to give each player.
 * @param Nplayers number of players
 * @return Array with number of cards to give to each player
*/
int* split_cards(int Nplayers) {
	int deckRemainder = 52 % Nplayers;
	int cardsPerPlayer = (52 - deckRemainder) / Nplayers;
	int* cardDistribution = malloc(sizeof(int) * Nplayers);
    int i;
    for (i = 0; i < Nplayers; i++) {
		cardDistribution[i] = cardsPerPlayer;
	}
	cardDistribution[Nplayers-1] += deckRemainder;
	return cardDistribution;
}

/**
 * Adds card to top of pile.
 * @param deck game pile
 * @param card Value of card being added
*/
void add_to_pile(Pile* deck, int card){
    deck->pile[deck->pileSize] = card;
    deck->pileSize ++;
}

/**
 * Performs actions of a single turn.
 * @param player Player taking the turn
 * @param deck Pile of cards
 * @return if unsuccessful -> add reward pile to previous player hand, else return NULL
*/
struct pile_struct* take_turn(Player* player, Pile* deck) {
	int topCard = 0;
    /* Retrieve value of top card */
	if (deck->pileSize > 0) {
		topCard = deck->pile[deck->pileSize-1];
	}

    /* If its a penalty card */
	if (card_penalty(topCard)) {
        int i;
		for (i = 0; i < (topCard - 10); i++) { /* Penalty cost */
			if (player->handSize > 0) {
				int nextCard = remove_top(player);
				if (nextCard == 0) {
					return deck;
				}
                add_to_pile(deck, nextCard);
				if (nextCard > 10) {
					return NULL;
				}
			} else { /* Empty hand */
			 return deck;
			}
		}
		return deck;
	} else { /* Non-penalty move */
		int playerTopCard = remove_top(player);
        add_to_pile(deck, playerTopCard);
        return NULL;
	}
}

/**
 * Plays a game of Beggar-your-neighbor.
 * @param Nplayers Number of players
 * @param deck Shuffled array of cards. Must contain 52 cards.
 * @param talkative If not 0, will print game information
 * @return Number of turns
*/
int beggar(int Nplayers, int* deck, int talkative) {

	/* Create deck */
	Pile* gamePile = malloc(sizeof(Pile));
	gamePile->pile = malloc(52 * sizeof(int));
    if (gamePile == NULL) {
        printf("Error: memory allocation failed for players\n");
        exit(EXIT_FAILURE);
    }

	/* Move deck cards to pile */
    int i;
	for (i = 0; i < 52; i++) {
	 gamePile->pile[i] = deck[i];
	}
	gamePile->pileSize = 52;

    /* Create players */
	int currentPlayer = 0;
	Player* players = malloc(sizeof(Player) * Nplayers);
    if (players == NULL) {
        printf("Error: memory allocation failed for players\n");
        exit(EXIT_FAILURE);
    }

    /* Create player hands and ids */
    int i;
	for (i = 0; i < Nplayers; i++) {
		players[i].hand = malloc(52 * sizeof(int));
		players[i].id = i;
	}

    /* Distribute cards from pile to players */
	int* cardSplit = split_cards(Nplayers);	
	int* tempDeck = gamePile->pile;
    int i;
	for (i = 0; i < Nplayers; i++) {
		players[i].handSize = cardSplit[i];
        int j;
        for (j = 0; j < cardSplit[i]; j++) {
			players[i].hand[j] = *tempDeck++;	
		}	
	}
	gamePile->pileSize = 0;

	free(cardSplit);


	int turns = 0;
	struct pile_struct *reward; 

    while(finished(players, Nplayers) != 1){

		if (players[currentPlayer].handSize > 0) {

			if (talkative != 0) {
				printf("Turn: %d", turns);
				
                /* Print Pile */
				printf("\nPile: ");
                int i;
                for (i = 0; i < gamePile->pileSize; i++) {
					printf("%d, ", gamePile->pile[i]);	
				}
				printf("\n");

                /* Print hands */
                int k;
                for (k = 0; k < Nplayers; k++) {
                    /* Highlight current player */
					if (k == currentPlayer) {
						printf("*   %d: ", k);
					} else {
						printf("    %d: ", k);
					}
                    /* Print hand cards */
                    int n;
                    for (n = 0; n < players[k].handSize; n++) {
						printf("%d ", players[k].hand[n]);	
					}
					printf("\n");
				}
			}

			reward = take_turn(&players[currentPlayer], gamePile);

			int loserCounter = 0;
            int i;
            for (i = 0; i < Nplayers; i++) {
				if (players[i].handSize == 0) {
					loserCounter ++;
				}
			}
            

            if (reward != NULL) {
                /* Retrieve previous player that hasnt lost */
                int previousID = previous_player(currentPlayer, Nplayers);
                while (players[previousID].handSize == 0) {
                    previousID = previous_player(previousID, Nplayers);
                }
                /* Give previous player the reward to end of hand */
                int i;
                for (i = 0; i < reward->pileSize; i++) {
                    players[previousID].hand[players[previousID].handSize] = reward->pile[i];
                    players[previousID].handSize ++;
                }	
                memset(reward->pile, 0, sizeof(int) * 52);
                reward->pileSize = 0;
            }

			/* Go to next player */
			currentPlayer = next_player(currentPlayer, Nplayers);
			turns++;
		}
		else {
			currentPlayer = next_player(currentPlayer, Nplayers);
		}

	}

	if (talkative !=0) {
		/* Printing the pile and hands after game end */

	    /* Print final pile */
		printf("Final pile: ");
        int i;
        for (i = 0; i < gamePile->pileSize; i++) {
			printf("%d, ", gamePile->pile[i]);	
		}
		printf("\n");

		/* Print hands of each player */
        int k;
        for (k = 0; k < Nplayers; k++) {
            printf("    %d: ", k); /* player number */
            int n;
            for (n = 0; n < players[k].handSize; n++) { 
				printf("%d ", players[k].hand[n]);	/* player hand */
			}
			printf("\n");
		}
	}

    /* Free all mallocs */
    int i;
    for (i = 0; i < Nplayers; i++) {
		free(players[i].hand);
	}
	free(gamePile->pile);
	free(gamePile);
	free(players);
	return turns;
}

{
	int sum = 0;

	struct gameStatistics* Statistics = malloc(sizeof(struct gameStatistics));

	Statistics->shortest = 1000;
	Statistics->longest = 2000;
    int i;
    for (i = 0; i < games; i++) {

		/* Create deck */
		int deck[] = {2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, ,11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14};

		/* Riffle shuffle deck */
        riffle(deck, 52, sizeof(int), 8);

        /* Run beggar game */
        int turns = beggar(Nplayers, deck, 0);

        /* If its shorter than previous shortest */
		if (turns < Statistics->shortest) {
			Statistics->shortest = turns;	
		}
        /* If its longer than previous longest */
		if (turns > Statistics->longest) {
			Statistics->longest = turns;
		}
		sum += turns;
	}

	Statistics->average = sum / games;

	return Statistics;
}