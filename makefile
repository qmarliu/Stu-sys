
stuSys : stuSys.c admin.c teacher.c student.c mylib.c show.c
	gcc -o stuSys stuSys.c admin.c teacher.c student.c mylib.c show.c  -g
	
clean:
	rm -f stuSys


	
