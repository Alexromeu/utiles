#include <string>
#include <iostream>
#include "reverse.h"

using namespace std;

string reverse(string original) {
    string reversed;

    for (int i = 0; i < original.length(); i++) {
        reversed += original[original.length() - i - 1];
    }

    return reversed;
}

