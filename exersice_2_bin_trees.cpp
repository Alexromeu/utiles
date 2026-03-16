#include <iostream>
#include <string>

using namespace std;

struct book {
    string name;
    string email;
    book* book_left;
    book* book_right;
};



book* insert(book* p_book, string name, string email) {
    if (p_book == nullptr) {
        book* new_p_book = new book;
        new_p_book->name = name;
        new_p_book->email = email;

        return new_p_book;
    }

    if (name < p_book->name) {
        p_book->book_left = insert(p_book->book_left,name, email);

    } else {
        p_book->book_right = insert(p_book->book_right, name, email);
    }

    return p_book;
}

string search(book *p_book, string name) {
    if (p_book == nullptr) {
        return "Not Found";
    }

    if (p_book->name == name) {
        return p_book->email;
    }

    if (name < p_book->name) {
        return search(p_book->book_left, name);
    } else {
        return search(p_book->book_right, name);
    }
}

void destroy(book* p_book) {
    if (p_book != nullptr) {
        destroy(p_book->book_left);
        destroy(p_book->book_right);
        delete p_book;
    }
}



int main() {


    return 0;
}

