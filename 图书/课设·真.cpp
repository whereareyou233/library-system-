#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>// 包含了getch函数，可以直接读入；不需按回车,针对按任意键返回； 
#include <malloc.h> 

struct book { // 图书信息
	char num[100],name[100],aut[100],clas[100],pub[100],time[100],price[100];
	struct book *next;
} str;

struct land { //登录信息
	int qq;
	char pw[20];
	struct land*next;
};


void cmain(); //图书馆信息菜单
void cmenu(); //存书菜单
void lmain();//登录菜单

void search();//搜索图书功能；
void gai();//更改图书信息
void cun();//存书功能
void land();//登陆功能
void xinjian();//新建账号功能
int match(int,int);//匹配密码是否正确
int math();//统计文件中的结构体个数
void pai();// 图书排序 
void look();   //浏览图书;

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
void gai() {  //修改图书信息；
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
		printf("暂无图书信息记录\n按任意键返回\n");
	else {
		rewind(fp);
		j=math();
		printf("\n请输入要修改图书的书名或者作者:\n");//输入修改图书书名
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
					printf("是否将同书名或作者的信息全部改为一致：（y/n）\n");
					getchar();
					gets(a);

					while(a[0]!='y'&&a[0]!='n') {
						printf("请重新输入(y/n)\n");
						gets(a);
					}
				}

				if(a[0]=='n') {
					printf("请输入更改后的信息；\n");
					scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
				} else {
					if(m==0) {
						printf("请输入更改后的信息：\n");
						scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
						p1=p2;
					} else {
						strcpy(p2->num,p1->num);//复制登录号
						strcpy(p2->name,p1->name);//复制书名
						strcpy(p2->aut,p1->aut);//复制作者名字
						strcpy(p2->clas,p1->clas);//复制类别
						strcpy(p2->pub,p1->pub);//复制出版社
						strcpy(p2->time,p1->time);//复制时间
						strcpy(p2->price,p1->price);//复制单价
					}
				}
				m++;
			}
			p2=p2->next;
		}
	}

	fp=fopen("library.txt","w");
	p2=head;

	for (; p2!=NULL;) { //把链表内容覆盖到文件
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
		p2=p2->next;
	}
	fclose(fp);
	system ("cls");
	if(m==0) {
		printf("无此图书信息\n按任意键返回\n");
	} else
		printf("\n修改成功 \n按任意键返回上一层\n");
	getch();
	pai();
	return ;
}

void cun() {  //存书
	//存书功能；

	system ("cls");
	FILE   *fp;
	struct book *p1,*p2,*head;
	char v,y;

	printf("\n请按以下格式输入图书信息:\n登录号 书名 作者 分类号 出版单位 出版时间 单价");
	printf("请输入:\n");
	p1=head=(struct book*)malloc(sizeof(struct book));
	scanf("%s%s%s%s%s%s%s",head->num,head->name,head->aut,head->clas,head->pub,head->time,head->price);

	p1=head;
	printf("\n请问是否继续存入,（y/n)\n");
	getchar();
	v=getchar();
	while (v!='n'&&v!='y') {
		getchar();
		printf("\n请重新输入（y/n)\n");
		v=getchar();
	}
	while(v!='n') {
		printf("\n请按以下格式输入图书信息:\n登录号 书名 作者 分类号 出版单位 出版时间 单价\n");
		p2=(struct book*)malloc(sizeof(struct book));
		scanf("%s%s%s%s%s%s%s",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);
		p1->next=p2;
		p1=p2;

		getchar();
		printf("\n请问是否继续存入,（y/n)\n");
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
	printf("保存完毕，按任意键返回");

	getch();
	pai();
	return ;
}

void dele() {   //删除功能；

	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,w=0,m=0,x=0;


	char jjnam[20]= {'\0'},l[20]= {'\0'};
	char i;
	FILE *fp;

	system ("cls");
	printf("\n请输入你要删除的书名:\n");//输入删除图书书名
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

	for (; p1!=NULL;) { //把链表内容覆盖到文件
		fprintf(fp,"%s        %s       %s       %s       %s               %s                 %s\n\n",p1->num,p1->name,p1->aut,p1->clas,p1->pub,p1->time,p1->price);
		p1=p1->next;
	}
	fclose(fp);
	system ("cls");
	if(x==0) {
		printf("无此图书信息\n按任意键返回\n");
	} else
		printf("\n删除成功 \n按任意键返回上一层\n");

	getch();
	cmenu();
}
void search() { //搜索图书功能；
	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,m=0;
	char na[20];
	FILE *fp;

	system ("cls");
	printf("\n请输入你要搜索的书名或者作者:\n");//输入搜索图书书名
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
				printf("查询结果:\n\n");
				printf("登录号\t书名\t作者\t分类号\t出版单位\t出版时间\t单价\n");
			}
			printf("%s        %s       %s       %s       %s               %s                 %s\n\n",p2->num,p2->name,p2->aut,p2->clas,p2->pub,p2->time,p2->price);

			m++;
		}
		p2=p2->next;
	}
	if (m==0) {
		system ("cls");
		printf("\n无符合记录!\n");
		getch();
		cmenu();
	}
	fclose(fp);
	getch();
	cmenu();
	return ;

}
void look() {    //浏览图书;

	struct book *head;
	struct book *p1,*p2;
	int n=0,j,k,m=0;
	char na[20],ch;
	FILE *fp;

	system ("cls");
	fp=fopen("library.txt","r");
	ch=fgetc(fp);
	if(ch==EOF)
		printf("暂无图书信息记录\n按任意键返回\n");
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
				printf("登录号\t书名\t作者\t分类号\t出版单位\t出版时间\t单价\n");
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
	fp=fopen("library.txt","r");//打开文件

	for (n=0; !feof(fp); n++) //逐个读文件
		fscanf(fp,"%s%s%s%s%s%s%s\n",str.num,str.name,str.aut,str.clas,str.pub,str.time,str.price);

	fclose(fp);//关闭文件
	return (n);//返回个数
}


void cmenu() { //图书系统
	system ("cls");
	int n;

	printf("****************************************************");

	printf("\n 1.增加图书\n\n");

	printf("\n 2.删除图书\n\n");

	printf("\n 3.查询图书\n\n");

	printf("\n 4.图书信息修改\n\n");

	printf("\n 5.图书浏览\n\n");

	printf("\n 6.返回上一层\n\n");

	printf("\n 请按键选择，回车确定\n");

	printf("***************************************************\n");
	printf("请输入你的选择：");
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


void cmain() {  // 图书馆信息菜单
	system("cls");
	int a;
	char b;

	printf("    ********************************************");
	printf("\n    *\n    *          1.图书系统\n    *\n    *");
	printf("\n    *\n    *          2.退出系统\n    *\n    *");
	printf("\n    *\n    *         请按键选择，回车确定\n" );
	printf("    ********************************************\n");
	printf("请输入你的选择：");
	scanf("%d",&a);
	switch(a) {

		case 1:
			cmenu();
		case 2:
			return  ;

	}
}

int match (int a, char b[20]) {    //账号匹配
	FILE *fp;
	int n=0,i=0;
	int zhanghao;
	char password[20];

	if ((fp=fopen("land.txt","r"))==NULL) { //不存在账号信息
		system ("cls");
		printf("\n 还未存在用户!请新建账户");
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


void land() {  //登录功能
	int qq;
	char pw[20];
	int i=2,j,k,n,hit;
	char b=0;
	system("cls");

	printf("\n请输入账号:\n");
	scanf("%d",&qq);
	printf("\n请输入密码:\n");
	scanf("%s",pw);

	i=match(qq,pw);       //进行账号匹配

	if(i==1) {
		printf("登陆成功!按任意键继续");
		getch();
		cmain();
	} else {
		char p;
		if(i==-1) {
			printf("密码错误!");
			printf("是否继续尝试(y/n)\n");

			p=getch();
			if(p=='y')
				land();
			else {
				system("cls");
				lmain();
			}
		}
		if(i==0)
			printf("不存在此用户");
		getch();
		system("cls");
		lmain();
	}
	return ;
}


void  xinjian() {  //新建账号
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
	printf("请输入账号：");
	scanf("%d",&qq);

	printf("请为此账号设置密码：");
	getchar();
	gets(pw);

	printf("请再次确认密码:");
	gets(pw1);
	if(strcmp(pw,pw1)==0) {
		fprintf(fp,"%d %s\n",qq,pw);
		printf("密码设置成功，按任意键返回");
		fclose(fp);
		getch();
		lmain();

	} else {
		printf("两次密码不一致，请重新建立账号") ;
		getch();
		xinjian();
	}
	return ;
}


void lmain() {//登录菜单
	system("cls");
	printf("*************欢迎使用图书管理系统*************\n");
	printf("**********************************************");
	printf("\n\n\t\t1.登录系统\n\n");
	printf("\n\n\t\t2.创建账号\n\n");
	printf("\n\n\t\t3.退出系统\n\n");
	printf("\n\n\t    请按键选择，回车确定\n");
	printf("**********************************************\n");

	char  n;
	n=getch();

	while(n!='1'&&n!='2'&&n!='3') {
		printf("请重新输入选择\n");
		n=getch();
	}

	switch(n) { //功能函数
		case '1':
			land();//登录函数
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

int main() { //主函数

	system("color 30");
	lmain();

	return 0;
}


