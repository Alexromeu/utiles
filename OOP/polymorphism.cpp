#include <iostream>
#include <vector>
using namespace std;

class StringConvertible {
    public: 
        virtual string toString() = 0;
        virtual ~StringConvertible() {}; 
};

class User : public StringConvertible {
    public:
        string toString();
        void setName(string n);
    private:
        string name;
};

void User::setName(string n) {
    this->name = n;
}

string User::toString() {
    return name;
}

void log(StringConvertible& user) {
    cout << user.toString();
}

int main() {
    User u;
    u.setName("alex");
    log(u);

    return 0;
}