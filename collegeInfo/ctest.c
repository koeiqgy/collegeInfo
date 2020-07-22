#include <stdlib.h>
/*
STU p = { 20000,"roy jones jr",250100 };
PSTU p1= &p;
PSTU p2 = query_stuino();
printf("no is %d\n", p2->stu_no);
printf("name is %s \n", p2->stu_name);
printf("id is %d\n ", p2->stu_identify);
*/

void setPtr(int **i) {
	if (*i != NULL) {
		*i = NULL;
	}
	else {
		//*i = 0;
		*i = (int *)malloc(sizeof(int));
		**i = 0;
	}
}


void setPtrError(int *i) {
	if (i != NULL) {
		i = NULL;
	}
	else {
		//*i = 0;
		i = (int *)malloc(sizeof(int));
		*i = 0;
	}
}

int main1039() {
	printf("--start--\n");
	for (int i = 0;i=3;i++) {
		printf("%d ",i);
	}
	printf("--end--\n");
	getchar();
}