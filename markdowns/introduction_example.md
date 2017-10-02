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
board: \begin{bmatrix}
0 & 1 & 1 \\
2 & 1 & 2 \\
1 & 2 & 0
\end{bmatrix} & board: \begin{bmatrix}
0 & 1 & 1 & 2 & 1 & 2 & 1 & 2 & 0
\end{bmatrix} & board: \left\{ (0,0):0, (0,1):1, (0,2):1, \\
(1,0):2, (1,1):1, (1,2):2, \\
(2,0):1, (2,1):2, (2,2):0 \right\}
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

> _Where is the problem with this 2D array_ ?

No problem, that's a very good choice, but let's make something different and see if we could **replace this array by a much simpler integer**.


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

> _Hey, why do I need more variables_ ?

In bitboard representation, sometimes we need **more than one bitboard** (we will see why later). In our case, the variable `position` has been added in complement.

And here is the **first trick**: If we want to know the opponent tiles position, we only need to make an exclusive or (XOR) between `board` and `position`.

```math
opponentTiles = playerTiles \oplus boardTiles
```

Very convenient, but it's peanuts compared to the main bitboard features. Let's go a little farther.

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
| `void putTile(int x, int y)` | `position |= (1 << y*WIDTH+x)` | Put a tile on the board at (x,y) |
| `bool isDrawPosition()` | `return position == 511` | Whether a position is draw or not |
| `bool isEmptyBoard()`   | `return position == 0` | Whether a board is empty or not |
| `Bitboard getOppTiles()` | `return board ^ position` | Get the current player opponent tiles position |
| `Bitboard getRow(int y)` | `return board & (UINT64_C(73) << y);` | Get a row on the board |
| `Bitboard getColumn(int x)` | `return board & (UINT64_C(7) << WIDTH*x);` | Get a column on the board |
| `void resetState()` | `board = 0; position = 0` | Reset the state to empty board |



# Bitboards and simulation

## Why should I care about bitboards ?

When making some AI, Bitboards come to be a **method for state representation** using the **BitArray data structure**. No no, stay here, I will explain. But before that, let's make a brief introduction on agents and environments.
