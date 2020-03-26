// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string>
  
#define PORT     8080 
#define MAXLINE 1024 
  
using namespace std;

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    unsigned int len;  
    int n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
    while(true) {
        n = ::recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
        buffer[n] = '\0'; 
        printf("Len: %d\n", n);

        std::string title[24] = { "X Acceleration",
        "Y Acceleration", 
        "Z Acceleration", 
        "X Gravity",
        "Y Gravity",
        "Z Gravity", 
        "X Rotation Rate", 
        "Y Rotation Rate", 
        "Z Rotation Rate", 
        "X Orientation (Azimuth)", 
        "Y Orientation (Pitch)", 
        "Z Orientation (Roll)", 
        "deprecated", 
        "deprecated",
        "Ambient Light",
        "Proximity 1",
        "Proximity 2",
        "Proximity 3",
        "Proximity 4",
        "Proximity 5",
        "Proximity 6",
        "Proximity 7",
        "Proximity 8"};

        int i = 0;
        for (int x = 0; x < n; x += 4) {
            unsigned int tmp;
            memcpy(&tmp, &buffer[x], sizeof(unsigned int));
            unsigned int tmp_swap = ntohl(tmp);
            float f; 
            memcpy(&f, &tmp_swap, sizeof(float));
            printf("%s: %1.4f\n", title[i].c_str(), f);
            i++;
        }
         //sleep(1);
    }
    
      
    return 0; 
}