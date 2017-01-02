#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "show.h"
#include "mylib.h"

char tips[255] = "";
int main(int argc,char* argv[])
{
	int select = 0;
	int ret;
	main_show();    //显示主界面
	for(;;) {
		select = get_select(); //用户选择登录类型
		switch( select )
		{
			case 1:  //管理员登录
				alt_tips("");
				ret = adm_opt();
				if( ret == -1 )
					alt_tips("管理员的数据文件操作失败，无法进行管理员操作");
				if( ret == -2)
					alt_tips("已退出管理员的登录");
				break;
			case 2:		//老师登录
				tea_opt();
				break;
			case 3:   //学生登录
				alt_tips("");
				ret = stu_opt();
				if( ret == -1 )
					alt_tips("学生的数据文件操作失败，无法进行管理员操作");
				if( ret == -2)
					alt_tips("已退出学生的登录");
				break;
			default:  //输入错误
				cover_char( WARNING_X, 0, CONSOLE_LEN);
				cover_char( MAIN_X_SUB-5, 0, CONSOLE_LEN);
				printf("\033[%d;%dH\033[31m输入的序号没有匹配的功能，请重新输入\033[0m",WARNING_X-2, WARNING_Y);
				printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB+6);
				continue;
		}
		main_show();    //显示主界面
	}
	return 0;
}
