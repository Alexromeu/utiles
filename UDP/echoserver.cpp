#define PORT 22000
#define MAX_SIZE 0x10

#include <array>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


class myserver
{
    int m_fd{};
    struct sockaddr_in m_addr{ };
    struct sockaddr_in m_client{ };

    public:
        explicit myserver(uint16_t port)
        {
            if (m_fd = ::socket(AF_INET, SOCK_DGRAM, 0); m_fd == -1) {
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
            socklen_t client_len = sizeof(m_client);
            return ::recvfrom(
                m_fd,
                buf.data(),
                buf.size(),
                0,
                (struct sockaddr *) &m_client,
                &client_len
            );
        }

        ssize_t send(std::array<char, MAX_SIZE> &buf, ssize_t len)
        {
            if (len >= buf.size()) {
                throw std::out_of_range("len >= buf.size()");
            }

            return ::sendto(
                m_fd,
                buf.data(),
                buf.size(),
                0,
                (struct sockaddr *) &m_client,
                sizeof(m_client)    
            );
        }

        void echo()
        {
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
        }

        ~myserver()
        {
            close(m_fd);
        }

};

int protected_main(int argc, char** argv)
    {
        std::cout << "server running";
        (void) argc;
        (void) argv;
        
        myserver server{PORT};
        server.echo();

        return EXIT_SUCCESS;
    }

int main( int argc, char** argv) 
{
    
    try {
        system("clear");
        std::cout << "Server running: \n";
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