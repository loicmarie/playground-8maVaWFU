# Introduction to Bitboards

## Commonly used structures

Do you know the famous [Tic-tac-toe](https://fr.wikipedia.org/wiki/Tic-tac-toe) ?

It's a simple game for two players, X and O, who take turns marking the spaces in a 3×3 grid. The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game.

![Tictactoe](http://media.istockphoto.com/photos/tictactoe-picture-id544478622?k=6&m=544478622&s=612x612&w=0&h=xn90aBPDceZURVcW3CPHIfbMl641M7AaEnrcOeWwD3k=)

Let's imagine that you are writting an artificial intelligence (AI) on this game. 

You have selected your algorithm, a minimax, or a Monte Carlo tree search for example. Unluckily, such algorithm need a high number of simulations and you're sceptical concerning the simulation engine you wrote.



# Game state representation

As a **representation of a game state**, you defined your board using a 2D array, or a 1D vector.


```math
\begin{array}{ccc}
2D Array & 1D Vector & Dictionary\\
\begin{bmatrix}
0 & 1 & 1 \\
2 & 1 & 2 \\
1 & 2 & 0
\end{bmatrix} & \begin{bmatrix}
0 & 1 & 1 & 2 & 1 & 2 & 1 & 2 & 0
\end{bmatrix} & \left\{ (0,0):0, (0,1):1, (0,2):1, (1,0):2, (1,1):1, \\
(1,2):2, (2,0):1, (2,1):2, (2,2):0 \right\}
\end{array}
```

In order to get a non-ambiguous state representation, you probably added a `player` variable to know the player who should play this turn. Ideally, we would have something like this:

```C++
struct State {
    int player;
    int board[3][3];
}
```

In reality you juste made a **very important choice** that can eventually result in a **considerable dropout of your program performances**.


# BitArray: binary data structure

Let me introduce you **_BitArray_**:

```math
\begin{array}{ccc}
BitArray \\
board = \begin{bmatrix}
0 & 1 & 1 & 1 & 1 & 1 & 1 & 1 & 0 & .. & 0
\end{bmatrix} \\
position = \begin{bmatrix}
0 & 1 & 1 & 0 & 1 & 0 & 1 & 0 & 0 & .. & 0
\end{bmatrix}
\end{array}
```

What happened here ? We have replaced our 2D array with **two 64bits integers**. Our structure should now be similar to the following:

```C++
typedef uint64_t Bitboard;

struct State {
    int player;
    Bitboard board;
    Bitboard position;
}
```

#### Explanation:

We've created a new type called "Bitboard" corresponding to a 64bits integer.
* `board` variable represents all tiles on the board _(bit 1 = tile, bit 0 = empty)_
* `position` variable represents current player tiles _(bit 1 = tile, bit 0 = empty)_

In bitboard representation, sometimes we need **more than one bitboard** (we will see why later). In our case, the variable `position` has been added in complement.

If we want to know the opponent tiles position, we only need to make an exclusive or (XOR) between `board` and `position`. Very convenient, but it's only one of many strength of bitboards.

# The Power of Bitboards

As you can now imagine, we call a **Bitboard** the BitArray application in **2D board games**, and particularly in the game state representation.

Despite of the lack of clarity in the code, the goal is to **transform all usual state operations** (actions, end testing, depth/breadth search, scoring, state copy and other) **into binary and boolean operations**. 

I see I'm a little foggy, let's take examples and write some methods from our above example (the Tic-Tac-Toe).

### Is winning position

```C++
bool isWinningPosition(State * state) {
    uint64_t p = state->position
    return (p==7) || (p==56) || (p==448) // rows
        || (p==73) || (p==146) || (p==292) // columns
        || (p==84) || (p==273)); // diags
}
```

Pretty straightforward, isn't it ?

Here is a non exhaustive list of usual methods in 2D board game (here for a Tic-Tac-Toe engine).

| Name           | Method | Description |
|:---------------|:-------|:------------|
| `void putTile(int x, int y)` | `state->position |= (1 << y*WIDTH+x)` | Put a tile on the board at (x,y) |
| `bool isDrawPosition(State * state)` | `return state->position == 511` | Whether a position is draw or not |
| `bool isEmptyBoard(State * state)`   | `return state->position == 0` | Whether a board is empty or not |
| `bitboard getOppTiles(State * state)` | `return state->board ^ state->position` | Get the current player opponent tiles position |
| `bitboard getRow(State * state, int row)` | `return state->board ^ state->position` | Get a row on the board |
| `void resetState(State * state)` | `state->board = 0; state->position = 0` | Reset the state to empty board |



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

#define WIDTH 3
#define HEIGHT 3

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

uint64_t putTile(uint64_t position, int x, int y) {
    return (1 << y*3+x);
} 

int main()
{
    uint64_t position = 0;
    displayBitboard(position);
    printf("\n");
    position = putTile(position, 2,2);
    display(0, position);
    // cout << test << endl;
    return 0;
}
```
