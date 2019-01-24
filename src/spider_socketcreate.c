#include <spider.h>

int spider_socketcreate(void)
{
    int socketfd;
    if((socketfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("Socketcreate error");
        return -1;
    }
    printf("[2]socket create success.....\n");
    return socketfd;
}
