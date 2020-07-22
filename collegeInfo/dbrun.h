/*定义几个数据库连接相关宏*/
#define HOST "localhost"   
#define USERNAME "root"        // MySQL用户名
#define PASSWORD "123456"  // 登陆密码
#define DATABASE "collegeinfo"            // 数据库名

char * error_mysql_info(MYSQL *conn);
int conn_mysql_info(int code);
void print_data(char *sql, char *colum);
MYSQL_RES * query_result(char *sql);

typedef struct DB_DATA_RES {
	char **  cloums;
	char ** data;
}DB_DATA_RES;

typedef DB_DATA_RES * DB_DATA_RES_PTR;