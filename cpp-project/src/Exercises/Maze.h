#ifndef TEST_EXERCICES_MAZE_H_
#define TEST_EXERCICES_MAZE_H_

#include <cstdlib>
#include <cstdio>
#include <cstdint>

using namespace std;

typedef uint64_t Bitboard;
typedef uint64_t OneHot;

class Maze {
    public:
};

OneHot moveUp(OneHot cell);
OneHot moveDown(OneHot cell);
OneHot moveLeft(OneHot cell);
OneHot moveRight(OneHot cell);
bool isWall(OneHot cell, Bitboard walls);
bool isExit(OneHot cell, OneHot exitPos);
void run();

#endif // TEST_EXERCICES_MAZE_H_
