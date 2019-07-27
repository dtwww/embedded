#include "sqlite.h"
sqlite3 *db;//全局的数据连接

//用户第一次打开数据库时应创建对应的table并添加适当的数据记录

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
/**
*
*建立与数据库的连接
*
*
*/
int sqliteDB_open(){

	int rc;//操作标志
	//printf("\ncreat database:test.db\n\ncreat table:table merchandise(contents:id name price)\n\nand add two records\n");
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	//printf("\nOpen sucess!");

	//if(!sqliteDB_create_table())
		//printf("\ntable exist");
	//创建persons table
	if(!sqliteDB_opt_create_person_table()){
		//printf("\n persons table exits!");
	}

	//if(!sqliteDB_insert_records()){
		//printf("\ninsert table faild");
//}
  //else sqliteDB_opt_select_all();
	return 1;
}
/**
*
* 关闭与数据库的连接
*
*/
int sqliteDB_close(){
	if(db != 0)
		sqlite3_close(db);
}
/**
*
* 添加一条记录到已知或未知数据库表
*
*/
int sqliteDB_opt_add(char *name,char *id,int price){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into merchandise values('";

// by sprife for mem out

	char tem_sql0[5] = "','";
      	char tem_sql1[5] = "',";
      	char tem_sql2[5] = ");";
	char tem_price[20];

	sprintf(tem_price, " %d" , price);//将int数据转换为字符串

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,id);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_price);
	sql = strcat(sql,tem_sql2);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**
*
* 删除表中的一条记录
* @param name
*/
int sqliteDB_opt_delete(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from merchandise where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**
*
* 删除表中的一条记录
* @param id
*/
int sqliteDB_opt_delete_by_id(char *id){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from merchandise where id = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,id);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/*******************************************************
******************************************************/
/**
*
* 修改数据库表中的记录内容
*/
int sqliteDB_opt_modify();
/**
*
* 用预编译的sql语句减少sql语句的分析时间
*
* 只举例 查询语句
* 查询语句
*/
int sqliteDB_opt_select_all(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *name,*id;
 	int price=0;
 	int nret=sqlite3_prepare(db,"SELECT * FROM merchandise;",strlen("SELECT * FROM merchandise;"),&stmt,(const char**)(&zErrMsg));

	if(nret!=SQLITE_OK)
  		return false;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		name=sqlite3_column_text(stmt,0);
  		id=sqlite3_column_text(stmt,1);
  		price=sqlite3_column_int(stmt,2);
  		printf("\t%s\t\t%s\t\t%d\n",name,id,price);
 	}

 	sqlite3_finalize(stmt);
 	printf("\n");
 	return true;
}
/**
* 查询符合查询条件的记录
* @param name
*/
int sqliteDB_opt_select(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_id;
 	int price=0;
 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from merchandise where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		_name=sqlite3_column_text(stmt,0);
  		_id=sqlite3_column_text(stmt,1);
  		price=sqlite3_column_int(stmt,2);
  		printf("\t%s\t\t%s\t\t%d\n",_name,_id,price);
 	}

	sqlite3_finalize(stmt);
	printf("\n");
	return true;
}
/**
* 查询符合查询条件的记录
* @param id
*/
int sqliteDB_opt_select_by_id(char *id){
	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char*id;
 	int price=0;
 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from merchandise where id = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,id);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return -1;
 	printf("\n\tname\t\tid\t\tprice\n");
 	printf("\t------------------------------------------------------------\n");

	while(1){
  	nret=sqlite3_step(stmt);
  	if(nret!=SQLITE_ROW)
   		break;
  	id=sqlite3_column_text(stmt,0);
  	printf("\t maxId=%s",id);
	}
	sqlite3_finalize(stmt);
	printf("\n");
	return id;
}
/**
**
**
**内部调用函数
**
**/
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  	int i;
  	for(i=0; i<argc; i++){
    		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  	}

  	printf("\n");
  	return 0;
}
/**
**
**内部调用函数
**功能判断所查询的记录是否存在
**/
int sqliteDB_exist(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name;
 	int price=0;
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from persons where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	printf("sql: %s",sql);
	if(nret!=SQLITE_OK)
		return false;
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		printf("\n this record does not exist!!");
		return false;
	}

	sqlite3_finalize(stmt);
	return true;
}
/**
**
**在用户还没有创建table时可用该函数创建table
**
**/
int sqliteDB_create_table(){

	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE merchandise(name varchar(40),id varchar(40),price smallint);";

	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else

  	return true;
}

/**
**
**初始化数据库table时预插入两条数据
**
**/
int sqliteDB_insert_records()
{
 	char* zErrMsg=NULL;

 	//int nret=sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);

 	//nret=sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);
 	//if(nret!=SQLITE_OK){
 	 	//printf("%s\n",sqlite3_errmsg(db));
  		//return false;
 	//}
 	//else
  	return true;
}

int sqliteDB_opt_create_person_table(){
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE persons(name varchar(40),number varchar(40)PRIMARY KEY ,psw varchar(40));";
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){
 		//printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else{
	//printf("persons chuanjianchen ggong\n");
  	return true;
}
}
int get_all_people(struct person** persons){
    sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	int i=0;
	int id;
       char* name;char* psw;char*number;
 	//char *name,*id;
	//struct person** persons;
 	int nret=sqlite3_prepare(db,"SELECT * FROM persons;",strlen("SELECT * FROM persons;"),&stmt,(const char**)(&zErrMsg));

	*persons=(struct person *)malloc(sizeof(struct person*)*20);
	if(nret!=SQLITE_OK)
  		return false;
 	printf("\n\t\tname\t\tnumber\tpsw\n");
 	//printf("\t------------------------------------------------------------\n");
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
        //(*persons+i)->id=sqlite3_column_int(stmt,0);//id
	  //id=sqlite3_column_int(stmt,0);//id
        (*persons+i)->name=(char*)malloc(sizeof(char)*9);
        //name=(char*)malloc(sizeof(char)*9);
        (*persons+i)->name=sqlite3_column_text(stmt,1);//name
			name=sqlite3_column_text(stmt,0);//name
        (*persons+i)->number=(char*)malloc(sizeof(char)*9);
        (*persons+i)->number=sqlite3_column_text(stmt,2);//number
	 		number=sqlite3_column_text(stmt,1);//number
        (*persons+i)->psw=(char*)malloc(sizeof(char)*9);
        (*persons+i)->psw=sqlite3_column_text(stmt,1);//psw
        psw=sqlite3_column_text(stmt,2);//psw
  	  //printf("\t%d\t\t%s\t\t%s\t%s\n",(*persons+i)->id,(*persons+i)->name,(*persons+i)->number,(*persons+i)->psw);

       printf("\t\t%s\t\t%s\t%s\n",name,number,psw);

       ++i;
 	}
 	sqlite3_finalize(stmt);
 	printf("\n");
 	return i;
}
//新增员工 by syd
int sqliteDB_opt_add_person(char* name,char* number,char* psw){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into persons (name,number,psw)values('";
	//name id number psw
// by sprife for mem out

	char tem_sql0[5] = "','";
      	char tem_sql1[5] = "',";
      	char tem_sql2[5] = ");";
//printf("\n########add people!#######################");
	//name
	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	//number
	sql=strcat(sql,number);
	sql = strcat(sql,tem_sql0);
	//psw
	sql=strcat(sql,psw);
	sql = strcat(sql,"'");
	sql = strcat(sql,tem_sql2);

	//printf("\n###############################");
	//printf("\n%s",sql);
	//printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		printf("<h1>添加学生失败,学号重复</h1>",zErrMsg);
		//printf("\n########add people fail %s\n#######################",zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}else{
       printf("<h1>添加成功!</h1>");
        return true;
    }
}

//创建签到表
int sqliteDB_opt_create_routine_table(){
	char* zErrMsg=NULL;
	int nret;
 	char sql[256]="CREATE TABLE routines(id INTEGER PRIMARY KEY AUTOINCREMENT ,pnumber varchar(40), date INTEGER, cometime INTEGER,isLate INTEGER NOT NULL DEFAULT 0,leavetime INTEGER,isEarlyLeave NOT NULL DEFAULT 0);";
	printf("creat table routines\n");
	printf("%s\n",sql);
	nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
 	if(nret!=SQLITE_OK){
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else
  	return true;
}

//签到
int sqliteDB_opt_Sign_Work(char* pnumber,int date,int cometime,int isLate){
	int rc;
	char *zErrMsg = 0;
	//char *sql=0;//动态生成的SQL语句
	char sql[256]="insert into routines(pnumber,date,cometime,isLate,leavetime,isEarlyLeave) values(160410408,20190707,111111,1,111111,1);";
	//pid date startWorkTime isLate finishWorkTime isEarlyLeave
// by sprife for mem out

	/*char tem_sql0[5] = "','";
      	char tem_sql1[5] = "',";
      	char tem_sql2[5] = ");";

	//pid

	char s[20];

	//sprintf(s," %d" , pid);//将int数据转换为字符串

    //itoa(pid,s,10);
	sql = strcat(tem_sql,pnumber);
	sql = strcat(sql,',');

	sprintf(s," %d" , date);//将int数据转换为字符串
	sql=strcat(sql,s);
	sql = strcat(sql,',');
	//cometime
	//itoa(cometime,s,10);

	sprintf(s," %d" , cometime);//将int数据转换为字符串
	sql=strcat(sql,s);
	sql=strcat(sql,',');
	//isLate
	//itoa(isLate,s,10);

	sprintf(s," %d" , isLate);//将int数据转换为字符串
	sql=strcat(sql,s);
	sql = strcat(sql,tem_sql2);*/

	printf("\n##########come #####################");
	printf("\n%s",sql);
	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}

	printf("\n##########success#####################");
	return true;
}

//签退
int sqliteDB_opt_Leave(int id,int leaveTime,int isEarlyLeave){
	int rc;
	char *zErrMsg = 0;
	//char* sql="update table routines set finishWorkTime="+finishWorkTime+"isEarlyLeave="+isEarlyLeave+"where id="+id+";";

	char sql[256]="update table routines set leaveTime=";

    char s[20];
   	sprintf(s," %d" , isEarlyLeave);//将int数据转换为字符串

    //itoa(leaveTime,s,10);

    strcat(sql,s);

    strcat(sql,",isEarlyLeave=");

    //itoa(isEarlyLeave,s,10);

    sprintf(s," %d" , isEarlyLeave);//将int数据转换为字符串

    strcat(sql,s);

    strcat(sql,"where id=");

    //itoa(id,s,10);

    sprintf(s," %d" , id);//将int数据转换为字符串

    strcat(sql,s);

    strcat(sql,";");

    printf("\n##########签退#####################");
	printf("\n%s",sql);
	printf("\n###############################");
	rc=sqlite3_exec(db,sql,callback,0,&zErrMsg);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"SQL error:%s\n",zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}

	printf("\n##########签退成功#####################");
	return true;
}

int get_routine_id(char* pnumber,int date){
    int rc;
    int nret;
	sqlite3_stmt* stmt=NULL;
	char *zErrMsg = 0;
	//char* sql="update table routines set finishWorkTime="+finishWorkTime+"isEarlyLeave="+isEarlyLeave+"where id="+id+";";
	char sql[256]="select id from routines where pnumber=";
    char s[20];
    strcat(sql,pnumber);
    strcat(sql,"and date=");
    sprintf(s,"%d" , date);//将int数据转换为字符串
    strcat(sql,s);
    strcat(sql,";");
    printf("\n##########查找签到记录id#####################");
	printf("\n%s",sql);
	printf("\n###############################");
    nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
  		return -1;
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  	 		return sqlite3_column_int(stmt,0);
 	}
 	sqlite3_finalize(stmt);
    return -1;
}

//通过number查找员工，返回数量，结果在结构体中

int get_employee_by_number(char* number1,struct person** persons){

 sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	int i=0;
	int id;

	int nret;
	char* sql1=0;
   char* psw;char*number;
 	char *name;
	//struct person** persons;

	char sql[255]="SELECT * FROM persons WHERE number='";
	//printf("\n canhsu :%s",number1);
	sql1=strcat(sql,number1);
	sql1=strcat(sql1,"'");

	sql1=strcat(sql1,";");

	 //printf("\n#############find person by name##################");
	//printf("\n%s",sql1);
	//printf("\n###############################");
 	nret=sqlite3_prepare(db,sql1,strlen(sql1),&stmt,(const char**)(&zErrMsg));

	*persons=(struct person *)malloc(sizeof(struct person*)*20);
	if(nret!=SQLITE_OK){
  		return false;
		}
		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW){
		return 0;
	}
	printf("<table width='100%'\n");
	printf("<tr>\n");
	printf("<th>姓名</th>");
	printf("<th>学号</th>");
	printf("<th>密码</th>");
	printf("</tr>\n");
 	while(1){

        //(*persons+i)->id=sqlite3_column_int(stmt,0);//id
	  //id=sqlite3_column_int(stmt,0);//id
        (*persons+i)->name=(char*)malloc(sizeof(char)*9);
        //name=(char*)malloc(sizeof(char)*9);
        (*persons+i)->name=sqlite3_column_text(stmt,1);//name
			name=sqlite3_column_text(stmt,0);//name
        (*persons+i)->number=(char*)malloc(sizeof(char)*9);
        (*persons+i)->number=sqlite3_column_text(stmt,2);//number
	 		number=sqlite3_column_text(stmt,1);//number
        (*persons+i)->psw=(char*)malloc(sizeof(char)*9);
        (*persons+i)->psw=sqlite3_column_text(stmt,1);//psw
        psw=sqlite3_column_text(stmt,2);//psw
  	  //printf("\t%d\t\t%s\t\t%s\t%s\n",(*persons+i)->id,(*persons+i)->name,(*persons+i)->number,(*persons+i)->psw);

       //printf("\t%s\t\t%s\t%s\n",name,number,psw);

		printf("<tr>\n");
		printf("<th>%s</th>",name);
		printf("<th>%s</th>",number);
		printf("<th>%s</th>",psw);
		printf("</tr>\n");
		++i;
		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;

	}
}

//通过name查找员工，返回数量，结果在结构体中

int get_employee_by_name(char* name1,struct person** persons){

    sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	int i=0;
	int id;

	int nret;
	char* sql1=0;
   char* psw;char*number;
 	char *name;
	//struct person** persons;

	char sql[255]="SELECT * FROM persons WHERE name='";
	//printf("\n canhsu :%s",name1);
	sql1=strcat(sql,name1);
	sql1=strcat(sql1,"'");

	sql1=strcat(sql1,";");

	// printf("\n#############find person by name##################");
	//printf("\n%s",sql1);
	//printf("\n###############################");
 	nret=sqlite3_prepare(db,sql,strlen(sql1),&stmt,(const char**)(&zErrMsg));

	*persons=(struct person *)malloc(sizeof(struct person*)*20);
	if(nret!=SQLITE_OK)
  		return false;
	nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW){
		return 0;
	}
	printf("<table width='100%'\n");
	printf("<tr>\n");
	printf("<th>姓名</th>");
	printf("<th>学号</th>");
	printf("<th>密码</th>");
	printf("</tr>\n");
 	while(1){

        //(*persons+i)->id=sqlite3_column_int(stmt,0);//id
	  //id=sqlite3_column_int(stmt,0);//id
        (*persons+i)->name=(char*)malloc(sizeof(char)*9);
        //name=(char*)malloc(sizeof(char)*9);
        (*persons+i)->name=sqlite3_column_text(stmt,1);//name
			name=sqlite3_column_text(stmt,0);//name
        (*persons+i)->number=(char*)malloc(sizeof(char)*9);
        (*persons+i)->number=sqlite3_column_text(stmt,2);//number
	 		number=sqlite3_column_text(stmt,1);//number
        (*persons+i)->psw=(char*)malloc(sizeof(char)*9);
        (*persons+i)->psw=sqlite3_column_text(stmt,1);//psw
        psw=sqlite3_column_text(stmt,2);//psw
  	  //printf("\t%d\t\t%s\t\t%s\t%s\n",(*persons+i)->id,(*persons+i)->name,(*persons+i)->number,(*persons+i)->psw);
		printf("<tr>\n");
		printf("<th>%s</th>",name);
		printf("<th>%s</th>",number);
		printf("<th>%s</th>",psw);
		printf("</tr>\n");
       //printf("\t%s\t\t%s\t%s\n",name,number,psw);

       ++i;
		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
 	}
	printf("</table>");
 	sqlite3_finalize(stmt);
 	printf("\n");
 	return i;

}

//根据日期查找签到签退数据

int get_routines_by_date(char* date,struct routine ** routines){

    sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	int i=0;
	int id;

	int nret;

	char s[20];
       char* name;char* psw;char*number;
	char* pnumber;
	int cometime,date1,isLate,leavetime,isEarlyLeave;
 	//char *name,*id;
	//struct person** persons;
	char* sql=0;

	char sqltemp[256]="select * from routines where date=";
	//printf("cashu:%s\n",date);

	//sprintf(s,"%d" , date);//将int数据转换为字符串

	sql=strcat(sqltemp,date);

	sql=strcat(sql,";");

	 //printf("\n#############根据日期查找签到签退数据##################");
	//printf("\n%s",sql);
	//printf("\n###############################");
 	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));

	routines=(struct routines *)malloc(sizeof(struct routines*)*50);
	if(nret!=SQLITE_OK)
  		return false;
 	//printf("\n\tid\tnumber\t\t\tdata1\t\tcometime\tisLate\t\tleavetime\tisEarlyLeave\n");
 	//printf("\t------------------------------------------------------------\n");

 	// 	char sql[256]="CREATE TABLE routines

 	//(id INTEGER PRIMARY KEY AUTO_INCREMENT ,pnumber varchar(40),

     // date INTEGER, cometime INTEGER,

     //isLate INTEGER NOT NULL DEFAULT 0,leavetime INTEGER,isEarlyLeave NOT NULL DEFAULT 0);";
	nret=sqlite3_step(stmt);
  	if(nret!=SQLITE_ROW){
		return 0;
	}
	printf("<table width='100%'\n");
	printf("<tr>\n");
	printf("<th>序号</th>");
	printf("<th>学号</th>");
	printf("<th>日期</th>");
	printf("<th>签到时间</th>");
	//printf("<th>是否迟到</th>");
	printf("<th>签退时间</th>");
	//printf("<th>是否早退</th>");
	printf("</tr>\n");
 	while(1){

        //(*routines+i)->id=sqlite3_column_int(stmt,0);//id
	  		id=sqlite3_column_int(stmt,0);//id
        //(*routines+i)->pnumber=(char*)malloc(sizeof(char)*20);
        pnumber=(char*)malloc(sizeof(char)*9);
        pnumber=sqlite3_column_text(stmt,1);//pnumber
			//name=sqlite3_column_text(stmt,0);//name
        //(*routines+i)->number=(char*)malloc(sizeof(char)*9);
        //(*routines+i)->date=sqlite3_column_int(stmt,2);//date
			date1=sqlite3_column_int(stmt,2);
			//number=sqlite3_column_text(stmt,1);//number
        //(*routines+i)->cometime=sqlite3_column_int(stmt,3);

			cometime=sqlite3_column_int(stmt,3);
			//(*routines+i)->isLate=sqlite3_column_int(stmt,4);
			isLate=sqlite3_column_int(stmt,4);

        //(*routines+i)->leavetime=sqlite3_column_int(stmt,5);
			leavetime=sqlite3_column_int(stmt,5);

        //(*routines+i)->isEarlyLeave=sqlite3_column_int(stmt,6);
			isEarlyLeave=sqlite3_column_int(stmt,6);
/*
printf("\t%d\t%s\t\t%d\t%d\t%d\t%d\t%d\n",(*routines+i)->id,(*routines+i)->pnumber,(*routines+i)->date,(*routines+i)->cometime,(*routines+i)->isLate,(*routines+i)->leavetime,(*routines+i)->isEarlyLeave);*/
	printf("<tr>\n");
	printf("<th>%d</th>",id);
	printf("<th>%s</th>",pnumber);
	printf("<th>%d-%d-%d</th>",date1/10000,(date1%10000)/100,date1%100);
	printf("<th>%d:%d:%d</th>",cometime/10000,(cometime%10000)/100,cometime%100);
//	if(isLate==1){
//		printf("<th>是</th>");
//	}else{
//		printf("<th>否</th>");
//	}

	printf("<th>%d:%d:%d</th>",leavetime/10000,(leavetime%10000)/100,leavetime%100);
//	if(isEarlyLeave==1){
//		printf("<th>是</th>");
//	}else{
//		printf("<th>否</th>");
//	}
	printf("</tr>\n");
	//printf("\n\t%d\t%s\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n",id,pnumber,date1,cometime,isLate,leavetime,isEarlyLeave);
       //printf("\t\t%s\t\t%s\t%s\n",name,number,psw);

       ++i;
		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
 	}
 	sqlite3_finalize(stmt);
//	printf("</table>");
//	printf("<table border='1' width='100%'\n");
//	printf("<tr bgcolor='gray'>>\n");
//	printf("<th>总人数</th>");
//	printf("<th>迟到人数</th>");
//	printf("<th>早退人数</th>");
//	printf("</tr>\n");
//
//	printf("<tr>\n");
//	printf("<th>%d</th>",get_employee_count());
//	printf("<th>%d</th>",get_late_count(date));
//	printf("<th>%d</th>",get_early_leave_count(date));
//	printf("</tr>\n");
/*
 //总人数

        count=get_employee_count();
			printf("\n people count:%d ",count);

        //迟到人数

        count=get_late_count(param);
			printf("  late count:%d ",count);

        //早退人数

        count=get_early_leave_count(param);
			printf("  early leave count:%d ",count);
 	//printf("count %d\n",i);*/
 	return i;

}

//查找总人数

int get_employee_count(){

    int rc;
    int nret;
	sqlite3_stmt* stmt=NULL;
	char *zErrMsg = 0;
	//char* sql="update table routines set finishWorkTime="+finishWorkTime+"isEarlyLeave="+isEarlyLeave+"where id="+id+";";
	char sql[256]="select count(*) from persons;";
    //printf("\n##########people count#####################");
	//printf("\n%s",sql);
	//printf("\n###############################");
    nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
  		return -1;
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  	 		return sqlite3_column_int(stmt,0);
 	}
 	sqlite3_finalize(stmt);
    return -1;

}

 //根据日期查找迟到人数

int get_late_count(char* date){

    int rc;
    int nret;
	sqlite3_stmt* stmt=NULL;
	char *zErrMsg = 0;
	char* sql=0;
	//char* sql="update table routines set finishWorkTime="+finishWorkTime+"isEarlyLeave="+isEarlyLeave+"where id="+id+";";
	char sqltemp[256]="select count(*) from routines where date=";
    char s[20];
    //sprintf(s,"%d" , date);//将int数据转换为字符串
    sql=strcat(sqltemp,date);

    sql=strcat(sql," and isLate=1");
    sql=strcat(sql,";");
    //printf("\n##########late count#####################");
	//printf("\n%s",sql);
	//printf("\n###############################");
    nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
  		return -2;
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  	 		return sqlite3_column_int(stmt,0);
 	}
 	sqlite3_finalize(stmt);
    return -1;
}

//根据日期查找早退人数

int get_early_leave_count(char* date){

    int rc;
    int nret;
	sqlite3_stmt* stmt=NULL;
	char *zErrMsg = 0;
	char* sql;
	//char* sql="update table routines set finishWorkTime="+finishWorkTime+"isEarlyLeave="+isEarlyLeave+"where id="+id+";";
	char sqltemp[256]="select count(*) from routines where date=";
    char s[20];
    //sprintf(s,"%d" , date);//将int数据转换为字符串
    sql=strcat(sqltemp,date);

    strcat(sql," and isEarlyLeave=1");
    strcat(sql,";");
    //printf("\n##########查找早退数量#####################");
	//printf("\n%s",sql);
	//printf("\n###############################");
    nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
  		return -1;
 	while(1){
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  	 		return sqlite3_column_int(stmt,0);
 	}
 	sqlite3_finalize(stmt);
    return -1;
}
