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
	int m=0;
    int fd;
    char param_number[20];
    char param_name[20];
    char param_psw[20];
    struct person* persons;

 	printf("Content-type:text/html;charset=gbk\n\n");
	printf("<HEAD>\n");
	printf("<TITLE>���ѧ��</TITLE>\n");
	printf("<style>\n");
	printf("h1{text-align:center}");
	printf("h3{text-align:center}");
	printf("BODY{background-color:#dfffdf}");
	printf("table{text-align:center}");
	printf("</style>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");

    req_method = getenv("REQUEST_METHOD");
    input = getcgidata(stdin, req_method);

	//printf("Your POST Message is %s\n", input);
    //printf("The following is query reuslt:\n");
	sqliteDB_open();
	//char* input="number=140410408&name=sunyundong&psw=123";
    //printf("%s\n",input);

    for (i = 7; i < (int)strlen(input); i++){//number=?&name=?&paw=
        if(input[i]=='&'){
            param_number[j]='\0';
            break;
        }
        param_number[j++]=input[i];
    }
     //printf("%s\n",param_number);

    j=0;
    for (i = 13+(int)strlen(param_number); i < (int)strlen(input); i++){
        if(input[i]=='&'){
            param_name[j]='\0';
            break;
        }
        param_name[j++]=input[i];
    }

    j=0;
    for (i = 18+((int)strlen(param_number))+((int)strlen(param_name)); i < (int)strlen(input); i++){
        if(input[i]=='&'){
            param_psw[j]='\0';
            break;
        }
        param_psw[j++]=input[i];
    }
    param_psw[j]='\0';

    //printf("%s\n%s\n%s",param_number,param_name,param_psw);
	sqliteDB_opt_add_person(param_name, param_number, param_psw); //��ѧ��������һ����Ϣ
	//get_all_people(&persons);
	//sqliteDB_opt_create_routine_table();
	//ǩ��
	//sqliteDB_opt_Sign_Work("140410408",getDateInt(),getTimeInt(),0);
	//ǩ��
	//���ҵ���ǰ��Ա����ǩ����Ϣ��Ŀ��id
	//routine_id=get_routine_id("140410408",getDateInt());
	//if(routine_id>=0){//����ǩ����Ϣ
    //ִ��ǩ��
    //sqliteDB_opt_Leave(routine_id,getTimeInt(),0);
	//}else{
    //	printf("\n��Ա������δǩ��,����ǩ��!\n");
	//}
    sqliteDB_close();
    close(fd);
    return 0;
 }
