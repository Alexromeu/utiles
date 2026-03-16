#include <array>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_SIZE 0x10
#define PORT 22000

struct packet
{
    uint64_t len;
    char buf[MAX_SIZE];

    uint64_t data1;
    uint64_t data2;
};

class myclient
{
    int m_fd{};
    struct sockaddr_in m_addr{};

public:
    explicit myclient(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1) {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if (connect() == -1) {
            throw std::runtime_error(strerror(errno));
        }
    }

    int connect()
    {
        return ::connect(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr)
        );
    }

    ssize_t send(packet &p)
    {
        
        return ::send(
            m_fd,
            static_cast<void *>(&p),
            sizeof(p),
            0
        );
    }

    void send_packet()
    {
        auto msg = std::string("hello world");
        packet p = {
            msg.size(),
            {},
            42,
            43
        };

        memcpy(p.buf, msg.data(), msg.size());
        send(p);
        
    }

    ~myclient()
    {
        close(m_fd);
    }
};

int protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    std::cout << "client running \n";
    myclient client{PORT};
    client.send_packet();

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    
    try{
        system("clear");
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