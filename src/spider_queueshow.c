#include <spider.h>

url_t *spider_queueshow(queue_t *p)
{
    int i = p->front;
    if(spider_queueempty(p))
    {
        printf("The Queue is Empty.\n");
        return NULL;
    }
    printf("SPIDER URL QUEUE START:\n");
    while(i!=p->rear)
    {
        printf("URL:%s\n",p->data[i].url);
        i++;
    }
    printf("Print End\n");
    return NULL;
}