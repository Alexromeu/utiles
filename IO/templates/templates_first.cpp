// template <typename T>
// T funct(T var, T var1) {
//     return  var + var1;
// }
#include <vector>
#include <iostream>

template <typename Type> 
Type add_elem(std::vector<Type> elements) {
    Type out;

    for (int i = 0; i < elements.size(); i++) {
        out += elements[i];
    }
    return out; 
}

int main() {
    std::vector<double> v = {2.3, 4.5, 6.4};
    std::vector<int> v1 = {1,2,3,4,5};

    std::cout << add_elem(v) << "\n";
    std::cout << add_elem(v1);
    return 0;
}