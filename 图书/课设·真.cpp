#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>// ������getch����������ֱ�Ӷ��룻���谴�س�,��԰���������أ� 
#include <malloc.h> 

struct book { // ͼ����Ϣ
	char num[100],name[100],aut[100],clas[100],pub[100],time[100],price[100];
	struct book *next;
} str;

struct land { //��¼��Ϣ
	int qq;
	char pw[20];
	struct land*next;
};


void cmain(); //ͼ�����Ϣ�˵�
void cmenu(); //����˵�
void lmain();//��¼�˵�

void search();//����ͼ�鹦�ܣ�
void gai();//����ͼ����Ϣ
void cun();//���鹦��
void land();//��½����
void xinjian();//�½��˺Ź���
int match(int,int);//ƥ�������Ƿ���ȷ
int math();//ͳ���ļ��еĽṹ�����
void pai();// ͼ������ 
void look();   //���ͼ��;

void pai() {

	struct book st[100];
	FILE *fp;
	int n=0,j,k,m=0,a,b;
	fp=fopen("library.txt","r");

	j=math();
	for( k=0; k<j; k++) {
		fscanf(fp,"%s%s%s%s%s%s%s",st[k].num,st[k].name,st[k].aut,st[k].clas,st[k].pub,st[k].time,st[k].price);
	}
	for(a=0; a<j-1; a++) {
		for(b=0; b<j-a-1; b++) {
			if(strcmp(st[b].num,st[b+1].num)>0) {
				str=st[b];
				st[b]=st[b+1];
				st[b+1]=str;
			}
		}
	}
	fclose(fp);
	fp=fopen("library.txt","w");
	for( k=0; k<j; k++) {
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n",st[k].num,st[k].name,st[k].aut,st[k].clas,st[k].pub,st[k].time,st[k].price);

	}
	fclose(fp);
	cmenu();
}
void gai() {  //�޸�ͼ����Ϣ��
	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,m=0;
	char na[20],a[20],ch;
	FILE *fp;

	system ("cls");

	fp=fopen("library.txt","r");
	j=math();
	ch=fgetc(fp);
	if(ch==EOF)
		printf("����ͼ����Ϣ��¼\n�����������\n");
	else {
		rewind(fp);
		j=math();
		printf("\n������Ҫ�޸�ͼ���������������:\n");//�����޸�ͼ������
		scanf("%s",na);
		for( k=0; k<j; k++) {

			if(k==0) {
				p1=head=(struct book*)malloc(sizeof(struct book));
				fscanf(fp,"%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);
				p1=head;
			} else {
				p2=(struct book*)malloc(sizeof(struct book));
				fscanf(fp,"%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
				p1->next=p2;
				p1=p2;
			}
		}
		p1->next=NULL;
		fclose(fp);

		p2=head;
		for (; p2!=NULL;) {

			if(strcmp(na,p2->name)==0||strcmp(na,p2->aut)==0) {
				if(m==0) {
					printf("�Ƿ�ͬ���������ߵ���Ϣȫ����Ϊһ�£���y/n��\n");
					getchar();
					gets(a);

					while(a[0]!='y'&&a[0]!='n') {
						printf("����������(y/n)\n");
						gets(a);
					}
				}

				if(a[0]=='n') {
					printf("��������ĺ����Ϣ��\n");
					scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
				} else {
					if(m==0) {
						printf("��������ĺ����Ϣ��\n");
						scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
						p1=p2;
					} else {
						strcpy(p2->num,p1->num);//���Ƶ�¼��
						strcpy(p2->name,p1->name);//��������
						strcpy(p2->aut,p1->aut);//������������
						strcpy(p2->clas,p1->clas);//�������
						strcpy(p2->pub,p1->pub);//���Ƴ�����
						strcpy(p2->time,p1->time);//����ʱ��
						strcpy(p2->price,p1->price);//���Ƶ���
					}
				}
				m++;
			}
			p2=p2->next;
		}
	}

	fp=fopen("library.txt","w");
	p2=head;

	for (; p2!=NULL;) { //���������ݸ��ǵ��ļ�
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
		p2=p2->next;
	}
	fclose(fp);
	system ("cls");
	if(m==0) {
		printf("�޴�ͼ����Ϣ\n�����������\n");
	} else
		printf("\n�޸ĳɹ� \n�������������һ��\n");
	getch();
	pai();
	return ;
}

void cun() {  //����
	//���鹦�ܣ�

	system ("cls");
	FILE   *fp;
	struct book *p1,*p2,*head;
	char v,y;

	printf("\n�밴���¸�ʽ����ͼ����Ϣ:\n��¼�� ���� ���� ����� ���浥λ ����ʱ�� ����");
	printf("������:\n");
	p1=head=(struct book*)malloc(sizeof(struct book));
	scanf("%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);

	p1=head;
	printf("\n�����Ƿ��������,��y/n)\n");
	getchar();
	v=getchar();
	while (v!='n'&&v!='y') {
		getchar();
		printf("\n���������루y/n)\n");
		v=getchar();
	}
	while(v!='n') {
		printf("\n�밴���¸�ʽ����ͼ����Ϣ:\n��¼�� ���� ���� ����� ���浥λ ����ʱ�� ����\n");
		p2=(struct book*)malloc(sizeof(struct book));
		scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
		p1->next=p2;
		p1=p2;

		getchar();
		printf("\n�����Ƿ��������,��y/n)\n");
		v=getchar();
	}
	p1->next=NULL;

	if ((fp=fopen("library.txt","r"))==NULL) {
		fp=fopen("library.txt","w");
		fclose(fp);
	}
	fp=fopen("library.txt","a");
	p2=head;

	for (; p2!=NULL;) {
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
		p2=p2->next;
	}
	fclose(fp);
	printf("������ϣ������������");

	getch();
	pai();
	return ;
}

void dele() {   //ɾ�����ܣ�

	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,w=0,m=0,x=0;


	char jjnam[20]= {'\0'},l[20]= {'\0'};
	char i;
	FILE *fp;

	system ("cls");
	printf("\n��������Ҫɾ��������:\n");//����ɾ��ͼ������
	gets(jjnam);

	while(strcmp(jjnam,l)==0) {
		gets(jjnam);
	}

	fp=fopen("library.txt","r");
	j=math();
	for( k=0; k<j; k++) {

		if(k==0) {
			p1=head=(struct book*)malloc(sizeof(struct book));
			fscanf(fp,"%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);
			p1=head;
		} else {
			p2=(struct book*)malloc(sizeof(struct book));
			fscanf(fp,"%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
			p1->next=p2;
			p1=p2;
		}
	}
	p1->next=NULL;
	fclose(fp);

	p1=head;
	for (; p1!=NULL;) {
		m++;
		if(strcmp(jjnam,p1->name)==0) {
			x++;
			if(m==1) {
				head=head->next;
				m=0;
			} else {
				p2->next=p1->next;
			}
		}
		p2=p1;
		p1=p1->next;

	}

	fp=fopen("library.txt","w");
	p1=head;

	for (; p1!=NULL;) { //���������ݸ��ǵ��ļ�
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n\n",p1->num,p1->name,p1->aut,p1->clas,p1->pub,p1->time,p1->price);
		p1=p1->next;
	}
	fclose(fp);
	system ("cls");
	if(x==0) {
		printf("�޴�ͼ����Ϣ\n�����������\n");
	} else
		printf("\nɾ���ɹ� \n�������������һ��\n");

	getch();
	cmenu();
}
void search() { //����ͼ�鹦�ܣ�
	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,m=0;
	char na[20];
	FILE *fp;

	system ("cls");
	printf("\n��������Ҫ������������������:\n");//��������ͼ������
	scanf("%s",na);
	fp=fopen("library.txt","a+");
	j=math();

	for( k=0; k<j; k++) {

		if(k==0) {
			p1=head=(struct book*)malloc(sizeof(struct book));
			fscanf(fp,"%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);
			p1=head;
		} else {
			p2=(struct book*)malloc(sizeof(struct book));
			fscanf(fp,"%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
			p1->next=p2;
			p1=p2;
		}
	}
	p1->next=NULL;
	p2=head;
	for (; p2!=NULL;) {
		if(strcmp(na,p2->name)==0||strcmp(na,p2->aut)==0) {

			if(m==0) {
				printf("��ѯ���:\n\n");
				printf("��¼��\t����\t����\t�����\t���浥λ\t����ʱ��\t����\n");
			}
			printf("%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);

			m++;
		}
		p2=p2->next;
	}
	if (m==0) {
		system ("cls");
		printf("\n�޷��ϼ�¼!\n");
		getch();
		cmenu();
	}
	fclose(fp);
	getch();
	cmenu();
	return ;

}
void look() {    //���ͼ��;

	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,m=0;
	char na[20],ch;
	FILE *fp;

	system ("cls");
	fp=fopen("library.txt","r");
	ch=fgetc(fp);
	if(ch==EOF)
		printf("����ͼ����Ϣ��¼\n�����������\n");
	else {
		rewind(fp);
		j=math();
		for( k=0; k<j; k++) {

			if(k==0) {
				p1=head=(struct book*)malloc(sizeof(struct book));
				fscanf(fp,"%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);
				p1=head;
			} else {
				p2=(struct book*)malloc(sizeof(struct book));
				fscanf(fp,"%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
				p1->next=p2;
				p1=p2;
			}
		}
		p1->next=NULL;
		fclose(fp);
		p2=head;
		for (; p2!=NULL;) {
			if(m==0) {
				printf("��¼��\t����\t����\t�����\t���浥λ\t����ʱ��\t����\n");
			}
			printf("%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);

			p2=p2->next;
		}

	}
	getch();
	cmenu();
	return ;
}

int math() {

	FILE *fp;
	int n;
	fp=fopen("library.txt","r");//���ļ�

	for (n=0; !feof(fp); n++) //������ļ�
		fscanf(fp,"%s%s%s%s%s%s%s\n",str.num,str.name,str.aut,str.clas,str.pub,str.time,str.price);

	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}


void cmenu() { //ͼ��ϵͳ
	system ("cls");
	int n;

	printf("****************************************************");

	printf("\n 1.����ͼ��\n\n");

	printf("\n 2.ɾ��ͼ��\n\n");

	printf("\n 3.��ѯͼ��\n\n");

	printf("\n 4.ͼ����Ϣ�޸�\n\n");

	printf("\n 5.ͼ�����\n\n");

	printf("\n 6.������һ��\n\n");

	printf("\n �밴��ѡ�񣬻س�ȷ��\n");

	printf("***************************************************\n");
	printf("���������ѡ��");
	scanf("%d",&n);
	switch(n) {
		case 1:
			cun();
			break;
		case 2:
			dele();
			break;
		case 3:
			search();
			break;
		case 4:
			gai();
			break;
		case 5:
			look();
			break;
		case 6:
			cmain();
			break;
	}
	return ;

}


void cmain() {  // ͼ�����Ϣ�˵�
	system("cls");
	int a;
	char b;

	printf("    ********************************************");
	printf("\n    *\n    *          1.ͼ��ϵͳ\n    *\n    *");
	printf("\n    *\n    *          2.�˳�ϵͳ\n    *\n    *");
	printf("\n    *\n    *         �밴��ѡ�񣬻س�ȷ��\n" );
	printf("    ********************************************\n");
	printf("���������ѡ��");
	scanf("%d",&a);
	switch(a) {

		case 1:
			cmenu();
		case 2:
			return  ;

	}
}

int match (int a, char b[20]) {    //�˺�ƥ��
	FILE *fp;
	int n=0,i=0;
	int zhanghao;
	char password[20];

	if ((fp=fopen("land.txt","r"))==NULL) { //�������˺���Ϣ
		system ("cls");
		printf("\n ��δ�����û�!���½��˻�");
		getch();
		system("cls");
		lmain();
		return 0;
	}

	for(; !feof(fp);) {
		fscanf(fp,"%d %s",&zhanghao,password);
		if(a==zhanghao) {
			if(strcmp(b,password)==0)

				return 1;
			else {

				return -1;
			}
		}
	}
}


void land() {  //��¼����
	int qq;
	char pw[20];
	int i=2,j,k,n,hit;
	char b=0;
	system("cls");

	printf("\n�������˺�:\n");
	scanf("%d",&qq);
	printf("\n����������:\n");
	scanf("%s",pw);

	i=match(qq,pw);       //�����˺�ƥ��

	if(i==1) {
		printf("��½�ɹ�!�����������");
		getch();
		cmain();
	} else {
		char p;
		if(i==-1) {
			printf("�������!");
			printf("�Ƿ��������(y/n)\n");

			p=getch();
			if(p=='y')
				land();
			else {
				system("cls");
				lmain();
			}
		}
		if(i==0)
			printf("�����ڴ��û�");
		getch();
		system("cls");
		lmain();
	}
	return ;
}


void  xinjian() {  //�½��˺�
	system("cls");
	int qq;
	char pw[20],pw1[20];
	char hit=0;
	FILE *fp;

	if((fp=fopen("land.txt","a"))==NULL) {
		fp=fopen("land.txt","w");
		fclose(fp);
	}

	fp=fopen("land.txt","a");
	printf("�������˺ţ�");
	scanf("%d",&qq);

	printf("��Ϊ���˺��������룺");
	getchar();
	gets(pw);

	printf("���ٴ�ȷ������:");
	gets(pw1);
	if(strcmp(pw,pw1)==0) {
		fprintf(fp,"%d %s\n",qq,pw);
		printf("�������óɹ��������������");
		fclose(fp);
		getch();
		lmain();

	} else {
		printf("�������벻һ�£������½����˺�") ;
		getch();
		xinjian();
	}
	return ;
}


void lmain() {//��¼�˵�
	system("cls");
	printf("*************��ӭʹ��ͼ�����ϵͳ*************\n");
	printf("**********************************************");
	printf("\n\n\t\t1.��¼ϵͳ\n\n");
	printf("\n\n\t\t2.�����˺�\n\n");
	printf("\n\n\t\t3.�˳�ϵͳ\n\n");
	printf("\n\n\t    �밴��ѡ�񣬻س�ȷ��\n");
	printf("**********************************************\n");

	char  n;
	n=getch();

	while(n!='1'&&n!='2'&&n!='3') {
		printf("����������ѡ��\n");
		n=getch();
	}

	switch(n) { //���ܺ���
		case '1':
			land();//��¼����
			break;
		case '2':
			xinjian();
			break;
		case '3':
			system("cls");
			break;
	}
	return ;
}

int main() { //������

	system("color 30");
	lmain();

	return 0;
}


