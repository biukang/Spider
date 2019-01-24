#include <spider.h>

int main(void)
{
    url_t url;
    strcpy(url.url,"http://img.pconline.com.cn/images/upload/upc/tx/wallpaper/1305/03/c1/20506501_1367563952702.jpg");
    //url解析   
    spider_analyticurl(&url);
    //创建socket
    int webfd = spider_socketcreate();
    //建立与web服务器的链接
    spider_connection(&url,webfd);
    //发送请求
    //获取响应
    //持久化资源
    return 0;
}
