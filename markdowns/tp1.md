# TP1: Escape the Maze

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

  void displayMaze(OneHot position, OneHot endPosition, Bitboard walls) {
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
                if (currPosition & 0x01)
                    symb = 'P';
                else if (endPosition & 0x01)
                    symb = 'E';
                else if (walls & 0x01)
                    symb = 'X';
                else
                    symb = '.';
                printf(" %c |", symb);
                currPosition >>= 1;
                walls >>= 1;
                endPosition >>= 1;
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

    printf("********** MAZE SIMULATION **********\n\n");
    Utils::displayMaze(startPos, exitPos, walls);

    return 0;
}
```

# Let's code

@[Escape the Maze]({"stubs": ["src/Exercises/Maze.cpp"],"command": "sh /project/target/run.sh"})
