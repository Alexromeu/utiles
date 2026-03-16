#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> image_filter(vector<string> images, string term) {
    vector<string> matched;
    for (int i = 0; i < images.size(); ++i) {
        if (images[i].find(term) != string::npos) {
            matched.push_back(images[i]);
        }
    }

    return matched;
}

int main() {

    const vector<string> images = {"cat.jpg", "dogToy.jpeg", "kitty-cat.png", "catNip.jpeg", "franken_cat.gif"};
    const string term = "cat";
    vector<string> matched = image_filter(images, term);
    for (int i = 0; i < matched.size(); ++i) {
        cout << matched[i]<< "\n";
    }
 
    return 0;
}