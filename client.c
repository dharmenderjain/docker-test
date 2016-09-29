#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 
    struct hostent* host;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    FILE *f = fopen("/tmp/client.log", "w+");
    if (f == NULL)
    {
        printf("Error opening file!\n");
    	exit(1);
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
    	host = gethostbyname(argv[1]);
	serv_addr.sin_addr.s_addr = *(long*)host->h_addr_list[0];
        //printf("\n inet_pton error occured\n");
        //return 1;
    } 

    while(1) {
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            fprintf(f,"\n Error : Could not create socket \n");
            return 1;
        } 
        if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
           fprintf(f,"\n Error : Connect Failed \n");
           return 1;
        } 
    
        while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
            recvBuff[n] = 0;
            if(fputs(recvBuff,f) == EOF)
            {
                fprintf(f,"\n Error : Fputs error\n");
            }
	   fflush(f);
        } 
    
        if(n < 0)
        {
            fprintf(f,"\n Read error \n");
        } 
	close(sockfd);
        sleep(5);
    }
    return 0;
}
