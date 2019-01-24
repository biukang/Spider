#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define TRUE 1
#define FALSE 0

/*URL类型*/
typedef  struct
{
    char url[4096];
    char domain[1024];
    char path[1024];
    char name[255];
    char ip[16];
    int port;
    int type;   //如果为TRUE是http，FALSE为https
}url_t;

int spider_analyticurl(url_t *);
int spider_socketcreate(void);
int spider_connection(url_t *u,int webfd);
int spider_createhead(char *head,url_t *u);
int spider_request(char *head,int webfd);
int spider_response(url_t *u,int webfd);
