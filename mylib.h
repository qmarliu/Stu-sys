#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//数据存储的文件位置定义
#define ADM_DB "./data/admin.db"
#define TEA_DB "./data/teacher.db"

//存储当前界面操作的结果提示
extern char tips[255];

//终端的宽度
#define CONSOLE_LEN 150

//分割线的长度和分割的起始位置
#define DIVISION_START_COL 10
#define DIVISION_LEN CONSOLE_LEN-2*DIVISION_START_COL

//显示右下角落的作者和时间位置
#define AUTHOR_X_SUB 39
#define AUTHOR_Y_SUB 100-DIVISION_START_COL


//显示提示的位置
#define TIP_X_SUB 1
#define TIP_Y_SUB DIVISION_START_COL

//显示主题内容的起始位
#define MAIN_X_SUB 10
#define MAIN_Y_SUB 60
#define MAIN_OFFSET_SUB 10

//用户数入错误，警告所在的位置
#define WARNING_X TIP_X_SUB+4
#define WARNING_Y TIP_Y_SUB

//课程最大名
#define CLASS_LEN 9

//名字最大长度 15表示五个中文字符，15个英文字符。
#define NAME_LEN 15

////密码最大长度 
#define PSW_LEN 16


//学生开始ID
#define STU_ID_START 1000
//老师开始ID
#define TEA_ID_START 10

//一次显示的个数
#define SHOW_CNT 10

//被删除的学生ID标记
#define STU_DELETE_ID -2

//容错宏
#define ERRP(con, func, ret) \
	do { \
		if(con) {     \
			perror(func); \
			ret; \
		}      \
	} while(0)

//判断是否返回上一层目录
#define GO_BACK(input, ret) \
	if( strcmp(input, "-1") == 0 ) \
		ret;


int get_select();
int get_find_select();
void get_psw(char *psw);
void cover_char(int x, int y, int cnt);
void get_name(char *name, int x, int y);
void get_gender(char *name, int x, int y);
void get_int(char *ch_num);
#endif
