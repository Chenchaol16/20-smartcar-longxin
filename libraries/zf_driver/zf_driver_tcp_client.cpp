#include "zf_driver_tcp_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int set_nonblocking(int fd) 
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


static sockaddr_in server_addr;
static int tcp_client_socket;

int8 tcp_client_init(const char *ip_addr, uint32 port)
{
    // 创建 UDP 套接字
    tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_socket < 0) 
    {
        printf("Failed to create socket\r\n");
        return -1;
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    server_addr.sin_port = htons(port);

    printf("Wait connect tcp server\r\n");

    // 连接到服务器
    int ret = connect(tcp_client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    if (ret < 0)
    {
        perror("connect() error");
        close(tcp_client_socket);
        return -1;
    }


    if (set_nonblocking(tcp_client_socket) < 0) {
        perror("set_nonblocking");
        close(tcp_client_socket);
        return -1;
    }

    return 0;
}


uint32 tcp_client_send_data(const uint8 *buff, uint32 length)
{

    // 发送消息到服务器
    int32 str_len;
    str_len = send(tcp_client_socket, buff, length, 0);
    if (str_len == -1)
    {
        printf("write() error");
        return length;
    }
    return 0;
}



uint32 tcp_client_read_data(uint8 *buff, uint32 length)
{
    // 接收服务器响应
    int32 str_len;

    str_len = recv(tcp_client_socket, buff, length, 0);

    if (str_len == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK) 
        {   // 暂时无数据可读，稍后重试或处理其他逻辑。
            return 0; // 返回0表示暂无数据可读，需要外部逻辑决定是否重试或退出。
        } 
        else 
        {   // 其他错误，处理错误。
            printf("read() error");
            return -1; // 返回-1表示发生错误。
        }
    }

    return str_len;
}



