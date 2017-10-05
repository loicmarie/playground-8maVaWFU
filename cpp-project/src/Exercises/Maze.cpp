// { autofold
#include "Maze.h"
// }

// { autofold
#include <cstdlib>
#include <cstdio>
#include <cstdint>

#define W 8
#define H 8
#define OH(x) (1 << (x))

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

const OneHot exitPos = 0x40000000000000;
const OneHot startPos = 0x8000000000000;
const Bitboard walls = 0xffb5a1ab89ada5ff;
OneHot currPos = startPos;

OneHot moveUp(OneHot pos) {
    return pos >> W;
    // put your magic here
}

OneHot moveDown(OneHot pos) {
    return pos << W;
    // put your magic here
}

OneHot moveLeft(OneHot pos) {
    return pos >> 1;
    // put your magic here
}

OneHot moveRight(OneHot pos) {
    return pos << 1;
    // put your magic here
}

bool isWall(OneHot cell, Bitboard walls) {
    return cell & walls;
}

bool isExit(OneHot cell, OneHot exitPos) {
    return cell & exitPos;
}

void run() {

}
