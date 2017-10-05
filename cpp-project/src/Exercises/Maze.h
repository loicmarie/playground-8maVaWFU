#ifndef TEST_EXERCICES_MAZE_H_
#define TEST_EXERCICES_MAZE_H_

#include <cstdlib>
#include <cstdio>
#include <cstdint>

using namespace std;

typedef uint64_t Bitboard;
typedef uint64_t OneHot;

Utils::display(Bitboard position);
Utils::displayPretty(Bitboard position);

class Maze {
    public:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool isWall(OneHot cell);
    bool isExit(OneHot cell);
};

#endif // TEST_EXERCICES_MAZE_H_
