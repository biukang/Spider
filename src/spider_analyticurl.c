#include <spider.h>

int spider_analyticurl(url_t *u)
{
    //init url
    bzero(u->domain,sizeof(u->domain));
    bzero(u->path,sizeof(u->path));
    bzero(u->name,sizeof(u->name));
    bzero(u->ip,sizeof(u->ip));
    //http://aaa.com/s/s/shtml
    int start;
    int i,j,size = 0;
    struct hostent *ent;
    /*1.确定http版本*/
    char * arr[] = {"http://","https://"};
    if(strncmp(u->url,arr[0],strlen(arr[0])) == 0)
    {
        //确定端口80/443
        u->type = TRUE;
        start = strlen(arr[0]);
        u->port = 80;
    }
    else
    {
        start = strlen(arr[1]);
        u->type = FALSE;
        u->port = 443;
    }
    /*2.获取主机名域名*/
    j = 0;
    for(i = start;u->url[i] != '/'&&u->url[i] != '\0';i++)
    {
        u->domain[j++]=u->url[i];
    }
    /*3.获取文件名*/
    for(i = strlen(u->url);u->url[i]!='/';i--,size++);
    j = 0;
    for(i = strlen(u->url)-size+1;u->url[i]!='\0';i++)
    {
        u->name[j++] = u->url[i];
    }
    /*4.获取资源路径*/
    j = 0;
    for(i = start + strlen(u->domain);i<strlen(u->url)-size;i++)
    {
        u->path[j++] = u->url[i];
    }
    /*5.获得IP*/
    //通过gethostbyname函数访问公网IP（本地host文件（www.baidu.com:192.168.1.1)).调用该函数需要网络
    if((ent = gethostbyname(u->domain))!=NULL)
    {
        inet_ntop(AF_INET,ent->h_addr_list[0],u->ip,sizeof(u->ip));
    }
    else
    {
        return 1;
    }
    printf("[1]Analytic url sucess...\n");
    printf("url[%s]\ndomain[%s]\nip[%s]\nport[%d]\ntype[%d]\npath[%s]\nname[%s]\n",u->url,u->domain,u->ip,u->port,u->type,u->path,u->name);
    return 0;
}
