#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int cs = socket(AF_INET,SOCK_STREAM,0);
	
	//structure
	
	struct sockaddr_in serv_addr,cli_addr;
	
	//create socket
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(5040);
	
	
	//binding

	printf("BINDED/n");
	bind(cs,(struct sockaddr *)&serv_addr,sizeof(serv_addr));	
	
	//listen
	printf("listening\n\n");
	listen(cs,3);
	int clength = sizeof(cli_addr);
	printf(" clength :: %d \n",clength);
	
	int ns = accept(cs,(struct sockaddr *)&cli_addr,&clength);
	
	//Reading request
	char str[60];
	read(ns,&str,60);
	
	printf("Client msg file name :: %s \n",str);
	
	FILE* f1 = fopen(str,"r");
	
	//Sending response
	char buff[4096];
	int cnt = 0;
	while(fgets(buff,4096,f1) != NULL){
		write(ns,buff,60);
		cnt++;
	}
	
	printf("Total loops :: %d", cnt);
	
	fclose(f1);
	close(cs);
	
	printf("File successfully transferred\n");
				 
	return 0;
}
