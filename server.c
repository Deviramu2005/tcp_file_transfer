#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);

    char buffer[BUFFER_SIZE];

    FILE *fp;

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    if(server_fd<0)
    {
        perror("Socket failed");
        exit(1);
    }

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    listen(server_fd,3);

    printf("Waiting for connection...\n");

    new_socket=accept(server_fd,
                      (struct sockaddr *)&address,
                      (socklen_t*)&addrlen);

    printf("Client connected\n");

    fp=fopen("received.txt","w");

    if(fp==NULL)
    {
        printf("File creation error\n");
        exit(1);
    }

    int bytes;

    while((bytes=recv(new_socket,
                      buffer,
                      BUFFER_SIZE,
                      0))>0)
    {
        fwrite(buffer,1,bytes,fp);
    }

    printf("File Transfer Successful\n");

    fclose(fp);

    close(new_socket);
    close(server_fd);

    return 0;
}
