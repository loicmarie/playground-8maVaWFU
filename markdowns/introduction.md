# Introduction to Bitboards

## Agent and Environment in artificial intelligence

When creating some artificial intelligence (AI), we have to carry about two things:
* The **environment**: where the agent will act and evolve. it defines the relation between a state, an action of the agent, and the resulting next state.
* The **agent**: anything that can perceive its environment through sensors and acts upon that

![Agent and environment](http://cs-alb-pc3.massey.ac.nz/notes/59302/fig02.01.gif)

Creating an AI means creating an agent that is able to act reasonably in the environment. In most of the currently existing intelligent algorithms, **we need to simulate the environment response** to an agent action. **The more states we simulate, the more accurate will be our agent**.

Improving the number of states simulations is very important, **but not as many as improving the algorithm**. This tutorial will be useful only when you'll have an efficient algorithm, and you think that only the simulations could be improved.

The purpose of this tutorial is to talk about a very efficient data structure for simulating 2D board games and other environments: **the biboards**.

```C++ runnable
#include <iostream>

#define WIDTH 8
#define HEIGHT 8

using namespace std;

// { autofold

void displayBitboard(uint64_t position) {
	int i,j;
	uint64_t currPosition = position;
    for(i=0; i < HEIGHT; i++) {
        // printf("%lu\n", position);
        // currPosition = position >> i;
        for ( j = 0; j < WIDTH; j++) {
          if (currPosition & 0x01) {
        		   printf("1");
          } else {
        		   printf("0");
          }
          currPosition = currPosition >> 1;
        }
    }
    printf("\n");
}

void display(uint64_t board, uint64_t position) { // TODO: afficher le jeu a l'endroit
    char symb;
	int i,j;
	uint64_t boardTmp = board,
	         positionTmp = position;
	printf("   |");
	for (j = 0; j < WIDTH; j++)
		printf(" %d |", j);
	printf("\n");
	for (j=0; j<WIDTH+1; j++)
	    printf("----");
	printf("\n");
    for(i=0; i < HEIGHT; i++) {
        // boardTmp = board >> i;
        // positionTmp = position >> i;
        printf(" %d |", i);
        for ( j = 0; j < WIDTH; j++) {
          if (positionTmp & 0x01) {
        		   symb = 'X';
          } else {
        		   symb = '.';
          }
          printf(" %c |", symb);
          boardTmp = boardTmp >> 1;
          positionTmp = positionTmp >> 1;
        }
        printf("\n");
    	for (j=0; j<WIDTH+1; j++)
    	    printf("----");
    	printf("\n");
    }
}

// }

uint64_t moveRight(uint64_t position) {
    return position >> 5;
}

int main()
{
    uint64_t position = 39685902827520;
    displayBitboard(position);
    display(0, position);
    position = moveRight(position);
    displayBitboard(position);
    printf("\n");
    display(0, position);
    // cout << test << endl;
    return 0;
}
```
