#include <iostream>
#include <vector>

template<typename T, std::size_t Alignment = 0x40>
class myallocator
{
    public:
        using value_type = T;
        using pointer = T *;
        using size_type = std::size_t;
        using is_always_equal = std::true_type;

        template<typename U> 
        struct rebind 
        {
            using other = myallocator<U, Alignment>;
        };

    public:
        myallocator()
        { }

        template <typename U>
        myallocator(const myallocator<U, Alignment> &other) noexcept
        { (void) other; } 

        pointer allocate(size_type n) 
        {
            if (auto ptr = aligned_alloc(Alignment, sizeof(value_type) * n)) {
                return static_cast<pointer>(ptr);
            }

            throw std::bad_alloc();
        }

        void deallocate(pointer p, size_type n)
        {
            (void) n;
            free(p);
        }
};

int main() {
    myallocator<int> uno;
    myallocator<int> myalloc(uno);

    auto ptr = myalloc.allocate(42);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 42);

    std::vector<int, myallocator<int>> myvector;
    myvector.emplace_back(42);
    std::cout << myvector.data();


    

    return 0;
}