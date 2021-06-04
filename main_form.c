#include"tools.c"

//�������� 

//�������� 
void error_check(int,int,int*);
void greet(struct tm* p,int);
struct tm* get_time();

/*
* function_name: main_form
* return_type  : int 
* param        : NULL
* description  : �������������ʾ���棬��ȡѡ����Ϣ�������� ������ main 
*/ 
int main_form(){
	system("cls");
	int greet_type = 0;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("��ѡ��������ݣ�\n");
	printf("1.�˿�\n");
	printf("2.������Ա\n");
	printf("3.�˳�\n");
	printf("�����������룺"); 
	scanf("%d",&choice);
	//����� ��ֹ�������ѡ���³������
	error_check(1,3,&choice);
	return choice;
} 

/*
* function_name: error_check 
* return_type  : void
* param        : int����߽磩, int���ұ߽磩,int* (ѡ��) 
* description  : ���ڼ�������Ƿ���ȷ����Ϊ�Ƿ����룬���ظ��޸�ѡ��ֱ���Ϸ� 
*/ 
void error_check(int range_left ,int range_right, int* choice){
	while(*choice < range_left || *choice > range_right){
		printf("�����������������:");
		scanf("%d",choice); 
	}
}

/*
* function_name: greet
* return_type  : void
* param        : struct tm* (ʱ��) , int (�ʺ����� 0-Ĭ�� 1-�û� 2-����Ա )
* description  : �ʺ��� ���ݵ�ǰʱ��,�û����͸����ʺ� 
*/  
void greet(struct tm* p , int greet_type){
	//ת��ʱ��
	int china_time = (p->tm_hour + 8) % 24;
	if(p->tm_hour + 8 >= 24) p->tm_mday -= 1; 
	//����ʱ�������ʺ�
	printf("+++++++++++++++++++++++++++++++++++++++++++\n");
	if(china_time >= 6 && china_time  < 8) printf("���Ϻã�");
	else if(china_time  >= 8 && china_time  < 12) printf("����ã�");
	else if(china_time  >= 12 && china_time  < 14) printf("����ã�");
	else if(china_time  >= 14 && china_time  < 18) printf("����ã�");
	else if(china_time  >= 18 && china_time  < 24) printf("���Ϻã�");
	else printf("ҹ���ע����Ϣ��");  
	
	printf("\n");
	
	if(greet_type == 0){
		printf("��ӭʹ�ò������ϵͳ��\n");;
	}
	else if(greet_type == 1){
		printf("���һ�ӭ���Ĺ��٣�\n");
	}
	else{
		printf("����Ҳ�ǳ���ϣ����һ�죡\n");
	}
}

/*
* function_name: get_time 
* return_type  : struct tm*
* param        : NULL
* description  : ��ȡʱ�䲢������ز��� 
*/ 
struct tm* get_time(){
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	
	return p;
} 
