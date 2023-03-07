#include<stdio.h>						 // gcc -o mysql mysql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
#include<stdlib.h>                      //  sudo ./mysql
#include<mysql.h>   //����ͷ�ļ�
 
void student_get_all(MYSQL *conn_prt); 

int main()
{
	MYSQL *conn_prt;     //����һ��MYSQL���
	conn_prt = mysql_init(NULL);  //��ʼ��MYSQL���
	int res; 
 
	if(!conn_prt)   //����ʼ�����ʧ��
	{
		printf("connect mysql failed");
		return -1;
	}
 
	/*������mysql���ݿ�����*/
	if(!mysql_real_connect(conn_prt,"localhost","root","123456","test",0,NULL,0))
	{
		printf("failed to coonect mysql:%s\n",mysql_error(conn_prt));
	}
 
	else
	{
		printf("connect success...........\n");
		student_get_all(conn_prt);
	}
 
 
	/*�ر���Mysql���ݿ�����ӣ����ͷ���Ӧ�ڴ�*/
	mysql_close(conn_prt);  //�ر����ӣ��ͷŶ�����ڴ�ռ�
	mysql_library_end();    //��������øú�������������ڴ�й¶
	return 0;
}

void student_get_all(MYSQL *conn_prt)    //��ȡ����ӡ student�� ���� 
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char buf[100];
    sprintf(buf, "SELECT * FROM student;");
    mysql_query(conn_prt, buf);
    result = mysql_store_result(conn_prt);
    if (result == NULL)
    {
 		//���Ϊ��
 		mysql_free_result(result);
        printf("null\n");
        return;
    }
    
    int r = mysql_num_rows(result);     //�� 
    int c = mysql_num_fields(result);   //�� 
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
    mysql_free_result(result);   //�ͷ�Ϊmysql_store_result,mysql_use_result����Ľ�����ڴ�
}

