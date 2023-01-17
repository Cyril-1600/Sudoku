//
// Created by Cyril Wu on 2023/1/12.
//

#include <iostream>
#include <random>
#include "Sudoku.h"

using namespace std;

void Sudoku::insert() {
    cout << "Please input index x and y from 0 to 8:" << endl;
    int x, y;
    cin >> x >> y;
    if ( Sudoku::board[x][y] != ' ' ){
        cout << "The location is filled, please choose another one" << endl;
        insert();
    }

    cout << "Please input your number from 1 to 9:" << endl;
    int digit;
    cin >> digit;
    while ( digit < 1 || digit > 9 ){
        cout << "Your number is over the range, please input again" << endl;
        cout << "Please input your number from 1 to 9:" << endl;
        cin >> digit;
    }

    Sudoku::board[x][y] = digit + '0';
}

void Sudoku::clear() {
    cout << "Please input index x and y from 0 to 8:" << endl;
    int x, y;
    cin >> x >> y;
    Sudoku::board[x][y] = ' ';
}

void Sudoku::hint() {
    cout << "Please input the index x and y from 0 to 8:" << endl;
    int x, y;
    cin >> x >> y;
    Sudoku::board[x][y] = Sudoku::res[x][y];
}

void Sudoku::newGame() {
    initialize();
}

void Sudoku::initialize() { // 如何幫數獨的版面做有意義的初始化
//    cout << "initialize" << endl;
    int x_loc;
    int y_loc;
    int randNum;
    int amountNum = 0;
    do{ // 如果隨機產生的位置已經有數字，就一直使用 do while 迴圈產出一個還沒輸入任何數字的位置
        x_loc = genRandomNum( 0, 8 );
        y_loc = genRandomNum( 0, 8 );
//        cout << "x_loc: "<< x_loc << " y_loc: " << y_loc << endl;
        if ( Sudoku::board[x_loc][y_loc] == ' ' ){
            do{
                randNum = genRandomNum( 1, 9 ); // 需要判斷這個位置產生的數字在 row, col, subbox 都沒有出現過
//                cout << "randNum: "<< randNum << endl;
            }
            while( isAppeared( Sudoku::board, x_loc, y_loc, randNum ) ); // 如果已經出現過的話就持續產出 random number 直到沒有 random 為止
            Sudoku::board[x_loc][y_loc] = randNum + '0';
            amountNum++;
        }
//        cout << "amountNum: " << amountNum << endl;
    } while( amountNum < 17 );
    Sudoku::showBoard( Sudoku::board );
}

void Sudoku::validSudoku() { // 這個比較複雜，最後再去處理
    bool isCorrect = true;
    for ( auto i = 0, j = 0; i < board.size() and j < res.size(); i++, j++ ){
        if ( board[i][j] != res[i][j] )
            isCorrect = false;
    }

    if ( isCorrect )
        cout << "Good job, you solved the Sudoku puzzle !!";
}

template <class T>
bool Sudoku::isAppeared( vector<vector<T>>& vec, int& x, int& y, int num ){
    for ( int i = 0; i < vec.size(); i++ ){ // 判斷維度一是否有出現相同的數字
        if ( vec[i][y] == num + '0' ){
            return true;
        }
    }

    for ( int j = 0; j < vec.size(); j++ ){ // 判斷維度二是否有出現相同的數字
        if ( vec[x][j] == num + '0' ){
            return true;
        }
    }

    int x_subBox = x / 3 * 3;
    int y_subBox = y / 3 * 3;
    int new_x = 0;
    int new_y = 0;
    for ( int k = 0; k < 3; k++ ){
        new_x = x_subBox + k;
        for ( int l = 0; l < 3; l++ ){
            new_y = y_subBox + l;
            if ( vec[new_x][new_y] == num + '0' )
                return true;
        }
    }

    return false;
}

template<class T>
void Sudoku::showBoard( vector<vector<T>>& vec ) {
//    cout << "Sudoku::board.size(): " << Sudoku::board.size() << endl;
//    cout << "Sudoku::board[i].size(): " << Sudoku::board[0].size() << endl;
    for ( int i = 0; i < vec.size(); i++ ){
        cout << " -------------------------------------" << endl;
        for ( int j = 0; j < vec[i].size(); j++ ){
            cout << " | " << vec[i][j];
        }
        cout << " |\n";
    }
    cout << " -------------------------------------\n" << endl;
}

void Sudoku::finalANS() {
    Sudoku::res = Sudoku::board;
//    Sudoku::showBoard( Sudoku::res );
    int n = res.size();
    // 使用三個 vector 來記錄那些數字已經被使用過
    vector<vector<int>> row( n, vector<int>( n + 1 ) );
    vector<vector<int>> col( n, vector<int>( n + 1 ) );
    vector<vector<int>> subbox( n, vector<int>( n + 1 ) );
    for ( int i = 0; i < res.size(); i++ ){
        for ( int j = 0; j < res.size(); j++ ){
            if ( res[i][j] != ' ' ){
                int num = res[i][j] - '0';
                row[i][num] = 1;
                col[j][num] = 1;
                subbox[(i/3)*3+(j/3)][num] = 1;
            }
        }
    }
    Sudoku s;
    backTrack( res, 0, 0, row, col, subbox );
//    Sudoku::showBoard( Sudoku::res );
//    cout << "finalANS end" << endl;
}

bool backTrack( vector<vector<char>>& res, int x, int y, vector<vector<int>>& row, vector<vector<int>>& col, vector<vector<int>>& subbox ){ // 使用 DFS 來計算出整個版面的解答，搭配 backtrack 做紀錄
    if ( y == 9 ) // 其實這裡的 y 被當成 row
        return true;

    int next_x = ( x + 1 ) % 9; // 確認 x 是否已經到最右邊
    int next_y = ( next_x == 0 )? y + 1: y; // 表示 x 已經到最右邊而且已經到最底

    if ( res[y][x] != ' ' ) // 確認已經到最右且最底都時候 call 自己來 return 結果
        return backTrack(res, next_x, next_y, row, col, subbox );

    for ( int num = 1; num <= res.size(); num++ ){
        if ( row[y][num] == 0 && col[x][num] == 0 && subbox[(y/3)*3+(x/3)][num] == 0 ){
            row[y][num] = 1;
            col[x][num] = 1;
            subbox[(y/3)*3+(x/3)][num] = 1;
            res[y][x] = num + '0';
            if ( backTrack( res, next_x, next_y, row, col, subbox ) ) // 給完值後進行條件判斷
                return true;
            row[y][num] = 0;
            col[x][num] = 0;
            subbox[(y/3)*3+(x/3)][num] = 0;
            res[y][x] = ' ';
        }
    }
    return false;
}

int Sudoku::genRandomNum( int x, int y ) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> range( x, y );
    return range( rd );
}

void Sudoku::valid(){
    validSudoku();
};