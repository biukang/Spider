#include <spider.h>

int spider_queuecreate(queue_t *p,int maxsize)
{
    p->data = (url_t *)malloc(sizeof(url_t)*maxsize);
    if(p->data = NULL)
    {
        spider_error("Queue_Create Call Failed",-1);
    }
    p->front = 0;
    p->rear = 0;
    p->size = 0;
    p->maxsize = maxsize;
    return 0;
}