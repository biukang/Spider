#include <spider.h>

int spider_connection(url_t *u,int webfd)
{
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(u->port);
    inet_pton(AF_INET,u->ip,&serveraddr.sin_addr.s_addr);
    if((connect(webfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==0)
    {
        printf("[3]connect webserver success...\n");
        return 0;  
    }
    else
    {
        perror("spider_connection error");
        return -1;
    }
}
