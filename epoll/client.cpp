#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
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
	int 		conn_fd;
	int 		epoll_fd;
	int 		nread;
	int		i;
	struct sockaddr_in cliaddr;
	struct 	epoll_event	ev;  //监听fd
	struct 	epoll_event	events[MAX_EPOLL];
	char 	buf[BUF_SIZE];
	socklen_t	len = sizeof( struct sockaddr_in );
	
	bzero( &cliaddr, sizeof( cliaddr ) );
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	cliaddr.sin_port = htons( PORT );
	
	if( ( conn_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
	{
		printf("socket error : %d\n" , errno );
		exit( EXIT_FAILURE );
	}
	
	if( setnonblocking( conn_fd ) == -1 )
	{
		printf("setnonblocking error : %d\n", errno);
		exit( EXIT_FAILURE );
	}

    int r = connect(conn_fd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

	epoll_fd = epoll_create( MAX_EPOLL );	//1.epoll_create
	//ev.events = EPOLLIN | EPOLLET;
	ev.events = EPOLLOUT;  //监听可写事件，代表连接成功，然后监听可读事件。
    ev.data.fd = conn_fd;
	if( epoll_ctl( epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev ) < 0 )		//2.epoll_ctl
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
			if( events[i].data.fd == conn_fd)		//监听端口有就绪事件
			{
                if (events[i].events & EPOLLOUT){
                    printf("Connect success\n");

                    if( epoll_ctl( epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev ) )
                    {
                        printf("Epoll Error : %d\n", errno);
                        exit( EXIT_FAILURE );
                    }

                    ev.events = EPOLLIN;
                    ev.data.fd = conn_fd;

                    if( epoll_ctl( epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev ) < 0 )
                    {
                        printf("Epoll Error : %d\n", errno);
                        exit( EXIT_FAILURE );
                    }
                    char write_buf[] = "abcdefgh";
                    write( events[i].data.fd, write_buf, sizeof(write_buf));

                }
                else if (events[i].events & EPOLLIN){
                    printf("Read data\n");

                    nread = read( events[i].data.fd, buf, sizeof( buf ) );
                    if( nread <= 0 )
                    {
                        //close( events[i].data.fd );
                        //epoll_ctl( epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev );
                        printf("Close Fd\n");
                        continue;
                    }
                    
                    //write( events[i].data.fd, buf, nread );
                }
                
			}
		}
	}
	
    close(conn_fd);
	return 0;
}
