# II.1 Single cell operations

These functions will be very useful. We will now see how to:
1. get the value of a cell
2. set the value of a cell

**Reminder**: in this tutorial (which uses C++), the `Bitboard` type has been defined as an unsigned 64bits integer (corresponding to the `uint64_t` type)

# Cells and positions

We have said that a position is of type `Bitboard`. So how is defined a cell ?

Response is... a Bitboard ! Yes, that's pretty confusing.

> _I don't get the difference ?_

In fact a bitboard representing a cell is a sequence with only **1 bit at 1** and **the other at 0**. This type of binary vector is often used in different computing domains and is called "**one-hot encoding**".

![Cell](img/cell.png)

# Accessing a cell

Now we simply want to transform (x,y) to bit position and vice-versa.

## Cartesian coordinates to bit position

```math
bitpos = y * WIDTH + x
```

## Bit position to cartesian coordinates

```math
\left \{
\begin{array}{r c l}
  x  & = & bitpos & \mod & WIDTH \\
  y  & = & bitpos & \div & WIDTH
\end{array}
\right .
```

Now that we know how are defined position and cells, we want to get the value at a position (x,y).

```math
bitboard \wedge (1 \ll bitpos)
```

# Setting a cell

## Activating a bit

We want to **add** an element at (x,y) coordinates.

In other words: we want to set the bit n° bitpos **at 1**. The formula is:

```math
bitboard = bitboard \vee (1 \ll bitpos))
```

We can write it up:

```C++
Bitboard setCell(Bitboard bitboard, int x, int y) {
    return bitboard | (1 << (y * 3 + x));
}
```

## Clearing a bit

We want to **remove** an element at (x,y) coordinates.

In other words: we want to set the bit n° bitpos **at 0**. The formula is:

```math
bitboard = bitboard \wedge ~(1 \ll bitpos)
```

We can write it up:

```C++
Bitboard clearCell(Bitboard bitboard, int x, int y) {
    return bitboard & ~(1 << (y * 3 + x));
}
```

# Test

```C++ runnable
#include <cstdio>
#include <cstdint>

typedef uint64_t Bitboard;

typedef struct StateSt {
  // autofold {
    int player;
    Bitboard board; // all tiles: (0 for empty, 1 for existing tile)
    Bitboard position; // current player tiles: (0 for empty, 1 for existing tile)
    StateSt() : player(0), board(0), position(0) {}
  // }
} State;

namespace Utils {
  // autofold {

    void display(Bitboard position) {
        int i,j;
        Bitboard currPosition = position;

        printf("Bitboard display:\n\n");
        for(i=0; i < 3; i++) {
            for ( j = 0; j < 3; j++) {
                printf((currPosition & 0x01) ? "1" : "0");
                currPosition >>= 1;
            }
        }
        printf("\n\n");
    }

    void displayPretty(Bitboard position) {
        char symb;
        int i,j;
        Bitboard currPosition = position;

        printf("Bitboard pretty display:\n\n");
        printf("   |");
        for (j = 0; j < 3; j++)
            printf(" %d |", j);
        printf("\n");
        for (j=0; j<4; j++)
            printf("----");
        printf("\n");
        for(i=0; i < 3; i++) {
            printf(" %d |", i);
            for ( j = 0; j < 3; j++) {
                printf(" %c |", (currPosition & 0x01) ? 'X' : '.');
                currPosition >>= 1;
            }
            printf("\n");
            for (j=0; j<4; j++)
                printf("----");
            printf("\n");
        }
        printf("\n");

  }

// }
}

bool getCell(Bitboard position, int x, int y) {
    return position & (1 << y*3+x);
}

Bitboard setCell(Bitboard position, int x, int y) {
    return position | (1 << (y*3+x));
}

Bitboard clearCell(Bitboard position, int x, int y) {
    return position &= ~(1 << (y*3+x));
}

int main() {
    State state;
    state.board = 27;
    Utils::displayPretty(state.board);
    printf("%d\n", getCell(state.board,2,1));
    state.board = setCell(state.board,2,1);
    state.board = clearCell(state.board,1,0);
    Utils::displayPretty(state.board);
    printf("%d", getCell(state.board,2,1));
}
```
