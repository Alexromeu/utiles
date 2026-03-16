#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Scores {
    string name;
    int score;
};



void insert_in_file(fstream& score_stream, Scores& element) {

    vector<int> scores;
    int curr_score;

    score_stream.clear();
    score_stream.seekg(0, ios::beg);

    while (score_stream >> curr_score) {
        scores.push_back(curr_score);
    }
    
    scores.push_back(element.score);

    score_stream.clear();
    score_stream.seekg(0, ios::beg);
    score_stream.close();
    score_stream.open("scores.txt", ios::in | ios::out | ios::trunc);
    
    for (int i = 0; i < scores.size(); i++) {
        score_stream << scores[i] << "\n";
    }
}

void out_binary(fstream& text) {
    if (!text.is_open()) {
        cout << " error at open";
        return;
    }

    // FIX: Add proper file mode
    fstream binary("scores.bin", ios::binary | ios::out);
    if (!binary.is_open()) {
        cout << " error creating binary file";
        return;
    }

    vector<int> scores;
    int current_score;

    text.clear();
    text.seekg(0, ios::beg);

    // FIX: Better loop condition with error checking
    while (text >> current_score) {
        scores.push_back(current_score);
        
        // Optional: Add a safety limit to prevent infinite loops
        if (scores.size() > 10000) { // Adjust as needed
            cout << "Warning: Large number of scores processed";
            break;
        }
    }

    // FIX: Check if loop ended due to error
    if (!text.eof() && text.fail()) {
        cout << "Warning: Some data may not have been read correctly\n";
        text.clear(); // Clear error state
    }

    // Write data only if we have scores
    if (!scores.empty()) {
        binary.write(reinterpret_cast<const char*>(scores.data()), 
                    scores.size() * sizeof(int));
        cout << "Successfully wrote " << scores.size() << " scores to binary file\n";
    } else {
        cout << "No scores were read from the text file\n";
    }

    binary.close();
}


int main() {
    Scores sc1;
    sc1.name = "Alex";
    sc1.score = 10;
    
    Scores sc2;
    sc2.name = "Bia";
    sc2.score = 20;

    Scores sc3;
    sc3.name = "Titi";
    sc3.score = 7;

    Scores sc4;
    sc4.name = "Gisi";
    sc4.score = 15;

    fstream score_file("scores.txt", ios::in | ios::out | ios::trunc);
    insert_in_file(score_file, sc1);
    insert_in_file(score_file, sc2);
    insert_in_file(score_file, sc3);
    insert_in_file(score_file, sc4);
    out_binary(score_file);

    return 0;
}