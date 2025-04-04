#include "zf_driver_udp.h"

#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

static sockaddr_in server_addr;
socklen_t server_addr_size;
static int udp_client_socket;

int8 udp_init(const char *ip_addr, uint32 port)
{
    // 创建 UDP 套接字
    udp_client_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (udp_client_socket == -1) 
    {
        printf("Failed to create socket\r\n");
        return -1;
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    server_addr.sin_port = htons(port);

    return 0;
}


uint32 udp_send_data(const uint8 *buff, uint32 length)
{
    // 发送消息到服务器
    ssize_t send_len = sendto(udp_client_socket, buff, length, 0, (sockaddr*)&server_addr, sizeof(server_addr));
    if (send_len == -1)
    {
        return length;
    }
    return 0;
}


uint32 udp_read_data(uint8 *buff, uint32 length)
{
 
    server_addr_size = sizeof(server_addr);

    // 接收客户端消息,非阻塞式
    ssize_t str_len = recvfrom(udp_client_socket, buff, length, MSG_DONTWAIT, (struct sockaddr *)&server_addr, &server_addr_size);
    if (str_len == -1) 
    {
        printf("recvfrom() error");
        return 0;
    }

    return str_len;
}
