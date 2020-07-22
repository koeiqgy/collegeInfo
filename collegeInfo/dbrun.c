#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>  /*mysql���ݿ�����ͷ�ļ�*/
#include <malloc.h>
#include "dbrun.h"



int main() {
	//print_data(" select * from  stduinfo ", NULL);
	query_result(" select * from  stduinfo ", NULL);
	getchar();
}

//����sql��䷵�ؽ����
MYSQL_RES * query_result(char *sql, char * colums) {
	MYSQL *conn;
	conn = mysql_init(NULL);
	MYSQL *conn2 = mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 3306, NULL, 0);
	mysql_query(conn2, "set names gbk");
	int res2 = mysql_query(conn2, sql);
	printf("����ֵ %d \n", res2);
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


//��ѯ��ӡsql���
void print_data(char *sql, char * colums) {
	MYSQL *conn;    // ���ݿ����Ӿ��
	int res;    // ִ��sql���ؽ��־          
	MYSQL_RES *res_ptr;     // ָ���ѯ�����ָ��
	MYSQL_FIELD *field;     // �ֶνṹָ��
	MYSQL_ROW result_row;   // ���з��صĲ�ѯ��Ϣ
	int row, column;
	int i, j;
	// ��ʼ��mysql���� my_connection
	conn = mysql_init(NULL);
	// ����mysql����
	if (NULL != mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 3306, NULL, 0)) {
		//conn_mysql_info(0);
		// ���ò�ѯ����Ϊgbk, ֧������
		mysql_query(conn, "set names gbk");
		res = mysql_query(conn, sql);
		if (res) {  // sqlִ��ʧ��
					//res ����ֵ��Ϊ0 ˵�����ش���,��ӡ������Ϣ
			char * error_str = error_mysql_info(conn);
			mysql_close(conn);
		}
		else {
			// ִ�гɹ�
			// ����ѯ�����res_ptr
			res_ptr = mysql_store_result(conn);
			// ��������Ϊ�վͽ������ӡ������̨
			if (res_ptr) {
				// ��ȡ��ѯ���������������
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);
				printf("��ѯ��%d�� %d��\n", row, column);
				//int arr_colums[10] = {0};
				//��̬���鸳ֵ
				int *arr_colums = malloc(sizeof(int)*column);
				// �������ֶε�����
				for (i = 0; field = mysql_fetch_field(res_ptr);i++) {
					if (colums == NULL || strcmp("", colums) == 0 || strcmp(field->name, colums) == 0) {
						arr_colums[i] = 1;
						printf("%10s ", field->name);
					}
				}
				printf("\n");
				// ����������
				for (i = 1; i < row + 1; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++) {
						if (arr_colums[j] == 1) {
							printf("%10s ", result_row[j]);
						}
					}
					printf("\n");
				}
				//�ͷ�������ڴ�
				free(arr_colums);
			}
			// �ر����ݿ�
			mysql_close(conn);
		}
	}
	// ���ݿ���ʧ��
	else {
		//printf("Error connecting to database:%s\n", mysql_error(conn));
		char * error_str = error_mysql_info(conn);
		printf("���ݿ�����ʧ��!");
	}
}

/**
mysql ��ȡ������־����
**/
char * error_mysql_info(MYSQL *conn) {
	char *error_str = mysql_error(conn);
	printf("Error connecting to database:%s\n", error_str);
	return error_str;
}

/**
mysql ���ݿ����ӳɹ���־ 0����ɹ� 1����ʧ��
**/
int conn_mysql_info(int code) {
	int ret_code = 0;
	if (code) {
		printf("���ݿ��ѯquery_sql����ʧ��!\n");
		ret_code = 1;
	}
	else {
		printf("���ݿ��ѯquery_sql���ӳɹ�!\n");
	}
	return ret_code;
}