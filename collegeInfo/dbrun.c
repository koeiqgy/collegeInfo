#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>  /*mysql数据库连接头文件*/
#include <malloc.h>
#include "dbrun.h"



int main() {
	//print_data(" select * from  stduinfo ", NULL);
	query_result(" select * from  stduinfo ", NULL);
	getchar();
}

//根据sql语句返回结果集
MYSQL_RES * query_result(char *sql, char * colums) {
	MYSQL *conn;
	conn = mysql_init(NULL);
	MYSQL *conn2 = mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 3306, NULL, 0);
	mysql_query(conn2, "set names gbk");
	int res2 = mysql_query(conn2, sql);
	printf("返回值 %d \n", res2);
	MYSQL_RES *res_ptr2 = mysql_store_result(conn2);
	DB_DATA_RES_PTR db_data_res = malloc(sizeof(DB_DATA_RES));
	int row_count = res_ptr2->row_count;
	int field_count = res_ptr2->field_count;
	printf("row_count=%d \n", row_count);
	printf("field_count=%d \n", field_count);
	int i,j,k;

	int *arrs_data = malloc(sizeof(int)*field_count);
	for (i=0;i < field_count;i++) {
		MYSQL_FIELD *field = mysql_fetch_field(res_ptr2);
		//printf("equal is %d ", strcmp(field->name, colum) == 0);
		if (colums==NULL || strcmp("", colums)==0 || strcmp(field->name, colums) == 0) {
			arrs_data[i] = 1;
			printf("%s  ", field->name);
		}
	}
	printf("\n");

	for (j = 1;j <= row_count;j++) {
		MYSQL_ROW result_row = mysql_fetch_row(res_ptr2);
		for (k = 0;k < field_count;k++) {
			if (arrs_data[k] == 1) {
				printf("%s ", result_row[k]);
			}
		}
		printf("\n");
	}



	/*
	MYSQL_ROW mysql_row = mysql_fetch_row(res_ptr2);
	printf("%s \n", mysql_row[1]);
	mysql_row = mysql_fetch_row(res_ptr2);
	printf("%s \n", mysql_row[1]);
	*/
}


//查询打印sql语句
void print_data(char *sql, char * colums) {
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
		//conn_mysql_info(0);
		// 设置查询编码为gbk, 支持中文
		mysql_query(conn, "set names gbk");
		res = mysql_query(conn, sql);
		if (res) {  // sql执行失败
					//res 返回值不为0 说明返回错误,打印错误信息
			char * error_str = error_mysql_info(conn);
			mysql_close(conn);
		}
		else {
			// 执行成功
			// 将查询结果给res_ptr
			res_ptr = mysql_store_result(conn);
			// 如果结果不为空就将结果打印到控制台
			if (res_ptr) {
				// 获取查询结果的列数和行数
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);
				printf("查询到%d行 %d列\n", row, column);
				//int arr_colums[10] = {0};
				//动态数组赋值
				int *arr_colums = malloc(sizeof(int)*column);
				// 输出结果字段的名字
				for (i = 0; field = mysql_fetch_field(res_ptr);i++) {
					if (colums == NULL || strcmp("", colums) == 0 || strcmp(field->name, colums) == 0) {
						arr_colums[i] = 1;
						printf("%10s ", field->name);
					}
				}
				printf("\n");
				// 按行输出结果
				for (i = 1; i < row + 1; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++) {
						if (arr_colums[j] == 1) {
							printf("%10s ", result_row[j]);
						}
					}
					printf("\n");
				}
				//释放申请的内存
				free(arr_colums);
			}
			// 关闭数据库
			mysql_close(conn);
		}
	}
	// 数据库连失败
	else {
		//printf("Error connecting to database:%s\n", mysql_error(conn));
		char * error_str = error_mysql_info(conn);
		printf("数据库连接失败!");
	}
}

/**
mysql 获取错误日志函数
**/
char * error_mysql_info(MYSQL *conn) {
	char *error_str = mysql_error(conn);
	printf("Error connecting to database:%s\n", error_str);
	return error_str;
}

/**
mysql 数据库连接成功日志 0代表成功 1代表失败
**/
int conn_mysql_info(int code) {
	int ret_code = 0;
	if (code) {
		printf("数据库查询query_sql连接失败!\n");
		ret_code = 1;
	}
	else {
		printf("数据库查询query_sql连接成功!\n");
	}
	return ret_code;
}