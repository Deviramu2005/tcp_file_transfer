#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock=0;
    struct sockaddr_in serv_addr;

    char buffer[BUFFER_SIZE];

    FILE *fp;

    sock=socket(AF_INET,SOCK_STREAM,0);

    if(sock<0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);

    inet_pton(AF_INET,
              "127.0.0.1",
              &serv_addr.sin_addr);

    connect(sock,
           (struct sockaddr *)&serv_addr,
           sizeof(serv_addr));

    fp=fopen("sample.txt","r");

    if(fp==NULL)
    {
        printf("File not found\n");
        return -1;
    }

    int bytesRead;

    while((bytesRead=fread(buffer,
                           1,
                           BUFFER_SIZE,
                           fp))>0)
    {
        send(sock,
             buffer,
             bytesRead,
             0);
    }

    printf("File Transfer Successful\n");

    fclose(fp);

    close(sock);

    return 0;
}
