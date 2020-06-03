#pragma once
#include <malloc.h>
/**student info struct**/
struct STUDENT {
	int  stu_no;
	char *stu_name;
	int  stu_identify;
};
typedef struct STUDENT STU;
typedef struct STUDENT *PSTU;

PSTU query_stuino();
void query_sql(char *sql);