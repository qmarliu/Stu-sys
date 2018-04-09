#include "mylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//功  能: 接收用户选择的数据
int get_select()
{
    char select[512];
    fgets( select, 512, stdin );
    if( select[strlen(select)-1] == '\n' )
        select[strlen(select)-1] = '\0';
    if( strcmp(select, "q") == 0 || strcmp(select, "Q") == 0 ) {
        system("clear");
        exit(0);
    }
    if( strcmp(select, "b") == 0 || strcmp(select, "B") == 0 ) {
        return -1;
    }
    int sel = atoi(select);
    return sel==-1 ? 0 : sel;
}

//功  能: 接收用户查找学生或老师时的数据
int get_find_select()
{
    char select[512];
    fgets( select, 512, stdin );
    if( select[strlen(select)-1] == '\n' )
        select[strlen(select)-1] = '\0';
    if( strcmp(select, "q") == 0 || strcmp(select, "Q") == 0 ) {
        system("clear");
        exit(0);
    }
    if( strcmp(select, "b") == 0 || strcmp(select, "B") == 0 ) {
        return -1;
    }
    if( strcmp(select, "b") == 0 || strcmp(select, "B") == 0 ) {
        return -1;
    }
    int sel = atoi(select);
    return sel==-1 ? 0 : sel;
}

//功  能: 获取密码输入
void get_psw(char *psw)
{
    int state = 0;
    printf("\033[s");
    do {
        state = 0;
        printf("\033[u\033[8m");
        fgets(psw, PSW_LEN+1, stdin);
        printf("\033[0m");
        cover_char( WARNING_X, 0, CONSOLE_LEN);
        if(psw[strlen(psw)-1] == '\n') {
            psw[strlen(psw)-1] = '\0';
            if(strlen(psw) < 3) {
                if( strcmp( psw, "b") == 0 || strcmp( psw, "B") == 0)
                    return;
                printf("\033[%d;%dH\033[31m密码小于3个字符,重新输入\033[0m\n",WARNING_X, WARNING_Y);
            }
        } else {
            while(getchar() !='\n') {
                state = 1;
            }
            if(state) {
                printf("\033[%d;%dH\033[31m密码超出%d个字符,重新输入\033[0m\n",WARNING_X, WARNING_Y,PSW_LEN);
            }
        }
    } while(state == 1 || strlen(psw) < 3);
}

//功  能: 用‘ ’覆盖x行原有的字符
void cover_char(int x, int y, int cnt)
{
    int i;
    printf("\033[%d;%dH", x, y);
    for(i=0; i<cnt; ++i) {
        printf(" ");
    }
    fflush(NULL);
}

//功  能: 获取名字
void get_name(char *name, int x, int y)
{
    printf("\033[s");
    for(;;) {
        printf("\033[u");
        fgets(name, NAME_LEN+1, stdin);
        if(strlen(name) == 1) {	
            cover_char( WARNING_X, 0, CONSOLE_LEN);
            printf("\033[%d;%dH\033[31m名字不能为空\033[0m\n",WARNING_X, WARNING_Y);
            continue;
        }
        if(name[strlen(name)-1] == '\n')
            name[strlen(name)-1] = '\0';
        else {
            if(getchar()  != '\n') {
                cover_char( WARNING_X, 0, CONSOLE_LEN);
                printf("\033[%d;%dH\033[31m名字超过%d个字符,重新输入\033[0m\n",WARNING_X, WARNING_Y, NAME_LEN);
                cover_char( x, y, CONSOLE_LEN - y);
                while(getchar()!='\n');
                continue;
            }
        }
        break;
    }
}

//功  能: 获取性别
void get_gender(char *gender, int x, int y)
{
    printf("\033[s");
    for(;;) {
        printf("\033[u");
        fgets(gender, 4, stdin);
        if(gender[strlen(gender)-1] == '\n')
            gender[strlen(gender)-1] = '\0';
        else 
            while(getchar()!='\n');
        if( strcmp(gender, "M")==0 || strcmp(gender, "m")==0) {
            strcpy(gender, "男");
            break;
        }
        if( strcmp(gender, "F")==0 || strcmp(gender, "f")==0) {
            strcpy(gender, "女");
            break;
        }
        if(strcmp(gender, "男") == 0 || strcmp(gender, "女") == 0 ||
                strcmp(gender, "b")==0 ||  strcmp(gender,"B") == 0) {
            break;
        }
        cover_char( WARNING_X, 0, CONSOLE_LEN);
        printf("\033[%d;%dH\033[31m性别输入有误,重新输入(输入内容只能为 男/M/m 女/F/f)\033[0m\n",WARNING_X, WARNING_Y);
        cover_char( x, y, CONSOLE_LEN - y);
    } 
}

//功  能: 获取id,年龄，成绩等int类型的输入
void get_int( char *ch_num )
{
    fgets(ch_num, 6, stdin);
    if(ch_num[strlen(ch_num)-1] == '\n')
        ch_num[strlen(ch_num)-1] = '\0';
    else 
        while(getchar()!='\n');
}
