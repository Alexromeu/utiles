#include <time.h>
#include <ctime>
#include <iostream>

int main() {
    time_t t = time(nullptr);
   // std::cout << t ;
    const time_t* t_ptr = &t;

    struct tm local_time_str;
    struct tm gm_time_str;

    local_time_str =  *localtime(t_ptr);
    gm_time_str = *gmtime(t_ptr);

    // std::cout << gm_time_str.tm_hour << '\n';
    // std::cout << asctime(&local_time_str) << '\n';
    // std::cout << asctime(&gm_time_str);

    //thread safe
    char buf[256]{};
    strftime(buf, sizeof(buf), "%m/%d/%y  %H:%M:%S", localtime(&t));
    std::cout << buf << '\n';
    std::cout << clock() << '\n';  
    
    return 0;
}