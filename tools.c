//ȫ�ֱ����Լ��õ���ͷ�ļ� �ڴ����� 
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

//�˵����ݽṹ 
typedef struct a{
	int no;//��� 
	char dish_name[20];
	double dish_price;
	int type;//���� 1-�Ȳ� 2-����  3-��ʳ 4- ��Ʒ 
}dish_menu; 

//�˿͵�˶����ļ��е����������� 
//1. ����״̬     1---��������  2---֧���ɹ�  3---�̼���ȷ�� 
//2. ���ݽṹ�е����� 
//�˿͵�˶��������ݽṹ
typedef struct b{
	int no;
	char dish_name[20];
	double dish_price;
	int type;
	int nums;//���ʱ������ 
}dish_order; 

#endif
