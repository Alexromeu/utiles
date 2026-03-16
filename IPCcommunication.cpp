#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <array>
#include <string_view>
#include <sys/shm.h>
using namespace std;

class pipe_c
{
    array<int, 2> m_handles;

    public:
        pipe_c()
        {
            if (pipe(m_handles.data()) < 0) {
                exit(1);
            }
        }
        
        ~pipe_c()
        {
            close(m_handles.at(0));
            close(m_handles.at(1));
        }

        string read() 
        {
            array<char, 256> buf;
            size_t bytes = ::read(m_handles.at(0), buf.data(), buf.size());

            if (bytes > 0) {
                return { buf.data(), bytes };
            }

            return {};
        }

        void write(const string &msg)
        {
            ::write(m_handles.at(1), msg.data(), msg.size());
        }
};

char* get_shared_memory() 
{
    auto key = ftok("myfile", 42);
    auto shm = shmget(key, 0x1000, 0666 | IPC_CREAT);

    return static_cast<char *>(shmat(shm, nullptr, 0));
}

int main(void) {
    pipe_c p;

    if (fork() != 0) {
        sleep(1);
        cout << "parent\n";

        p.write("done");
        wait(nullptr);

    } else {
        auto msg = p.read();
        cout << "child\n";
        cout << "msg: " << msg << '\n';
    }
}