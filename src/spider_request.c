#include <spider.h>
int spider_request(char *head,int webfd)
{
    if((send(webfd,head,strlen(head),0))>0)
    {
        printf("[5] Send Request Head to WebServer Success...\n");
        return 0;
    }
}
