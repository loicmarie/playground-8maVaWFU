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

int main() {
    try {

        // Maze maze;
        // AssertEquals(5, Universe::CountAllStars(galaxy1), "Running Universe::CountAllStars(2, 3)...");
        run();
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
