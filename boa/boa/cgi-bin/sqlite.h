#include <stdio.h>
#include "./sqlite/sqlite3.h"
#include <stdlib.h>
#include<string.h>
#include<time.h>
#ifndef false
 #define false 0
#endif
#ifndef true
 #define true 1
#endif
struct person{
    int id;
    char* number;
    char* psw;
    char* name;

};
struct routine{
    int id;
    char* pnumber;
    int date;
    int cometime;
    int leavetime;
    int isLate;
    int isEarlyLeave;
};
int sqliteDB_open();

int sqliteDB_close();

int sqliteDB_opt_delete(char *name);

int sqliteDB_opt_delete_by_id(char *id);

int sqliteDB_opt_add(char *name,char *id,int price);

int sqliteDB_opt_select(char *name);

int sqliteDB_opt_select_by_id(char *id);

int sqliteDB_opt_select_all();

//创建员工表
int sqliteDB_opt_create_person_table();
//添加人员
int sqliteDB_opt_add_person(char* name,char* number,char* psw);
//获取当前最大员工id
int sqliteDB_opt_get_max_person_id();
//创建签到表
int sqliteDB_opt_create_routine_table();
//签到
int sqliteDB_opt_Sign_Work(char* pnumber,int date,int comeTime,int isLate);
//签退
int sqliteDB_opt_Leave(int id,int leaveTime,int isEarlyLeave);
//获取所有员工
//int get_all_people();
int get_all_people(struct person** persons);
//通过员工号和日期查找签到信息id
//找不到返回-1
int get_routine_id(char* pnumber,int date);
//通过number查找员工，返回数量，结果在结构体中
int get_employee_by_number(char* number,struct person** persons);
//通过name查找员工，返回数量，结果在结构体中
int get_employee_by_name(char* name,struct person** persons);
//根据日期查找签到签退数据
int get_routines_by_date(char* date,struct routine ** routines);
//查找总人数
int get_employee_count();
//根据日期查找迟到人数
int get_late_count(char* date);
//根据日期查找早退人数
int get_early_leave_count(char* date);

/*
struct tm* gettime(){
    time_t timep;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);
    return p;
}
char* getyear(){
    struct tm* p=gettime();
    int y=1900+p->tm_year;
    static char year[4];
    sprintf(year," %d" , y);//将int数据转换为字符串
    //itoa(y,year,10);
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return year;
}
int getyearint(){
    struct tm* p=gettime();
    int y=1900+p->tm_year;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return y;
}
char* getmonth(){
    struct tm* p=gettime();
    int m=1+p->tm_mon;
    static char month[4];
	 sprintf(month," %d" , m);//将int数据转换为字符串
//itoa(m,month,10);
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return month;
}
int getmonthint(){
    struct tm* p=gettime();
    int m=1+p->tm_mon;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return m;
}
char* getday(){
    struct tm* p=gettime();
    int d=p->tm_mday;
    static char day[4];
    //itoa(d,day,10);
	 sprintf(day," %d" , d);//将int数据转换为字符串
//printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return day;
}
int getdayint(){
    struct tm* p=gettime();
    int d=p->tm_mday;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return d;
}
char* gethour(){
    struct tm* p=gettime();
    int h=p->tm_hour;
    static char hour[2];
    sprintf(hour," %d" , h);//将int数据转换为字符串
    //itoa(h,hour,10);
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return hour;
}
int gethourint(){
    struct tm* p=gettime();
    int h=p->tm_hour;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return h;
}
char* getminute(){
    struct tm* p=gettime();
    int h=p->tm_min;
    static char hour[2];
    //itoa(h,hour,10);
	 sprintf(hour," %d" , h);//将int数据转换为字符串
//printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return hour;
}
int getminuteint(){
    struct tm* p=gettime();
    int h=p->tm_min;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return h;
}
char* getsec(){
    struct tm* p=gettime();
    int h=p->tm_sec;
    static char hour[2];
    //itoa(h,hour,10);
	 sprintf(hour," %d" , h);//将int数据转换为字符串
//printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return hour;
}
int getsecint(){
    struct tm* p=gettime();
    int h=p->tm_sec;
    //printf("日期：%s\n",year);
    //char * u;
    //strcpy(u,year);
    return h;
}
//获取年月日
char* getDate(){
    static char date[50] ;
    strcpy(date,getyear());
    strcat(date,"-");
    strcat(date,getmonth());
    strcat(date,"-");

    strcat(date,getday());
    return date;
}
//获取日期封装成整数
long getDateInt(){
    return (getyearint()*10000+getmonthint()*100+getdayint());
}
//获取时间封装成整数返回
long getTimeInt(){
    return (gethourint()*10000+getminuteint()*100+getsecint());
}
*/
/*
//把整数日期转换成日期字符串格式
char* parseDateInt(long date_int){
    printf("%d\n",date_int);
    static char s[12];
    char y[4];
    itoa(date_int/10000,y,10);
    printf("%s\n",y);
    strcpy(s,y);//年份
    strcat(s,"-");
    itoa(date_int%10000/100,y,10);
    strcat(s,y);//月份
    strcat(s,"-");
    itoa(date_int%100,y,10);
    strcat(s,y);//天
    return s;
}
//把时间转换成时间字符串格式
char* parseTimeInt(long date_int){
//获取所有员工
    printf("%d\n",date_int);
    static char s[12];
    char y[4];
    itoa(date_int/10000,y,10);
    printf("%s\n",y);
    strcpy(s,y);//时
    strcat(s,":");
    itoa(date_int%10000/100,y,10);
    strcat(s,y);//分
    strcat(s,":");
    itoa(date_int%100,y,10);
    strcat(s,y);//秒
    return s;
}
//test
int get(struct person **persons){
    *persons=(struct person*)malloc(sizeof(struct person*)*5);
    int i=0;
    for(i=0;i<5;++i){
        (*persons+i)->id=i;
        (*persons+i)->name=(char*)malloc(sizeof(char)*9);
        (*persons+i)->name="孙云栋";
        (*persons+i)->number=(char*)malloc(sizeof(char)*9);
        (*persons+i)->number="140410408";
        (*persons+i)->psw=(char*)malloc(sizeof(char)*9);
        (*persons+i)->psw="140410408";
        printf("%d %s %s\n",(*persons+i)->id,(*persons+i)->psw,(*persons+i)->number);
    }
    return i;
}
*/

