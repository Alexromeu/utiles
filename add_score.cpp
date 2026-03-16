#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> scores_board(0);

void show_scores(vector<int> &board) {
    vector<int>::iterator iter;

    for (iter = board.begin(); iter != board.end(); ++iter) {
        cout << *iter << endl;
    }
}

void add_score(vector<int> &board, int score) {
    vector<int>::iterator iter;
    
    for (iter = board.begin(); iter != board.end(); ++iter) {
        if (*iter <= score) {
            board.insert(iter, score);
            return;
        } 
    }
    board.push_back(score);
}

int main() {
    add_score(scores_board, 100);
    add_score(scores_board, 150);
    add_score(scores_board, 300);
    add_score(scores_board, 500);
    add_score(scores_board, 400);
    add_score(scores_board, 200);
    show_scores(scores_board);
    return 0;
}