#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

using namespace std;

int main()
{
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("cannot create socket"); 
        return 0; 
    }
    cout << "Successfully create TCP socket" << std::endl;

    sockaddr_in address;
    const int PORT = 8080;

    memset((char *)&address, 0, sizeof(address)); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); //The IP of the server (0.0.0.0)
    address.sin_port = htons(PORT); 

    if (::bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) 
    { 
        perror("bind failed"); 
        return 0; 
    }

    cout << "Successful bind TCP socket to port 8080" << std::endl;

    if (listen(server_fd, 3) < 0) 
    { 
        perror("In listen"); 
        exit(EXIT_FAILURE); 
    }

    cout << "Server now listen to incomming connections on port 8080" << std::endl;

    int new_socket;
    int addrlen = sizeof(address);

    while(true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");            
            exit(EXIT_FAILURE);        
        }

        char buffer[1024] = {0};

        int valread = read( new_socket , buffer, 1024); 
        printf("%s\n",buffer );
        if(valread < 0) 
        { 
            printf("No bytes are there to read");
        }
        
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

        write(new_socket , hello , strlen(hello));
    
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
   
}