#include <spider.h>
ssl_t* spider_opensslcreate(int webfd)
{
    ssl_t *ssl = (ssl_t*)malloc(sizeof(ssl_t));
    //加载错误信息
    SSL_load_error_strings();
    //初始化ssl库
    SSL_library_init();
    //初始化散列函数
    OpenSSL_add_ssl_algorithms();
    //生成上下文信息
    ssl->sslctx = SSL_CTX_new(SSLv23_method());
    //生成socket
    ssl->sslsocket = SSL_new(ssl->sslctx);
    //使用原有的webfd对sslsocket进行设置
    SSL_set_fd(ssl->sslsocket,webfd);
    //使用sslsocket进行https的链接与认证
    SSL_connect(ssl->sslsocket);
    return ssl;
}
