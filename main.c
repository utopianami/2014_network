
/* Sample TCP server */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>





int main(int argc, char**argv)
{
    int listenfd,connfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;
    char mesg[4096];
    char header[] = "HTTP/1.0 200 OK\r\nDate: Wed, 12 Mar 2014 00:14:10 GMT\r\n\r\n";
    char buf[BUFSIZ];
    
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(32000);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    listen(listenfd,1024);
  
    for(int i = 0; i < 100;i++) {
        clilen=sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        //printf("connected (%d)\n", connfd);
        
        
        char *basicAdd = "/Users/youngnam/Desktop/network/utopia";
        char *plusAdd;
        char finalAdd[100];
        char *split;
        int compare;
        
        if (connfd > 0) {
            //parsing
            int i = 0;
            split = strtok(mesg, " ");
            while (split != NULL) {
                if ( i == 1){
                    plusAdd = split;
                    printf("%s", plusAdd);
                }
                split = strtok(NULL, " ");
                i++;
            }

           //switch 
            compare = strcmp(plusAdd, "/");  
            if (compare == 0){
                sprintf(finalAdd, "%s%s", basicAdd, "/index.html");
            }else{
                sprintf(finalAdd, "%s%s", basicAdd, plusAdd);
            }
            
            n = recv(connfd,mesg,4096,0);
            mesg[n] = 0;
            //printf("=====\n%s=====\n", mesg);
            
            
            send(connfd,header,strlen(header),0);
            int fd = open(finalAdd, O_RDONLY);
            
            while ((n = read(fd, buf, BUFSIZ)) > 0) {
                send(connfd,buf,n,0);
            }
            close(fd);
            close(connfd);
        }
    }
}
