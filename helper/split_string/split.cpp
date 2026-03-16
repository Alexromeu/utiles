#include <vector>
#include <string>
#include <iostream>
#include "split.h"

using namespace std;


namespace strlib 
{
    class str_operations;
} 

vector<string>  strlib::str_operations::split(string str, char separator) {
    int prev = -1;
    int next;
    vector<string> result;
    
    for (int i = str.find(separator, 0); i != string::npos; i = str.find(separator, i)) {
        next = i;
        int runner;
        string str_out = "";

        if (prev != -1) {
            runner = prev + 1;
            while (runner < next) {
                if (str[runner] != ' ') {
                    str_out += str[runner];
                    runner++;

                } else {
                    runner++;
                }
            }
            
        } else {
            runner = 0;
            while (runner < next) {
                if (str[runner] != ' ') {
                    str_out += str[runner];
                    runner++;

                } else {
                    runner++;
                } 
            }
        }

        prev = next;
        i++;
        result.push_back(str_out);
    }

    string final_cut;
    for (int i = prev + 1; str[i] != '\n' && i < str.size(); ++i) {
        if (str[i] != ' ') {
            final_cut += str[i];
        } else {
            ++i;
        } 
    }
    result.push_back(final_cut);

    return result;
}

int main() {
    string str = "Alexander romeu garcia";
    vector<string> output = strlib::str_operations::split(str, ' ');

    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << "\n";
    }
   

    return 0;
}


// take the string and first we need to copy it to the heap
// now iterate over each element until the separator is found
// when found :
// 