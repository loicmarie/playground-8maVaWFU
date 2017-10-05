#include "Exercises/Maze.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


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


void Message(string channel, string msg) {
    stringstream ss(msg);
    string line;
    while (getline(ss, line, '\n')) {
        cout << "TECHIO> message --channel \"" << channel << "\" \"" << line << "\"" << endl;
    }
}

void Success(bool success) {
    cout << "TECHIO> success " << (success ? "true" : "false") << endl;
}

// check if a string exists in a text file
bool ExistsInFile(string str, string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.find(str) != string::npos ) {
            return true;
        }
    }

    return false;
}

void AssertEquals(int expected, int found, string message) {
    if(expected != found) {
        ostringstream error;
        error << message << " Expected: " << expected << ", Found: " << found  << endl;
        throw logic_error(error.str());
    }
}

const OneHot exitPos = 0x40000000000000;
const OneHot startPos = 0x8000000000000;
const Bitboard walls = 0xffb5a1ab89ada5ff;
OneHot currPos = startPos;

int main() {
    try {

        // Maze maze;
        // AssertEquals(5, Universe::CountAllStars(galaxy1), "Running Universe::CountAllStars(2, 3)...");
        run();
        displayMaze(currPos, startPos, exitPos, walls);

        printf("----- isWall CHECKING -----\n\n");
        AssertEquals(true, isWall(1, walls), "CHECK isWall(0, walls)\n");
        AssertEquals(true, isWall(2, walls), "CHECK isWall(2, walls)\n\n");
        AssertEquals(false, isWall(512, walls), "CHECK isWall(512, walls)\n\n");

        printf("----- isExit CHECKING -----\n\n");
        AssertEquals(true, isExit(18014398509481984, exitPos), "CHECK isExit(18014398509481984, exitPos)\n\n");
        AssertEquals(false, isExit(512, exitPos), "CHECK isExit(512, exitPos)\n\n");

        printf("DO moveUp(%lu)\n\n", currPos);
        currPos = moveUp(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveRight(%lu)\n\n", currPos);
        currPos = moveRight(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveUp(%lu)\n\n", currPos);
        currPos = moveUp(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveUp(%lu)\n\n", currPos);
        currPos = moveUp(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveRight(%lu)\n\n", currPos);
        currPos = moveRight(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveLeft(%lu)\n\n", currPos);
        currPos = moveLeft(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveRight(%lu)\n\n", currPos);
        currPos = moveRight(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveRight(%lu)\n\n", currPos);
        currPos = moveRight(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveDown(%lu)\n\n", currPos);
        currPos = moveDown(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveDown(%lu)\n\n", currPos);
        currPos = moveDown(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        printf("DO moveDown(%lu)\n\n", currPos);
        currPos = moveDown(currPos);
        displayMaze(currPos, startPos, exitPos, walls);

        Success(true);

        // vector<int> galaxy1 {2, 3};
        // AssertEquals(5, Universe::CountAllStars(galaxy1), "Running Universe::CountAllStars(2, 3)...");
        //
        // vector<int> galaxy2 {9, -3};
        // AssertEquals(6, Universe::CountAllStars(galaxy2), "Running Universe::CountAllStars(9, -3)...");
        // Success(true);
        //
        // if (ExistsInFile("accumulate", "src/Exercises/Universe.cpp")) {
        //     Message("My personal Yoda, you are. 🙏", "* ● ¸ .　¸. :° ☾ ° 　¸. ● ¸ .　　¸.　:. • ");
        //     Message("My personal Yoda, you are. 🙏", "           　★ °  ☆ ¸. ¸ 　★　 :.　 .   ");
        //     Message("My personal Yoda, you are. 🙏", "__.-._     ° . .　　　　.　☾ ° 　. *   ¸ .");
        //     Message("My personal Yoda, you are. 🙏", "'-._\\7'      .　　° ☾  ° 　¸.☆  ● .　　　");
        //     Message("My personal Yoda, you are. 🙏", " /'.-c    　   * ●  ¸.　　°     ° 　¸.    ");
        //     Message("My personal Yoda, you are. 🙏", " |  /T      　　°     ° 　¸.     ¸ .　　  ");
        //     Message("My personal Yoda, you are. 🙏", "_)_/LI");
        // } else {
        //     Message("Kudos 🌟", "Did you know that you can use the accumulate method to sum up a vector? Try it!");
        //     Message("Kudos 🌟", " ");
        //     Message("Kudos 🌟", "#include <numeric>");
        //     Message("Kudos 🌟", " ");
        //     Message("Kudos 🌟", "vector<int> galaxies {37, 3, 2};");
        //     Message("Kudos 🌟", "int totalStars = accumulate(galaxies.begin(), galaxies.end(), 0); // 42");
        // }

    } catch (const exception& e)  {
        Success(false);
        Message("Oops! 🐞", e.what());
        Message("Hint 💡", "Did you properly accumulate all stars into 'totalStars'? 🤔");
    }

  return 0;
}
