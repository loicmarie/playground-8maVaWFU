# II.1 Single cell operations

We will now see how to:
* get the value of a cell
* set the value of a cell

**Reminder**: in this tutorial (which uses C++), the `Bitboard` type has been defined as an unsigned 64bits integer (corresponding to the `uint64_t` type)

# Cells and positions

We have said that a position is of type `Bitboard`. So how is defined a cell ?

Response is... a Bitboard ! Yes, that's pretty confusing.

> _I don't get the difference ?_

In fact a bitboard representing a cell is a sequence with only **1 bit at 1** and **the other at 0**. This type of binary vector is often used in different computing domains and is called "**one-hot encoding**".

![Cell](img/cell.png)

# Getting a cell

Now that we know how are defined position and cells, we want to get the value at a position, and we want to get it with (x,y) cartesian coordinates.

```C++ runnable
#include <cstdint>

typedef uint64_t Bitboard;

typedef struct StateSt {
    int player;
    Bitboard board; // all tiles: (0 for empty, 1 for existing tile)
    Bitboard position; // current player tiles: (0 for empty, 1 for existing tile)
} State;

namespace Utils {
  // autofold {

  namespace Bitboard {

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

  }

// }
}

int main() {
    Bitboard cell;
}
```
