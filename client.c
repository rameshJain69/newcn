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
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(5040);
	
	//connect
	connect(cs,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	//requesting file
	printf("Enter the srcfile name:- ");
	char str[60];
	scanf("%s",str);
	
	write(cs,str,60);
	
	//Read
	int n;
	char rec[60];
	while((n = read(cs,rec,60)) != 0){
		printf("%s",rec);
	}
	
	close(cs);
	return 0;
}
