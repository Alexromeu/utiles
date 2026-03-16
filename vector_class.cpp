#include <iostream>

using namespace std;

namespace vector_class {

class Vector {
    public:
        Vector();
        Vector(int size);
        ~Vector();

        int get(int index);
        void set(int& index, int& value);
        void pushback(int& element);
        void pushfront(int& element);
        Vector& operator= (const Vector& other);
        Vector (const Vector& other);

    private:
        int _size;
        int _capacity;
        int* vect;
};
}

vector_class::Vector& vector_class::Vector::operator= (const vector_class::Vector& other) {
    if (this->vect == other.vect) {
        return *this;
    }

    _size = other._size;
    _capacity = other._capacity;
    vect = new int[_capacity];

    for (int i = 0; i < _size; ++i) {
        vect[i] = other.vect[i];
    }

    return *this;
    
}

vector_class::Vector::Vector (const vector_class::Vector& other) 
   :_size(other._size), vect(new int[other._size])   
   {
    for (int i = 0; i < _size; i++) {
        vect[i] = other.vect[i];
    }
}

vector_class::Vector::Vector ()
{
    this->_size = 0;
    this->_capacity = this->_size;
    this->vect = new int[32];
}

vector_class::Vector::Vector (int size) 
{
    this->_size = size;
    this->vect = new int[size];
}

int vector_class::Vector::get(int index) {
    return this->vect[index];
}

void vector_class::Vector::set(int& index, int& value) {
    if (_size < 32) {
        for (int i = _size; i > index; i--) {
                vect[i] = vect[i - 1];               
        }
        vect[index] = value;
        _size++;

    } else {
        int* new_vect = new int(_size * 2);
        
        for (int i = 0; i < _size; i++) {
            new_vect[i] = vect[i];
        }

        delete[] vect;
        vect = new_vect;

        for (int i = _size; i > index; i--) {  
            vect[i] = vect[i - 1];               
        }

        vect[index] = value;
        _size++;

    }
}

vector_class::Vector::~Vector() {
    delete[] this->vect;
}

void vector_class::Vector::pushback(int& element) {
    if (_size == _capacity) {
       int* new_vect = new int[_capacity * 2];

       for (int i = 0; i < _size; ++i) {
            new_vect[i] = vect[i];
        }

        delete[] vect;
        vect = new_vect;
        _capacity *= 2;
    }

    vect[_size] = element;
    _size++;
}

void vector_class::Vector::pushfront(int& element) {
    if (_size < _capacity) {
        for (int i = _size; i > 0; --i) {
        vect[i] = vect[i - 1];
        }

        vect[0] = element;
        _size++;

    } else {
        int* new_vect = new int[_capacity * 2];
        for (int i = 0; i < _size; i++) {
            new_vect[i + 1] = vect[i];
        }
        delete[] vect;
        vect = new_vect;
        vect[0] = element;
        _size++;
    }
}

int main() {

    vector_class::Vector v;
    int elem = 1;
    int elem2 = 2;
    int elem3 = 3;
    v.pushback(elem);
    v.pushback(elem2);
    v.pushback(elem3);

    vector_class::Vector b;
    b = v;

    cout << b.get(0) ;
    cout << b.get(1) ;
    cout << b.get(2) ;


    return 0;
}