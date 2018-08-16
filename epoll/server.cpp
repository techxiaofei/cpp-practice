#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
 
#define	MAX_EPOLL		1000
#define	BUF_SIZE		1024
#define PORT			6000
 
 
int setnonblocking( int fd )
{
	if( fcntl( fd, F_SETFL, fcntl( fd, F_GETFD, 0 )|O_NONBLOCK ) == -1 )
	{
		printf("Set blocking error : %d\n", errno);
		return -1;
	}
	return 0;
}
 
int main( int argc, char ** argv )
{
	int 		listen_fd;
	int 		conn_fd;
	int 		epoll_fd;
	int 		nread;
	int		i;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	struct 	epoll_event	ev;  //监听fd
	struct 	epoll_event	events[MAX_EPOLL];
	char 	buf[BUF_SIZE];
	socklen_t	len = sizeof( struct sockaddr_in );
	
	bzero( &servaddr, sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servaddr.sin_port = htons( PORT );
	
	if( ( listen_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
	{
		printf("socket error : %d\n" , errno );
		exit( EXIT_FAILURE );
	}
	
	if( setnonblocking( listen_fd ) == -1 )
	{
		printf("setnonblocking error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
	
	if( bind( listen_fd, ( struct sockaddr *)&servaddr, sizeof( struct sockaddr ) ) == -1 )
	{
		printf("bind error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
 
	if( listen( listen_fd, 10 ) == -1 )
	{
		printf("Listen Error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
	
	epoll_fd = epoll_create( MAX_EPOLL );	//1.epoll_create
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = listen_fd;
	if( epoll_ctl( epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev ) < 0 )		//2.epoll_ctl
	{
		printf("Epoll Error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
	
	while( 1 )
	{
		int ready_counts = 0;
		if( ( ready_counts = epoll_wait( epoll_fd, events, MAX_EPOLL, -1 ) ) == -1 )		//3.epoll_wait,就绪的event在events里面
		{
			printf( "Epoll Wait Error : %d\n", errno );
			exit( EXIT_FAILURE );
		}
 
		for( i = 0; i < ready_counts; i++ )
		{
			if( events[i].data.fd == listen_fd)		//监听端口有就绪事件
			{
				if( ( conn_fd = accept( listen_fd, (struct sockaddr *)&cliaddr, &len ) ) == -1 )
				{
					printf("Accept Error : %d\n", errno);
					exit( EXIT_FAILURE );
				}
				
				printf( "Server get from client !\n"/*,  inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port */);
				
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_fd;
				if( epoll_ctl( epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev ) < 0 )
				{
					printf("Epoll Error : %d\n", errno);
					exit( EXIT_FAILURE );
				}
			}
			else
			{
                printf("Server read data\n");
				nread = read( events[i].data.fd, buf, sizeof( buf ) );
				if( nread <= 0 )
				{
					close( events[i].data.fd );
					epoll_ctl( epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev );
					continue;
				}
				
				write( events[i].data.fd, buf, nread );
			}
		}
	}
	
	close( listen_fd );
	return 0;
}
