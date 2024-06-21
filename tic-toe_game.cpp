#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void display_board(vector<vector<char>> &board) {
    cout << "+-------+-------+-------+" << endl;
    for (int row = 0; row < 3; ++row) {
        cout << "|       |       |       |" << endl;
        for (int col = 0; col < 3; ++col) {
            cout << "|   " << board[row][col] << "   ";
        }
        cout << "|" << endl;
        cout << "|       |       |       |" << endl;
        cout << "+-------+-------+-------+" << endl;
    }
}

void enter_move(vector<vector<char>> &board) {
    bool ok = false;
    while (!ok) {
        cout << "Enter your move: ";
        string move;
        cin >> move;
        if (move.length() == 1 && move >= "1" && move <= "9") {
            int pos = stoi(move) - 1;
            int row = pos / 3;
            int col = pos % 3;
            char sign = board[row][col];
            if (sign != 'O' && sign != 'X') {
                board[row][col] = 'O';
                ok = true;
            } else {
                cout << "Field already occupied - repeat your input!" << endl;
            }
        } else {
            cout << "Bad move - repeat your input!" << endl;
        }
    }
}

vector<pair<int, int>> make_list_of_free_fields(vector<vector<char>> &board) {
    vector<pair<int, int>> free;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] != 'O' && board[row][col] != 'X') {
                free.push_back({row, col});
            }
        }
    }
    return free;
}

string victory_for(vector<vector<char>> &board, char sgn) {
    string who;
    if (sgn == 'X') {
        who = "me";
    } else if (sgn == 'O') {
        who = "you";
    } else {
        who = "Tie!";
    }
    bool cross1 = true, cross2 = true;
    for (int rc = 0; rc < 3; ++rc) {
        if (board[rc][0] == sgn && board[rc][1] == sgn && board[rc][2] == sgn) {
            return who;
        }
        if (board[0][rc] == sgn && board[1][rc] == sgn && board[2][rc] == sgn) {
            return who;
        }
        if (board[rc][rc] != sgn) {
            cross1 = false;
        }
        if (board[2 - rc][2 - rc] != sgn) {
            cross2 = false;
        }
    }
    if (cross1 || cross2) {
        return who;
    }
    return "";
}

void draw_move(vector<vector<char>> &board) {
    vector<pair<int, int>> free = make_list_of_free_fields(board);
    int cnt = free.size();
    if (cnt > 0) {
        int this_move = rand() % cnt;
        int row = free[this_move].first;
        int col = free[this_move].second;
        board[row][col] = 'X';
    }
}

int main() {
    srand(time(0));
    vector<vector<char>> board(3, vector<char>(3));
    int num = 1;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = num + '0';
            ++num;
        }
    }
    board[1][1] = 'X';

    bool human_turn = true;
    while (true) {
        display_board(board);
        vector<pair<int, int>> free = make_list_of_free_fields(board);
        string victor;
        if (human_turn) {
            enter_move(board);
            victor = victory_for(board, 'O');
        } else {
            draw_move(board);
            victor = victory_for(board, 'X');
        }
        if (!free.empty() && victor.empty()) {
            human_turn = !human_turn;
        } else {
            display_board(board);
            if (victor == "you") {
                cout << "You won!" << endl;
            } else if (victor == "me") {
                cout << "I won!" << endl;
            } else {
                cout << "Tie!" << endl;
            }
            break;
        }
    }

    return 0;
}
