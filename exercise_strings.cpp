#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <set>
using namespace std;

//find a substring in a string all ocurences
int string_counter(const string& haystack, const string& needle) {
    int count = 0;

    for (int i = haystack.find(needle, 0); i != string::npos; i = haystack.find(needle, i)) {  
        count++;
        i++;
    }

    return count;
}


void csv_enter() {
    std::vector<std::string> lines;
    std::string user_input;

    std::cout << "Enter tabular data line by line (press Enter on empty line to finish):\n";

    // Step 1: Collect lines
    while (true) {
        std::getline(std::cin, user_input);
        if (user_input.empty()) break;
        lines.push_back(user_input);
    }

    // Step 2: Track punctuation characters per line
    std::map<char, int> punctuation_count;

    for (const auto& line : lines) {
        std::set<char> seen_in_line;
        for (char c : line) {
            if (!std::isalnum(c)) {
                seen_in_line.insert(c);
            }
        }
        for (char p : seen_in_line) {
            punctuation_count[p]++;
        }
    }

    // Step 3: Find punctuation that appears in every line
    std::vector<char> common_punctuations;
    for (const auto& [punct, count] : punctuation_count) {
        if (count == lines.size()) {
            common_punctuations.push_back(punct);
        }
    }

    // Step 4: Prompt user to choose separator
    if (common_punctuations.empty()) {
        std::cout << "No common punctuation found across all lines.\n";
        return;
    }

    std::cout << "Choose a separator from these options:\n";
    for (char c : common_punctuations) {
        std::cout << "  '" << c << "'\n";
    }

    char chosen_separator;
    std::cout << "Enter your chosen separator: ";
    std::cin >> chosen_separator;

    // Step 5: Parse lines using chosen separator
    std::cout << "\nParsed table:\n";
    for (const auto& line : lines) {
        std::string field;
        for (char c : line) {
            if (c == chosen_separator) {
                std::cout << "[" << field << "] ";
                field.clear();
            } else {
                field += c;
            }
        }
        std::cout << "[" << field << "]\n"; // last field
    }
}
        
     
void html_converter(string& html_text) {
    map<string, string> acepted_tags = 
    {
        {"<html>", "</html>"},
        {"<head>","</head>"},
        {"<body>", "</body>"},
        {"<b>", "</b>"},
        {"<i>", "</i>"},
        {"<a>", "</a>"}
    };

    vector<string> lines;
    map<string, string>::iterator itr;
    for (int i = 0; i < html_text.length(); ++i) {
        if (html_text[i] == '<') {
            string label;
            while (i < html_text.length() && html_text[i] != '>') {
                label += html_text[i];
                ++i;
            }
            label += '>';
            if (acepted_tags.find(label) != acepted_tags.end()) {
                int runner = i + 1;
                string line;
                while (html_text[runner] != '<') {
                    line += html_text[runner];
                    runner++;
                }
                lines.push_back(line);
            }
        }
    }

    for (string &line : lines) {
        cout << line << "\n";
    }
}


//create input to get the data
// iterate over the data if a char is a non-letter, 


int main() {
    //cout << string_counter("alexander alex", "alex") ;
    string st = "<html><a>Hey there</a><a>Hey you</a></html>";
    html_converter(st);
    //csv_enter();
    return 0;
}


