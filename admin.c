#include "admin.h"
#include "mylib.h"
#include "show.h"

//功  能: 管理员的主要功能选择
//返回值:	0, 正常返回
//			-1，文件不存在、打开或创建失败
//			-2, 退出登录
int adm_opt()
{
	int ret = adm_vertify();
	if(ret == -1)
		return -1;
	if(ret == -2)
		return -2;
	alt_tips("管理员登录成功");
	for(;;) {
		adm_opt_show();
		int select = get_select();

		switch(select)
		{
			case 1: //学生报名
				ret = stu_add();
				if( ret==0 ) {
					alt_tips("添加成功");
				} else if(ret == -1) {
					alt_tips("文件错误，添加失败");
				} else if(ret == -2) {
					alt_tips("已取消添加");
				}
				break;
			case 2: //学生查找
				ret = stu_find();
				if( ret ==0) {
					alt_tips("已退出查询");
				} else if(ret == -1) {
					alt_tips("文件错误，不能查询");
				}
				break;
			case 3: //老师登记
				break;
			case 4: //老师查找
				break;
			case 5: //修改密码
				ret = adm_alt_psw();
				if( ret==0 ) {
					alt_tips("修改密码成功");
				} else if(ret == -1) {
					alt_tips("文件错误，密码修改失败");
				} else if(ret == -2) {
					alt_tips("已取消修改密码");
				}
				break;
			case -1:
				return -2;
			default:
				cover_char( WARNING_X, 0, CONSOLE_LEN);
				cover_char( MAIN_X_SUB-5, 0, CONSOLE_LEN);
				printf("\033[%d;%dH\033[31m输入的序号没有匹配的功能，请重新输入\033[0m",WARNING_X-2, WARNING_Y);
				printf("\033[%d;%dH\033[0m", MAIN_X_SUB-5, MAIN_Y_SUB+6);
				continue;
		}
	}
}

//功  能: 验证或创建管理员的身份
//返回值: 0,验证或创建成功
//		  -1,文件操作失败
//		  -2,取消登录,返回主界面
int adm_vertify()
{
	if( access(ADM_DB, F_OK) != 0 ) {
		//没有管理员，询问创建
		alt_tips("");
		adm_create_show();
		char psw[PSW_LEN+1] = "";
		char psw2[PSW_LEN+1] = "";
		do {
			printf("\033[%d;%dH",MAIN_X_SUB, MAIN_Y_SUB+10);
			get_psw(psw);
			if( strcmp(psw, "b")== 0 || strcmp(psw,"back") == 0 )
				return -2;
			printf("\033[%d;%dH",MAIN_X_SUB, MAIN_Y_SUB+10);
			printf("\033[2B");
			get_psw(psw2);
			if( strcmp(psw2, "b")== 0 || strcmp(psw2,"back") == 0)
				return -2;
			if( strcmp(psw, psw2)!= 0) {
				cover_char( WARNING_X, 0, CONSOLE_LEN);
				printf("\033[%d;%dH\033[31m两次输入的密码不一致\033[0m\n",WARNING_X, WARNING_Y);
			}  
		} while ( strcmp(psw,psw2)!=0 );
		FILE *fp = fopen(ADM_DB, "w");
		ERRP( fp==NULL, "fopen", return -1);
		fwrite(psw, PSW_LEN+1, 1, fp);
		fclose(fp);
		return  0;
	} 
	//有管理员直接登录
	FILE *fp = fopen(ADM_DB, "r");
	ERRP( fp==NULL, "fopen", return -1);
	char psw[PSW_LEN+1] = "";
	char psw2[PSW_LEN+1] = "";
	fread(psw, PSW_LEN+1, 1, fp);
	alt_tips("");
	adm_login_show(); 
	do {
		printf("\033[%d;%dH",MAIN_X_SUB, MAIN_Y_SUB+10);
		get_psw(psw2);	
		if( strcmp(psw2, "b")== 0 || strcmp(psw2,"back") == 0)
			return -2;
		if( strcmp(psw, psw2)!= 0) {
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			printf("\033[%d;%dH\033[31m密码不正确，重新输入\033[0m\n",WARNING_X, WARNING_Y);
		}
	} while( strcmp(psw, psw2) != 0);
	return 0; 
}

//功  能: 修改管理员密码
//返回值: 0,修改成功
//		  -1，文件操作失败
//		  -2, 取消修改
int adm_alt_psw()
{
	alt_tips("");
	adm_alt_show();

	char o_psw[PSW_LEN+1] = "";
	FILE *fp = fopen(ADM_DB, "r");
	ERRP( fp==NULL, "fopen", return -1);
	fread(o_psw, PSW_LEN+1, 1, fp);
	fclose(fp);

	char psw[PSW_LEN+1] = "";
	char psw2[PSW_LEN+1] = "";
	char psw3[PSW_LEN+1] = "";
	do {
		printf("\033[%d;%dH",MAIN_X_SUB, MAIN_Y_SUB+10);
		get_psw(psw);
		if( strcmp(psw, "b")== 0 || strcmp(psw,"back") == 0 )
			return -2;

		printf("\033[%d;%dH",MAIN_X_SUB+2, MAIN_Y_SUB+10);
		get_psw(psw2);
		if( strcmp(psw2, "b")== 0 || strcmp(psw2,"back") == 0)
			return -2;

		printf("\033[%d;%dH",MAIN_X_SUB+4, MAIN_Y_SUB+10);
		get_psw(psw3);
		if( strcmp(psw3, "b")== 0 || strcmp(psw2,"back") == 0)
			return -2;

		if( strcmp(psw, o_psw) != 0) {
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			printf("\033[%d;%dH\033[31m密码不正确，请输入正确的密码\033[0m\n",WARNING_X, WARNING_Y);	
		}

		if( strcmp(psw2, psw3)!= 0) {
			cover_char( WARNING_X, 0, CONSOLE_LEN);
			printf("\033[%d;%dH\033[31m两次输入的新密码不一致\033[0m\n",WARNING_X, WARNING_Y);
		} 
	} while ( strcmp(psw2,psw3)!=0 || strcmp(psw, o_psw)!=0 );

	fp = fopen(ADM_DB, "w");
	ERRP( fp==NULL, "fopen", return -1);
	fwrite(psw2, PSW_LEN+1, 1, fp);
	fclose(fp);
	return 0;
}




