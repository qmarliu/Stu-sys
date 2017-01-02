#include "student.h"
#include "show.h"
/*#include "list.h"*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//功  能: 学生的主要功能选择
//返回值:	0, 正常返回
//			-1，文件不存在、打开或创建失败
//			-2, 退出登录
int stu_opt()
{
	STUDENT stu;
	int ret = stu_vertify(&stu);
	if(ret == -1)
		return -1;
	if(ret == -2)
		return -2;
	alt_tips("学生登录成功");
	for(;;) {
		stu_opt_show();
		login_stu_msg(stu);
		int select = get_select();

		switch(select)
		{
			case 1: //老师查询
				/*
				 *ret = stu_add();
				 *if( ret==0 ) {
				 *    alt_tips("添加成功");
				 *} else if(ret == -1) {
				 *    alt_tips("文件错误，密码修改失败");
				 *} else if(ret == -2) {
				 *    alt_tips("已取消添加");
				 *}
				 */
				break;
			case 2: //学生修改密码
				break;
			case -1:
				return -2;
			default:
				break;
		}
	}
}

//功  能: 添加学生到数据
//返回值: 0,添加成功
//		  -1，文件操作失败
//		  -2, 取消添加
int stu_add()
{
	if( access(STU_DB, F_OK) != 0 ) { 
	//没有学生数据，初始化数据文件
		FILE *fp = fopen(STU_DB, "w");
		ERRP( fp==NULL, "fopen", return -1);
		int id_start = STU_ID_START;
		fwrite(&id_start, 4, 1, fp);
		fclose(fp);
	}

	alt_tips("");
	stu_add_show();
	STUDENT stu;
	FILE *fp = fopen(STU_DB, "r");
	ERRP( fp==NULL, "fopen", return -1);
	fread(&stu.id, 4, 1, fp);
	fclose(fp);

	printf("\033[%d;%dH\033[34m添加学号 \033[32m%d \033[34m的学生信息.\033[0m",MAIN_X_SUB-2, MAIN_Y_SUB + 15, ++stu.id);
	printf("\033[%d;%dH", MAIN_X_SUB, MAIN_Y_SUB+10);
	get_name(stu.name, MAIN_X_SUB, MAIN_Y_SUB+10);
	if( strcmp(stu.name, "B")==0 || strcmp(stu.name, "b")==0 ) 
		return -2;

	printf("\033[%d;%dH", MAIN_X_SUB+2, MAIN_Y_SUB+10);
	get_gender(stu.gender, MAIN_X_SUB+2, MAIN_Y_SUB+10);
	if( strcmp(stu.gender, "B")==0 || strcmp(stu.gender, "b")==0 ) 
		return -2;
	
	char ch_num[4];
	printf("\033[%d;%dH", MAIN_X_SUB+4, MAIN_Y_SUB+10);
	get_int(ch_num);
	if( strcmp(ch_num, "B")==0 || strcmp(ch_num, "b")==0 ) 
		return -2;
	stu.age = atoi(ch_num);//年龄
	if(stu.age<=0 || stu.age >=100)
		stu.age = 23;

	printf("\033[%d;%dH", MAIN_X_SUB+6, MAIN_Y_SUB+10);
	get_int(ch_num);
	if( strcmp(ch_num, "B")==0 || strcmp(ch_num, "b")==0 ) 
		return -2;
	stu.c_score = atoi(ch_num);//c成绩
	if(stu.c_score<0 || stu.c_score >100)
		stu.c_score = 0;

	printf("\033[%d;%dH", MAIN_X_SUB+8, MAIN_Y_SUB+10);
	get_int(ch_num);
	if( strcmp(ch_num, "B")==0 || strcmp(ch_num, "b")==0 ) 
		return -2;
	stu.cpp_score = atoi(ch_num);//cpp成绩
	if(stu.cpp_score<0 || stu.cpp_score >100)
		stu.cpp_score = 0;

	strcpy(stu.psw,"123");

	alt_tips("");
	confirm_show("是否添加此学生信息?");
	add_stu_dislay(stu);
	printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
	char ch;
	scanf("%c", &ch);
	while(getchar() != '\n');

	if(ch != 'y' && ch != 'Y') {
		return -2;
	}
	fp = fopen(STU_DB, "r+");
	ERRP( fp==NULL, "fopen", return -1);
	fwrite(&stu.id, 4, 1, fp);
	fseek(fp, 0, SEEK_END);
	fwrite(&stu, sizeof(STUDENT), 1, fp);
	fclose(fp);
	system("clear");
	return 0;
}

//功  能: 新添加的学生显示在侧边栏
void add_stu_dislay(STUDENT stu)
{
	printf("\033[%d;%dH\033[36m", MAIN_X_SUB -1, DIVISION_START_COL+20);
	printf("学    号: %d",stu.id);
	printf("\033[%d;%dH", MAIN_X_SUB + 1, DIVISION_START_COL+20);
	printf("姓    名: %s",stu.name);
	printf("\033[%d;%dH", MAIN_X_SUB + 3, DIVISION_START_COL+20);
	printf("性    别: %s",stu.gender);
	printf("\033[%d;%dH", MAIN_X_SUB + 5, DIVISION_START_COL+20);
	printf("年    龄: %d",stu.age);
	printf("\033[%d;%dH", MAIN_X_SUB + 7, DIVISION_START_COL+20);
	printf("C   成绩: %d",stu.c_score);
	printf("\033[%d;%dH", MAIN_X_SUB + 9, DIVISION_START_COL+20);
	printf("CPP 成绩: %d",stu.cpp_score);
	printf("\033[%d;%dH", MAIN_X_SUB + 11, DIVISION_START_COL+20);
	printf("密    码: %s",stu.psw);
	printf("\033[0m");
	fflush(NULL);
}

//功  能: 显示登录学生的信息在作者栏以上
void login_stu_msg(STUDENT stu)
{
	printf("\033[%d;%dH\033[33m", AUTHOR_X_SUB-3, DIVISION_START_COL);
	printf("|学号: ");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+6);
	printf("%d", stu.id);

	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+17+6);
	printf("|姓名:");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+6+24);
	printf("%s",stu.name);

	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+17+30);
	printf("|性别:");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+6+47);
	printf("%s",stu.gender);

	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+17+53);
	printf("|年龄:");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+6+70);
	printf("%d",stu.age);

	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+17+76);
	printf("|c成绩:");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+7+93);
	printf("%d",stu.c_score);
	
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+17+100);
	printf("|cpp成绩:");
	printf("\033[%d;%dH", AUTHOR_X_SUB-3, DIVISION_START_COL+9+117);
	printf("%d",stu.cpp_score);

	printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
	fflush(NULL);
}


//功  能: 学生验证
//返回值: 0,验证成功
//		  -1,文件操作失败
//		  -2,取消登录,返回主界面
//		  -3,没有学生信息
int stu_vertify(STUDENT *stu)
{
	if( access(STU_DB, F_OK) != 0 ) {
		return -1;
	}
	int last_id,tmp_id=0;
	FILE *fp = fopen(STU_DB, "r");
	ERRP( fp==NULL, "fopen", return -1);
	fread(&last_id, 4, 1, fp);
	fclose(fp);
	if( last_id == STU_ID_START ) {
		return -3;
	}
	alt_tips("");
	stu_tea_vertify_show();

	for(;;) {
		cover_char( MAIN_X_SUB, MAIN_Y_SUB + 12 , CONSOLE_LEN - (MAIN_Y_SUB + 12));
		cover_char( MAIN_X_SUB + 2, MAIN_Y_SUB + 12 , CONSOLE_LEN - (MAIN_Y_SUB + 12));
		char ch_id[11];
		for(;;) { //获取学生ID;
			printf("\033[%d;%dH", MAIN_X_SUB, MAIN_Y_SUB+12);
			get_int(ch_id);
			if( strcmp(ch_id, "B")==0 || strcmp(ch_id, "b")==0 ) 
				return -2;
			tmp_id = atoi(ch_id);
			if(tmp_id <= STU_ID_START || tmp_id > last_id) {
				cover_char( WARNING_X, 0, CONSOLE_LEN);
				printf("\033[%d;%dH\033[31m没有学号为 %d 的学生\033[0m\n",WARNING_X, WARNING_Y, tmp_id);
				cover_char( MAIN_X_SUB, MAIN_Y_SUB + 12 , CONSOLE_LEN - (MAIN_Y_SUB + 12));
				continue;
			}
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			break;
		}	
		char str_psw[PSW_LEN+1];
		printf("\033[%d;%dH", MAIN_X_SUB + 2, MAIN_Y_SUB+12);
		get_psw(str_psw); //获取学生登录密码
		if( strcmp(str_psw, "B")==0 || strcmp(str_psw, "b")==0 ) 
			return -2;

		FILE *fp = fopen(STU_DB, "r");
		ERRP( fp==NULL, "fopen", return -1);
		fseek( fp, 4+(tmp_id-STU_ID_START-1)*sizeof(STUDENT), SEEK_SET);
		fread(stu, sizeof(STUDENT), 1, fp);
		fclose(fp);
		if( stu->id == STU_DELETE_ID ) {
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			printf("\033[%d;%dH\033[31m学号为 %d 的学生已被管理员删除\033[0m\n",WARNING_X, WARNING_Y, stu->id);
		 	continue;
		}
		if( strcmp(str_psw, stu->psw) != 0) {
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			printf("\033[%d;%dH\033[31m用户名或密码错误\033[0m\n",WARNING_X, WARNING_Y);
			continue;
		}
		break;
	}
	return 0;
}

//功  能: 学生查找
//参  数: 0,管理员查找学生 1,老师查找学生
//返回值: 0,退出查询
//		  -1,文件错误
int stu_find(int type)
{
	if( access(STU_DB, F_OK) != 0 ) {
		return -1;
	}
	alt_tips("学生信息");
	stu_find_show();
	find_stu_msg();

	int len=0;
	FILE *fp = fopen(STU_DB, "r");
	ERRP( fp==NULL, "fopen", return -1);
	fread(&len, 4, 1, fp);
	fclose(fp);
	len -= STU_ID_START;

	//显示学生信息
	STU_LIST handle; 
	memset(&handle, 0, sizeof(STU_LIST));
	handle.next = &handle;
	handle.prev = &handle;
	/*将STU_SHOW_CNT个学生的信息，读到handle中*/
	stu_list_read( &handle, 0, len);
	int cnt=0,tmp;
	char ch;
	const int GAP = 15;
	const int offset = 24;
	printf("\033[%d;%dH\033[32m", MAIN_X_SUB , DIVISION_START_COL+offset);
	printf("学号");

	printf("\033[%d;%dH", MAIN_X_SUB, DIVISION_START_COL+offset+GAP);
	printf("姓名");

	printf("\033[%d;%dH", MAIN_X_SUB, DIVISION_START_COL+offset+2*GAP);
	printf("性别");

	printf("\033[%d;%dH", MAIN_X_SUB, DIVISION_START_COL+offset+3*GAP);
	printf("年龄");

	printf("\033[%d;%dH", MAIN_X_SUB, DIVISION_START_COL+offset+4*GAP);
	printf("C成绩");

	printf("\033[%d;%dH", MAIN_X_SUB, DIVISION_START_COL+offset+5*GAP);
	printf("Cpp成绩");

	fflush(NULL); 
	for(;;) {
		/*将handle中的信息显示出来*/
		tmp = stu_list_display(&handle, cnt, SHOW_CNT);
		cnt += tmp;

INPUT:
		//光标定位在输入区
		cover_char( MAIN_X_SUB-5 , MAIN_Y_SUB+6, CONSOLE_LEN-(MAIN_Y_SUB+6));
		printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
		//用户输入选择
		ch = getchar();
		if(ch=='\n') {
			break;
		}
		while(getchar()!='\n');

		cover_char( WARNING_X, 0, CONSOLE_LEN);
		switch(ch) 
		{
			case 'n':
				if(len <= cnt) {
					cnt -= tmp;
					printf("\033[%d;%dH\033[31m已经是最后页\033[0m\n",WARNING_X, WARNING_Y);	
				} else {
					clear_stu_display();
				}	
				break;
			case 'N':
				cnt -= tmp;
				cnt -= SHOW_CNT;
				if(cnt < 0) {
					cnt += SHOW_CNT;
					printf("\033[%d;%dH\033[31m已经是开始页\033[0m\n",WARNING_X, WARNING_Y);
				} else {
					clear_stu_display();
				}
				break;
			case 'Q':
			case 'q':
				system("clear");
				exit(0);
			case 'B':
			case 'b':
				return 0;

			case '1':
				clear_stu_display();
				stu_sort_id(&handle, len);
				cnt =0;
				break;
			case '2':
				clear_stu_display();
				stu_sort_gender(&handle, len);
				cnt =0;
				break;
			case '3':
				clear_stu_display();
				stu_sort_age(&handle, len);
				cnt =0;
				break;
			case '4':
				clear_stu_display();
				stu_sort_c(&handle, len);
				cnt =0;
				break;
			case '5':
				clear_stu_display();
				stu_sort_cpp(&handle, len);
				cnt =0;
				break;

			default:
				cover_char( WARNING_X, 0, CONSOLE_LEN);
				printf("\033[%d;%dH\033[31m请按提示输入\033[0m\n",WARNING_X, WARNING_Y);
				goto INPUT;
		}
	}

	//获取学号
	char ch_id[6]="";
	printf("\033[%d;%dH\033[32m", MAIN_X_SUB-3, DIVISION_START_COL + 6);
	fgets(ch_id, NAME_LEN+1, stdin);
	if(ch_id[strlen(ch_id)-1] == '\n')
		ch_id[strlen(ch_id)-1] = '\0';
	else
		while(getchar()!='\n');
    if( strcmp(ch_id, "B")==0 || strcmp(ch_id, "b")==0 ) 
		return 0;

	//获取名字
	char ch_name[NAME_LEN+1]="";
	printf("\033[%d;%dH", MAIN_X_SUB-3, DIVISION_START_COL+17+6 + 6);
	fgets(ch_name, NAME_LEN+1, stdin);
	if(ch_name[strlen(ch_name)-1] == '\n')
		ch_name[strlen(ch_name)-1] = '\0';
	else
		while(getchar()!='\n');
	if( strcmp(ch_name, "B")==0 || strcmp(ch_name, "b")==0 ) 
		return 0;

	//获取性别
	char ch_gender[4]="";
	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+30+6);
	if(ch_gender[strlen(ch_gender)-1] == '\n')
		ch_gender[strlen(ch_gender)-1] = '\0';
	else
		while(getchar()!='\n');
	if( strcmp(ch_gender, "B")==0 || strcmp(ch_gender, "b")==0 ) 
		return 0;

	//获取年龄
	char ch_age[4]="";
	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+53+6);
	get_int(ch_age);
	if( strcmp(ch_age, "B")==0 || strcmp(ch_age, "b")==0 ) 
		return 0;

	//获取c成绩
	char ch_c[4]="";
	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+76+6);
	get_int(ch_c);
	if( strcmp(ch_c, "B")==0 || strcmp(ch_c, "b")==0 ) 
		return 0;
	
	char ch_cpp[4]="";
	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+100+6);
	get_int(ch_cpp);
	if( strcmp(ch_cpp, "B")==0 || strcmp(ch_cpp, "b")==0 ) 
		return 0;
	
	clear_stu_display();
	STU_LIST *tail = handle.next;
	if(strcmp(ch_id,"")!=0) {
		int id = atoi(ch_id);
		for(tail=handle.next; tail!=&handle; tail =tail->next) {
			if(tail->stu.id == id) {
				stu_data_display(&tail->stu, 1);
				break;
			}
		}
		if(tail==&handle) {
			printf("\033[%d;%dH\033[32m", MAIN_X_SUB+2 , DIVISION_START_COL+24);
			printf("查询没有结果\n");	
		}
	} else {
		printf("\033[%d;%dH\033[32m", MAIN_X_SUB+2 , DIVISION_START_COL+24);
		printf("查询没有结果.\n");	
	}
	printf("\033[0m");
	getchar();
	stu_free(&handle);
}


//学号排序
void stu_sort_id(STU_LIST *head,const int len)
{
	STU_LIST *p = head->next;
	STU_LIST *q = head->next;
	STUDENT stu;
	for(p=head; p->next!=head; p=p->next) {
		for(q=head->next; q!=head; q=q->next) {
			if(p->stu.id > q->stu.id) {
				memcpy(&stu, &q->stu, sizeof(STUDENT));
				memcpy(&q->stu, &p->stu, sizeof(STUDENT));
				memcpy(&p->stu,&stu, sizeof(STUDENT));
			} //end if
		} //end q
	}
	p = head->prev;
	for(q=head->next;q!=p;q=q->next) {
		if(p->stu.id > q->stu.id) {
			memcpy(&stu, &q->stu, sizeof(STUDENT));
			memcpy(&q->stu, &p->stu, sizeof(STUDENT));
			memcpy(&p->stu,&stu, sizeof(STUDENT));	
		}
	}
}

//性别排序
void stu_sort_gender(STU_LIST *head,const int len)
{
	STU_LIST *p = head->next;
	STU_LIST *q = head->next;
	STUDENT stu;
	for(p=head; p->next!=head; p=p->next) {
		for(q=head->next; q!=head; q=q->next) {
			if(strcmp(p->stu.gender, q->stu.gender)>0) {
				memcpy(&stu, &q->stu, sizeof(STUDENT));
				memcpy(&q->stu, &p->stu, sizeof(STUDENT));
				memcpy(&p->stu,&stu, sizeof(STUDENT));
			} //end if
		} //end q
	}
	p = head->prev;
	for(q=head->next;q!=p;q=q->next) {
		if(strcmp(p->stu.gender, q->stu.gender)>0) {
			memcpy(&stu, &q->stu, sizeof(STUDENT));
			memcpy(&q->stu, &p->stu, sizeof(STUDENT));
			memcpy(&p->stu,&stu, sizeof(STUDENT));	
		}
	}
}

//年龄排序
void stu_sort_age(STU_LIST *head,const int len)
{
	STU_LIST *p = head->next;
	STU_LIST *q = head->next;
	STUDENT stu;
	for(p=head; p->next!=head; p=p->next) {
		for(q=head->next; q!=head; q=q->next) {
			if(p->stu.age > q->stu.age) {
				memcpy(&stu, &q->stu, sizeof(STUDENT));
				memcpy(&q->stu, &p->stu, sizeof(STUDENT));
				memcpy(&p->stu,&stu, sizeof(STUDENT));
			} //end if
		} //end q
	}
	p = head->prev;
	for(q=head->next;q!=p;q=q->next) {
		if(p->stu.age > q->stu.age) {
			memcpy(&stu, &q->stu, sizeof(STUDENT));
			memcpy(&q->stu, &p->stu, sizeof(STUDENT));
			memcpy(&p->stu,&stu, sizeof(STUDENT));	
		}
	}
}

//c成绩排序
void stu_sort_c(STU_LIST *head,const int len)
{
	STU_LIST *p = head->next;
	STU_LIST *q = head->next;
	STUDENT stu;
	for(p=head; p->next!=head; p=p->next) {
		for(q=head->next; q!=head; q=q->next) {
			if(p->stu.c_score > q->stu.c_score) {
				memcpy(&stu, &q->stu, sizeof(STUDENT));
				memcpy(&q->stu, &p->stu, sizeof(STUDENT));
				memcpy(&p->stu,&stu, sizeof(STUDENT));
			} //end if
		} //end q
	}
	p = head->prev;
	for(q=head->next;q!=p;q=q->next) {
		if(p->stu.c_score > q->stu.c_score) {
			memcpy(&stu, &q->stu, sizeof(STUDENT));
			memcpy(&q->stu, &p->stu, sizeof(STUDENT));
			memcpy(&p->stu,&stu, sizeof(STUDENT));	
		}
	}
}

//cpp成绩排序
void stu_sort_cpp(STU_LIST *head,const int len)
{
	STU_LIST *p = head->next;
	STU_LIST *q = head->next;
	STUDENT stu;
	for(p=head; p->next!=head; p=p->next) {
		for(q=head->next; q!=head; q=q->next) {
			if(p->stu.cpp_score > q->stu.cpp_score) {
				memcpy(&stu, &q->stu, sizeof(STUDENT));
				memcpy(&q->stu, &p->stu, sizeof(STUDENT));
				memcpy(&p->stu,&stu, sizeof(STUDENT));
			} //end if
		} //end q
	}
	p = head->prev;
	for(q=head->next;q!=p;q=q->next) {
		if(p->stu.cpp_score > q->stu.cpp_score) {
			memcpy(&stu, &q->stu, sizeof(STUDENT));
			memcpy(&q->stu, &p->stu, sizeof(STUDENT));
			memcpy(&p->stu,&stu, sizeof(STUDENT));	
		}
	}
}


//功  能: 释放空间
void stu_free(STU_LIST *head)
{
	STU_LIST *tail, *tmp;
	for(tail = head->next; tail!=head; tail = tmp ) {
		tmp = tail->next;
		free(tail);	
	}
}

//功  能: 在handle中存入STU_DB中start开始的cnt个数据
//返回值: 实际存入hanlde中的数据
int stu_list_read(STU_LIST *handle, int start, int cnt)
{
	FILE *fp = fopen(STU_DB, "r");
	ERRP( fp==NULL, "fopen", return 0);
	int i,len;
	fread(&len, 4, 1, fp);
	len = len - STU_ID_START;
	if(len <= start)
		return 0;
	if(len > cnt+start)
		len = cnt+start;
	fseek(fp, 4+(start)*sizeof(STUDENT), SEEK_SET);
	STU_LIST *tail= handle;
	for(i=0; i<len-start; ++i,tail= tail->next) {
		STU_LIST *newD  = (STU_LIST *)malloc(sizeof(STU_LIST));
		fread(&newD->stu, sizeof(STUDENT), 1, fp);
		newD->next = handle;
		newD->prev = tail;
		tail->next = newD;
		handle->prev = newD;
	}
	return len-start; 
}

//功  能: 显示handle中的数据
int stu_list_display(STU_LIST *handle, int start, int cnt)
{
	STU_LIST *tail;
	int i;
	for(tail=handle->next, i=0; tail!=handle && i!=start ; ++i, tail = tail->next);
	if(tail == handle)
		return 0;
	for(i=0; tail!=handle && i<cnt; ++i, tail = tail->next) {
		stu_data_display(&tail->stu, i);
 	} 
	return i;
}
//功  能: 覆盖已经显示的学生信息
void clear_stu_display()
{
	int num;
	for(num=0;num<SHOW_CNT; ++num) {
		cover_char( 2+MAIN_X_SUB + 2*num, 0, CONSOLE_LEN);
	}
	fflush(NULL); 
}

//显示学生结构体信息
void stu_data_display(STUDENT *stu, int num)
{
	const int GAP = 15;
	const int offset = 24;
	printf("\033[%d;%dH\033[32m",2+ MAIN_X_SUB+2*num , DIVISION_START_COL+offset);
	printf("%d",stu->id);

	printf("\033[%d;%dH",2+ MAIN_X_SUB+2*num, DIVISION_START_COL+offset+GAP);
	printf("%s",stu->name);

	printf("\033[%d;%dH",2+ MAIN_X_SUB+2*num, DIVISION_START_COL+offset+2*GAP);
	printf("%s",stu->gender);

	printf("\033[%d;%dH", 2+MAIN_X_SUB+2*num, DIVISION_START_COL+offset+3*GAP);
	printf("%d",stu->age);

	printf("\033[%d;%dH",2+ MAIN_X_SUB+2*num, DIVISION_START_COL+offset+4*GAP);
	printf("%d",stu->c_score);

	printf("\033[%d;%dH",2+ MAIN_X_SUB+2*num, DIVISION_START_COL+offset+5*GAP);
	printf("%d",stu->cpp_score);

	printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
	fflush(NULL); 
}

//功  能: 显示查找条件
void find_stu_msg()
{
	printf("\033[%d;%dH\033[33m", MAIN_X_SUB-3, DIVISION_START_COL);
	printf("学号:_______");

	printf("\033[%d;%dH", MAIN_X_SUB-3, DIVISION_START_COL+17+6);
	printf("姓名:_______");

	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+30);
	printf("性别:_______");

	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+53);
	printf("年龄:________");

	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+76);
	printf("C   :_______");
	
	printf("\033[%d;%dH", MAIN_X_SUB -3, DIVISION_START_COL+17+100);
	printf("Cpp :_____");

	printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
	 fflush(NULL);
}




