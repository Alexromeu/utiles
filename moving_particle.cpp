#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

vector<vector<char>> create_matrix(int wi, int hi, char filler) {
    vector<vector<char>> matrix(hi, vector<char>(wi));
    for (int i = 0; i < hi; ++i) {
        for (int j = 0; j < wi; ++j) {
            matrix[i][j] = filler;
        }
    }

    return matrix;
}

void print_matrix(vector<vector<char>>& matrix,int width,int height) {
    //system("clear");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    } 
}

void print_walking(int wi, int hi, char filler) {
    vector<vector<char>> matrix = create_matrix(wi, hi, filler);

}

int main() {
    int width = 50;
    int height = 50;
    int walk_right = 0;
    int walk_down = 0;
    vector<vector<char>> field = create_matrix(width, height, ' ');

    while (walk_down < height && walk_right < width) {
        field[walk_down][walk_right] = '0';
        print_matrix(field, width, height);  
      //  sleep(0.4);

        walk_right++;
        if (walk_right == width - 1) {
            walk_down++;
            walk_right = 0;
        }
        
    }
    

    return 0;
}