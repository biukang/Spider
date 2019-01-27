#include <spider.h>

int spider_queuein(queue_t *p,url_t u)
{
    if(spider_queuefull(p))
    {
        return FALSE;
    }
    else
    {
        p->data[p->rear] = u;
        p->rear = (p->rear+1)%p->maxsize;
        return TRUE;
    }
}