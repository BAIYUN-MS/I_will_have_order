#include "tools.c"
//��������
//char pw[20] = "123456";                        //Ԥ�����룬������� 
//����ȫ�ֱ���
char hot_dish_filename[20] = "hot_dish.txt";
char cold_dish_filename[20] = "cold_dish.txt";
char staple_food_filename[20] = "staple_food.txt";
char drink_filename[20] = "drink.txt"; 
//�������� 
void gotoxy(int,int);
void input_password(char pw_input[],int wrong_time);     //�������� 
int check_password(char pw_input[]);      //������ 
int admin_menu();                         //����Ա�˵� 
void order_check();                       //����ȷ��
void order_complete();                    //��ɶ��� 
void income_check();                      //�鿴Ӫҵ�� 
void add_dish();                          //��Ӳ�Ʒ 
void del_dish();                          //ɾ����Ʒ 
void price_adjust();                      //�۸���� 
void change_password();                   //�����޸� 
void create_date_filename(char*);         //���ɵ����ļ��� 
void format_input_income(FILE*,double,double,double,double,double);            //�����ʽ�������ļ�
void format_output_income(FILE*,double*,double*,double*,double*,double*);      //�����ʽ����������� 
void calculate_value(char* , double* , double* , double* , double * , double*);//�������� 
void create_order_filename(int,char*);         //�����������ɶ����ļ���  
void record_income(double,double,double,double,double);                        //���ڼ�¼���ʶ���������Ϣ�������ļ��� 
void input_date_filename(char* fstr);          //������������������ļ��� 


//�ⲿ�������� 
extern void error_check(int,int,int*);
extern void greet(struct tm* p,int);
extern struct tm* get_time();

/*
* function_name: admin_form 
* return_type  : void
* param        : NULL
* description  : ����Աϵͳ����ѭ�� 
*/ 
void admin_form(){
	system("cls");
	printf("========��ӭʹ�ú�̨����ϵͳ��========\n");
	int choice;
	printf("�������������̨����:");
	char pw_input[20];
	
	int wrong_time = 0;
	input_password(pw_input , wrong_time);
	
	int flag;
	do{
		flag = check_password(pw_input);
		if(flag != 0 ){
			wrong_time++;
			printf("�����������������:");
			input_password(pw_input , wrong_time);
		}
		else{
			printf("������ȷ����ӭ����Ա��\n");
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
* description  : ��λ��Ļ����� ��x , y�� 
*/ 
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

/*
* function_name: input_password
* return_type  : void
* param        : char*(Ҫ���������) , int(���Ĵ���) 
* description  : �������� 
*/ 
void input_password(char pw_input[],int wrong_time){
	//����ַ���
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
		if(ch == 13){//�س��� 
			;
		}
		else if(ch == 8){//�˸�� 
			i--;
			cnt--;
			x--;
			gotoxy(x,y);
			printf(" ");
			gotoxy(x,y);
		}
		else{//��ͨ�ַ� 
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
* param        : char*(���������)
* description  : �������������Ƿ���ȷ����ȷ����0 �������0 
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
* description  : �޸����� 
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
	printf("����������룺");
	scanf("%s", pw_old_input);
	
	while(strcmp(pw_old , pw_old_input) != 0){
		printf("����������������룺");
		scanf("%s", pw_old_input);
	}
	
	printf("�����������룺");
	scanf("%s", pw_new);
	
	printf("��ȷ�������룺");
	scanf("%s" , pw_check);
	
	while(strcmp(pw_new , pw_check) != 0){
		printf("����������������룺\n");
		
		printf("�����������룺");
		scanf("%s", pw_new);
	
		printf("��ȷ�������룺");
		scanf("%s" , pw_check);
	}
	
	fp = fopen("password.txt" , "w");
	fprintf(fp ,"%s" , pw_new);
	fclose(fp);
	
	int i ;
	printf("�޸���ɣ����μ������룺%s\n" , pw_new);
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
* description  : ����Ա��������ʾ��������ѡ�� 
*/ 
int admin_menu(){
	system("cls");
	int greet_type = 2;
	struct tm* p = get_time();
	greet(p,greet_type);
	
	int choice;
	printf("��ѡ�����\n");
	printf("1.ȷ�Ϲ˿Ͷ���\n");
	printf("2.��ɹ˿Ͷ���\n");
	printf("3.�鿴Ӫҵ��\n");
	printf("4.��Ӳ�Ʒ\n");
	printf("5.ɾ����Ʒ\n");
	printf("6.�޸ļ۸�\n");
	printf("7.�����޸�\n"); 
	printf("8.�˳�\n");
	printf("�ڴ����룺");
	scanf("%d",&choice);
	
	error_check(1,8,&choice);
	return choice;
}

/*
* function_name: order_check
* return_type  : void
* param        : NULL
* description  : ȷ�϶��� 
*/ 
void order_check(){
	system("cls"); 
	int tn = 1;
	int flag = 0;
	//�������ż����ļ��������ļ���
	//������20������ 
	printf("**************************************\n");
	for(tn = 1 ; tn <= 20 ; tn++){
		// version 1.7 ����������ع� 
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
				printf("����:%d �����֧����\n",tn);
				printf("�Ƿ�ȷ�϶����� 1.�� 2.��\n");
				int choice;
				printf("�����������룺");
				scanf("%d",&choice);
				
				error_check(1,2,&choice);
				
				//���ȷ���������ñ�־λΪ 3 
				if(choice == 1){
					fp = fopen(fstr , "r+");
					fseek(fp , 0 , SEEK_SET);
					fprintf(fp,"%d" , 3);
					fclose(fp);
					
					printf("����:%d�Ķ�����ȷ�ϳɹ���\n",tn);
				}
			} 
		}
	}
	
	if(flag == 0){
		printf("���޶�����Ҫȷ�ϣ�\n");
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
* description  : ��ɶ��� �� ����������Ϣ�洢�������ļ��� 
*/ 
void order_complete(){
	system("cls"); 
	int tn = 1;
	int flag = 0;
	//�������ż����ļ��������ļ���
	//������20������ 
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
				printf("����:%d �����ȷ�ϣ����ͽ������ѡ����ɶ�����\n",tn);
				printf("�Ƿ�ȷ����ɶ����� 1.�� 2.��\n");
				int choice;
				printf("�����������룺");
				scanf("%d",&choice);
				
				error_check(1,2,&choice);
				
				if(choice == 1){
					double account = 0, account_hot_dish = 0,account_cold_dish = 0,account_staple_food = 0,account_drink = 0;
					calculate_value(fstr,&account,&account_hot_dish,&account_cold_dish,&account_staple_food,&account_drink);
					
					printf("����:%d�Ķ�������ɣ�\n",tn);
					// ���ܣ�������������Ϣ��¼�� income �ļ����� 
					record_income(account,account_hot_dish,account_cold_dish,account_staple_food,account_drink); 
					
					remove(fstr); 
				}
			} 
		}
	}
	
	if(flag == 0){
		printf("���޶���������ᣡ\n");
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
* param        : 5��double���� ���붩���и���������Ϣ 
* description  : ����ȡ���Ķ���������Ϣ��¼�� income �ļ��� ��Ӧ���ڵ��ļ��� 
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
* param        : FILE* fp 5 ��double���� 
* description  : ��ʽ���������� ����5��double���ݸ�ʽ�����뵽�ļ��� 
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
* param        : FILE* fp 5 ��double���� 
* description  : ��ʽ��������� ����5��double���ݸ�ʽ������������� 
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
* param        : char* fdate(���ڷ������ɺ���ļ���)
* description  : �Զ���ȡ�������ڣ��������ļ��� ��202161.txt 
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
* param        : int ���ţ����ڶ�λ�ļ���  char* ���ڷ����ļ��� 
* description  : ���������Զ������ļ��� ���� 1.txt 
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
* param        : char* ���ڷ����ļ��� 
* description  : ����������������������ļ��� 
*/
void input_date_filename(char* fstr){
	int year,month,day;
	printf("������Ҫ��ѯ����ݣ�");
	scanf("%d",&year);
	error_check(1900,3000,&year);
	printf("������Ҫ��ѯ���·ݣ�");
	scanf("%d",&month);
	error_check(1,12,&month);
	printf("������Ҫ��ѯ�����ڣ�");
	scanf("%d",&day);
	
	//�ж��Ƿ�Ϊ����
	int flag = 0;
	if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
		flag = 1;
	}
	
	int normal[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int special[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	
	//���������� 
	if(flag){
		error_check( 1 , special[month - 1] , &day);
	}
	else{
		error_check( 1 , normal[month - 1] , &day);
	}
	
	//�����ļ���	 
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
* description  : �鿴���� 
*/ 
void income_check(){
	//�����ж����ļ�������������ᶩ��������
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
		printf("��һ�����û��ӪҵӴ!\n");
	} else{
		format_output_income(fp,&all_income,&hot_dish_income,&cold_dish_income,&staple_food_income,&drink_income);
		fclose(fp);
	}

	printf("������:%.2lf\n",all_income);
	printf("�Ȳ�����:%.2lf\n",hot_dish_income);
	printf("��������:%.2lf\n",cold_dish_income);
	printf("��ʳ����:%.2lf\n",staple_food_income);
	printf("��Ʒ����:%.2lf\n",drink_income);
	printf("**************************************\n");
	getch();
}

/*
* function_name: calculate_value 
* return_type  : void
* param        : char* �ļ����� �� 5��double* �ֱ����ڷ��ؼ���ֵ 
* description  : �Ӷ����ļ��� ��ȡ�������ֵ ��ͨ�����������������������ú����� 
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
* description  : ��Ӳ�Ʒ 
*/ 
void add_dish(){
	//�����ļ�ָ��
	FILE *fp;
	
	//������Ʊ���
	int choice; 
 
	//������������
	do{
		//�����������
		dish_menu new_dish; 
		
		//���ܽ��� 
		system("cls");
		printf("�������Ʒ��ţ�");
		scanf("%d",&new_dish.no); 
		printf("�������Ʒ���ƣ�");
		scanf("%s",new_dish.dish_name); 
		printf("�������Ʒ�۸�");
		scanf("%lf",&new_dish.dish_price);
		printf("�������Ʒ���ࣺ");
		scanf("%d",&new_dish.type);
		
		char filename[20];
		switch(new_dish.type){
			case 1:strcpy( filename , hot_dish_filename );break;
			case 2:strcpy( filename , cold_dish_filename );break;
			case 3:strcpy( filename , staple_food_filename );break;
			case 4:strcpy( filename , drink_filename );break;
		}
		
		fp = fopen( filename , "a");
		//����Ʒ��Ϣ¼���ļ� 
		fprintf(fp,"%d\n",new_dish.no);
		fprintf(fp,"%s\n",new_dish.dish_name);
		fprintf(fp,"%lf\n",new_dish.dish_price);
		fprintf(fp,"%d\n",new_dish.type); 
		
		fclose(fp);
		
		//�ж��Ƿ����ִ�� 
		printf("�Ƿ������Ӳ�Ʒ��\n");
		printf("1.��\n");
		printf("2.��\n");
		scanf("%d",&choice);
		
		//�����쳣���
		error_check(1,2,&choice);
		 
	}while(choice != 2);
}

/*
* function_name: del_dish
* return_type  : void
* param        : NULL
* description  : ɾ����Ʒ 
*/ 
void del_dish(){
	int choice;
	int quit_handle = 0;
	int pos;
	do{
		system("cls");
		printf("1.�Ȳ�\n");
		printf("2.����\n");
		printf("3.��ʳ\n");
		printf("4.��Ʒ\n");
		printf("��ѡ��ɾ����Ʒ������:");
		int type;
		scanf("%d" , &type);
		
		error_check(1,4,&type);
		
		//���ݲ�Ʒ���ʹ򿪶�Ӧ�ļ�
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
		
		printf("��������Ҫɾ���Ĳ�Ʒ��ţ�");
		int del_no;
		scanf("%d",&del_no);
		
		//�����ļ� �ò�Ʒ�Ƿ���� 
		int flag = 0;
		do{
			int i;
			for(i = 0 ; i < cnt-1 ; i++){
				if(dm[i].no == del_no) flag=1;
				pos = i;
			}
			if(flag == 0){
				printf("û�иò�Ʒ!\n");
				printf("1.�˳�\n");
				printf("2.��������\n");
				
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
		
		printf("�Ƿ�ȷ��ɾ��<%s>��Ʒ��1.�� 2.��",dm[pos].dish_name);
		int del_choice;
		scanf("%d",&del_choice);
		
		error_check(1,2,&del_choice);
		
		//ɾ����Ʒ
		if(del_choice == 1){
			int i;
			int j = 0;
			for(i = 0 ; i < cnt - 1 ; i++){
				if(i == pos){ // �����ò�Ʒ 
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
			
			//�� dm_new ���¸���¼�뵽�˵��ļ���
			fp = fopen(filename , "w");
			for(i = 0 ; i < cnt -2 ; i++){
				fprintf(fp , "%d\n",dm_new[i].no);
				fprintf(fp , "%s\n",dm_new[i].dish_name);
				fprintf(fp , "%lf\n",dm_new[i].dish_price);
				fprintf(fp , "%d\n",dm_new[i].type);
			}
			fclose(fp);
			
			printf("ɾ���ɹ���\n");	 
		} 
		
		
		if(quit_handle == 1) break;
		
		printf("�Ƿ����ɾ����1.�ǣ�2��");
		scanf("%d",&choice);
		
		error_check(1,2,&choice);
	}while(choice != 2);
}

/*
* function_name: price_adjust 
* return_type  : void
* param        : NULL
* description  : �۸���� 
*/ 
void price_adjust(){
	int choice;
	int quit_handle = 0;
	int pos;
	do{
		system("cls");
		printf("1.�Ȳ�\n");
		printf("2.����\n");
		printf("3.��ʳ\n");
		printf("4.��Ʒ\n");
		printf("��ѡ���޸Ĳ�Ʒ������:");
		int type;
		scanf("%d" , &type);
		
		error_check(1,4,&type);
		
		//���ݲ�Ʒ���ʹ򿪶�Ӧ�ļ�
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
		
		printf("��������Ҫ�޸ļ۸�Ĳ�Ʒ��ţ�");
		int adjust_no;
		scanf("%d",&adjust_no);
		
		//�����ļ� �ò�Ʒ�Ƿ���� 
		int flag = 0;
		do{
			int i;
			for(i = 0 ; i < cnt-1 ; i++){
				if(dm[i].no == adjust_no) flag=1;
				pos = i;
			}
			if(flag == 0){
				printf("û�иò�Ʒ!\n");
				printf("1.�˳�\n");
				printf("2.��������\n");
				
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
		
		//�޸Ĳ�Ʒ 
		printf("�Ƿ�ȷ���޸�<%s>��Ʒ�ļ۸�1.�� 2.��",dm[pos].dish_name);
		int adjust_choice;
		scanf("%d",&adjust_choice);
		
		error_check(1,2,&adjust_choice);
		
		if(adjust_choice == 1){
			printf("�������޸Ĳ�Ʒ��ļ۸�");
			double re_price;
			scanf("%lf",&re_price); 
			
			int i;
			int j = 0;
			for(i = 0 ; i < cnt - 1 ; i++){
				if(i == pos){ //�޸ļ۸� 
					dm[i].dish_price = re_price;
				}
			}
			
			//�� dm���¸���¼�뵽�˵��ļ���
			fp = fopen(filename , "w");
			for(i = 0 ; i < cnt -1 ; i++){
				fprintf(fp , "%d\n",dm[i].no);
				fprintf(fp , "%s\n",dm[i].dish_name);
				fprintf(fp , "%lf\n",dm[i].dish_price);
				fprintf(fp , "%d\n",dm[i].type);
			}
			fclose(fp);
			
			printf("�޸ĳɹ���\n");	 
		} 
		
		
		if(quit_handle == 1) break;
		
		printf("�Ƿ�����޸ģ�1.�ǣ�2��");
		scanf("%d",&choice);
		
		error_check(1,2,&choice);
	}while(choice != 2);
}


