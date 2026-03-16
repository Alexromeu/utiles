#include <array>
#include <string>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 22000
#define MAX_SIZE 0x10

struct packet
{
    uint64_t len;
    char buf[MAX_SIZE];

    uint64_t data1;
    uint64_t data2;
};

class myserver 
{
    int m_fd{};
    int m_client{};
    struct sockaddr_in m_addr{};  

    public:
        myserver(uint16_t)
        {
            if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1) {
                throw std::runtime_error(strerror(errno));
            }

            m_addr.sin_family = AF_INET;
            m_addr.sin_port = htons(PORT);
            m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

            if (this->bind() == -1) {
                throw std::runtime_error(strerror(errno));
            }
        }

        int bind() 
        {
            return ::bind(
                m_fd,
                reinterpret_cast<struct sockaddr *>(&m_addr),
                sizeof(m_addr)
            );
        }

        ssize_t recv(packet &p)
        {
            return ::recv(
                m_client,
                static_cast<void*>(&p),
                sizeof(p),
                0
            );
        }

        void recv_packet()
        {
            if (::listen(m_fd, 0) == -1) {
                throw std::runtime_error(strerror(errno));
            }

            if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1) {
                throw std::runtime_error(strerror(errno));
            }

            packet p{};

            if (auto len = recv(p); len != 0) {
                auto msg = std::string(p.buf, p.len);
                ssize_t siz = sizeof(p);
                std::cout << "data1: " << p.data1 << '\n';
                std::cout << "data2: " << p.data2 << '\n';
                std::cout << "msg: \"" << msg << "\"\n";
                std::cout << "len: " << len << '\n';
            }

            close(m_client);
        }

        ~myserver() 
        {
            close(m_fd);
        }
};

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    myserver server{PORT};
    server.recv_packet();

    return EXIT_SUCCESS;
}

int
main(int argc, char** argv)
{
    try {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
    }
        return EXIT_FAILURE;
}