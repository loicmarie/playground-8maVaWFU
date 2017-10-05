#ifndef TEST_EXERCICES_MAZE_H_
#define TEST_EXERCICES_MAZE_H_

using namespace std;

typedef unsigned int Bitboard;
typedef unsigned int OneHot;

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
