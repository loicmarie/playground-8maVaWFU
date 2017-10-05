#ifndef TEST_EXERCICES_MAZE_H_
#define TEST_EXERCICES_MAZE_H_

#include <string>
#include <vector>
#include <iostream>

#include <cstdlib>
#include <cstdint>

#define W 8
#define H 8
#define OH(x) (1 << (x))

typedef uint64_t Bitboard;
typedef uint64_t OneHot;

using namespace std;

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
