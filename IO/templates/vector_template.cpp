#include <iostream>
#include <iomanip>

using namespace std;

namespace vector_class {
template <typename Type> class Vector {
    public:
        Vector();
        Vector(int size);
        ~Vector();

        Type get(int index);
        void set(int& index, Type& value);
        void pushback(Type& element);
        void pushfront(Type& element);
        Vector& operator= (const Vector& other);
        Vector (const Vector& other);

    private:
        int _size;
        int _capacity;
        Type* vect;
};
}
template<typename Type>
vector_class::Vector<Type>& vector_class::Vector<Type>::operator= (const vector_class::Vector<Type>& other) {
    if (this->vect == other.vect) {
        return *this;
    }

    _size = other._size;
    _capacity = other._capacity;
    vect = new Type[_capacity];

    for (int i = 0; i < _size; ++i) {
        vect[i] = other.vect[i];
    }

    return *this;
    
}

template<typename Type>
vector_class::Vector<Type>::Vector (const vector_class::Vector<Type>& other) 
   :_size(other._size), vect(new Type[other._size])   
   {
    for (int i = 0; i < _size; i++) {
        vect[i] = other.vect[i];
    }
}

template<typename Type>
vector_class::Vector<Type>::Vector ()
{
    this->_size = 0;
    this->_capacity = this->_size;
    this->vect = new Type[32];
}

template <typename Type>
vector_class::Vector<Type>::Vector (int size) 
{
    this->_size = size;
    this->vect = new int[size];
}

template <typename Type>
Type vector_class::Vector<Type>::get(int index) {
    return this->vect[index];
}

template <typename Type>
void vector_class::Vector<Type>::set(int& index, Type& value) {
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

template<typename Type>
vector_class::Vector<Type>::~Vector() {
    delete[] this->vect;
}


template<typename Type>
void vector_class::Vector<Type>::pushback(Type& element) {
    if (_size == _capacity) {
       Type* new_vect = new Type[_capacity * 2];

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

template<typename Type>
void vector_class::Vector<Type>::pushfront(Type& element) {
    if (_size < _capacity) {
        for (int i = _size; i > 0; --i) {
        vect[i] = vect[i - 1];
        }

        vect[0] = element;
        _size++;

    } else {
        Type* new_vect = new Type[_capacity * 2];
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

    vector_class::Vector<int> v;
    int elem = 1;
    int elem2 = 2;
    int elem3 = 3;
    v.pushback(elem);
    v.pushback(elem2);
    v.pushback(elem3);

    vector_class::Vector<int> b;
    b = v;

    cout << setw(10) << right << b.get(0) ;
    cout << b.get(1) ;
    cout << b.get(2) ;


    return 0;
}