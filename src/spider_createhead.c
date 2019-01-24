#include <spider.h>

int spider_createhead(char *head,url_t *u)
{
    bzero(head,4096);
    sprintf(head,"GET %s HTTP/1.1\r\n"\
                 "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
                 "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"\
                 "Host:%s\r\n"\
                 "Connection:close\r\n\r\n",u->url,u->domain);
    printf("[4] Create request head:\n%s\n",head);
    return 0;
}
