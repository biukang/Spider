#include <spider.h>
int spider_request(char *head,int webfd,ssl_t *ssl)
{
    if(ssl!=NULL)
    {
        if((SSL_write(ssl->sslsocket,head,strlen(head)))>0)
        {
            printf("[5] SSL Request Head Send to WebServer Success...\n");
            return 0;
        }
        else
        {
            perror("spider_request error");
            return -1;
        }
    }
    else
    {
        if((send(webfd,head,strlen(head),0))>0)
        {
            printf("[5] Send Request Head to WebServer Success...\n");
            return 0;
        }
        else
        {
            perror("spider_request error");
            return -1;
        }
    }
}
