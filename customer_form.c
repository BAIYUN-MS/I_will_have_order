#include "tools.c"
//变量声明 
int table_no;                 //餐台号 
extern char hot_dish_filename[20];
extern char cold_dish_filename[20];
extern char staple_food_filename[20];
extern char drink_filename[20]; 
//函数声明 
int customer_menu();          //菜单界面
void cold_dish();             //凉菜 
void hot_dish();              //热菜 
void staple_food();           //主食 
void drink();                 //饮品 
void over_view();             //总览 
void check_bill();            //支付订单 
void order_status();          //订单状态
void page_controller(dish_menu* , int);       //菜单分页 
int display_menu(dish_menu* , int , int);     //显示菜单信息
void create_order(dish_menu* , int ,int);     //生成订单 
void read_menu(char* , dish_menu* , int*);             //从文件中读取菜单 

//外部函数声明 
extern void error_check(int,int,int*);
extern void greet(struct tm* p,int);
extern struct tm* get_time();
extern void create_order_filename(int,char*); 

/*
* function_name: customer_form 
* return_type  : void
* param        : NULL
* description  : 顾客系统的主循环 
*/ 
void customer_form(){
	system("cls");
	
	int choice;
	printf("**************************************\n");
	printf("请输入您的餐台号：");
	scanf("%d",&table_no);
	
	//打开菜单界面 
	do{
		choice = customer_menu();
		switch(choice){
			case 1:hot_dish();break;
			case 2:cold_dish();break;
			case 3:staple_food();break;
			case 4:drink();break;
			case 5:over_view();break;
			case 6:check_bill();break;
			case 7:order_status();break;
			default:break;		
		}
	}while(choice != 8);
}

/*
* function_name: customer_menu 
* return_type  : int
* param        : NULL
* description  : 顾客系统的主显示界面，获取并向 customer_form 返回选择值 
*/ 
int customer_menu(){
	system("cls");
	int greet_type = 1;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("餐台：%d 请选择您的操作\n",table_no);
	printf("1.热菜\n"); 
	printf("2.凉菜\n"); 
	printf("3.主食\n");
	printf("4.饮品\n"); 
	printf("5.总览\n"); 
	printf("6.结账\n"); 
	printf("7.订单状态\n");
	printf("8.退出\n");
	printf("在这里输入:");
	scanf("%d",&choice);

	error_check(1,8,&choice);
	return choice;
}

/*
* function_name: read_menu
* return_type  : void
* param        : char* (filename) , dish_menu* (用于返回读取内容) , int* (计数器)
* description  : 读取菜单 
*/
void read_menu(char* filename , dish_menu* dm , int* cnt){
	FILE* fp;
	fp = fopen(filename , "r");
	while(!feof(fp)){
		fscanf(fp,"%d",&dm[*cnt].no);
		fscanf(fp,"%s",dm[*cnt].dish_name);
		fscanf(fp,"%lf",&dm[*cnt].dish_price);
		fscanf(fp,"%d",&dm[*cnt].type);
		(*cnt)++;
	}
	fclose(fp);
} 

/*
* function_name: cold_dish
* return_type  : void
* param        : NULL
* description  : 获取凉菜菜单，并由 分页控制——page_controller函数显示该菜单 
*/ 
void cold_dish(){
	//采用结构体数组保存读取到的菜单品信息
	dish_menu cold_dish_menu[MAX_LENGTH]; 
	
	//设置一个计数器保存菜品实际数量
	int cnt = 0 ; 
	
	//打开 cold_dish.txt 并读取数据进行显示
	read_menu(cold_dish_filename , cold_dish_menu , &cnt);
	
	//采用分页控制显示菜单并执行点菜操作
	page_controller(cold_dish_menu,cnt); 
	 
}

/*
* function_name: hot_dish 
* return_type  : void
* param        : NULL
* description  : 获取热菜菜单，并由 分页控制——page_controller函数显示该菜单 
*/ 
void hot_dish(){
	//采用结构体数组保存读取到的菜单品信息
	dish_menu hot_dish_menu[MAX_LENGTH]; 
	
	//设置一个计数器保存菜品实际数量
	int cnt = 0 ; 
	
	//打开 cold_dish.txt 并读取数据进行显示
	read_menu(hot_dish_filename , hot_dish_menu , &cnt);
	
	//采用分页控制显示菜单并执行点菜操作
	page_controller(hot_dish_menu,cnt); 
}

/*
* function_name: staple_food 
* return_type  : void
* param        : NULL
* description  : 获取主食菜单，并由 分页控制——page_controller函数显示该菜单 
*/ 
void staple_food(){
	//采用结构体数组保存读取到的菜单品信息
	dish_menu staple_food_menu[MAX_LENGTH]; 
	
	//设置一个计数器保存菜品实际数量
	int cnt = 0 ; 
	
	//打开 staple_food.txt 并读取数据进行显示
	read_menu(staple_food_filename , staple_food_menu , &cnt);
	
	//采用分页控制显示菜单并执行点菜操作
	page_controller(staple_food_menu, cnt); 
}

/*
* function_name: drink
* return_type  : void
* param        : NULL
* description  : 获取饮品菜单，并由 分页控制——page_controller函数显示该菜单 
*/ 
void drink(){
	//采用结构体数组保存读取到的菜单品信息
	dish_menu drink_menu[MAX_LENGTH]; 
	
	//设置一个计数器保存菜品实际数量
	int cnt = 0 ; 
	
	//打开 drink.txt 并读取数据进行显示
	read_menu(drink_filename , drink_menu , &cnt);
	
	//采用分页控制显示菜单并执行点菜操作
	page_controller(drink_menu,cnt); 
}

/*
* function_name: over_view
* return_type  : void
* param        : NULL
* description  : 获取当前已点订单，并将其显示 
*/ 
void over_view(){
	system("cls");
	int cnt = 0;
	dish_order my_order[MAX_LENGTH];
	//根据桌号生成订单文件名 && version 1.7 对这里进行更新 
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//判断是否存在该文件，若不存在，则该订单不存在
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("**************************************\n");
		printf("您还没有下单！\n");
		printf("**************************************\n");
		getch();
		return ; 
	}
	else{
		//从文件中获取订单内容
		//提取标志位，防止误读
		int flag_temp;
		fscanf(fp , "%d" , &flag_temp); 
		//读出文件信息 
		
		while(!feof(fp)){
			fscanf(fp, "%d %s %lf %d %d" , &my_order[cnt].no , my_order[cnt].dish_name , &my_order[cnt].dish_price , &my_order[cnt].type , &my_order[cnt].nums);
			cnt++;
		}
	}
	fclose(fp); 
	
	//订单信息读取结束后显示
	printf("===========================================================\n");
	int i;
	printf("序号 菜品编号     菜品名称       单价   数量     小计\n");
	for( i = 0 ; i < cnt-1 ; i++){
		printf("%d\t %d\t  %s\t %.2lf\t %d\t %.2lf\n",i+1 , my_order[i].no , my_order[i].dish_name , my_order[i].dish_price , my_order[i].nums , my_order[i].dish_price * my_order[i].nums);
	}
	
	printf("***********************************************************\n");
	getch(); 
}

/*
* function_name: check_bill
* return_type  : void
* param        : NULL
* description  : 获取当前订单总价，并支付订单 
*/ 
void check_bill(){
	system("cls");
	double account = 0;
	int cnt = 0;
	dish_order my_order[MAX_LENGTH];
	//根据桌号生成订单文件名
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	printf("**************************************\n");
	//判断是否存在该文件，若不存在，则该订单不存在
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("您还没有下单！\n"); 
		printf("**************************************\n");
		getch();
		return ;
	}
	else{
		//从文件中获取订单内容
		//提取标志位，防止误读
		int flag_temp;
		fscanf(fp , "%d" , &flag_temp); 
		if(flag_temp != 1){
			printf("您已完成支付，请稍候为您上餐\n");
			system("pause");
			return ;
		}
		//读出文件信息 
		
		while(!feof(fp)){
			fscanf(fp, "%d %s %lf %d %d" , &my_order[cnt].no , my_order[cnt].dish_name , &my_order[cnt].dish_price , &my_order[cnt].type , &my_order[cnt].nums);
			account += my_order[cnt].dish_price * my_order[cnt].nums;
			cnt++;
		}
	}
	fclose(fp); 
	
	printf("宁需要支付：%.2lf元\n",account);
	printf("请支付:");
	double pay;
	scanf("%lf",&pay);
	
	while( pay < account){
		printf("客官，钱还不够！\n");
		printf("客官再给点：");
		scanf("%lf",&pay); 
	}
	if(pay>account){
		printf("客官大气，找您%.2lf元\n",pay-account);
	}
	printf("客官请稍等，小的这就通知老板给您上菜\n");
	
	
	//设置标志位为 2 ，为支付完成 ，重新录入文件
	fp = fopen(fstr , "w");
	//设置标志位
	fprintf(fp , "%d\n" , 2); 
	int i;
	for(i = 0 ; i < cnt-1 ; i++ ){
		fprintf(fp,"%d %s %lf %d %d\n" , my_order[i].no , my_order[i].dish_name ,my_order[i].dish_price , my_order[i].type , my_order[i].nums);
	}
	fclose(fp); 
	
	printf("**************************************\n");
	int a;
	for(a = 0 ; a < 3 ;a++){
		printf(".");
		Sleep(1000);
	}
}

/*
* function_name: order_status 
* return_type  : void
* param        : NULL
* description  : 用户查询订单状态 
*/ 
void order_status(){
	system("cls");
	//根据桌号生成订单文件名
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//判断是否存在该文件，若不存在，则该订单不存在
	printf("**************************************\n");
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("您还没有下单！\n");
		printf("**************************************\n");
		getch();
		return ; 
	}
	int flag_temp;
	fscanf(fp,"%d",&flag_temp);
	fclose(fp);
	
	if(flag_temp == 1){
		printf("您已点菜，可以移步去支付哟！\n");
	}
	else if(flag_temp == 2){
		printf("您已支付完成，老板大大正在确认中！\n");
	}
	else if(flag_temp == 3){
		printf("正在为您出餐，稍等！\n");
	}
	else if(flag_temp == 4){
		printf("祝您用餐愉快，欢迎下次光临！\n");
	}
	printf("**************************************\n");
	getch();
}

/*
* function_name: page_controller 
* return_type  : void
* param        : dish_menu*(菜单) , int(菜品数量)
* description  : 设置菜品菜单分页显示的逻辑，同时由create_order实现点菜功能 
*/ 
void page_controller(dish_menu *dm , int cnt){
	//在这里设定每页显示的菜品数量 
	int record_num = 10;
	//设定部分显示相关变量 
	int base = 0;
	int start,end;
	start = base;
	end = start + record_num > cnt ? cnt-1 : start + record_num; 
	
	int choice;
	do{
		choice = display_menu(dm , start , end);
		switch(choice){
			case 1:{
				if(end - start < record_num){
					end = end - (end - start);
				}else{
					end -= record_num;	
				}
				start -= record_num;
				break;
			}
			case 2:{
				start += record_num;
				end = start + record_num > cnt ? cnt-1 : start+record_num;
				break;
			}
			case 3:{
				int mode = dm[0].type;
				create_order(dm,mode,cnt);
				break;
			}
			case 4:break;
		}	
	} while(choice != 4);
} 

/*
* function_name: display_menu
* return_type  : int
* param        : dish_menu* (菜单) , int(起点) , int(终点)
* description  :显示菜单 
*/ 
int display_menu(dish_menu *dm, int start , int end){
	int i;
	int choice;
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("序号  菜品编号    菜品名称      价格\n");
	for( i = start ; i < end ; i++){
		printf(" %d\t %d\t  %s\t%.2lf\n",i+1,dm[i].no,dm[i].dish_name,dm[i].dish_price);
	}
	printf("----------------------------------------------------------\n"); 
	
	//添加控制逻辑，防止误判 
	if(start == 0 && end-start < 10){
		//printf("1.上一页\n");
		//printf("2.下一页\n");
		printf("3.点菜\n");
		printf("4.退出\n");
		scanf("%d",&choice);
		//输入异常检测 
		while(choice<3 || choice > 4){
			printf("输入错误，请重新输入：");
			scanf("%d",&choice);
		} 
	}
	else if(start == 0){//无上一页选项 
		//printf("1.上一页\n");
		printf("2.下一页\n");
		printf("3.点菜\n");
		printf("4.退出\n");
		scanf("%d",&choice);
		//输入异常检测 
		while(choice<2 || choice > 4){
			printf("输入错误，请重新输入：");
			scanf("%d",&choice);
		} 
	}
	else if(end - start != 10){//无下一页选项 
		printf("1.上一页\n");
		//printf("2.下一页\n");
		printf("3.点菜\n");
		printf("4.退出\n");
		scanf("%d",&choice);
		//输入异常检测 
		while(choice<1 || choice > 4 || choice == 2){
			printf("输入错误，请重新输入：");
			scanf("%d",&choice);
		} 
	}
	else{//正常显示 
		printf("1.上一页\n");
		printf("2.下一页\n");
		printf("3.点菜\n");
		printf("4.退出\n");
		scanf("%d",&choice);
		//输入异常检测 
		while(choice<1 || choice > 4){
			printf("输入错误，请重新输入：");
			scanf("%d",&choice);
		} 
	}
	return choice; 
}

/*
* function_name: create_order 
* return_type  : void
* param        : dish_menu*(菜单) , int (模式——热菜，凉菜，主食，饮品) , int (菜品数量)
* description  :
*/ 
void create_order(dish_menu *dm , int mode,int count){
	//采用点菜数据结构保存 点菜信息 
	int cnt = 0;
	dish_order new_order[MAX_LENGTH];  
	
	//根据mode打开文件
	char filename[20];
	switch(mode){
		case 1:strcpy(filename,hot_dish_filename);break;
		case 2:strcpy(filename,cold_dish_filename);break;
		case 3:strcpy(filename,staple_food_filename);break;
		case 4:strcpy(filename,drink_filename);break;
	} 
	FILE* fp;
	fp = fopen(filename,"r");
	
	int choice;
	int temp_no;
	int temp_num;
	do{
		printf("请输入菜品编号：");
		scanf("%d",&temp_no);
		//检测菜品编号是否存在
		int flag = 0;
		do{
			int i;
			for( i = 0 ; i < count ; i++){
				if(dm[i].no == temp_no){
					flag = 1;
					new_order[cnt].no = dm[i].no;
					strcpy(new_order[cnt].dish_name , dm[i].dish_name);
					new_order[cnt].dish_price = dm[i].dish_price;
					new_order[cnt].type = dm[i].type;
					break;
				}
			}
			
			if(flag == 0){
				printf("输入的菜品编号不存在，请输入正确的菜品编号：");
				scanf("%d",&temp_no);
			}
		} while(flag == 0);
		
		//菜品编号存在时输入点菜数量
		printf("请输入点菜数量：");
		scanf("%d",&temp_num); 
		new_order[cnt].nums = temp_num;
		cnt++;
		
		//判断是否继续点菜
		printf("是否继续点菜？ 1.是 2.否 ：");
		scanf("%d",&choice);

		error_check(1,2,&choice);
		
	} while(choice != 2);	
	fclose(fp);
	
	//根据桌号生成订单文件名
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//end test
	//首先判断该文件是否存在，如不存在则创建一个，并设置标志位为1  
	fp = fopen(fstr , "r");
	if(fp == NULL) { 
		fp = fopen(fstr , "w");
		fprintf(fp , "%d\n" , 1);
	}
	fclose(fp);
	//而后以追加模式重新打开文件，将订单信息添加进去 
	fp = fopen(fstr , "a");
	int i = 0 ;
	for( i = 0 ; i < cnt ; i++){
		fprintf(fp , "%d %s %lf %d %d\n" , new_order[i].no , new_order[i].dish_name , new_order[i].dish_price , new_order[i].type ,new_order[i].nums); 
	}
	fclose(fp); 
}

 
