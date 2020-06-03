#include "stdinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>  /*mysql数据库连接头文件*/

/*定义几个数据库连接相关宏*/
#define HOST "localhost"   
#define USERNAME "root"        // MySQL用户名
#define PASSWORD "123456"  // 登陆密码
#define DATABASE "collegeinfo"            // 数据库名

int main() {
	STU p = { 20000,"roy jones jr",250100 };
	PSTU p1= &p;
	PSTU p2 = query_stuino();
	/*
	printf("no is %d\n", p2->stu_no);
	printf("name is %s \n", p2->stu_name);
	printf("id is %d\n ", p2->stu_identify);
	*/
	query_sql(" select * from  stduinfo ");
	getchar();


	return 0;
}

/** query student**/
PSTU query_stuino() {
	/**局部变量地址分配在栈上，函数结束后，地址变量消失**/
	PSTU p1=(PSTU)malloc(sizeof(STU));
	if (p1 == NULL) {
		exit(1);
	}
	p1->stu_no = 2020;
	//结构体中的指针成员需要初始化后才能赋值
	p1->stu_name = (char *)malloc(sizeof(char)*40);
	if (p1->stu_name == NULL) {
		exit(1);
	}
	strcpy(p1->stu_name, "paul");
	p1->stu_identify = 230108;
	return p1;
}


void query_sql(char *sql) {
	MYSQL *conn;    // 数据库连接句柄
	int res;    // 执行sql返回结标志          
	MYSQL_RES *res_ptr;     // 指向查询结果的指针
	MYSQL_FIELD *field;     // 字段结构指针
	MYSQL_ROW result_row;   // 按行返回的查询信息
	int row, column;
	int i, j;


	// 初始化mysql连接 my_connection
	conn = mysql_init(NULL);
	// 建立mysql连接
	if (NULL != mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 3306, NULL, 0)) {

		printf("数据库查询query_sql连接成功!\n");

		// 设置查询编码为gbk, 支持中文
		mysql_query(conn, "set names gbk");
		res = mysql_query(conn, sql);

		if (res) {  // sql执行失败
			printf("Error: mysql_query!\n");
			mysql_close(conn);
		}
		else {  // 执行成功

				// 将查询结果给res_ptr
			res_ptr = mysql_store_result(conn);

			// 如果结果不为空就将结果打印到控制台
			if (res_ptr) {
				// 获取查询结果的列数和行数
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);
				printf("查询到%d行\n", row);

				// 输出结果字段的名字
				for (i = 0; field = mysql_fetch_field(res_ptr); i++) {
					printf("%10s ", field->name);
				}
				printf("\n");

				// 按行输出结果
				for (i = 1; i < row + 1; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++) {
						printf("%10s ", result_row[j]);
					}
					printf("\n");
				}
			}

			// 关闭数据库
			mysql_close(conn);
		}

	}

	// 数据库连失败
	else {
		printf("Error connecting to database:%s\n", mysql_error(conn));
		printf("数据库连接失败!");
	}
}