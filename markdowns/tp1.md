# TP1: Escape the Maze

Now we are going to help a poor man to **find the exit in a 8x8 maze**.

You are given the following variables:
* `startPos` is the **start position** of the character (**one-hot**)
* `exitPos` is the **exit position** he has to reach (**one-hot**)
* `walls` is the representation of walls position (**bitboard**)
* `currPos` is the **current position** of the character (**one-hot**)
* 
```C++ runnable

#define W 8
#define H 8

typedef uint64_t Bitboard;
typedef uint64_t OneHot;
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
        for(i=0; i < H; i++) {
            for ( j = 0; j < W; j++) {
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
        for (j = 0; j < W; j++)
            printf(" %d |", j);
        printf("\n");
        for (j=0; j<W+1; j++)
            printf("----");
        printf("\n");
        for(i=0; i < H; i++) {
            printf(" %d |", i);
            for ( j = 0; j < W; j++) {
                printf(" %c |", (currPosition & 0x01) ? 'X' : '.');
                currPosition >>= 1;
            }
            printf("\n");
            for (j=0; j<W+1; j++)
                printf("----");
            printf("\n");
        }
        printf("\n");

  }

// }
}

bool getCell(Bitboard position, int x, int y) {
    return position & (1 << y*W+x);
}

Bitboard activateCell(Bitboard position, int x, int y) {
    return position | (1 << (y*W+x));
}

Bitboard clearCell(Bitboard position, int x, int y) {
    return position & ~(1 << (y*W+x));
}

Bitboard switchCell(Bitboard position, int x, int y) {
    return position ^ (1 << y * W + x);
}

Bitboard swapCells(Bitboard position, int x1, int y1, int x2, int y2) {
    return position ^ (1 << (y2 * W + x2)) ^ (1 << (y1 * W + x1));
}

Bitboard up(Bitboard cell) {
    return cell >> W;
}

Bitboard right(Bitboard cell) {
    return cell << 1;
}

Bitboard left(Bitboard cell) {
    return cell >> 1;
}

Bitboard down(Bitboard cell) {
    return cell << W;
}

const Bitboard notFirstCol = 0xfefefefefefefefe;
const Bitboard notLastCol = 0x7f7f7f7f7f7f7f7f;

Bitboard moves(Bitboard cell) {
    return up(cell) | down(cell) 
        | left(cell & notFirstCol) 
        | right(cell & notLastCol);
}

Bitboard availableMoves(Bitboard cell, Bitboard walls) {
    return moves(cell) & ~walls;
}

int main() {
    State state;
    state.board = 27;
    
    Bitboard walls = 6648849073569327880;
    Bitboard visited = 1;
    Bitboard current = 1;
    // Bitboard movesMask = 

    Utils::displayPretty(walls);
    
    Utils::displayPretty(visited);
    visited |= availableMoves(current, walls) & ~visited;
    Utils::displayPretty(visited);
    
    for (int i=0; i<30; i++) {
        current = availableMoves(visited, walls);
        visited |= current & ~visited;
        Utils::displayPretty(visited);
    }
    /*
    current = availableMoves(visited, walls);
    visited |= current & ~visited;
    Utils::displayPretty(visited);
*/}
```

To help yourself, you're given the traditional `display` and `displayPretty` functions, which I add an extra:
```C++
void displayMaze(OneHot pos, OneHot startPos, OneHot endPos, Bitboard walls)
```

Let's take a look at those 4 variables et 3 methods in action:

```C++ runnable
// { autofold
#include <cstdlib>
#include <cstdio>
#include <cstdint>

#define W 8
#define H 8

typedef uint64_t Bitboard;
typedef uint64_t OneHot;
// }
namespace Utils {
  // autofold {

    void display(Bitboard position) {
        int i,j;
        Bitboard currPosition = position;

        printf("Bitboard display:\n\n");
        for(i=0; i < H; i++) {
            for ( j = 0; j < W; j++) {
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
        for (j = 0; j < W; j++)
            printf(" %d |", j);
        printf("\n");
        for (j=0; j<W+1; j++)
            printf("----");
        printf("\n");
        for(i=0; i < H; i++) {
            printf(" %d |", i);
            for ( j = 0; j < W; j++) {
                printf(" %c |", (currPosition & 0x01) ? 'X' : '.');
                currPosition >>= 1;
            }
            printf("\n");
            for (j=0; j<W+1; j++)
                printf("----");
            printf("\n");
        }
        printf("\n");

  }

  void displayMaze(OneHot pos, OneHot startPos, OneHot endPos, Bitboard walls) {
        char symb;
        int i,j;
        Bitboard currPos = pos;

        printf("Bitboard pretty display:\n\n");
        printf("   |");
        for (j = 0; j < W; j++)
            printf(" %d |", j);
        printf("\n");
        for (j=0; j<W+1; j++)
            printf("----");
        printf("\n");
        for(i=0; i < H; i++) {
            printf(" %d |", i);
            for ( j = 0; j < W; j++) {
                if (currPos & 0x01)
                    symb = 'C';
                else if (startPos & 0x01)
                    symb = 'S';
                else if (endPos & 0x01)
                    symb = 'E';
                else if (walls & 0x01)
                    symb = 'X';
                else
                    symb = '.';
                printf(" %c |", symb);
                currPos >>= 1;
                walls >>= 1;
                startPos >>= 1;
                endPos >>= 1;
            }
            printf("\n");
            for (j=0; j<W+1; j++)
                printf("----");
            printf("\n");
        }
        printf("\n");

  }

// }
}

int main() {
    const OneHot exitPos = 0x40000000000000;
    const OneHot startPos = 0x200;
    const Bitboard walls = 0xffb5a1ab89ada5ff;
    OneHot currPos = startPos;

    printf("********** MAZE SIMULATION **********\n\n");
    Utils::displayMaze(currPos, startPos, exitPos, walls);

    return 0;
}
```

Concerning the symbols in the above:
* `C` is the character to move
* `E` is the exit position
* `X` is a wall

# Let's code

@[Escape the Maze]({"stubs": ["src/Exercises/Maze.cpp"],"command": "sh /project/target/run.sh"})
