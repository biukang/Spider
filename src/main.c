#include <spider.h>

int main(void)
{
    url_t url;
    char head[4096];
    strcpy(url.url,"http://img.pconline.com.cn/images/upload/upc/tx/wallpaper/1305/03/c1/20506501_1367563952702.jpg");
    //url解析   
    spider_analyticurl(&url);
    //创建socket
    int webfd = spider_socketcreate();
    //建立与web服务器的链接
    spider_connection(&url,webfd);
    //构造请求头
    spider_createhead(head,&url);
    //发送请求
    spider_request(head,webfd);
    //获取响应
    //持久化资源
    spider_response(&url,webfd);
    return 0;
}
