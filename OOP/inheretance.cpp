#include <iostream>
#include <vector>
using namespace std;

class Comparable {
    public:
        virtual int compare(Comparable& other) = 0; // return 1 0 -1
        virtual ~Comparable() {};       
};

class HighScoreElement: public Comparable {
    public:
        HighScoreElement(int score);
        ~HighScoreElement();
        int compare(Comparable& other);
    private:
        int* score;
        string name;
};

HighScoreElement::HighScoreElement(int s) {
    *this->score = s; 
}

// int HighScoreElement::compare(Comparable& other) {
//    if (this->score > other.score) {
//     return 1;
//    } else if (this->score < other.score) {
//     return -1;
//    } else {
//     return 0;
//    }
// }



HighScoreElement::~HighScoreElement() {
    delete score; 
}


int sort(vector<HighScoreElement*> interface) {

}

int main() {
// HighScoreElement elem;
// HighScoreElement elem2;

//  elem.compare(elem2)
    return 0;
}