#include <spider.h>

int main(void)
{
    url_t url;
    url_t tmp;
    ssl_t *ssl;
    char head[4096];
    int webfd;
    queue_t wque, yque;
    datafd = open("data.html", O_RDWR | O_CREAT, 0775);
    strcpy(url.url, "https://baike.baidu.com/item/linux/27050?fr=aladdin");
    //url容器创建
    spider_queuecreate(&wque, 1000);
    spider_queuecreate(&yque, 1000);
    if (spider_notinque(&wque, url.url) && spider_notinque(&yque, url.url))
    {
        spider_queuein(&wque, url);
    }
    while (!spider_queueempty(&wque))
    {
        spider_queueout(&wque, &tmp);
        //url解析
        spider_analyticurl(&tmp);
        //创建socket
        int webfd = spider_socketcreate();
        //建立与web服务器的链接
        spider_connection(&tmp, webfd);
        //构造请求头
        spider_createhead(head, &tmp);
        if (url.type == TRUE)
        {
            //发送请求
            spider_request(head, webfd, NULL);
            //获取响应
            //持久化资源
            spider_response(&tmp, webfd, NULL);
        }
        else
        {
            ssl = spider_opensslcreate(webfd);
            spider_request(head, webfd, ssl);
            spider_response(&tmp, webfd, ssl);
        }
        spider_analytichtml(&wque, &yque, &tmp);
        spider_queueshow(&wque);
    }
    return 0;
}
