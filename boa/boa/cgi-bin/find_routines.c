#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite.h"
#include "utils.h"
int main(){
    int routine_id;
    char *input;
    char *req_method;
    char led[10];
    int i = 0;
    int j = 0;
    int fd;
    struct routine* routines;
    int count;//�������
    char param[20];//����
    char eque='=';

    printf("Content-type:text/html;charset=gbk\n\n");
	printf("<HEAD>\n");
	printf("<TITLE>ǩ��ǩ����Ϣ</TITLE>\n");
	printf("<style>\n");
	printf("h1{text-align:center}");
	printf("h3{text-align:center}");
	printf("BODY{background-color:#dfffdf}");
	printf("table{text-align:center}");
	printf("</style>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	printf("<h1>ǩ��ǩ����Ϣ</h1>");

    req_method = getenv("REQUEST_METHOD");
    input = getcgidata(stdin, req_method);

	//printf("Your POST Message is \"%s\". \n\n", input);
    //printf("The following is query reuslt:\n");
	sqliteDB_open();

    if(strstr(input,"date")){
        for(j=0;j<strlen(input);++j){
            if(input[j-1]=='='){
            //printf("Your POST =%d",j);
                i=j;
            }
            if(i>0){
                param[j-i]=input[j];
            }
        }
		//printf("Your POST date is %s\n",param);
        //printf("date:%s",param);
        //sqliteDB_opt_create_routine_table();
        //sqliteDB_opt_Sign_Work("140410408",20170707,getTimeInt(),1);
        //sqliteDB_opt_Sign_Work("140410428",20170707,getTimeInt(),0);

        get_routines_by_date(param,&routines); //��������(param)��routines���в�ѯ��Ϣ(routines)

        //count=get_employee_by_number(param,persons);
        //��ӡ������Ϣ
        //todo ͳ��
    } else {
        printf("\n ָ������!\n");
    }
    sqliteDB_close();
    close(fd);
    return 0;
 }
