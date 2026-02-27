#define _POSIX_C_SOURCE 200809L
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int create_client(const char *ip, const char *port) {
    struct addrinfo hints, *res, *rc;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(ip, port, &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        return -1;
    }

    int fd = -1;

    for (rc = res; rc != NULL; rc = rc->ai_next) {
        fd = socket(rc->ai_family, rc->ai_socktype, rc->ai_protocol);
        if (fd < 0) {
            continue;
        }

        if (connect(fd, rc->ai_addr, rc->ai_addrlen) == 0) {
            freeaddrinfo(res);
            return fd;
        }
        
        close(fd);
        fd = -1;
        
    }
    freeaddrinfo(res);
    return -1;
}

char* gen_message(char* filename, char* ip, char* port) {
    char* message = malloc(1024);
    snprintf(message, 1024, 
    "GET /file/%s HTTP/1.1\r\n" "Host: %s:%s\r\n" "Connection: close\r\n" "\r\n", filename, ip, port);
    return message;
}

char* add_string_plus_nums(char* s1, int n1) {
    int n2 = atoi(s1);
    int n3 = n1 + n2;
    char *s3 = malloc(16);
    snprintf(s3, 16, "%d", n3);
    return s3;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Only 2 arguments\n");
        return -1;
    }
    printf("IP: %s\n", argv[1]);
    printf("PORT: %s\n", argv[2]);

    char* ip = argv[1];
    char* port = argv[2];
    
    
    char *buf = malloc(1024);
    char* message = gen_message("data", ip, port);
    printf("Message ready!\n");
    
    for (int i = 0; i < 20; i++) {
        
        int fd = create_client(ip, port);
        if (fd < 0) { 
            printf("client %d failed to connect\n", i); 
            
            continue; 
        }
        
        send(fd, message, strlen(message), 0);

        printf("message sent");
        
        int r;  
        while ((r = recv(fd, buf, 1023, 0)) > 0) {
            buf[r] = '\0';
            printf("client %d response: \n%s\n", i, buf);
        }
        close(fd);
    }
    free(message);      
    free(buf);
    
    return 0;
}

