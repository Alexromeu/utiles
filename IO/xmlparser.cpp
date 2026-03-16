#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Parser {
    public:
        Parser(string filename);
        ~Parser() {};
        //files scanned will call methods above on conditions
        void display_info();
        
    private:
        map<string, map<string, string>> attributes; 
        vector<string> body_text;
        vector<string> _lines; 

        void scan_file();
        void nodeTextRead(string text);
        void nodeEnd(string node_name);  
        void nodeStart(string node_name, string line);
        void attribute_read(string node_name, string line);
};

string reverse(string original); 

Parser::Parser(string filename) {
    ifstream file(filename, ios::in);
   
    string line;
    if (!file.is_open()) 
    {
        cout << "error fetching file";
    }

    while (getline(file, line)) {
        this->_lines.push_back(line);
    }
}

void Parser::scan_file() {
    vector<string>lines = this->_lines;
    for (string line : lines) {
        string body_text;
        for (int i = 0; i< line.length(); i++) {
            string tag;
            if (line[i] == '<') {
                string nodeName;
                int runner = i + 1;
                while (runner < line.length() && line[runner] != '>') {
                    nodeName += line[runner];
                    runner++;
                }

                this->nodeStart(nodeName, line);
                int run = i + 1;
                while ( run < line.length() && line[run] != '<') {
                    body_text += line[run];
                    run++;
                }

                if (line[run] == '<' && line[run+1] == '/') {
                    this->nodeEnd(nodeName);
                }
                    this->nodeTextRead(body_text);
                    i = runner;
            }
        }
    }
}

void Parser::nodeStart(string node_name, string line) {
    this->attribute_read(node_name, line);
}

void Parser::attribute_read(string node_name, string line) {
    map<string, string> new_attribute;
    
    for (int i = 0; i < line.length(); i++) {


        if (line[i] == '=') {
            string key;
            string value;
            int runner_left = i - 1;
            int runner_right = i + 1;

            while (runner_left >= 0 && isalpha(line[runner_left])) {
                key += line[runner_left];
                runner_left--;
            }

            while (runner_right < line.length() && 
                   line[runner_right] != '"' && 
                   line[runner_right] != '\'' && 
                   line[runner_right] != ' ') {
                value += line[runner_right];
                runner_right++;
            }

           new_attribute[key] = reverse(value);
        }

        
    }

    this->attributes[node_name] = new_attribute;
   
}

void Parser::nodeTextRead(string text) {
    this->body_text.push_back(text);
}

void Parser::nodeEnd(string nodeName) {
    cout << "end lable" << "\n";
}

void Parser::display_info() {
    this->scan_file();
    vector<string> text = this->body_text;
    cout << "Atributes: " << "\n";
    //iterate over attributes map
    map<string, map<string, string>>::iterator itr = (this->attributes).begin();
    for (itr; itr != (this->attributes).end(); itr++) {
        cout << "Tag -> " << itr->first << "\n";
        map<string, string>::iterator attr_value_itr = (itr->second).begin(); 

        for (attr_value_itr; attr_value_itr != (itr->second).end(); attr_value_itr++) {
            cout << "Atribute: " << attr_value_itr->first << "value: " << attr_value_itr->second << "\n";
        }
    }   

    for (int i = 0; i < text.size(); i++) {
        cout << text[i] << "\n";
    }
}
 
string reverse(string original) {
    string reversed;

    for (int i = 0; i < original.length(); i++) {
        reversed += original[original.length() - i - 1];
    }

    return reversed;
}

int main() {
    Parser file("xmlparser_test.txt");
    file.display_info();
    return 0;
}



// void html_converter(string& html_text) {
//     map<string, string> acepted_tags = 
//     {
//         {"<html>", "</html>"},
//         {"<head>","</head>"},
//         {"<body>", "</body>"},
//         {"<b>", "</b>"},
//         {"<i>", "</i>"},
//         {"<a>", "</a>"}
//     };

//     vector<string> lines;
//     map<string, string>::iterator itr;
//     for (int i = 0; i < html_text.length(); ++i) {
//         if (html_text[i] == '<') {
//             string label;
//             while (i < html_text.length() && html_text[i] != '>') {
//                 label += html_text[i];
//                 ++i;
//             }
//             label += '>';
//             if (acepted_tags.find(label) != acepted_tags.end()) {
//                 int runner = i + 1;
//                 string line;
//                 while (html_text[runner] != '<') {
//                     line += html_text[runner];
//                     runner++;
//                 }
//                 lines.push_back(line);
//             }
//         }
//     }

//     for (string &line : lines) {
//         cout << line << "\n";
//     }
// }



// while (line[i] != '>') {
//                     while (line[i] != '=' && isalpha(line[i])) {
//                         tag+= line[i];
//                     }
                    
//                     if (line[i] == '=') {
//                         string key;
//                         string value;
//                         int runner_left = i - 1;
//                         int runner_right = i + 1;
//                         while (isalpha(line[runner_left])) {
//                             key += line[runner_left];
//                             runner_left--;
//                         }

//                         while (isalnum(line[runner_right])) {
//                             value += line[runner_right];
//                             runner_right++;
//                         }
                        
//                     }
//                 }