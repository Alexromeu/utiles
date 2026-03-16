// #include <thread>
// #include <iostream>
// class myclass
// {
//     int m_data{0};
//     public:
//         ~myclass()
//         {
//             std::cout << "myclass deleted\n";
//         }

//         void inc()
//         { 
//             m_data++;
//         }
// };

// std::thread t1;
// std::thread t2;

// void thread2(myclass *ptr)
// {
//     for (auto i = 0; i < 100000; i++) {
//         ptr->inc();
//     }
   
//     std::cout << "thread2: complete\n";
// }

// void thread1()
// {
//     auto ptr = std::make_unique<myclass>();
//     t2 = std::thread(thread2, ptr.get());
    
//     for (auto i = 0; i < 10; i++) {
//         ptr->inc();
//     }
//         std::cout << "thread1: complete\n";
// }

// int main()
// {
//     t1 = std::thread(thread1);
//     t1.join();
//     t2.join();
// }

#include <thread>
#include <iostream>
#include <memory>

class myclass
{
    int m_data{0};
    public:
        ~myclass()
        {
            std::cout << "myclass deleted\n";
        }
            void inc(){ m_data++; }
};

std::thread t1;
std::thread t2;

void thread2(const std::shared_ptr<myclass> ptr)
{
    for (auto i = 0; i < 100000; i++) {
        ptr->inc();
    }
    std::cout << "thread2: complete\n";
}

void thread1()
{
    auto ptr = std::make_shared<myclass>();
    t2 = std::thread(thread2, ptr);
    for (auto i = 0; i < 10; i++) {
        ptr->inc();
    }
    
    std::cout << "thread1: complete\n";
}

int main()
{
    t1 = std::thread(thread1);
    t1.join();
    t2.join();
}
// g++ -std=c++17 -lpthread scratchpad.cpp; ./a.out
// thread1: complete
// thread2: complete
// myclass deleted

