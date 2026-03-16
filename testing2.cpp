#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    // constexpr auto mode = ios::out | ios::in | ios::trunc; 
    // auto file = fstream("text.txt", mode);
    // string data = " hello there2";
    // string to_write = "to write";
    // //char ch = file.get();
    // // file.seekp(0);
    // // char buf[8] = {};
    // // file.read(buf, 8);
    // // cout << buf << "\n";
    // file.write("hey", 2); 

    // auto path = filesystem::current_path();
    // filesystem::create_directories("test");
    // path /= "test";
    // fstream(path / "text.txt", ios::app);

   


    return 0;
}