#ifndef STUDENT_H
#define STUDENT_H
#include "mylib.h"

//存储学生信息的路径
#define STU_DB "./data/student.db"

typedef struct student{
	int id;
	char name[NAME_LEN+1];
	char gender[4];
	int age;
	int c_score;
	int cpp_score;
	char psw[PSW_LEN+1];
}STUDENT;

typedef struct student_ptr {
	STUDENT stu;
	struct student_ptr *prev;
	struct student_ptr *next;
}STU_LIST;


int stu_opt();

int stu_add();
void add_stu_dislay(STUDENT stu);
void login_stu_msg(STUDENT stu);
int stu_find(int type);
void find_stu_msg();
void stu_data_display(STUDENT *stu, int num);

int stu_list_read(STU_LIST *handle, int start, int cnt);
int stu_list_display(STU_LIST *handle,int start, int cnt);
void stu_sort_age(STU_LIST *head,const int len);
void stu_sort_id(STU_LIST *head,const int len);
void stu_sort_c(STU_LIST *head,const int len);
void stu_sort_gender(STU_LIST *head,const int len);
void stu_sort_cpp(STU_LIST *head,const int len);
void stu_free(STU_LIST *head);
void clear_stu_display();
#endif
