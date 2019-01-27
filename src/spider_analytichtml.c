#include <spider.h>

int spider_analytichtml(queue_t *wque, queue_t *yque, url_t *tmpurl)
{
    int fd, len;
    int flags = 0;
    int datafd;
    regex_t treg;
    regex_t dreg;
    regex_t areg;
    regmatch_t tmatch[2];
    regmatch_t dmatch[2];
    regmatch_t amatch[3];
    url_t node;
    char name[1024];
    char description[4096];
    char url[2048];
    char title[1024];
    char *string;
    bzero(name, sizeof(name));
    bzero(description, sizeof(description));
    bzero(url, sizeof(url));
    bzero(title, sizeof(title));
    fd = open(tmpurl->name, O_RDWR);
    len = lseek(fd, 0, SEEK_END);
    string = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    char *tmp = string;

    //生成多个正则标记
    regcomp(&treg, "<h1 >\\([^<]\\+\\?\\)</h1>", 0);
    regcomp(&dreg, "<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">", 0);
    regcomp(&areg, "<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>", 0);
    //通过表达式标记在源数据中使用正则表达式匹配抽取信息
    if ((regexec(&treg, tmp, 2, tmatch, 0)) == 0)
    {
        snprintf(name, tmatch[1].rm_eo - tmatch[1].rm_so + 1, "%s", tmp + tmatch[1].rm_so);
        write(datafd, "<html>", strlen("<html>"));
        write(datafd, "<head><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\"></head>", strlen("<head><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\"></head>"));
        write(datafd, "<body>", strlen("<body>"));
        write(datafd, "<div style='width:1360px;display:block;word-break:break-all;word-wrap:break-word;white-space:pre-wrap;'>", strlen("<div style='width:1360px;display:block;word-break:break-all;word-wrap:break-word;white-space:pre-wrap;'>"));
        write(datafd, name, strlen(name));
        printf("词条名：%s\n", name);
    }
    if ((regexec(&dreg, tmp, 2, dmatch, 0)) == 0)
    {
        snprintf(description, dmatch[1].rm_eo - dmatch[1].rm_so + 10, "<h3>%s</h3>", tmp + dmatch[1].rm_so);
        write(datafd, description, strlen(description));
        snprintf(url, strlen(tmpurl->url) * 2 + 16, "<a href=\"%s\">%s</a>", tmpurl->url, tmpurl->url);
        write(datafd, url, strlen(url));
        write(datafd, "</div>", strlen("</div>"));
        write(datafd, "</body>", strlen("</body>"));
        write(datafd, "</html>", strlen("</html>"));
        printf("词条描述:%s\n", description);
    }
    while ((regexec(&areg, tmp, 3, amatch, 0)) == 0)
    {
        bzero(node.url, sizeof(node.url));
        bzero(node.title, sizeof(node.title));
        snprintf(node.url, amatch[1].rm_eo - amatch[1].rm_so + strlen(tmpurl->domain) + 9, "https://%s%s", tmpurl->domain, tmp + amatch[1].rm_so);
        snprintf(node.title, amatch[2].rm_eo - amatch[2].rm_so + 1, "%s", tmp + amatch[2].rm_so);
        if (spider_notinque(wque, node.url) && spider_notinque(yque, node.url))
        {
            spider_queuein(wque, node);
            ++flags;
        }
        else
            printf("忽略重复词条:%s\tURL:%s\n", node.title, node.url);
        printf("title:%s\turl:%s\n", node.title, node.url);
        tmp += amatch[0].rm_eo;
    }
    printf("Analytic HTML 解析新词条链接总数:%d\n", flags);
    regfree(&areg);
    regfree(&treg);
    regfree(&dreg);
    close(fd);
    munmap(string, len);
    unlink(tmpurl->name);
    return 0;
}
