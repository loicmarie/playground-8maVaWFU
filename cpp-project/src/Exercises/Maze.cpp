// { autofold
#include "Maze.h"
// }

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

const OneHot exitPos = 0x40000000000000;
const OneHot startPos = 0x200;
const Bitboard walls = 0xffb5a1ab89ada5ff;

void moveUp() {
    // put your magic here
}

void moveDown() {
    // put your magic here
}

void moveLeft() {
    // put your magic here
}

void moveRight() {
    // put your magic here
}

bool isWall(OneHot cell) {
    // put your magic here
}

bool isExit(OneHot cell) {

}

void run() {
    printf("ok\n");
}
