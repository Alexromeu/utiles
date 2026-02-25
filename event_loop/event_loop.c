#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <aio.h>
#include <errno.h>

#define BUF_SIZE 1024
#define PORT "2000"
#define MAX_TEXT_SIZE 4096

char* get_time() {
    time_t timep;
    timep = time(NULL);
    char* tim_str = ctime(&timep);

    return tim_str;
} 

int async_receive(int fd, char* buf, int buf_size, struct aiocb *aiocbp) { 
    memset(aiocbp, 0, sizeof(*aiocbp));

    aiocbp->aio_buf = buf;
    aiocbp->aio_fildes = fd;
    aiocbp->aio_nbytes = buf_size;
    aiocbp->aio_offset = 0;
    aiocbp->aio_reqprio = 0;
    aiocbp->aio_lio_opcode = 0;
    aiocbp->aio_sigevent.sigev_notify = SIGEV_NONE;

    int r = aio_read(aiocbp);
    if (r < 0) 
        perror("Async read error");
    
    return r;
}

int async_send(int fd, char* buf, int buf_size, struct aiocb *aiocbp) { 
    
    memset(aiocbp, 0, sizeof(*aiocbp));

    aiocbp->aio_buf = buf;
    aiocbp->aio_fildes = fd;
    aiocbp->aio_nbytes = buf_size;
    aiocbp->aio_offset = 0;
    aiocbp->aio_reqprio = 0;
    aiocbp->aio_lio_opcode = 0;
    aiocbp->aio_sigevent.sigev_notify = SIGEV_NONE;

    int w = aio_write(aiocbp);
    if (w < 0) 
        perror("Async write error");
    
    return w;
}

char* extract_filename(char* req) {
    char *end = strstr(req, "\r\n");
    size_t len = end - req;

    char request_line[1024];
    memcpy(request_line, req, len);
    request_line[len] = '\0';

    char method[16], path[1024], version[16];
    sscanf(request_line, "%s %s %s", method, path, version);

    if (strncmp(path, "/file/", 6) == 0) {
        char *name = path + 6;
        printf("Requested name: %s\n", name);
        return name;
    }
    perror("Error extracting file name");
    return "Error extracting file name";
}

char* read_file(char* file_nam) {
    char path[1024];
    snprintf(path, sizeof(path), "./%s", file_nam);
    struct stat statbuf;
    
    int fd = open(path, O_RDONLY);

    if (fd <= 0) {
        perror("Unable to read");
        return "Unable to read"; 
    }

    if (fstat(fd, &statbuf) < 0) {
        perror("Unable to get file info");
        return "Unable to get file info";
    }

    int file_size = statbuf.st_size;
    char* output_text = malloc(file_size + 1);

    if (!output_text) { 
        close(fd); 
        perror("Memory error");
        return "Memory error"; 
    }

    int total_bytes = 0;
    while (total_bytes < file_size) { 
        ssize_t curr = read(fd, output_text + total_bytes, file_size - total_bytes);
        if (curr <= 0) break;
        total_bytes += curr;

    }
     
    output_text[file_size] = '\0';
    return output_text;
}

char* generate_response(char* body) {
    char* time_resp = get_time();
    int body_len = strlen(body);
    char* new_respond = malloc(MAX_TEXT_SIZE);
    int total_len = body_len + 100;
    snprintf(new_respond, MAX_TEXT_SIZE, "HTTP/1.1 200 OK\r\n" "Content-Type: text/plain\r\n" "Content-Length: %d\r\n" "%s\n" "%s\n" "\r\n" 
        ,total_len, time_resp, body);

    return new_respond;
}

int create_server(char* port) {
    int                      sfd, s, acc_sck;
    char                     buf[BUF_SIZE];
    socklen_t                peer_addrlen;
    struct addrinfo          hints;
    struct addrinfo          *result, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    s = getaddrinfo(NULL, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  

        close(sfd);
    }

    if (rp == NULL) {
        perror("Could not bind");
        return -1;
    }
    freeaddrinfo(result);

    if (listen(sfd, 10) < 0) {
        perror("error with listen");
        return -1;
    }
    printf("Waiting...\n");

    return sfd;
    
}


int main() {
    int listen_fd = create_server(PORT);
    int clients[FD_SETSIZE];
    int num_clients = 0;

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(listen_fd, &readfds);
        int maxfd = listen_fd;

        for (int i = 0; i < num_clients; i++) {
            FD_SET(clients[i], &readfds);
            if (clients[i] > maxfd)
                maxfd = clients[i];
        }

        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("error with select()");
            break;
        }

        // new connection?
        if (FD_ISSET(listen_fd, &readfds)) {
            struct sockaddr_storage peer;
            socklen_t peer_len = sizeof(peer);
            int client_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
            if (client_fd >= 0)
                clients[num_clients++] = client_fd;
        }
        
        // existing clients
        for (int i = 0; i < num_clients; ) {
            int fd = clients[i];
            if (FD_ISSET(fd, &readfds)) {
                char buf[BUF_SIZE];
                struct aiocb aiocbp_rec; 
                struct aiocb aiocbp_sen;
                //ssize_t n = recv(fd, buf, BUF_SIZE - 1, 0);
                int n = async_receive(fd, buf, sizeof(buf), &aiocbp_rec);

                if (n < 0) {
                    close(fd);
                    clients[i] = clients[--num_clients];
                    continue;
                }

                while (aio_error(&aiocbp_rec) == EINPROGRESS) {
                    ;
                }

                n = aio_return(&aiocbp_rec);
                
                buf[n] = '\0';

                if (strstr(buf, "\r\n\r\n")) {
                    char* filename = extract_filename(buf);
                    char* filedata = read_file(filename);
                    char *resp = generate_response(filedata);

                    printf("Data ready to send\n");
                    ssize_t s = async_send(fd, resp, strlen(resp), &aiocbp_sen);
                    while (aio_error(&aiocbp_sen) == EINPROGRESS) {
                    ;
                    }

                    printf("bytes sent: %ld\n", s);
                    

                    free(resp);
                    close(fd);
                    clients[i] = clients[--num_clients];
                    continue;
                }
            }
            i++;
        }
    }
    close(listen_fd);
    return 0;
}
