#include"tools.c" 

//函数声明 
extern int main_form();
extern void customer_form();
extern void admin_form();

/*
* function_name: main
* return_type  : int
* param        : NULL
* description  : 程序的入口，设定基本循环保证程序运行 
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
