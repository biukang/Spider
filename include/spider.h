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
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <regex.h>
#include <sys/mman.h>

#define TRUE 1
#define FALSE 0

typedef struct
{
    SSL_CTX *sslctx;
    SSL *sslsocket;
} ssl_t;

/*URL类型*/
typedef struct
{
    char url[4096];
    char domain[1024];
    char path[1024];
    char name[255];
    char ip[16];
    char title[1024];
    int port;
    int type; //如果为TRUE是http，FALSE为https
} url_t;

typedef struct queue
{
    url_t *data; /*队列员工*/
    int front;   //头索引
    int rear;    //尾索引
    int maxsize; //队列最大数
    int size;    //当前使用数
} queue_t;

int spider_analyticurl(url_t *);
int spider_socketcreate(void);
int spider_connection(url_t *u, int webfd);
int spider_createhead(char *head, url_t *u);
int spider_request(char *head, int webfd, ssl_t *ssl);
int spider_response(url_t *u, int webfd, ssl_t *ssl);
int spider_analytichtml(queue_t *wque, queue_t *yque, url_t *tmpurl);
ssl_t *spider_opensslcreate(int webfd);
void spider_error(char *str, int errcode);

/*URL容器*/
int spider_notinque(queue_t *p, const char *url);
int spider_queuecreate(queue_t *p, int maxsize);
int spider_queuefull(queue_t *p);
int spider_queueempty(queue_t *p);
int spider_queuein(queue_t *p, url_t u);
int spider_queueout(queue_t *p, url_t *u);
url_t *spider_queueshow(queue_t *p);
