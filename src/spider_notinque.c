#include <spider.h>
int spider_notinque(queue_t *p,const char * url)
{
    int i = p->front;
    if(spider_queueempty(p))
    {
        return TRUE;
    }    
    while(i!=p->rear)
    {
        if((strcmp(p->data[i].url,url))==0)
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}