#include "stdinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>  /*mysql���ݿ�����ͷ�ļ�*/

/*���弸�����ݿ�������غ�*/
#define HOST "localhost"   
#define USERNAME "root"        // MySQL�û���
#define PASSWORD "123456"  // ��½����
#define DATABASE "collegeinfo"            // ���ݿ���

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
	/**�ֲ�������ַ������ջ�ϣ����������󣬵�ַ������ʧ**/
	PSTU p1=(PSTU)malloc(sizeof(STU));
	if (p1 == NULL) {
		exit(1);
	}
	p1->stu_no = 2020;
	//�ṹ���е�ָ���Ա��Ҫ��ʼ������ܸ�ֵ
	p1->stu_name = (char *)malloc(sizeof(char)*40);
	if (p1->stu_name == NULL) {
		exit(1);
	}
	strcpy(p1->stu_name, "paul");
	p1->stu_identify = 230108;
	return p1;
}


void query_sql(char *sql) {
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

		printf("���ݿ��ѯquery_sql���ӳɹ�!\n");

		// ���ò�ѯ����Ϊgbk, ֧������
		mysql_query(conn, "set names gbk");
		res = mysql_query(conn, sql);

		if (res) {  // sqlִ��ʧ��
			printf("Error: mysql_query!\n");
			mysql_close(conn);
		}
		else {  // ִ�гɹ�

				// ����ѯ�����res_ptr
			res_ptr = mysql_store_result(conn);

			// ��������Ϊ�վͽ������ӡ������̨
			if (res_ptr) {
				// ��ȡ��ѯ���������������
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);
				printf("��ѯ��%d��\n", row);

				// �������ֶε�����
				for (i = 0; field = mysql_fetch_field(res_ptr); i++) {
					printf("%10s ", field->name);
				}
				printf("\n");

				// ����������
				for (i = 1; i < row + 1; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++) {
						printf("%10s ", result_row[j]);
					}
					printf("\n");
				}
			}

			// �ر����ݿ�
			mysql_close(conn);
		}

	}

	// ���ݿ���ʧ��
	else {
		printf("Error connecting to database:%s\n", mysql_error(conn));
		printf("���ݿ�����ʧ��!");
	}
}