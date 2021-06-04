#include "tools.c"
//�������� 
int table_no;                 //��̨�� 
extern char hot_dish_filename[20];
extern char cold_dish_filename[20];
extern char staple_food_filename[20];
extern char drink_filename[20]; 
//�������� 
int customer_menu();          //�˵�����
void cold_dish();             //���� 
void hot_dish();              //�Ȳ� 
void staple_food();           //��ʳ 
void drink();                 //��Ʒ 
void over_view();             //���� 
void check_bill();            //֧������ 
void order_status();          //����״̬
void page_controller(dish_menu* , int);       //�˵���ҳ 
int display_menu(dish_menu* , int , int);     //��ʾ�˵���Ϣ
void create_order(dish_menu* , int ,int);     //���ɶ��� 
void read_menu(char* , dish_menu* , int*);             //���ļ��ж�ȡ�˵� 

//�ⲿ�������� 
extern void error_check(int,int,int*);
extern void greet(struct tm* p,int);
extern struct tm* get_time();
extern void create_order_filename(int,char*); 

/*
* function_name: customer_form 
* return_type  : void
* param        : NULL
* description  : �˿�ϵͳ����ѭ�� 
*/ 
void customer_form(){
	system("cls");
	
	int choice;
	printf("**************************************\n");
	printf("���������Ĳ�̨�ţ�");
	scanf("%d",&table_no);
	
	//�򿪲˵����� 
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
* description  : �˿�ϵͳ������ʾ���棬��ȡ���� customer_form ����ѡ��ֵ 
*/ 
int customer_menu(){
	system("cls");
	int greet_type = 1;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("��̨��%d ��ѡ�����Ĳ���\n",table_no);
	printf("1.�Ȳ�\n"); 
	printf("2.����\n"); 
	printf("3.��ʳ\n");
	printf("4.��Ʒ\n"); 
	printf("5.����\n"); 
	printf("6.����\n"); 
	printf("7.����״̬\n");
	printf("8.�˳�\n");
	printf("����������:");
	scanf("%d",&choice);

	error_check(1,8,&choice);
	return choice;
}

/*
* function_name: read_menu
* return_type  : void
* param        : char* (filename) , dish_menu* (���ڷ��ض�ȡ����) , int* (������)
* description  : ��ȡ�˵� 
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
* description  : ��ȡ���˲˵������� ��ҳ���ơ���page_controller������ʾ�ò˵� 
*/ 
void cold_dish(){
	//���ýṹ�����鱣���ȡ���Ĳ˵�Ʒ��Ϣ
	dish_menu cold_dish_menu[MAX_LENGTH]; 
	
	//����һ�������������Ʒʵ������
	int cnt = 0 ; 
	
	//�� cold_dish.txt ����ȡ���ݽ�����ʾ
	read_menu(cold_dish_filename , cold_dish_menu , &cnt);
	
	//���÷�ҳ������ʾ�˵���ִ�е�˲���
	page_controller(cold_dish_menu,cnt); 
	 
}

/*
* function_name: hot_dish 
* return_type  : void
* param        : NULL
* description  : ��ȡ�Ȳ˲˵������� ��ҳ���ơ���page_controller������ʾ�ò˵� 
*/ 
void hot_dish(){
	//���ýṹ�����鱣���ȡ���Ĳ˵�Ʒ��Ϣ
	dish_menu hot_dish_menu[MAX_LENGTH]; 
	
	//����һ�������������Ʒʵ������
	int cnt = 0 ; 
	
	//�� cold_dish.txt ����ȡ���ݽ�����ʾ
	read_menu(hot_dish_filename , hot_dish_menu , &cnt);
	
	//���÷�ҳ������ʾ�˵���ִ�е�˲���
	page_controller(hot_dish_menu,cnt); 
}

/*
* function_name: staple_food 
* return_type  : void
* param        : NULL
* description  : ��ȡ��ʳ�˵������� ��ҳ���ơ���page_controller������ʾ�ò˵� 
*/ 
void staple_food(){
	//���ýṹ�����鱣���ȡ���Ĳ˵�Ʒ��Ϣ
	dish_menu staple_food_menu[MAX_LENGTH]; 
	
	//����һ�������������Ʒʵ������
	int cnt = 0 ; 
	
	//�� staple_food.txt ����ȡ���ݽ�����ʾ
	read_menu(staple_food_filename , staple_food_menu , &cnt);
	
	//���÷�ҳ������ʾ�˵���ִ�е�˲���
	page_controller(staple_food_menu, cnt); 
}

/*
* function_name: drink
* return_type  : void
* param        : NULL
* description  : ��ȡ��Ʒ�˵������� ��ҳ���ơ���page_controller������ʾ�ò˵� 
*/ 
void drink(){
	//���ýṹ�����鱣���ȡ���Ĳ˵�Ʒ��Ϣ
	dish_menu drink_menu[MAX_LENGTH]; 
	
	//����һ�������������Ʒʵ������
	int cnt = 0 ; 
	
	//�� drink.txt ����ȡ���ݽ�����ʾ
	read_menu(drink_filename , drink_menu , &cnt);
	
	//���÷�ҳ������ʾ�˵���ִ�е�˲���
	page_controller(drink_menu,cnt); 
}

/*
* function_name: over_view
* return_type  : void
* param        : NULL
* description  : ��ȡ��ǰ�ѵ㶩������������ʾ 
*/ 
void over_view(){
	system("cls");
	int cnt = 0;
	dish_order my_order[MAX_LENGTH];
	//�����������ɶ����ļ��� && version 1.7 ��������и��� 
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//�ж��Ƿ���ڸ��ļ����������ڣ���ö���������
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("**************************************\n");
		printf("����û���µ���\n");
		printf("**************************************\n");
		getch();
		return ; 
	}
	else{
		//���ļ��л�ȡ��������
		//��ȡ��־λ����ֹ���
		int flag_temp;
		fscanf(fp , "%d" , &flag_temp); 
		//�����ļ���Ϣ 
		
		while(!feof(fp)){
			fscanf(fp, "%d %s %lf %d %d" , &my_order[cnt].no , my_order[cnt].dish_name , &my_order[cnt].dish_price , &my_order[cnt].type , &my_order[cnt].nums);
			cnt++;
		}
	}
	fclose(fp); 
	
	//������Ϣ��ȡ��������ʾ
	printf("===========================================================\n");
	int i;
	printf("��� ��Ʒ���     ��Ʒ����       ����   ����     С��\n");
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
* description  : ��ȡ��ǰ�����ܼۣ���֧������ 
*/ 
void check_bill(){
	system("cls");
	double account = 0;
	int cnt = 0;
	dish_order my_order[MAX_LENGTH];
	//�����������ɶ����ļ���
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	printf("**************************************\n");
	//�ж��Ƿ���ڸ��ļ����������ڣ���ö���������
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("����û���µ���\n"); 
		printf("**************************************\n");
		getch();
		return ;
	}
	else{
		//���ļ��л�ȡ��������
		//��ȡ��־λ����ֹ���
		int flag_temp;
		fscanf(fp , "%d" , &flag_temp); 
		if(flag_temp != 1){
			printf("�������֧�������Ժ�Ϊ���ϲ�\n");
			system("pause");
			return ;
		}
		//�����ļ���Ϣ 
		
		while(!feof(fp)){
			fscanf(fp, "%d %s %lf %d %d" , &my_order[cnt].no , my_order[cnt].dish_name , &my_order[cnt].dish_price , &my_order[cnt].type , &my_order[cnt].nums);
			account += my_order[cnt].dish_price * my_order[cnt].nums;
			cnt++;
		}
	}
	fclose(fp); 
	
	printf("����Ҫ֧����%.2lfԪ\n",account);
	printf("��֧��:");
	double pay;
	scanf("%lf",&pay);
	
	while( pay < account){
		printf("�͹٣�Ǯ��������\n");
		printf("�͹��ٸ��㣺");
		scanf("%lf",&pay); 
	}
	if(pay>account){
		printf("�͹ٴ���������%.2lfԪ\n",pay-account);
	}
	printf("�͹����Եȣ�С�����֪ͨ�ϰ�����ϲ�\n");
	
	
	//���ñ�־λΪ 2 ��Ϊ֧����� ������¼���ļ�
	fp = fopen(fstr , "w");
	//���ñ�־λ
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
* description  : �û���ѯ����״̬ 
*/ 
void order_status(){
	system("cls");
	//�����������ɶ����ļ���
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//�ж��Ƿ���ڸ��ļ����������ڣ���ö���������
	printf("**************************************\n");
	FILE* fp;
	fp = fopen(fstr , "r");
	if(fp == NULL){
		printf("����û���µ���\n");
		printf("**************************************\n");
		getch();
		return ; 
	}
	int flag_temp;
	fscanf(fp,"%d",&flag_temp);
	fclose(fp);
	
	if(flag_temp == 1){
		printf("���ѵ�ˣ������Ʋ�ȥ֧��Ӵ��\n");
	}
	else if(flag_temp == 2){
		printf("����֧����ɣ��ϰ�������ȷ���У�\n");
	}
	else if(flag_temp == 3){
		printf("����Ϊ�����ͣ��Եȣ�\n");
	}
	else if(flag_temp == 4){
		printf("ף���ò���죬��ӭ�´ι��٣�\n");
	}
	printf("**************************************\n");
	getch();
}

/*
* function_name: page_controller 
* return_type  : void
* param        : dish_menu*(�˵�) , int(��Ʒ����)
* description  : ���ò�Ʒ�˵���ҳ��ʾ���߼���ͬʱ��create_orderʵ�ֵ�˹��� 
*/ 
void page_controller(dish_menu *dm , int cnt){
	//�������趨ÿҳ��ʾ�Ĳ�Ʒ���� 
	int record_num = 10;
	//�趨������ʾ��ر��� 
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
* param        : dish_menu* (�˵�) , int(���) , int(�յ�)
* description  :��ʾ�˵� 
*/ 
int display_menu(dish_menu *dm, int start , int end){
	int i;
	int choice;
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("���  ��Ʒ���    ��Ʒ����      �۸�\n");
	for( i = start ; i < end ; i++){
		printf(" %d\t %d\t  %s\t%.2lf\n",i+1,dm[i].no,dm[i].dish_name,dm[i].dish_price);
	}
	printf("----------------------------------------------------------\n"); 
	
	//��ӿ����߼�����ֹ���� 
	if(start == 0 && end-start < 10){
		//printf("1.��һҳ\n");
		//printf("2.��һҳ\n");
		printf("3.���\n");
		printf("4.�˳�\n");
		scanf("%d",&choice);
		//�����쳣��� 
		while(choice<3 || choice > 4){
			printf("����������������룺");
			scanf("%d",&choice);
		} 
	}
	else if(start == 0){//����һҳѡ�� 
		//printf("1.��һҳ\n");
		printf("2.��һҳ\n");
		printf("3.���\n");
		printf("4.�˳�\n");
		scanf("%d",&choice);
		//�����쳣��� 
		while(choice<2 || choice > 4){
			printf("����������������룺");
			scanf("%d",&choice);
		} 
	}
	else if(end - start != 10){//����һҳѡ�� 
		printf("1.��һҳ\n");
		//printf("2.��һҳ\n");
		printf("3.���\n");
		printf("4.�˳�\n");
		scanf("%d",&choice);
		//�����쳣��� 
		while(choice<1 || choice > 4 || choice == 2){
			printf("����������������룺");
			scanf("%d",&choice);
		} 
	}
	else{//������ʾ 
		printf("1.��һҳ\n");
		printf("2.��һҳ\n");
		printf("3.���\n");
		printf("4.�˳�\n");
		scanf("%d",&choice);
		//�����쳣��� 
		while(choice<1 || choice > 4){
			printf("����������������룺");
			scanf("%d",&choice);
		} 
	}
	return choice; 
}

/*
* function_name: create_order 
* return_type  : void
* param        : dish_menu*(�˵�) , int (ģʽ�����Ȳˣ����ˣ���ʳ����Ʒ) , int (��Ʒ����)
* description  :
*/ 
void create_order(dish_menu *dm , int mode,int count){
	//���õ�����ݽṹ���� �����Ϣ 
	int cnt = 0;
	dish_order new_order[MAX_LENGTH];  
	
	//����mode���ļ�
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
		printf("�������Ʒ��ţ�");
		scanf("%d",&temp_no);
		//����Ʒ����Ƿ����
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
				printf("����Ĳ�Ʒ��Ų����ڣ���������ȷ�Ĳ�Ʒ��ţ�");
				scanf("%d",&temp_no);
			}
		} while(flag == 0);
		
		//��Ʒ��Ŵ���ʱ����������
		printf("��������������");
		scanf("%d",&temp_num); 
		new_order[cnt].nums = temp_num;
		cnt++;
		
		//�ж��Ƿ�������
		printf("�Ƿ������ˣ� 1.�� 2.�� ��");
		scanf("%d",&choice);

		error_check(1,2,&choice);
		
	} while(choice != 2);	
	fclose(fp);
	
	//�����������ɶ����ļ���
	char fstr[50] = "order//";
	create_order_filename(table_no,fstr); 
	
	//end test
	//�����жϸ��ļ��Ƿ���ڣ��粻�����򴴽�һ���������ñ�־λΪ1  
	fp = fopen(fstr , "r");
	if(fp == NULL) { 
		fp = fopen(fstr , "w");
		fprintf(fp , "%d\n" , 1);
	}
	fclose(fp);
	//������׷��ģʽ���´��ļ�����������Ϣ��ӽ�ȥ 
	fp = fopen(fstr , "a");
	int i = 0 ;
	for( i = 0 ; i < cnt ; i++){
		fprintf(fp , "%d %s %lf %d %d\n" , new_order[i].no , new_order[i].dish_name , new_order[i].dish_price , new_order[i].type ,new_order[i].nums); 
	}
	fclose(fp); 
}

 
