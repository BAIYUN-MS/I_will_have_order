//全局变量以及用到的头文件 在此声明 
#ifndef __init__
#define __init__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <io.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

#define MAX_LENGTH 100

//菜单数据结构 
typedef struct a{
	int no;//编号 
	char dish_name[20];
	double dish_price;
	int type;//种类 1-热菜 2-凉菜  3-主食 4- 饮品 
}dish_menu; 

//顾客点菜订单文件中的两部分内容 
//1. 订单状态     1---订单生成  2---支付成功  3---商家已确认 
//2. 数据结构中的内容 
//顾客点菜订单的数据结构
typedef struct b{
	int no;
	char dish_name[20];
	double dish_price;
	int type;
	int nums;//点菜时的数量 
}dish_order; 

#endif
