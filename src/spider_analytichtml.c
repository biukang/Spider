#include <spider.h>

int spider_analytichtml(url_t *u)
{
    int fd,len;
    regex_t treg;
    regex_t dreg;
    regex_t areg;
    regmatch_t tmatch[2];
    regmatch_t dmatch[2];
    regmatch_t amatch[3];
    char name[1024];
    char description[4096];
    char url[2048];
    char title[1024];
    char *string;
    bzero(name,sizeof(name));
    bzero(description,sizeof(description));
    bzero(url,sizeof(url));
    bzero(title,sizeof(title));
    fd = open(u->name,O_RDWR);
    len = lseek(fd,0,SEEK_END);
    string = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    char* tmp = string;
    close(fd);
    //生成多个正则标记
    regcomp(&treg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
	regcomp(&dreg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">",0);
	regcomp(&areg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>",0);
    //通过表达式标记在源数据中使用正则表达式匹配抽取信息
    if((regexec(&treg,tmp,2,tmatch,0))==0)
    {
        snprintf(name,tmatch[1].rm_eo - tmatch[1].rm_so+1,"%s",tmp+tmatch[1].rm_so);
        printf("词条名：%s\n",name);
    }
    if((regexec(&dreg,tmp,2,dmatch,0))==0){
            snprintf(description,dmatch[1].rm_eo - dmatch[1].rm_so + 1,"%s",tmp + dmatch[1].rm_so);
            printf("词条描述:%s\n",description);
    }
    while((regexec(&areg,tmp,3,amatch,0))==0){
            snprintf(url,amatch[1].rm_eo - amatch[1].rm_so + 1,"%s",tmp + amatch[1].rm_so);
            snprintf(title,amatch[2].rm_eo - amatch[2].rm_so + 1,"%s",tmp + amatch[2].rm_so);
            printf("词条链接:%s\t词条标题:%s\n",url,title);
            bzero(url,sizeof(url));
            bzero(title,sizeof(title));
            tmp += amatch[0].rm_eo;
    }
    munmap(string,len);
    unlink(u->name);
    return 0;
}

