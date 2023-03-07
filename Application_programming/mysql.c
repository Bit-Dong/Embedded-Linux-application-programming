#include<stdio.h>						 // gcc -o mysql mysql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
#include<stdlib.h>                      //  sudo ./mysql
#include<mysql.h>   //所需头文件
 
void student_get_all(MYSQL *conn_prt); 

int main()
{
	MYSQL *conn_prt;     //创造一个MYSQL句柄
	conn_prt = mysql_init(NULL);  //初始化MYSQL句柄
	int res; 
 
	if(!conn_prt)   //若初始化句柄失败
	{
		printf("connect mysql failed");
		return -1;
	}
 
	/*尝试与mysql数据库连接*/
	if(!mysql_real_connect(conn_prt,"localhost","root","123456","test",0,NULL,0))
	{
		printf("failed to coonect mysql:%s\n",mysql_error(conn_prt));
	}
 
	else
	{
		printf("connect success...........\n");
		student_get_all(conn_prt);
	}
 
 
	/*关闭与Mysql数据库的连接，并释放相应内存*/
	mysql_close(conn_prt);  //关闭连接，释放对象的内存空间
	mysql_library_end();    //如果不调用该函数，可能造成内存泄露
	return 0;
}

void student_get_all(MYSQL *conn_prt)    //获取并打印 student表 数据 
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char buf[100];
    sprintf(buf, "SELECT * FROM student;");
    mysql_query(conn_prt, buf);
    result = mysql_store_result(conn_prt);
    if (result == NULL)
    {
 		//结果为空
 		mysql_free_result(result);
        printf("null\n");
        return;
    }
    
    int r = mysql_num_rows(result);     //行 
    int c = mysql_num_fields(result);   //列 
    //printf("%d %d\n", r, c);
    printf("%s\n",buf);

    for (int i = 0; i < r; ++i)
    {
        row = mysql_fetch_row(result);
        for (int j = 0; j < c; ++j)
        {
            if (row[j] == NULL) printf("null");
            else printf("%s ", row[j]);
        }
        printf("\n");
    }
    mysql_free_result(result);   //释放为mysql_store_result,mysql_use_result分配的结果集内存
}

