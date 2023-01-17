//
// Created by Cyril Wu on 2023/1/12.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include <vector>

using namespace std;

class Sudoku{
    friend bool backTrack( vector<vector<char>>& res, int x, int y, vector<vector<int>>& row, vector<vector<int>>& col, vector<vector<int>>& subbox );
public:
    Sudoku(){}; // 因為至少要有 17 個數字才能求出唯一解，所以需要在 9 * 9 出現隨機跳出 17 個數字，但是
    void insert();
    void clear();
    void hint();
    void newGame();
    template<class T> void showBoard( vector<vector<T>>& vec );
    void finalANS();
    void initialize();
    template <class T> bool isAppeared( vector<vector<T>>& vec, int& x, int& y, int num );
    vector<vector<char>> board{ size, vector<char>( size, ' ' ) }; // 想要在 class 內初始化 vector 就一定要使用大括號
    vector<vector<char>> res{board};
    void valid();
private:
    const static int size = 9;
    void validSudoku();
    int genRandomNum( int x, int y );
};

bool backTrack( vector<vector<char>>& res, int x, int y, vector<vector<int>>& row, vector<vector<int>>& col, vector<vector<int>>& subbox );

#endif //SUDOKU_SUDOKU_H