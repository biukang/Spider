#include <spider.h>
void spider_error(char *str,int errcode)
{
    perror(str);
    exit(errcode);
}