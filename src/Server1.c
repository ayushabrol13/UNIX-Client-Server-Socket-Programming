#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256

char *calculate_function(char *expr);

int main(int argc, char *argv[])
{
    int sockfd, portnum, new_socket, n;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    int addrlen = sizeof(server_addr);
    char inputbuf[MAX_INPUT_SIZE];

    if (argc < 2)
    {
        fprintf(stderr, "usage %s <server-ip-addr> <server-port>\n", argv[0]);
        exit(0);
    }
    portnum = atoi(argv[1]);

    /* Create server socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0)
    {
        fprintf(stderr, "ERROR opening socket\n");
        exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        fprintf(stderr, "ERROR setsockopt\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;

    if (!inet_aton("127.0.0.1", &server_addr.sin_addr))
    {
        fprintf(stderr, "ERROR invalid server IP address\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_port = htons(portnum);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    /* Bind server socket */
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "ERROR on binding\n");
        exit(1);
    }
    if (listen(sockfd, 0) < 0)
    {
        fprintf(stderr, "ERROR on listen\n");
        exit(1);
    }

    client_addr_size = sizeof(struct sockaddr_in);

    if ((new_socket = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size)) < 0)
    {
        perror("accept");
        exit(1);
    }

    close(sockfd);
    do
    {
        bzero(inputbuf, MAX_INPUT_SIZE);
        n = read(new_socket, inputbuf, MAX_INPUT_SIZE);
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("Connected with client socket number %d\n", new_socket - 3);
        printf("Client socket %d sent message: %s\n", new_socket - 3, inputbuf);
        char *answer;
        answer = calculate_function(inputbuf);
        n = write(new_socket, answer, sizeof(answer));
        if (n < 0)
        {
            perror("ERROR writing to socket");
            exit(1);
        }
        printf("Sending Reply: %s\n", answer);

    } while (1);

    close(new_socket);

    return 0;
}

char *calculate_function(char *expr)
{
    char *result = (char *)malloc(50);
    int a = 0, b = 0;

    int i = 0;

    while (isdigit(expr[i]))
    {
        a = a * 10 + (expr[i] - '0');
        i++;
    }

    char op = expr[i];

    i++;

    while (expr[i] != '\n' && expr[i + 1] != '\0')
    {
        b = b * 10 + (expr[i] - '0');

        i++;
    }

    switch (op)
    {
    case '+':
        a = a + b;
        break;
    case '-':
        a = a - b;
        break;
    case '*':
        a = a * b;
        break;
    case '/':
        a = a / b;
        break;
    case '%':
        a = a % b;
        break;
    }

    sprintf(result, "%d", a);

    return result;
}