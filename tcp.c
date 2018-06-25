//UNIX_connect
#include <sys/socket.h>
#include <sys/un.h>
#include "tcp.h"


/*TCP客户端连接客户端*/
/*返回连接服务端的sockfd*/
//Tcp socket client
int Gps_tcp_clientSocket()
{
	int sockfd;
	int size;
	int ret ;
	//int re_len = 0;
	//char tmp_buf[LEN_MAX];

	struct sockaddr_un saddr;
	size = sizeof(struct sockaddr_un);
	char *unix_sock_path = "/var/run/gpsd.sock";
	//struct sockaddr_in caddr;

	bzero(&saddr,sizeof(saddr));    //初始化
	saddr.sun_family = AF_UNIX;     //AF_INET表示IPv4的类型,AF_UNIX表示nuix_sock
	//strncpy( saddr.sun_path, unix_sock_path, strlen(unix_sock_path));
	strncpy( saddr.sun_path, unix_sock_path, sizeof(saddr.sun_path)-1);
	//unlink( unix_sock_path );

    sockfd = socket(AF_UNIX,SOCK_STREAM,0);//返回-1表示失败；
	if(sockfd<0)
    {
    	perror("failed to socket");
    	return -1;
    }

	printf("sockfd=%d.\n",sockfd);
	//printf("path=len=%d ,path_size= %ld.\n", (int)strlen(unix_sock_path),sizeof(unix_sock_path));
/*
   //create unix_sock
    if ( bind( sockfd, ( struct sockaddr * )&saddr, size ) < 0 )
    {
        perror("bind");
        return -1;
    }
*/
    ret=connect(sockfd,(struct sockaddr*)&saddr,size);
    if(ret<0)
    {
    	perror("failed to connect");
    	return -1;
    }

//    char* nmea_cmd = "?WATCH={\"enable\":true,\"nmea\":true}";
    //char cmdStr[] = {0xB5,0x62,0x06,0x04,0x04,0x00,0xFF,0xFF,0x02,0x00,0x0E,0x61};  //ublox cold,len=12
    //echo '&/dev/ttyS0=B56206040400FFFF02000E61' | socat - UNIX-CONNECT:/var/run/gpsd.sock
    char* coldstart = "&/dev/ttyS0=B56206040400FFFF02000E61";
//    send(sockfd, nmea_cmd, strlen(nmea_cmd), 0);
    send(sockfd, coldstart, strlen(coldstart), 0);
    printf("send finished!ready to exit!\n");
/*
    int cycle = 0;

	while(1)
	{
		//bzero(tmp_buf,sizeof(tmp_buf));
		re_len	= read (sockfd, tmp_buf, LEN_MAX);
		printf("receive len is: %d\n", re_len);
		if(re_len < LEN_MAX)
		{
			tmp_buf[re_len] = '\0';
			printf("%s\n",tmp_buf);
			//process_GpsData(rebuf);
		}
		else
		{
			printf("OverLen!\n");  //printf(" Receive len over %d .\n" , RE_MAX);
			return -1;
		}

		printf("cycle=%d.\n",cycle);
		if (cycle++ == 40)
		{
			cycle = 0;
			printf("send cold start cmd:%s.\n", coldstart );
			send(sockfd, coldstart, strlen(coldstart), 0);
		}

		//printf(" Receive data is: %s# \n\n" , rebuf);
	}
*/
    return sockfd;
}









