#include <spider.h>

int spider_response(url_t *u,int webfd,ssl_t *ssl)
{
    char buf[8192];
    char res[4096];
    bzero(buf,sizeof(buf));
    bzero(buf,sizeof(res));
    char * pos;
    int len;
    if(ssl!=NULL)
    {
        len = SSL_read(ssl->sslsocket,buf,sizeof(buf));
        if((pos = strstr(buf,"\r\n\r\n"))!=NULL)
        {
            snprintf(res,pos-buf,"%s",buf);
        }
        int fd = open(u->name,O_RDWR|O_CREAT,0775);
        write(fd,pos+4,len-(pos-buf+4));
        printf("[6] SSL Get ResHead Success...\n%s\n",res);
        bzero(buf,sizeof(buf));
        while((len = SSL_read(ssl->sslsocket,buf,sizeof(buf)))>0)
        {
            write(fd,buf,len);
            bzero(buf,sizeof(buf));
        }
        close(webfd);
        free(ssl);
        close(fd);
    }
    else
    {
        len = recv(webfd,buf,sizeof(buf),0);
        if((pos = strstr(buf,"\r\n\r\n"))!=NULL)
        {
            snprintf(res,pos-buf,"%s",buf);
        }
        int fd = open(u->name,O_RDWR|O_CREAT,0775);
        write(fd,pos+4,len-(pos-buf+4));
        printf("[6] Get ResHead Success...\n%s\n",res);
        bzero(buf,sizeof(buf));
        while((len = read(webfd,buf,sizeof(buf)))>0)
        {
            write(fd,buf,len);
            bzero(buf,sizeof(buf));
        }
        close(webfd);
        close(fd);
    }
    return 0;
}

