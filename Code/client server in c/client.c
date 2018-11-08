// Please note this is a C program
// It compiles without warnings with gcc
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char hostname[256];

    if (argc != 3) {
       fprintf(stderr,"usage %s hostname port\nAssuming Manual entry...\n", argv[0]);
       char begun[255];
         printf("Enter server host name: ");
         fgets(begun,255,stdin);
         if(begun[0]!='\n'){
                strcpy(hostname, strtok(begun,"\n"));
         }else{
                error("Empty host name!\n");
         }

         printf("Enter server port number: ");
         fgets(begun,255,stdin);
         portno = atoi(begun);
	 printf("\n");
    }else{
	strcpy(hostname,argv[1]);
	portno = atoi(argv[2]);
    }
//    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    /*if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    */
    char temp[256];    

    do{
    printf("Enter a college major: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);

    if(buffer[0]=='\n'){break;}

    strcpy(temp,buffer);//copy to not change the buffer
    strtok(temp,"\n");//take off the newline of the major14
	///////////////////////////////////////////
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)error("ERROR opening socket");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
        serv_addr.sin_port = htons(portno);

	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

	//////////////////////////////////////////
/*
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    strcpy(temp,buffer);
    */

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");

   // buffer[0] = '\0';
   // memset(&buffer,0,256);
   bzero(buffer,256);

    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");

    do{
	if(buffer[0]=='\0' && buffer[0]=='\n'){
	    bzero(buffer,256);
	    n = read(sockfd,buffer,255);
	    if (n < 0)
        	 error("ERROR reading from socket");
	}else{
	  //print out all the info
	  char *ch;
	  char bfr[256];
	  strncpy(bfr,buffer,255);
	  char early[12];char mid[12];
//	printf("Here?");
          ch = strtok(bfr, ",");
	  strncpy(early,ch,12);
	  ch = strtok(NULL, " ");
	  strncpy(mid,ch,12);
	  if(strcmp(early,"null\0")){
	  	printf("The average early career for a %s major is $%s\nThe corresponding mid-career pay is $%s\n\n",temp,early,mid);
	  }else{
	  	printf("That major is not in the table\n\n");
	  }
	  break;
	}

    }while(1/*buffer[0]!='\0' && buffer[0]!='\n'*/);
   
	close(sockfd); 

    }while(strcmp(temp,"\n"));

    printf("Exit character Detected...\n\nNow closing program\n\n\n");

    return 0;
}
