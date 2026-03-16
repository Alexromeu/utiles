#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void add_element(map<string, string>& book, string& name, string& email) {
    book[name] = email;
    cout << "element added successfuly" << endl;
}

void remove_element(map<string, string> &book, string& name) {
    map<string, string>::iterator itr = book.find(name);
    if (itr != book.end()) {
        book.erase(name);
    }
}

void change_element(map<string, string> &book, string& name, string& email) {
    map<string, string>::iterator itr = book.find(name);
    if (itr != book.end()) {
        book[name] = email;
    } else {
        cout << "element not found" << "\n";
    }
}

void display_entries(map<string, string> &book) {
    map<string, string>::iterator itr;

    for (map<string, string>::iterator itr = book.begin(); itr != book.end(); ++itr) {
        cout << "Displaying Users: " << "\n";
        cout << "Name --> "<< itr->first << "|" << "Address --> " << itr->second << "\n";
    }
}

void show_user_info(map<string, string> &book, string name) {
    map<string, string>::iterator itr = book.find(name);

    if (itr != book.end()) {
        cout << "Name: " << itr->first << "Address: " << itr->second;
    } else {
        cout << "User Not Found";
    }
}

void show_menu() {
    cout << "select an option: " << endl;
    cout << "1. add user" << endl;
    cout << "2. edit user" << endl;
    cout << "3. remove User" << endl;
    cout << "4. show user" << endl;
    cout << "5. Display all users" << endl;
    cout << "6. EXIT" << endl;
}

int main() {
    int choice;
    bool running = true;

    map<string, string> address_book;

    while (running) {
        show_menu();
        cin >> choice;
        switch (choice)
        {
        case 1: {
            string name;
            string email;
            cout << "Enter Name: " << endl;
            cin >> name;
            cout << "Enter email: " << endl;
            cin >> email;
            add_element(address_book, name, email);
            break;
            }

        case 2: {
            string name;
            string email;

            cout << "To edit a user and email, please enter the name and then the email: ";
            cout << "Name: " << endl;
            cin >> name;
            cout << "New Email" << endl;
            cin >> email;
            change_element(address_book, name, email);
            cout << "Email succesfully added";
            break;
        }

        case 3: {
            string name;
            cout << "to remove user enter name." << endl;
            cout << "Name: " << endl;
            cin >> name;
            remove_element(address_book, name);
            break;
        }

        case 4: {
            string name;
            cout << "To see a user enter its name: " << endl;
            cout << "Name: " << endl;
            cin >> name;
            show_user_info(address_book, name); 
            break;
        }

        case 5:
            cout << "All Users: " << endl;
            display_entries(address_book);
            break;
        case 6: {
            while (true) {
                string option;
                cout << "are you sure you want to exit ?:" << endl;
                cout << "Y" << "|" << "N" << endl;
                cin >> option;

            
                if (option == "Y" || option == "y") {
                    running = false;
                    break;

                } else if (option == "N" || option == "n") {
                    break;

                } else {
                    cout << "Comand not recognize, try again";
                    break;
                }
            }
            
        }
            
        default:
            break;
        }
    }






    return 0;
}

//create a map for the address and names
//create function to remove entries
//create function to change entries
//create function to list entries