#include <spider.h>
int spider_queueempty(queue_t *p)
{
    if(p->front == p->rear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    } 
}