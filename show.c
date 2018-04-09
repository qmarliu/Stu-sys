#include "show.h"
#include "mylib.h"
#include <time.h>

//功  能: 右下角显示时间和作者
void author_time_show()
{
    time_t rawtime;
    struct tm *timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    printf("\033[%d;%dH\033[36m学生管理系统 | 作者: 刘磊 | 时间: %d-%2d-%2d %2d:%2d\033[0m",
            AUTHOR_X_SUB, AUTHOR_Y_SUB, 
            1900+timeinfo->tm_year, 1+timeinfo->tm_mon,timeinfo->tm_mday,
            timeinfo->tm_hour,timeinfo->tm_min); 
}

//功  能: 将屏幕用黑色线分成四段，并把光标定位在选择段
//参  数:	ischoice, 0 表示选择段和提示段合并为提示段
//					  1 表示表示段和提示段不合并
void division(const char * const tip)
{
    int i;
    printf("\033[%d;%dH\033[33m提示: %s", TIP_X_SUB, TIP_Y_SUB, tip);

    printf("\033[%d;%dH\033[30m", AUTHOR_X_SUB-1, DIVISION_START_COL);   //作者上的分割线
    for(i=0; i<DIVISION_LEN; ++i)
        printf("-");

    printf("\033[%d;%dH", TIP_X_SUB+1, DIVISION_START_COL);  //提示下的分割线
    for(i=0; i<DIVISION_LEN; ++i)
        printf("-");

    printf("\033[%d;%dH", MAIN_X_SUB-4, DIVISION_START_COL); // 内容上的分割线
    for(i=0; i<DIVISION_LEN; ++i)
        printf("-");

    last_status();
    printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB + 6);
    fflush(NULL);
}

//功  能: 显示主界面
void main_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m 1. 管 理 员 登 录", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH\033[32m 2. 老 师 登 录(未实现,不可选)", MAIN_X_SUB + 2, MAIN_Y_SUB );
    printf("\033[%d;%dH\033[32m 3. 学 生 登 录\033[0m", MAIN_X_SUB + 4, MAIN_Y_SUB);

    division("输入字符Q/q退出程序;  输入序号进入相应功能.");
}

//功  能: 显示管理员的主要操作
void adm_opt_show()
{	
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m 1. 学 生 报 名", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH 2. 学 生 查 找", MAIN_X_SUB+2, MAIN_Y_SUB);
    printf("\033[%d;%dH 3. 老 师 登 记(未实现,不可选)", MAIN_X_SUB+5, MAIN_Y_SUB);
    printf("\033[%d;%dH 4. 老 师 查 找(未实现,不可选)", MAIN_X_SUB+7, MAIN_Y_SUB);
    printf("\033[%d;%dH 5. 修 改 密 码", MAIN_X_SUB+10, MAIN_Y_SUB);

    printf("\033[%d;%dH\033[30m-__________________-", MAIN_X_SUB+3, MAIN_Y_SUB-2);
    printf("\033[%d;%dH\033[30m-__________________-\033[0m", MAIN_X_SUB+8, MAIN_Y_SUB-2);

    division("Q/q退出程序; B/b返回.");
}

//功  能: 显示管理员创建操作
void adm_create_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m密    码:", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH密码确认:", MAIN_X_SUB+2, MAIN_Y_SUB);

    division("B/b返回.");
}

//功  能: 管理员登录界面操作
void adm_login_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m密    码:", MAIN_X_SUB, MAIN_Y_SUB);

    division("B/b返回.");
}

//功  能: 管理员修改密码
void adm_alt_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m原始密码:", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH新 密 码:", MAIN_X_SUB + 2, MAIN_Y_SUB);
    printf("\033[%d;%dH密码确认:", MAIN_X_SUB+4, MAIN_Y_SUB);

    division("B/b返回.");
}

//功  能: 显示学生的主要操作界面
void stu_opt_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m 1. 查 找 老 师(未实现）", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH 2. 修 改 密 码(未实现）", MAIN_X_SUB+3, MAIN_Y_SUB);

    printf("\033[%d;%dH\033[30m-__________________-", MAIN_X_SUB+1, MAIN_Y_SUB-2);

    division("Q/q退出程序; B/b返回.");
}

//功  能: 显示查找学生界面
void stu_find_show()
{
    system("clear");
    author_time_show();

    /*printf("\033[%d;%dH\033[32m 1. 查 找 老 师", MAIN_X_SUB, MAIN_Y_SUB);*/

    printf("\033[%d;%dH\033[30m", MAIN_X_SUB-2, DIVISION_START_COL); 
    int i;
    for(i=0; i<DIVISION_LEN; ++i)
        printf("-");

    division( "Q/q退出程序; B/b返回.n/N前后翻阅,直接回车进入条件选择\n");
    printf("\033[%d;%dH\033[33m1.学号排序 2.性别 3.年龄 4.c成绩 5.cpp成绩\n\033[0m", TIP_X_SUB+2, TIP_Y_SUB);
}

//功  能: 添加学生界面
void stu_add_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m姓    名:", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH性    别:", MAIN_X_SUB + 2, MAIN_Y_SUB);
    printf("\033[%d;%dH年    龄:", MAIN_X_SUB+4, MAIN_Y_SUB);
    printf("\033[%d;%dHc  成 绩:", MAIN_X_SUB+6, MAIN_Y_SUB);
    printf("\033[%d;%dHcpp成 绩:", MAIN_X_SUB+8, MAIN_Y_SUB);

    division("B/b返回.");
}

//学生和老师登录界面
void stu_tea_vertify_show()
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32mI      D :", MAIN_X_SUB, MAIN_Y_SUB);
    printf("\033[%d;%dH密     码:", MAIN_X_SUB + 2, MAIN_Y_SUB);

    division("B/b返回.");
}

//功  能: 确认界面
void confirm_show(char *confirm_msg)
{
    system("clear");
    author_time_show();

    printf("\033[%d;%dH\033[32m%s", MAIN_X_SUB+4, MAIN_Y_SUB, confirm_msg);

    division("Y/y保存.");
}

//功  能: 显示这个界面操作的结果提示
void last_status()
{
    printf("\033[%d;%dH\033[36m", MAIN_X_SUB - 1, DIVISION_START_COL);
    printf("%s",tips);
    printf("\033[0m");
    fflush(NULL);
}

//功  能: 修改全局变量tips
void alt_tips(const char * const tip)
{
    strcpy(tips,tip);
}
