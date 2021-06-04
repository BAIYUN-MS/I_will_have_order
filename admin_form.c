#include "tools.c"
//变量声明
//char pw[20] = "123456";                        //预置密码，方便调试 
//部分全局变量
char hot_dish_filename[20] = "hot_dish.txt";
char cold_dish_filename[20] = "cold_dish.txt";
char staple_food_filename[20] = "staple_food.txt";
char drink_filename[20] = "drink.txt"; 
//函数声明 
void gotoxy(int,int);
void input_password(char pw_input[],int wrong_time);     //输入密码 
int check_password(char pw_input[]);      //密码检测 
int admin_menu();                         //管理员菜单 
void order_check();                       //订单确认
void order_complete();                    //完成订单 
void income_check();                      //查看营业额 
void add_dish();                          //添加菜品 
void del_dish();                          //删除菜品 
void price_adjust();                      //价格调整 
void change_password();                   //密码修改 
void create_date_filename(char*);         //生成当日文件名 
void format_input_income(FILE*,double,double,double,double,double);            //收入格式化输入文件
void format_output_income(FILE*,double*,double*,double*,double*,double*);      //收入格式化输出到程序 
void calculate_value(char* , double* , double* , double* , double * , double*);//计算收入 
void create_order_filename(int,char*);         //依据桌号生成订单文件名  
void record_income(double,double,double,double,double);                        //用于记录单笔订单收入信息至收入文件中 
void input_date_filename(char* fstr);          //依据输入的日期生成文件名 


//外部函数声明 
extern void error_check(int,int,int*);
extern void greet(struct tm* p,int);
extern struct tm* get_time();

/*
* function_name: admin_form 
* return_type  : void
* param        : NULL
* description  : 管理员系统的主循环 
*/ 
void admin_form(){
	system("cls");
	printf("========欢迎使用后台管理系统！========\n");
	int choice;
	printf("请在这里输入后台密码:");
	char pw_input[20];
	
	int wrong_time = 0;
	input_password(pw_input , wrong_time);
	
	int flag;
	do{
		flag = check_password(pw_input);
		if(flag != 0 ){
			wrong_time++;
			printf("输入错误，请重新输入:");
			input_password(pw_input , wrong_time);
		}
		else{
			printf("输入正确！欢迎管理员！\n");
			int i;
			for( i = 0 ; i < 3 ; i++){
				printf(".");
				Sleep(1000);
			}
		}
	}while (flag == 1);
	
	do{
		choice = admin_menu();
		switch(choice){
			case 1:order_check();break;
			case 2:order_complete();break;
			case 3:income_check();break;
			case 4:add_dish();break;
			case 5:del_dish();break;
			case 6:price_adjust();break;
			case 7:change_password();break; 
			default:break;
		}
	}while(choice != 8);
}

/*
* function_name: gotoxy 
* return_type  : void
* param        : int(x) , int(y)
* description  : 定位屏幕光标至 （x , y） 
*/ 
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

/*
* function_name: input_password
* return_type  : void
* param        : char*(要输入的密码) , int(输错的次数) 
* description  : 输入密码 
*/ 
void input_password(char pw_input[],int wrong_time){
	//清空字符串
	memset(pw_input,0,20);
	int x,y;
	x = 21;
	y = 1 + wrong_time;
	gotoxy(x,y);
	char ch;
	char temp_input[20];
	int cnt = 0;
	int i = 0;
	do{
		ch = getch();
		if(ch == 13){//回车键 
			;
		}
		else if(ch == 8){//退格键 
			i--;
			cnt--;
			x--;
			gotoxy(x,y);
			printf(" ");
			gotoxy(x,y);
		}
		else{//普通字符 
			temp_input[i] = ch;
			printf("*");
			x++;
			i++;
			cnt++;
		}
	}while(ch != 13);
	printf("\n");
	
	strncpy(pw_input , temp_input , cnt);
}

/*
* function_name: check_password
* return_type  : int
* param        : char*(输入的密码)
* description  : 检测输入的密码是否正确，正确返回0 ，否则非0 
*/ 
int check_password(char pw_input[]){
	FILE* fp;
	char pw[20]="";
	fp = fopen("password.txt" , "r");
	fscanf(fp , "%s" , pw);
	fclose(fp); 
	
	return strcmp(pw_input,pw);
}

/*
* function_name: change_password
* return_type  : void
* param        : NULL
* description  : 修改密码 
*/
void change_password(){
	char pw_old[20];
	char pw_old_input[20];
	char pw_new[20];
	char pw_check[20];
	FILE* fp;
	fp = fopen("password.txt" , "r");
	fscanf(fp , "%s" , pw_old);
	fclose(fp); 
	
	system("cls");
	printf("**************************************\n");
	printf("请输入旧密码：");
	scanf("%s", pw_old_input);
	
	while(strcmp(pw_old , pw_old_input) != 0){
		printf("输入错误，请重新输入：");
		scanf("%s", pw_old_input);
	}
	
	printf("请输入新密码：");
	scanf("%s", pw_new);
	
	printf("请确认新密码：");
	scanf("%s" , pw_check);
	
	while(strcmp(pw_new , pw_check) != 0){
		printf("输入错误，请重新输入：\n");
		
		printf("请输入新密码：");
		scanf("%s", pw_new);
	
		printf("请确认新密码：");
		scanf("%s" , pw_check);
	}
	
	fp = fopen("password.txt" , "w");
	fprintf(fp ,"%s" , pw_new);
	fclose(fp);
	
	int i ;
	printf("修改完成，请牢记新密码：%s\n" , pw_new);
	printf("**************************************\n");
	for( i = 0 ; i < 3 ; i++){
		printf(".");
		Sleep(1000);
	}
	
}

/*
* function_name: admin_menu 
* return_type  : int
* param        : NULL
* description  : 管理员主界面显示，并返回选择 
*/ 
int admin_menu(){
	system("cls");
	int greet_type = 2;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("请选择操作\n");
	printf("1.确认顾客订单\n");
	printf("2.完成顾客订单\n");
	printf("3.查看营业额\n");
	printf("4.添加菜品\n");
	printf("5.删除菜品\n");
	printf("6.修改价格\n");
	printf("7.密码修改\n"); 
	printf("8.退出\n");
	printf("在此输入：");
	scanf("%d",&choice);
	
	error_check(1,8,&choice);
	return choice;
}

/*
* function_name: order_check
* return_type  : void
* param        : NULL
* description  : 确认订单 
*/ 
void order_check(){
	system("cls"); 
	int tn = 1;
	int flag = 0;
	//根据桌号检索文件，生成文件名
	//假设有20张桌子 
	printf("**************************************\n");
	for(tn = 1 ; tn <= 20 ; tn++){
		// version 1.7 对这里进行重构 
		char fstr[50] = "order//";
		create_order_filename(tn,fstr); 
		
		FILE* fp;
		fp = fopen(fstr , "r");
		if(fp == NULL){
			continue;
		}
		else{
			int flag_temp;
			fscanf(fp,"%d",&flag_temp);
			fclose(fp);
			if(flag_temp == 2){
				flag = 1;
				printf("桌号:%d 已完成支付！\n",tn);
				printf("是否确认订单？ 1.是 2.否\n");
				int choice;
				printf("请在这里输入：");
				scanf("%d",&choice);
				
				error_check(1,2,&choice);
				
				//如果确定订单则置标志位为 3 
				if(choice == 1){
					fp = fopen(fstr , "r+");
					fseek(fp , 0 , SEEK_SET);
					fprintf(fp,"%d" , 3);
					fclose(fp);
					
					printf("桌号:%d的订单已确认成功！\n",tn);
				}
			} 
		}
	}
	
	if(flag == 0){
		printf("暂无订单需要确认！\n");
	}
	printf("**************************************\n");
	int a;
	for(a = 0 ; a < 3 ;a++){
		printf(".");
		Sleep(1000);
	}
}

/*
* function_name: order_complete 
* return_type  : void
* param        : NULL
* description  : 完成订单 ， 并将收入信息存储至收入文件中 
*/ 
void order_complete(){
	system("cls"); 
	int tn = 1;
	int flag = 0;
	//根据桌号检索文件，生成文件名
	//假设有20张桌子 
	printf("**************************************\n");
	for(tn = 1 ; tn <= 20 ; tn++){
		char fstr[50] = "order//";
		create_order_filename(tn,fstr); 
		
		FILE* fp;
		fp = fopen(fstr , "r");
		if(fp == NULL){
			continue;
		}
		else{
			int flag_temp;
			fscanf(fp,"%d",&flag_temp);
			fclose(fp);
			if(flag_temp == 3){
				flag = 1;
				printf("桌号:%d 已完成确认，出餐结束后可选择完成订单！\n",tn);
				printf("是否确认完成订单？ 1.是 2.否\n");
				int choice;
				printf("请在这里输入：");
				scanf("%d",&choice);
				
				error_check(1,2,&choice);
				
				if(choice == 1){
					double account = 0, account_hot_dish = 0,account_cold_dish = 0,account_staple_food = 0,account_drink = 0;
					calculate_value(fstr,&account,&account_hot_dish,&account_cold_dish,&account_staple_food,&account_drink);
					
					printf("桌号:%d的订单已完成！\n",tn);
					// 功能：将订单收入信息记录至 income 文件夹中 
					record_income(account,account_hot_dish,account_cold_dish,account_staple_food,account_drink); 
					
					remove(fstr); 
				}
			} 
		}
	}
	
	if(flag == 0){
		printf("暂无订单可以完结！\n");
	}
	printf("**************************************\n");
	int a;
	for(a = 0 ; a < 3 ;a++){
		printf(".");
		Sleep(1000);
	}
}

/*
* function_name: record_income
* return_type  : void
* param        : 5个double数据 传入订单中各项收入信息 
* description  : 将读取到的订单收入信息记录到 income 文件夹 对应日期的文件中 
*/
void record_income(double account, double account_hot_dish, double account_cold_dish, double account_staple_food, double account_drink){
	double all_income, staple_food_income, hot_dish_income,cold_dish_income,drink_income;
	
	char fdate[50]="";
	create_date_filename(fdate); 
					
	FILE *fp1;
	fp1 = fopen(fdate , "r");
	if(fp1 == NULL){
		fp1 = fopen(fdate,"w");
		format_input_income(fp1,account,account_hot_dish,account_cold_dish,account_staple_food,account_drink);
		fclose(fp1);
	}
	else{
		format_output_income(fp1,&all_income,&hot_dish_income,&cold_dish_income,&staple_food_income,&drink_income) ;
		fclose(fp1);
		all_income+=account;
		hot_dish_income+=account_hot_dish;
		cold_dish_income+=account_cold_dish;
		staple_food_income+=account_staple_food;
		drink_income+=account_drink;
		fp1 = fopen(fdate , "w");
		format_input_income(fp1,all_income,hot_dish_income,cold_dish_income,staple_food_income,drink_income);
		fclose(fp1); 
	} 
}

/*
* function_name: format_input_income 
* return_type  : void
* param        : FILE* fp 5 个double数据 
* description  : 格式化输入数据 ，将5个double数据格式化输入到文件中 
*/
void format_input_income(FILE* fp,double a,double b,double c,double d,double e){
	fprintf(fp,"%lf\n",a);
	fprintf(fp,"%lf\n",b);
	fprintf(fp,"%lf\n",c);
	fprintf(fp,"%lf\n",d);
	fprintf(fp,"%lf\n",e);
}

/*
* function_name: format_output_income 
* return_type  : void
* param        : FILE* fp 5 个double数据 
* description  : 格式化输出数据 ，将5个double数据格式化输出到程序中 
*/
void format_output_income(FILE* fp,double* a,double* b,double* c,double* d,double* e){
	fscanf(fp,"%lf\n",a);
	fscanf(fp,"%lf\n",b);
	fscanf(fp,"%lf\n",c);
	fscanf(fp,"%lf\n",d);
	fscanf(fp,"%lf\n",e);
}

/*
* function_name: create_date_filename
* return_type  : void
* param        : char* fdate(用于返回生成后的文件名)
* description  : 自动获取当天日期，并返回文件名 如202161.txt 
*/
void create_date_filename(char* fdate){
	char date[20] = "";
	struct tm* p = get_time();
	if(p->tm_hour + 8 >= 24) p->tm_mday -= 1;
	
	char year[5] = "";
	char month[5] = "";
	char day[5] = "";
	itoa(p->tm_year + 1900 , year , 10);
	itoa(p->tm_mon + 1 , month , 10);
	itoa(p->tm_mday + 1, day , 10);
	strcat(date,year);
	strcat(date,month);
	strcat(date,day);
	strcat(date,".txt");
	
	strcat(fdate , "income//");
	strcat(fdate , date);
}

/*
* function_name: create_order_filename
* return_type  : void
* param        : int 桌号，用于定位文件名  char* 用于返回文件名 
* description  : 根据桌号自动生成文件名 ，如 1.txt 
*/
void create_order_filename(int table_num ,char * fstr){
	char str[5];
	itoa(table_num ,str,10);
	strcat(fstr , str);
	strcat(fstr , ".txt");
}

/*
* function_name: input_date_filename
* return_type  : void
* param        : char* 用于返回文件名 
* description  : 根据输入的日期生成日期文件名 
*/
void input_date_filename(char* fstr){
	int year,month,day;
	printf("请输入要查询的年份：");
	scanf("%d",&year);
	error_check(1900,3000,&year);
	printf("请输入要查询的月份：");
	scanf("%d",&month);
	error_check(1,12,&month);
	printf("请输入要查询的日期：");
	scanf("%d",&day);
	
	//判断是否为闰年
	int flag = 0;
	if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
		flag = 1;
	}
	
	int normal[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int special[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	
	//日期输入检查 
	if(flag){
		error_check( 1 , special[month - 1] , &day);
	}
	else{
		error_check( 1 , normal[month - 1] , &day);
	}
	
	//生成文件名	 
	char date[20];
	char sy[5];
	char sm[5];
	char sd[5];
	itoa(year,sy,10);
	itoa(month,sm,10);
	itoa(day,sd,10);
	strcpy(date,sy);
	strcat(date,sm);
	strcat(date,sd);
	strcat(date,".txt");
	strcpy(fstr , "income//");
	strcat(fstr , date);
}

/*
* function_name: income_check
* return_type  : void
* param        : NULL
* description  : 查看收入 
*/ 
void income_check(){
	//打开所有订单文件，计算所有完结订单的收入
	system("cls"); 
	int tn = 1;
	
	double all_income, staple_food_income, hot_dish_income, cold_dish_income, drink_income;

	char fdate[50] = "";
	printf("**************************************\n");
	input_date_filename(fdate);
	
	printf("**************************************\n");
	FILE* fp;
	fp = fopen(fdate , "r");
	if(fp == NULL ){
		printf("这一天好像没有营业哟!\n");
	} else{
		format_output_income(fp,&all_income,&hot_dish_income,&cold_dish_income,&staple_food_income,&drink_income);
		fclose(fp);
	}

	printf("总收入:%.2lf\n",all_income);
	printf("热菜收入:%.2lf\n",hot_dish_income);
	printf("凉菜收入:%.2lf\n",cold_dish_income);
	printf("主食收入:%.2lf\n",staple_food_income);
	printf("饮品收入:%.2lf\n",drink_income);
	printf("**************************************\n");
	getch();
}

/*
* function_name: calculate_value 
* return_type  : void
* param        : char* 文件名称 ， 5个double* 分别用于返回计算值 
* description  : 从订单文件中 读取并计算价值 并通过参数将计算结果返回至调用函数中 
*/ 
void calculate_value(char* fstr, double* all, double* hot_dish , double* cold_dish, double* staple_food, double* drink){
	FILE* fp;
	fp = fopen(fstr , "r");
	int temp;
	fscanf(fp , "%d" , &temp);
	
	int no,type;
	char dish_name[20];
	int nums;
	double price;
	int cnt = 0 ;
	int temp_no = 0; 
	while(!feof(fp)){
		fscanf(fp ,"%d %s %lf %d %d",&no,dish_name,&price,&type,&nums );
		if(temp_no == no){
			break;
		}
		temp_no = no;
		*all += price * nums;
		switch(type){
			case 1:*hot_dish += price * nums;break;
			case 2:*cold_dish += price * nums;break;
			case 3:*staple_food += price * nums;break;
			case 4:*drink += price * nums;break;
		}
	}
	fclose(fp);
}

/*
* function_name: add_dish 
* return_type  : void
* param        : NULL
* description  : 添加菜品 
*/ 
void add_dish(){
	//定义文件指针
	FILE *fp;
	
	//定义控制变量
	int choice; 
 
	//功能运行主体
	do{
		//定义添加主体
		dish_menu new_dish; 
		
		//功能界面 
		system("cls");
		printf("请输入菜品编号：");
		scanf("%d",&new_dish.no); 
		printf("请输入菜品名称：");
		scanf("%s",new_dish.dish_name); 
		printf("请输入菜品价格：");
		scanf("%lf",&new_dish.dish_price);
		printf("请输入菜品种类：");
		scanf("%d",&new_dish.type);
		
		char filename[20];
		switch(new_dish.type){
			case 1:strcpy( filename , hot_dish_filename );break;
			case 2:strcpy( filename , cold_dish_filename );break;
			case 3:strcpy( filename , staple_food_filename );break;
			case 4:strcpy( filename , drink_filename );break;
		}
		
		fp = fopen( filename , "a");
		//将菜品信息录入文件 
		fprintf(fp,"%d\n",new_dish.no);
		fprintf(fp,"%s\n",new_dish.dish_name);
		fprintf(fp,"%lf\n",new_dish.dish_price);
		fprintf(fp,"%d\n",new_dish.type); 
		
		fclose(fp);
		
		//判断是否继续执行 
		printf("是否继续添加菜品：\n");
		printf("1.是\n");
		printf("2.否\n");
		scanf("%d",&choice);
		
		//输入异常检测
		error_check(1,2,&choice);
		 
	}while(choice != 2);
}

/*
* function_name: del_dish
* return_type  : void
* param        : NULL
* description  : 删除菜品 
*/ 
void del_dish(){
	int choice;
	int quit_handle = 0;
	int pos;
	do{
		system("cls");
		printf("1.热菜\n");
		printf("2.凉菜\n");
		printf("3.主食\n");
		printf("4.饮品\n");
		printf("请选择删除菜品的类型:");
		int type;
		scanf("%d" , &type);
		
		error_check(1,4,&type);
		
		//依据菜品类型打开对应文件
		char filename[20];
		switch(type){
			case 1:strcpy(filename,hot_dish_filename);break; 
			case 2:strcpy(filename,cold_dish_filename);break;
			case 3:strcpy(filename,staple_food_filename);break;
			case 4:strcpy(filename,drink_filename);break;
		}
		 
		FILE *fp;
		dish_menu dm[MAX_LENGTH];
		dish_menu dm_new[MAX_LENGTH];
		int cnt = 0;
		
		fp = fopen(filename , "r");
		while(!feof(fp)){
			fscanf(fp,"%d",&dm[cnt].no);
			fscanf(fp,"%s",dm[cnt].dish_name);
			fscanf(fp,"%lf",&dm[cnt].dish_price);
			fscanf(fp,"%d",&dm[cnt].type);
			cnt++;
		}
		fclose(fp);
		
		printf("请输入需要删除的菜品编号：");
		int del_no;
		scanf("%d",&del_no);
		
		//检索文件 该菜品是否存在 
		int flag = 0;
		do{
			int i;
			for(i = 0 ; i < cnt-1 ; i++){
				if(dm[i].no == del_no) flag=1;
				pos = i;
			}
			if(flag == 0){
				printf("没有该菜品!\n");
				printf("1.退出\n");
				printf("2.重新输入\n");
				
				int _choice;
				scanf("%d",&_choice);
				
				error_check(1,2,&_choice);
				
				if(_choice == 1){
					quit_handle = 1;
					break;
				}
				
				if(_choice == 2) scanf("%d",&del_no); 
			}
		}while(flag == 0);
		
		printf("是否确认删除<%s>菜品？1.是 2.否",dm[pos].dish_name);
		int del_choice;
		scanf("%d",&del_choice);
		
		error_check(1,2,&del_choice);
		
		//删除菜品
		if(del_choice == 1){
			int i;
			int j = 0;
			for(i = 0 ; i < cnt - 1 ; i++){
				if(i == pos){ // 跳过该菜品 
					continue; 
				}
				else{
					dm_new[j].no = dm[i].no;
					strcpy(dm_new[j].dish_name , dm[i].dish_name);
					dm_new[j].dish_price = dm[i].dish_price;
					dm_new[j].type = dm[i].type;
					j++;
				}
			}
			
			//将 dm_new 重新覆盖录入到菜单文件中
			fp = fopen(filename , "w");
			for(i = 0 ; i < cnt -2 ; i++){
				fprintf(fp , "%d\n",dm_new[i].no);
				fprintf(fp , "%s\n",dm_new[i].dish_name);
				fprintf(fp , "%lf\n",dm_new[i].dish_price);
				fprintf(fp , "%d\n",dm_new[i].type);
			}
			fclose(fp);
			
			printf("删除成功！\n");	 
		} 
		
		
		if(quit_handle == 1) break;
		
		printf("是否继续删除？1.是，2否？");
		scanf("%d",&choice);
		
		error_check(1,2,&choice);
	}while(choice != 2);
}

/*
* function_name: price_adjust 
* return_type  : void
* param        : NULL
* description  : 价格调整 
*/ 
void price_adjust(){
	int choice;
	int quit_handle = 0;
	int pos;
	do{
		system("cls");
		printf("1.热菜\n");
		printf("2.凉菜\n");
		printf("3.主食\n");
		printf("4.饮品\n");
		printf("请选择修改菜品的类型:");
		int type;
		scanf("%d" , &type);
		
		error_check(1,4,&type);
		
		//依据菜品类型打开对应文件
		char filename[20];
		switch(type){
			case 1:strcpy(filename,hot_dish_filename);break; 
			case 2:strcpy(filename,cold_dish_filename);break;
			case 3:strcpy(filename,staple_food_filename);break;
			case 4:strcpy(filename,drink_filename);break;
		}
		 
		FILE *fp;
		dish_menu dm[MAX_LENGTH];
		int cnt = 0;
		
		fp = fopen(filename , "r");
		while(!feof(fp)){
			fscanf(fp,"%d",&dm[cnt].no);
			fscanf(fp,"%s",dm[cnt].dish_name);
			fscanf(fp,"%lf",&dm[cnt].dish_price);
			fscanf(fp,"%d",&dm[cnt].type);
			cnt++;
		}
		fclose(fp);
		
		printf("请输入需要修改价格的菜品编号：");
		int adjust_no;
		scanf("%d",&adjust_no);
		
		//检索文件 该菜品是否存在 
		int flag = 0;
		do{
			int i;
			for(i = 0 ; i < cnt-1 ; i++){
				if(dm[i].no == adjust_no) flag=1;
				pos = i;
			}
			if(flag == 0){
				printf("没有该菜品!\n");
				printf("1.退出\n");
				printf("2.重新输入\n");
				
				int _choice;
				scanf("%d",&_choice);
				
				error_check(1,2,&_choice);
				
				if(_choice == 1){
					quit_handle = 1;
					break;
				}
				
				if(_choice == 2) scanf("%d",&adjust_no); 
			}
		}while(flag == 0);
		
		//修改菜品 
		printf("是否确认修改<%s>菜品的价格？1.是 2.否",dm[pos].dish_name);
		int adjust_choice;
		scanf("%d",&adjust_choice);
		
		error_check(1,2,&adjust_choice);
		
		if(adjust_choice == 1){
			printf("请输入修改菜品后的价格：");
			double re_price;
			scanf("%lf",&re_price); 
			
			int i;
			int j = 0;
			for(i = 0 ; i < cnt - 1 ; i++){
				if(i == pos){ //修改价格 
					dm[i].dish_price = re_price;
				}
			}
			
			//将 dm重新覆盖录入到菜单文件中
			fp = fopen(filename , "w");
			for(i = 0 ; i < cnt -1 ; i++){
				fprintf(fp , "%d\n",dm[i].no);
				fprintf(fp , "%s\n",dm[i].dish_name);
				fprintf(fp , "%lf\n",dm[i].dish_price);
				fprintf(fp , "%d\n",dm[i].type);
			}
			fclose(fp);
			
			printf("修改成功！\n");	 
		} 
		
		
		if(quit_handle == 1) break;
		
		printf("是否继续修改？1.是，2否？");
		scanf("%d",&choice);
		
		error_check(1,2,&choice);
	}while(choice != 2);
}


