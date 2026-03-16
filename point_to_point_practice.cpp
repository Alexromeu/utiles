#include <iostream>

int main() {

    int hi = 50;
    int wi = 50;

    int** matrix = new int*[hi];
    for (int i = 0; i < hi; ++i) {
        matrix[i] = new int[wi];

        for (int j = 0; j < wi; ++j) {
            matrix[i][j] = 0;
        }
    } 


    for (int i = 0; i < hi; ++i) {
        for (int j = 0; j < wi; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    } 

    return 0;
}