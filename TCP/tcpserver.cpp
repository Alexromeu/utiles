#define PORT 22000
#define MAX_SIZE 0x10

#include <array>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

class myserver
{
    int m_fd{};
    int m_client{};
    struct sockaddr_in m_addr{};

    public:
        myserver(uint16_t port) 
        {
            if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1) {
                throw std::runtime_error(strerror(errno));
            }

            m_addr.sin_family = AF_INET;
            m_addr.sin_port = htons(port);
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

        ssize_t recv(std::array<char, MAX_SIZE> &buf)
        {
            return ::recv(
                m_client,
                buf.data(),
                buf.size(),
                0
            );
        }

        ssize_t send(std::array<char, MAX_SIZE> &buf, ssize_t len)
        {
            if (len >= buf.size()) {
                throw std::out_of_range("len >= buf.size()");
            }

            return ::send(
                m_client,
                buf.data(),
                len,
                0
            );
        }

        void echo()
        {
            if (::listen(m_fd, 0) == -1) {
                throw std::runtime_error(strerror(errno));
            }

            if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1) {
                throw std::runtime_error(strerror(errno));
            }

            while (true) 
            {
                std::array<char, MAX_SIZE> buf{};

                if (auto len = recv(buf); len != 0) {
                    send(buf, len);
                } 
                else {
                    break;
                }
            }

            close(m_client);
        }

};

int protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    myserver server{PORT};
    server.echo();

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
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