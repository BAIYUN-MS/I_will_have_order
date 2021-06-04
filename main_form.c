#include"tools.c"

//变量声明 

//函数声明 
void error_check(int,int,int*);
void greet(struct tm* p,int);
struct tm* get_time();

/*
* function_name: main_form
* return_type  : int 
* param        : NULL
* description  : 程序主界面的显示界面，获取选择信息并返回至 主函数 main 
*/ 
int main_form(){
	system("cls");
	int greet_type = 0;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("请选择您的身份：\n");
	printf("1.顾客\n");
	printf("2.管理人员\n");
	printf("3.退出\n");
	printf("请在这里输入："); 
	scanf("%d",&choice);
	//差错检测 防止输入错误选择导致程序崩溃
	error_check(1,3,&choice);
	return choice;
} 

/*
* function_name: error_check 
* return_type  : void
* param        : int（左边界）, int（右边界）,int* (选择) 
* description  : 用于检测输入是否正确，若为非法输入，则重复修改选择直至合法 
*/ 
void error_check(int range_left ,int range_right, int* choice){
	while(*choice < range_left || *choice > range_right){
		printf("输入错误！请重新输入:");
		scanf("%d",choice); 
	}
}

/*
* function_name: greet
* return_type  : void
* param        : struct tm* (时间) , int (问候类型 0-默认 1-用户 2-管理员 )
* description  : 问候函数 依据当前时间,用户类型给出问候 
*/  
void greet(struct tm* p , int greet_type){
	//转换时区
	int china_time = (p->tm_hour + 8) % 24;
	if(p->tm_hour + 8 >= 24) p->tm_mday -= 1; 
	//依据时间首先问好
	printf("+++++++++++++++++++++++++++++++++++++++++++\n");
	if(china_time >= 6 && china_time  < 8) printf("早上好！");
	else if(china_time  >= 8 && china_time  < 12) printf("上午好！");
	else if(china_time  >= 12 && china_time  < 14) printf("中午好！");
	else if(china_time  >= 14 && china_time  < 18) printf("下午好！");
	else if(china_time  >= 18 && china_time  < 24) printf("晚上好！");
	else printf("夜已深，注意休息！");  
	
	printf("\n");
	
	if(greet_type == 0){
		printf("欢迎使用餐厅点菜系统！\n");;
	}
	else if(greet_type == 1){
		printf("热烈欢迎您的光临！\n");
	}
	else{
		printf("今天也是充满希望的一天！\n");
	}
}

/*
* function_name: get_time 
* return_type  : struct tm*
* param        : NULL
* description  : 获取时间并返回相关参数 
*/ 
struct tm* get_time(){
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	
	return p;
} 
