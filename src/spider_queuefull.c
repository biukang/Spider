#include <spider.h>
int spider_queuefull(queue_t *p)
{
    if(p->front == (p->rear+1) % p->maxsize)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    } 
}