# Introduction to Bitboards

## Commonly used structures

```math
\begin{array}{lcr}
2D array & 1D vector & item1n\\
\begin{bmatrix}
0 & 1 & 1 \\
2 & 1 & 2 \\
1 & 2 & 0
\end{bmatrix} & \begin{bmatrix}
0 & 1 & 1 & 2 & 1 & 2 & 1 & 2 & 0
\end{bmatrix} & item2n
\end{array}
```

## BitArray: binary data structure

# Bitboards and simulation

## Why should I care about bitboards ?

When making some AI, Bitboards come to be a **method for state representation** using the **BitArray data structure**. No no, stay here, I will explain. But before that, let's make a brief introduction on agents and environments.

## Agent and Environment in AI

When creating some artificial intelligence (AI), we have to carry about two things:
* The **environment**: where the agent will act and evolve. it defines the relation between a state, an action of the agent, and the resulting next state.
* The **agent**: anything that can perceive its environment through sensors and acts upon that

![Agent and environment](http://cs-alb-pc3.massey.ac.nz/notes/59302/fig02.01.gif)

> That's cool ! Why are we talking about that ?

The reason is: with bitboards we're not gonna make an agent, but an **efficient environment or simulation of the environment** in order to power up our simulation-based algorithms.

## Importance of simulations

Creating an AI means creating an agent that is able to act reasonably in the environment. In most of the currently existing intelligent algorithms, **we need to simulate the environment response** to an agent action.

**The more states we simulate, the more accurate will be our agent**.

> OK, so at the end of the tutorial I could get an AI better than the world chess champion ?

Don't be on a rush !

No, I really don't think so, for two reasons:
* Improving the number of states simulations is very important, **but not as many as improving the algorithm**. This tutorial will be useful only when you'll have an efficient algorithm, and you think that only the simulations could be improved.
* Bitboards cannot be implemented without a lot of condition, and we will see later that it is not always the response to every problem. However, it remains a powerful tool that you should know about !

# Introduction to bitmaps

## Common data structures

The state representation depends on the environment and can be implemented in numerous different ways. We're not going to analyze all the methods but will quickly show the
most used ones. We'll use some Tic-Tac-Toe examples in order to spot the differences, and write the State class and the associated methods.

### 2D vectors

The most standard manner to represent 2D board games is with 2D arrays. In the case of the Tic-Tac-Toe, we could represent a state of the board like the following.

```math
\begin{bmatrix}
0 & 1 & 1 \\
2 & 1 & 2 \\
1 & 2 & 0
\end{bmatrix}
```

::: The full code of 2D vector board representation

```C++ runnable

#include <iostream>
#include <stdlib.h>

using namespace std;

class Move {
// autofold {
    public:

	int x,y;
	Move(int x, int y) : x(x), y(y) {}
// }
};


class State {
    public:

    int player; // player to play this turn
    int board[3][3]; // 0 for empty, 1 for first player tiles, 2 for opponent tiles

    State() {
        player = 0;
        for(int y=0; y<3; y++) {
			for (int x=0; x<3; x++)
			    board[y][x] = 0;
        }
    }
	int play(Move * move) {
		board[move->y][move->x] = player;
		player = 1-player;
	}
	Move ** getMoves() {
	    Move ** moves = (Move **) malloc((4) * sizeof(Move *) );
		int k = 0, x, y;
		for(y=0; y < 3; y++) {
			for (x=0; x < 3; x++) {
				if (board[y][x] == ' ' ) {
					moves[k] = new Move(x,y);
					k++;
				}
			}
		}
		return moves;
	}
	bool isWinningPosition() {
	    int ¨prevPlayer = 1-player, x, y;
	    bool isRow = false,
	         isCol = false,
	         isDiag = false;
		for(y=0; y < 3; y++) {
		    bool isRowTmp = true;
			for (x=0; x < 3; x++) {
			    isRowTmp &&= board[y][x] == prevPlayer+1;
			}
		}
	}
};

void display(State * state) { // autofold {
	int y,x;
	std::string symbs = ".XO";
	printf("   |");
	for ( x = 0; x < 3; x++)
		printf(" %d |", x);
	printf("\n");
	printf("----------------");
	printf("\n");

	for(y=0; y < 3; y++) {
		printf(" %d |", y);
		for ( x = 0; x < 3; x++)
			printf(" %c |", symbs[state->board[y][x]]);
		printf("\n");
		printf("----------------");
		printf("\n");
	}
	printf("\n");
}

void dumbPlay(State * state) {
	state->play(state->getMoves()[0]);
}

int main() {
    State state;
    cout << "ok" << endl;
}
```
:::

### 1D vectors

```C++
class State {
  int player; // player to play this turn
  int board[9]; // 0 for empty, 1 for first player tiles, 2 for opponent tiles
}
```

### BitArray (or one-hot vector)

We call a **Bitboard** a representation of an 8x8 game that uses a **BitArray data structure**.

Modifying the above example, we get:

```C++
class State {
  int player;
  uint64_t board; // bitboard
  uint64_t position; // bitboard
}
```

### Bitboards: BitArray exploitation in 2D board games

The purpose of this tutorial is to talk about a very efficient data structure for simulating 2D board games and other environments: **the biboards**.

Many games can be represented using bitboards:
* Chess
* Othello
* Connect four
* Tic-Tac-Toe

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
