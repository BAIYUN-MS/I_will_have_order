#include"tools.c" 

//�������� 
extern int main_form();
extern void customer_form();
extern void admin_form();

/*
* function_name: main
* return_type  : int
* param        : NULL
* description  : �������ڣ��趨����ѭ����֤�������� 
*/ 
int main(int argc, char *argv[]) {
	int choice;
	do{
		choice = main_form();
		
		switch(choice){
			case 1:customer_form();break;
			case 2:admin_form();break;
		}
	}while(choice != 3);
	
	return 0;
}
