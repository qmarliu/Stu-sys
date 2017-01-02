
main() 
 |
 |-adm_opt (admin.h)	
 |	|
 |	|-adm_vertify() (admin.h) 
 |	|-adm_alt_psw() (admin.h)
 |	|-tea_add() (teacher.h)
 |	|-tea_find() (teacher.h) (区分管理员查找和学生查找)
 |	|	|-tea_sort() (teacher.h)
 |	|	|-tea_del() (teacher.h)
 |	|	|-tea_alt() (teacher.h)
 |	|-stu_add() (student.h)
 |	|-stu_find() (student.h) （区分管理员查找和老师查找）
 |	|	|-stu_sort() (teacher.h)
 |	|	|-stu_del() (student.h)
 |	|	|-stu_alt() (student.h)
 |	|
 |-tea_opt (teacher.h)
 |	|
 |	|-tea_vertify() (teacher.h)
 |	|-tea_alt_psw() (teacher.h)
 |	|-stu_find() (student.h)	
 |	|	|-tea_sort(teacher.h)
 |	|	|-stu_alt() (student.h)
 |	|	
 |-stu_opt (student.h, list.h)
 |	|
 |	|-stu_vertify() (student.h)
 |	|-stu_alt_psw() (student.h)
 |	|-tea_find() (teacher.h)
 |	|	|-tea_sort() (teacher.h)

list.c
	list_read();
	list_append();
	list_sort();
	list_write();

show.c

  main_show();//显示主界面
  adm_opt_show();//显示管理员操作界面
  tea_opt_show();//显示老师操作界面
  stu_opt_show();//显示学生操作界面

  adm_create_show();//询问是否创建
  adm_login_show(); //管理员登录
  adm_alt_show(); //管理员修改密码
  
  stu_find_show();
  stu_add_show();//学生添加显示
  stu_vertify_show(); //学生验证显示框
mylib.c
  get_select();
  get_psw();
