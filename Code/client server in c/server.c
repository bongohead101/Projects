// A simple server in the internet domain using TCP
// The port nu1mber is passed as an argument

// Please note this is a C program
// It compiles without warnings with gcc

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


void error(char *msg)
{
    perror(msg);
    exit(1);
}

struct info{ // to make an array of these
	char major[256];
	int early,mid;
};

int findmajor(struct info[],char []);

void printarr(struct info[]);

void getinfo(struct info[], int, char[]);

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];char inputfile[255];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc != 3) {
         fprintf(stderr,"ERROR, no port or filename/path provided \nAssuming manual entry...\n");
	 char begun[255];
	 printf("Enter the name of the Data file: ");
	 fgets(inputfile,255,stdin);
	 if(inputfile[0]!='\n'){
		strcpy(inputfile, strtok(inputfile,"\n"));
	 }else{
		error("Empty Filename!\n");
	 }

	 printf("Enter server port number: ");
	 fgets(begun,255,stdin);
         portno = atoi(begun);
	 printf("\n");
     }else{
	strcpy(inputfile,argv[2]);
	portno = atoi(argv[1]);
     }
     
/////////////////////////////////////////////////////////
//make the info array
	struct info arr[512]; int i =0;
	///////////////////////////////////
	//file reading		//https://www.tutorialspoint.com/cprogramming/c_file_io.htm
		FILE *fp; char buff[256];	// creating file pointer and temp varriable to hold string
		fp = fopen(inputfile, "r");	// opens file on argument 2
		while(fgets(buff,256,(FILE*)fp)&& i <512){		//reads each line til \n or eof
			///////////////////////////////
			//split string
			char *ch;
			ch = strtok(buff, "\t");
			while (ch != NULL) {
			strncpy(arr[i].major,ch,256); //for the major
			//printf("%s\n", ch);
			ch = strtok(NULL, "\t");

			arr[i].early = atoi(ch);// for early pay
                        //printf("%s\n", ch);
                        ch = strtok(NULL, "\t");

			arr[i].mid = atoi(ch);// for mid pay
                        //printf("%s\n", ch);
                        ch = strtok(NULL, "\t");
  			}
			///////////////////////////////

			//strncpy(arr[i].major,buff,256);		//copy string to object major
			//printf("%s",arr[i].major);
			i = i+1;
		}

	///////////////////////////////////

/////////////////////////////////////////////////////////



     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
//     portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
	// first while start
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
	//tutorial while is here
  while(1){
	printf("Waiting for connection\n");
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0) 
          error("ERROR on accept");
	printf("Connected ...\n");
  //do{
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
  
	// second while here (read in the information and else)
     if (n < 0) error("ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);
     printf("Looking for message in DB...\n");
     int t = findmajor(arr,buffer);
     char tem[256];
     getinfo(arr,t,tem);

     if(t>-1){
	printf("Found result at index number: %i\n",t);
	printf("Info for \"%s\" is: %s\n",buffer,tem);
	printf("Sending info to client\n");
	n = write(newsockfd,tem,255);
	printf("info sent!\n\n");

     }else if(buffer[0]=='\n'){
	printf("Sending goodbye\n");
	n = write(newsockfd,"Recieved closing symbol...Goodbye!",255);
	printf("Exit character detected\nClearing connection \n\n\n");

     }else{
	printf("Did not find result \"%s\"\tReturning null...\n",buffer);
	printf("Sending info to client\n");
	n = write(newsockfd,tem,255);
	printf("Sent NULL!\n\n");

     }
     //n = write(newsockfd,"I got your message",18);
   
     if (n < 0) error("ERROR writing to socket");
  

  //}while(strcmp(buffer,"\n"));
	
	//printf("Exit character detected\nClearing connection \n\n\n");
 }

 return 0;
}
int findmajor(struct info arr[],char major[]){

    if(major[0]!= '\n'&& major[0]!= '\0'){
	for(int i=0; i< 512; i++){
		if(arr[i].major[0] == '\0'){
			break;
		}
		
		if(strcmp(arr[i].major,strtok(major,"\n"))==0){
			return i;
		}
	}
    }
	return -1;
}

void printarr(struct info arr[]){
	for(int i=0;arr;i++){       //print out the items in the array
                        if(arr[i].major[0] == '\0'){
                                break;
                        }
                        printf("%s: early:%i mid:%i\n",arr[i].major,arr[i].early,arr[i].mid);
                        i++;
        }	
}

void getinfo(struct info arr[],int index,char result[]){
	if(index != -1){
		char one[12];
		char two[12];
		sprintf(one, "%d",arr[index].early);
		sprintf(two, "%d",arr[index].mid);
		strcpy(result,one);
		strcat(result,",");
		strcat(result,two);

	}else{ 
		strcpy(result,"null,null");
	}
	
}

