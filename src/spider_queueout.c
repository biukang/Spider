#include <spider.h>

int spider_queueout(queue_t *p,url_t* u)
{
    if(spider_queuefull(p))
    {
        return FALSE;
    }
    else
    {
       *u =  p->data[p->front];
        p->front = (p->front+1)%p->maxsize;
        return TRUE;
    }
}