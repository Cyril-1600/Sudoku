#include <iostream>
#include <random>
#include <thread>
#include "Sudoku.h"

using namespace std;

int main() {
    Sudoku test;
    cout << "Wellcome to my Sudoku, enjoy the game" << endl;
    int opt = 0;

    while( opt != 5 ){
        cout << "Please input following option: " << endl;
        cout << "1) Create a new Game" << endl;
        cout << "2) insert a number" << endl;
        cout << "3) give you a hint" << endl;
        cout << "4) Clear your insert number" << endl;
        cout << "5) Exit Sudoku" << endl;

        cin >> opt;
        switch ( opt ){
            case 1:
                test.newGame();
                test.finalANS();
                test.showBoard( test.board );
                break;
            case 2:
                test.insert();
                test.valid();
                test.showBoard( test.board );
                break;
            case 3:
                test.hint();
                test.valid();
                test.showBoard( test.board );
                break;
            case 4:
                test.clear();
                test.showBoard( test.board );
                break;
            case 5:
                cout << "Thanks for your test" << endl;
                std::this_thread::sleep_for(2s);
                break;
        }
    }

    return 0;
}