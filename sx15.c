//植泳辉1305553156
//刘坤1305553137
//亮点：
//程序有密码功能，只要输入错误5次之后，需要等30秒，才能再次输入密码。
//如果在30秒等待的时间内关闭程序，再开启时还要再等30秒。
//第一次使用时，要设置密码和二级密码，输入密码是*隐藏，输入错误能退格。
//使用二级密码能重置密码。
//我先设置的密码是123456，二级密码是123，如果想体验设置密码，可以删除mima.txt文件。
//能一次性删除，同类型信息，删除前会显示删除的信息，和询问确认。
//录入和插入时，会显示录入的信息和询问是否录入。
//修改时会显示修改的信息，可以多个修改，可以个别修改。
//统计有保存功能，能询问后在保存。
//输入方面，编号有规定的格式，其他输入也有大小长度的限制。
//如果不符合规定的格式、长度会报错。
//例如y/n,就只能输入Y、y、N、n，整数的地放输入1.2、字母字符都会报错。
//使用链表代替了数组。


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

#define HEADER1 "-----------------------------------产品信息------------------------------------\n"
#define HEADER2 "|商品编号| 商品类别 | 商品名称 | 商品单价 | 商品数量 |出售数量 |     总额     |\n"
#define HEADER3 "|--------|----------|----------|----------|----------|---------|--------------|\n"
#define FORMAT  "| %-7s|%-10s|%-10s|%-10.2lf|  %-8d| %-8d|%-14.2lf|\n"
#define DATA      p->num,p->type,p->name,p->price,p->amount,p->sold,p->total
#define END     "--------------------------------------------------------------------------\n"
#define N 100

int saveflag=0;

typedef struct commodity
{     	 
	char num[16];
	char type[20];
   char name[15];
   double price;
   int amount;
	int sold;                 
   double total;
   struct commodity *next;
} COMMDITY;

void menu()
{
	system("cls");
	printf("                    商品信息管理系\n\n");
	printf("    *******************主菜单*******************\n");
	printf("    *      1 录入信息            2 显示信息    *\n");
	printf("    *      3 删除信息            4 查询信息    *\n");
	printf("    *      5 修改信息            6 插入信息    *\n");
	printf("    *      7 排序信息            8 统计信息    *\n");
	printf("    *      9 保存信息            0 退出系统    *\n");
	printf("    ********************************************\n");
}

void printheader()
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
void printdata(COMMDITY *p)
{
	printf(FORMAT,DATA);
}

void Wrong()
{
	printf("\n\n*********Error:输入有错！敲任意键继续*******\n");
	getch();
}

void Nofind()
{
	printf("\n=====>未找到相关信息\n");
}



void stringinput(char *t,int maxlens,int minlens,char *notice)
{
	char str[20];
	do
	{
		printf(notice);
		scanf("%s",str);
		if((int)strlen(str)>maxlens)
			printf("超过规定的长度!\n");
		if((int)strlen(str)<minlens)
			printf("小于规定的长度!\n");
	}while((int)strlen(str)>maxlens||(int)strlen(str)<minlens);
	strcpy(t,str);
}

void doubleinput(double *t,int max,char *notice)
{
	char str[255];
	double price=0;
	int i,flag;
	do
	{	
		printf(notice);
		while(1)
		{
			flag=0;
			scanf("%s",str);
			for(i=0;i<(int)strlen(str);i++)
			{
				if(i==0||flag==1)
				{
					if(str[i]<'0'||str[i]>'9')
					{
						printf("输入有误！请重新输入");
						break;
					}
				}
				else
					if((str[i]>='0'&&str[i]<='9')||str[i]=='.')
					{if(str[i]=='.')
					flag=1;}
					else
					{	
						printf("输入有误！请重新输入");
						break;
					}
			}
			if(i==(int)strlen(str))
			{
				price=atof(str);
				break;
			}
		}
		if(price>max||price<0)
			printf("超过规定!\n");
	}while(price>max||price<0);
	*t=price;	
}

void numinput(int *t,int max,char *notice)
{
	int num,i;
	char str[255];
	do
	{
	num=0;
	printf(notice);
	while(1)
		{scanf("%s",str);
			for(i=0;i<(int)strlen(str);i++)
				if(str[i]<'0'||str[i]>'9')
				{
					printf("输入有误！请重新输入");
					break;
				}
			if(i==(int)strlen(str))
			{
				num=atoi(str);
				break;
			}
		}
		if(num>max||num<0)
		{
			printf("超过规定!\n");
		}
	}while(num>max||num<0);
	*t=num;	
}

void strnuminput(char *t,char *notice)
{
	char str[20];
	int i;
	int flag;
	do
	{
		flag=0;
		printf(notice);
		scanf("%s",str);
		if(strlen(str)==1&&str[0]=='0')
		{
			strcpy(t,str);
			return;
		}
		for(i=0;i<(int)strlen(str);i++)
		{	
			if(i==0)
			{
				if(str[i]<'a'||str[i]>'z')
				{	
					flag=1;
					break;
				}
			}
			else if(str[i]<'0'||str[i]>'9')	
			{
				flag=1;
			}
		}
		if((int)strlen(str)!=6||flag==1)
			printf("不符合规格!\n");
	}while((int)strlen(str)!=6||flag!=0);
	strcpy(t,str);
}

void strnuminput1(char *t,char *notice)
{
	char str[20];
	int i;
	int flag;
	do
	{
		flag=0;
		printf(notice);
		scanf("%s",str);
		for(i=0;i<(int)strlen(str);i++)
		{	
			if(i==0)
			{
				if(str[i]<'a'||str[i]>'z')
				{	
					flag=1;
					break;
				}
			}
			else if(str[i]<'0'||str[i]>'9')	
				flag=1;
		}
		if((int)strlen(str)!=6||flag==1)
			printf("不符合规格!\n");
	}while((int)strlen(str)!=6||flag!=0);
	strcpy(t,str);
}

void stringinput1(char *t,int lens,char *notice)
{
	char str[20];
	int i;
	do
	{
		i=0;
		printf(notice);
		while((str[i]=getchar())!='\n')
			i++;
		if(str[0]=='\n')
			strcpy(str,t);
		else
		str[i]='\0';
		if((int)strlen(str)>lens)
			printf("超过规定的长度!\n");
		if((int)strlen(str)<3)
			printf("小于规定的长度!\n");
	}while((int)strlen(str)>lens||(int)strlen(str)<3);
	strcpy(t,str);
}

void doubleinput1(double *t,int max,char *notice)
{
	char str[255];
	double price=0;
	int i,flag;
	do
	{	
		printf(notice);
		while(1)
		{	i=0;
			flag=0;
			while((str[i]=getchar())!='\n')
				i++;
			if(str[0]=='\n')
				sprintf(str,"%.2lf",*t);
			else
				str[i]='\0';
			for(i=0;i<(int)strlen(str);i++)
			{
				if(i==0||flag==1)
				{
					if(str[i]<'0'||str[i]>'9')
					{
						printf("输入有误！请重新输入");
						break;
					}
				}
				else
					if((str[i]>='0'&&str[i]<='9')||str[i]=='.'||str[i]=='\n')
					{if(str[i]=='.')
					flag=1;}
					else
					{	
						printf("输入有误！请重新输入");
						break;
					}
			}
			if(i==(int)strlen(str))
			{
				price=atof(str);
				break;
			}
		}
		if(price>max||price<0)
			printf("\n超过规定!\n");
	}while(price>max||price<0);
	*t=price;	
}

void numinput1(int *t,int max,char *notice)
{
	int num,i;
	char str[255];
	do
	{
	num=0;
	printf(notice);
	while(1)
		{i=0;
			while((str[i]=getchar())!='\n')
				i++;
			if(str[0]=='\n')
				sprintf(str,"%d",*t);
			else
				str[i]='\0';
			for(i=0;i<(int)strlen(str);i++)
			{
				if(i==0)
				{
					if(str[0]<'0'||str[0]>'9')
					{
						printf("输入有误！请重新输入");
						break;
					}
				}
				else
					if((str[i]>='0'&&str[i]<='9')||str[i]=='\n');
					else
					{
						printf("输入有误！请重新输入");
						break;
					}
			}
			if(i==(int)strlen(str))
			{
				num=atoi(str);
				break;
			}
		}
		if(num>max||num<0)
				printf("\n超过规定!\n");
	}while(num>max||num<0);
	*t=num;	
}



void Disp(COMMDITY *pt,int n)
{
	int i;
	if(n==0)
		printf("\n====>尚无记录!\n");
	else
	{
		printf("\n\n");
		printheader();
		i=0;
		while(i<n)
		{
			printdata(pt);
			i++;
			pt=pt->next;
			printf(HEADER3);
		}
	}
}

int Locate(COMMDITY *pp,int n,char findmess[],char nameornumortype[])
{
	int i=0,k=0,num=0;double pri=0;
	if(strcmp(nameornumortype,"price")==0)
	{
		pri=atof(findmess);
		while(i<n)
		{
			if(pp->price==pri) return i;
			pp=pp->next;
			i++;
		}
	}
	else if(strcmp(nameornumortype,"num")==0)
	{
		while(i<n)
		{
			if(strcmp(pp->num,findmess)==0) return i;
			i++;
			pp=pp->next;
		}
	}
	else if(strcmp(nameornumortype,"type")==0)
	{
		while(i<n)
		{
			if(strcmp(pp->type,findmess)==0) return i;
			i++;
			pp=pp->next;
		}
	}
	else if(strcmp(nameornumortype,"amount")==0)
	{
		for(k=0;findmess[k]>='0'&&findmess[k]<='9';k++)
		num=num*10+findmess[k]-'0';
		while(i<n)
		{
			if(pp->amount==num) return i;
			i++;
			pp->next;
		}
	}
	else if(strcmp(nameornumortype,"sold")==0)
	{
		for(k=0;findmess[k]>='0'&&findmess[k]<='9';k++)
		num=num*10+findmess[k]-'0';
		while(i<n)
		{
			if(pp->sold==num) return i;
			i++;
			pp=pp->next;
		}
	}
	else if(strcmp(nameornumortype,"name")==0)
	{
		while(i<n)
		{
			if(strcmp(pp->name,findmess)==0) return i;
			i++;
			pp=pp->next;
			
		}
	}
	return -1;
}


void Save1(COMMDITY *pt,int n,const char *path)   //保存1
{	
	FILE*fp;
	char ch[30];
	int i=0;
	printf("\n==>是否保存记录到文件?(y/n):");
	while(1)
	{
		scanf("%s",ch);
		if(strlen(ch)>1)
		printf("请输入y/n\n");
		else if(ch[0]=='y'||ch[0]=='Y')
		{
			fp=fopen(path,"w");
			if(fp==NULL)
			{
				printf("\n=====>打开文件失败!\n");
				getch();break;
			}
			for(i=0;i<n;i++)
			{
				if(fwrite(pt,sizeof(COMMDITY),1,fp)==1)
					{
						pt=pt->next;
						continue;
					}
					else break;
			}
			if(i>0)
			{
				getchar();
				printf("\n\n=====>完成文件保存，全部保存的记录有:%d条\n",i);
				getchar();
			}
			else
			{
				system("cls");
				printf("无记录被新保存!\n");
				getch();
			}
			fclose(fp);
			return;
		}
		else if(ch[0]=='n'||ch[0]=='N')
			break;
		else
			printf("请输入y/n\n");
	}	
}

int Addif(COMMDITY *p,int n)
{
	char ch[20];
	Disp(p,n);
	printf("请确认(y/n):");
	while(1)
	{
		scanf("%s",ch);
		if(strlen(ch)>1)
			printf("请输入y/n\n");
		else if(ch[0]=='y'||ch[0]=='Y')
		{	printf("已经成功录入\n");return 1;}
		else if(ch[0]=='n'||ch[0]=='N')
		{
			printf("已经取消录入\n");
			return 0;
		}
		else
			printf("请输入y/n\n");
	}
}

int Add(COMMDITY *p,int n)  //录入

{
	COMMDITY *pt,*pn;
	char ch[10],num[10];
	int i,flag=0;
	if(n<=0)
		{
			system("cls");
			printf("\n=====>系统中无记录!\n");
		}
	else
	{system("cls");
	Disp(p,n);}
	pt=p;
	while(1)
	{
		while(1)
		{
			strnuminput(num,"输入编号(例:a12345)(按'0'返回主菜单):");
			flag=0;
			if(strcmp(num,"0")==0) 
			{
				return n;
			}
			i=0;
			pt=p;
			while(i<n)
			{
				if(strcmp(pt->num,num)==0)
				{	flag=1;break;}
				pt=pt->next;
				i++;
			}
			if(flag==1)
			{
				getchar();
				printf("==>编号%s已经存在，再试一次?(y/n):",num);
				while(1)
				{
					scanf("%s",ch);
					if(strlen(ch)>1)
						printf("请输入y/n\n");
					else if(ch[0]=='y'||ch[0]=='Y')
					{
						break;
					}
					else if(ch[0]=='n'||ch[0]=='N')
						return n;
					else
						printf("请输入y/n\n");
				}
			}
			else break;
		}
		if(n==0)
		{
			
			strcpy(p->num,num);
			stringinput(p->type,10,3,"Type:");
			stringinput(p->name,10,3,"Name:");
			doubleinput(&p->price,100000,"Price:");
			numinput(&p->amount,100000,"Amount:");
			numinput(&p->sold,p->amount,"Sold:");
			p->total=p->price*p->amount;
			if(Addif(p,1))
			{
				saveflag=1;
				p->next=NULL;
				n++;
			}
		}
		else
		{
			i=0;
			pt=p;
			while(i<n-1)
			{	
				pt=pt->next;
				i++;
			}
			pn=(COMMDITY *)malloc(sizeof(COMMDITY));pn->next=NULL;	
			strcpy(pn->num,num);
			stringinput(pn->type,10,3,"Type:");
			stringinput(pn->name,10,3,"Name:");
			doubleinput(&pn->price,100000,"Price:");
			numinput(&pn->amount,100000,"Amount:");
			numinput(&pn->sold,pn->amount,"Sold:");
			pn->total=pn->price*pn->amount;
			
			if(Addif(pn,1))
			{
				saveflag=1;
				if(i==0)
					p->next=pn;
				else
					pt->next=pn;
				n++;
			}
		}
	}
	return n;
}

int Delif()
{
	char ch[20];
	printf("请确认(y/n):");
	while(1)
	{
		scanf("%s",ch);
		if(strlen(ch)>1)
			printf("请输入y/n\n");
		else if(ch[0]=='y'||ch[0]=='Y')
			return 1;
		else if(ch[0]=='n'||ch[0]=='N')
		{
			printf("已经取消删除\n");
			return 0;
		}
		else
			printf("请输入y/n\n");
	}
}


int Del(COMMDITY *ph,int n)  //删除
{
	COMMDITY *p1,*p2,*p3,*pht,*pt,*pp=ph;
	char select1[20];
	char ch[255];
	char findmess[20];
	double findmess1;
	int p,i=0,select,j,t;
	while(1)
	{	t=0;
		pt=ph;
		pp=ph;
		if(n<=0)
		{
			system("cls");
			printf("\n=====>系统中无记录!\n");
			getch();
			return n;
		}
		
		system("cls");
		Disp(pt,n);
		printf("\n");
		printf("    *********************************子菜单************************************\n");
		printf("    *1 根据名称进行删除         2 根据编号进行删除       3 根据类别进行删除   *\n");
		printf("    *4 根据单价进行删除         0 退出                                        *\n");
		printf("    ***************************************************************************\n");
		printf("            请选择[0,1,2,3,4]:");
		scanf("%s",select1);
		for(i=0;i<strlen(select1);i++)
			if(select1[i]>'9'||select1[i]<'0')
				break;
		if(i==strlen(select1))
			select=atoi(select1);
		else
			select=100;
		switch(select)
		{   case 1:
			stringinput(findmess,10,3,"输入一个已有的名称:");
			for(i=0;i<n;i++)
			{	
				if(t==0)
				{	if(strcmp(pt->name,findmess)==0)
					{
						p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
						p1->next=NULL;
						p2=p1;
						pht=p1;
					}
					else;
				}	
				else
				{
					if(strcmp(pt->name,findmess)==0)
					{
						p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						p1->next=NULL;
						p2->next=p1;
						p2=p1;
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
					}
				}
				pt=pt->next;
			}
			if(t!=0)
			{
				printf("\n该信息共有%d\n",t);
				Disp(pht,t);
			}
			else
			{
				Nofind();
				getch();
			}
			if(t!=0&&Delif())
			{	p=Locate(ph,n,findmess,"name");
				getch();
				if(p!=-1)
				{
					for(j=0;j<n;j++)
					{
						pp=ph;
						for(i=0;i<p;i++)
							pp=pp->next;
						p3=pp->next;
						for(i=p+1;i<n;i++)
						{
							strcpy(pp->num,p3->num);
							strcpy(pp->type,p3->type);
							strcpy(pp->name,p3->name);
							pp->price=p3->price;
							pp->amount=p3->amount;
							pp->sold=p3->sold;
							pp->total=p3->total;
							pp->next=p3->next;
							pp=p3;
						}n--;
						p=Locate(ph,n,findmess,"name");
						if(p==-1) break;
					}
					printf("\n删除成功!\n");
					saveflag=1;
				}
			}
			break;
			case 2:
			stringinput(findmess,6,0,"请输入一个已存在的编号:");
			for(i=0;i<n;i++)
			{	
				if(t==0)
				{	if(strcmp(pt->num,findmess)==0)
					{
						p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
						p1->next=NULL;
						p2=p1;
						pht=p1;
					}
					else;
				}	
				else
				{
					if(strcmp(pt->num,findmess)==0)
					{
						p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						p1->next=NULL;
						p2->next=p1;
						p2=p1;
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
					}
				}
				pt=pt->next;
			}
			if(t!=0)
			{
				printf("\n该信息共有%d\n",t);
				Disp(pht,t);
			}
			else
			{
				Nofind();
				getch();
			}
			if(t!=0&&Delif())
			{
				p=Locate(pp,n,findmess,"num");
				getchar();
				if(p!=-1)
				{
					for(i=0;i<p;i++)
						pp=pp->next;
					p3=pp->next;
					for(i=p+1;i<n;i++)
					{
						strcpy(pp->num,p3->num);
						strcpy(pp->type,p3->type);
						strcpy(pp->name,p3->name);
						pp->price=p3->price;
						pp->amount=p3->amount;
						pp->sold=p3->sold;
						pp->total=p3->total;
						pp->next=p3->next;
						pp=p3;
					}
					printf("\n=====>删除成功!\n");
					n--;
					saveflag=1;
				}
				else
				{Nofind();
				getch();
				}
			}
				break;
			case 3:
			stringinput(findmess,8,3,"请输入一个已存在的类别:");
			for(i=0;i<n;i++)
			{	
				if(t==0)
				{	if(strcmp(pt->type,findmess)==0)
					{
						p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
						p1->next=NULL;
						p2=p1;
						pht=p1;
					}
					else;
				}	
				else
				{
					if(strcmp(pt->type,findmess)==0)
					{
						p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						p1->next=NULL;
						p2->next=p1;
						p2=p1;
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
					}
				}
				pt=pt->next;
			}
			if(t!=0)
			{
				printf("\n该信息共有%d\n",t);
				Disp(pht,t);
			}
			else
			{
				Nofind();
				getch();
			}
			if(t!=0&&Delif())
			{
				p=Locate(ph,n,findmess,"type");
				getchar();
				if(p!=-1)
				{
					for(j=0;j<n;j++)
					{
						pp=ph;
						for(i=0;i<p;i++)
						pp=pp->next;
						p3=pp->next;
						for(i=p+1;i<n;i++)
						{
							strcpy(pp->num,p3->num);
							strcpy(pp->type,p3->type);
							strcpy(pp->name,p3->name);
							pp->price=p3->price;
							pp->amount=p3->amount;
							pp->sold=p3->sold;
							pp->total=p3->total;
							pp->next=p3->next;
							pp=p3;
						}
						n--;
						saveflag=1;
						p=Locate(ph,n,findmess,"type");
						if(p==-1) break;
					}
						printf("\n=====>删除成功!\n");
				}
			}break;
			case 4:
			doubleinput(&findmess1,10000000,"请输入一个已存在的单价:");
			for(i=0;i<n;i++)
			{	
				if(t==0)
				{	if(pt->price==findmess1)
					{
						p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
						p1->next=NULL;
						p2=p1;
						pht=p1;
					}
					else;
				}	
				else
				{
					if(pt->price==findmess1)
					{
						p1=(COMMDITY*)malloc(sizeof(COMMDITY));
						p1->next=NULL;
						p2->next=p1;
						p2=p1;
						strcpy(p1->num,pt->num);
						strcpy(p1->name,pt->name);
						strcpy(p1->type,pt->type);
						p1->price=pt->price;
						p1->amount=pt->amount;
						p1->sold=pt->sold;
						p1->total=pt->total;
						t++;
					}
				}
				pt=pt->next;
			}
			if(t!=0)
			{
				printf("\n该信息共有%d\n",t);
				Disp(pht,t);
			}
			else
			{
				Nofind();
				getch();
			}
			if(t!=0&&Delif())
			{	
				sprintf(findmess,"%lf",findmess1);
				p=Locate(ph,n,findmess,"price");
				getchar();
				if(p!=-1)
				{
					for(j=0;j<n;j++)
					{
						pp=ph;
						for(i=0;i<p;i++)
							pp=pp->next;
						p3=pp->next;
						for(i=p+1;i<n;i++)
						{
							strcpy(pp->num,p3->num);
							strcpy(pp->type,p3->type);
							strcpy(pp->name,p3->name);
							pp->price=p3->price;
							pp->amount=p3->amount;
							pp->sold=p3->sold;
							pp->total=p3->total;
							pp->next=p3->next;
							pp=p3;
						}
						n--;
						saveflag=1;
						p=Locate(ph,n,findmess,"price");
						if(p==-1) break;
					}
					printf("\n=====>删除成功!\n");
				}
				else
				{
					Nofind();
					getch();
				}
			}
			break;
			case 0:return n;break;
			default: Wrong();break;
		}	
		printf("是否继续(y/n):");
		while(1)
			{
				scanf("%s",ch);
				if(strlen(ch)>1)
					printf("请输入y/n\n");
				else if(ch[0]=='y'||ch[0]=='Y')
					break;
				else if(ch[0]=='n'||ch[0]=='N')
					return n;
				else
				printf("请输入y/n\n");
			}
	}
}



void Modify(COMMDITY *pt,int n)   //修改 
{
	int select;
	char findmess[20],select1[20];
	char ch[20];
	COMMDITY *pp;
	int p=0,i;
	pp=pt;
	if(n<=0)
		{
			system("cls");
			printf("\n=====>系统中无记录!\n");
			getch();
			return;
		}
	while(1)
	{
		pt=pp;
		system("cls");
		printf("修改系统记录");
		Disp(pp,n);
		stringinput(findmess,10,0,"请输入一个已存在的编号:(不存在退出)");
		p=Locate(pt,n,findmess,"num");
		getchar();
		if(p!=-1)
		{
			for(i=0;i<p;i++)
				pt=pt->next;
			Disp(pt,1);
			printf("\n");
			printf("*********************************选择修改内容**********************************\n");
			printf("* 1、多个修改   2、名字   3、类别   4、单价   5、数量   6、出售数量   0、不改 *\n");
			printf("*******************************************************************************\n");
			printf("\n            请输入你的选择(0~6:)");
			scanf("%s",select1);
			getchar();
			for(i=0;i<strlen(select1);i++)
				if(select1[i]>'6'||select1[i]<'0')
					break;
			if(i==strlen(select1))
				select=atoi(select1);
			else
					select=100;
		}
		pt=pp;
		for(i=0;i<p;i++)
			pt=pt->next;
		if(p!=-1&&select==1)
		{	
			printf("Number:%s\n",pt->num);
			printf("Name:%s,",pt->name);
			stringinput1(pt->name,15,"请输入新的姓名(回车跳过):");
			printf("Type:%s,",pt->type);
			stringinput1(pt->type,15,"请输入新的类别:(回车跳过)");
			printf("Price:%.2lf,",pt->price);
			doubleinput1(&pt->price,10000,"请输入新的单价(回车跳过):");
			printf("Amount:%d,",pt->amount);
			numinput1(&pt->amount,100000,"请输入新的数量(回车跳过):");
			printf("Sold:%d,",pt->sold);
			numinput1(&pt->sold,pt->amount,"请输入新的出售数量(回车跳过):");
			pt->total=pt->price*pt->amount;
			printf("\n=====>修改成功!(任意键继续)\n");
			getch();
			saveflag=1;
		}
		else if(p!=-1&&select==2)
		{
			printf("Name:%s,",pt->name);
			stringinput1(pt->name,15,"请输入新的姓名(回车跳过):");
			printf("\n=====>修改成功!(任意键继续)\n");
			getch();
			saveflag=1;
		}
		else if(p!=-1&&select==3)
		{
			printf("Type:%s,",pt->type);
			stringinput1(pt->type,15,"请输入新的类别:(回车跳过)");
			printf("\n=====>修改成功!(任意键继续)\n");
			getch();
			saveflag=1;
		}
		else if(p!=-1&&select==4)
		{
			printf("Price:%.2lf,",pt->price);
			doubleinput1(&pt->price,10000,"请输入新的单价(回车跳过):");
			pt->total=pt->price*pt->amount;
			printf("\n=====>修改成功!(任意键继续)\n");
			getch();
			saveflag=1;
		}
		else if(p!=-1&&select==5)
		{
			printf("Amount:%d,",pt->amount);
			numinput1(&pt->amount,100000,"请输入新的数量(回车跳过):");
			pt->total=pt->price*pt->amount;
			printf("\n=====>修改成功!(任意键继续)\n");
			getch();
			saveflag=1;
		}
		else if(p!=-1&&select==6)
		{
			printf("Sold:%d,",pt->sold);
			numinput1(&pt->sold,pt->amount,"请输入新的出售数量(回车跳过):");
			printf("\n=====>修改成功!(任意键继续)\n");
			;
			saveflag=1;
		}
		else if(p!=-1&&select==0);
		else
		{
			Nofind();
			while(1)
			{
				printf("是否继续?(y/n):");
				scanf("%s",ch);
				if(strlen(ch)>1)
					printf("请输入y/n\n");
				else if(ch[0]=='y'||ch[0]=='Y')
				{
					break;
				}
				else if(ch[0]=='n'||ch[0]=='N')
					return;
				else
					printf("请输入y/n\n");
			} 
		}
	}
}


int Insert(COMMDITY *ph,int n)  //插入
{
	char ch[10],num[10],s[10];
	COMMDITY *pn;
	COMMDITY *pp;
	COMMDITY *ptt;
	COMMDITY *pt;
	int flag=0,i=0;
	while(1)
	{
		pp=ph;
		pt=ph;
		ptt=pt;
		if(n<=0)
		{
			system("cls");
			printf("\n=====>系统中无记录!\n");
			getch();
			return 0;
		}
		system("cls");
		Disp(pp,n);
		while(1)
		{
			stringinput(s,10,0,"请输入一个记录编号，带插入的记录将位于该编号记录的后面（不存在退出）:");
			flag=0;i=0;ptt=pp;
			while(i<n)
			{	
				if(strcmp(ptt->num,s)==0)
				{
					flag=1;break;
				}
				ptt=ptt->next;
				i++;
			}	
			if(flag==1) break;
			else
			{  
				getchar();
				printf("\n=====>编号%s不存在，再试一次?(y/n):",s);
				while(1)
				{
					scanf("%s",ch);
					if(strlen(ch)>1)
						printf("请输入y/n\n");
					else if(ch[0]=='y'||ch[0]=='Y')
					{
						break;
					}
					else if(ch[0]=='n'||ch[0]=='N')
						return n;
					else
						printf("请输入y/n\n");
				} 
			} 
		}
		while(1)
		{
			strnuminput1(num,"请输入新的编号:");
			i=0;flag=0;pt=pp;
			while(i<n)
			{
				if(strcmp(pt->num,num)==0)
				{
					flag=1;break;
				}
				i++;
				pt=pt->next;
			}
			if(flag==1)
			{
				getch();
				printf("\n=====>Sorry,编号%s已经存在，再试一次?(y/n):",num);
				while(1)
				{
					scanf("%s",ch);
					if(strlen(ch)>1)
					printf("请输入y/n\n");
					else if(ch[0]=='y'||ch[0]=='Y')
					{
						break;
					}
					else if(ch[0]=='n'||ch[0]=='N')
						return n;
					else
						printf("请输入y/n\n");
				}
			
		}
		else break;
		}
		pn=(COMMDITY *)malloc(sizeof(COMMDITY));
		strcpy(pn->num,num);
		stringinput(pn->name,10,3,"Name:");
		stringinput(pn->type,10,3,"Type:");
		doubleinput(&pn->price,100000,"Price:");
		numinput(&pn->amount,100000,"Amount:");
		numinput(&pn->sold,pn->amount,"Sold:");
		pn->total=pn->amount*pn->price;
		if(Addif(pn,1))
		{
			saveflag=1;
			pn->next=ptt->next;
			ptt->next=pn;
			n++;
			printf("是否继续一次?(y/n):");
					while(1)
					{
						scanf("%s",ch);
						if(strlen(ch)>1)
						printf("请输入y/n\n");
						else if(ch[0]=='y'||ch[0]=='Y')
							break;
						else if(ch[0]=='n'||ch[0]=='N')
							return n;
						else
							printf("请输入y/n\n");
					}
		}
	}
}

void chang(COMMDITY* pmin,COMMDITY* ptt)
{
	COMMDITY *pttt=(COMMDITY *)malloc(sizeof(COMMDITY));
	strcpy(pttt->num,pmin->num);
	strcpy(pmin->num,ptt->num);
	strcpy(ptt->num,pttt->num);
	strcpy(pttt->type,pmin->type);
	strcpy(pmin->type,ptt->type);
	strcpy(ptt->type,pttt->type);
	strcpy(pttt->name,pmin->name);
	strcpy(pmin->name,ptt->name);
	strcpy(ptt->name,pttt->name);
	pttt->price=pmin->price;
	pmin->price=ptt->price;
	ptt->price=pttt->price;
	pttt->amount=pmin->amount;
	pmin->amount=ptt->amount;
	ptt->amount=pttt->amount;
	pttt->sold=pmin->sold;
	pmin->sold=ptt->sold;
	ptt->sold=pttt->sold;
	pttt->total=pmin->total;
	pmin->total=ptt->total;
	ptt->total=pttt->total;
}
void SelectSort(COMMDITY *ph,int n)  //排序
{
	char select1[255];
	int i,j,select;
	COMMDITY *pt;
	COMMDITY *ptt;
	COMMDITY *pmin;
	COMMDITY *pttt=(COMMDITY *)malloc(sizeof(COMMDITY));
	if(n<=0)
	{
		system("cls");
		printf("\n=====>尚无记录!\n");
		getch();
		return ;
	}
	while(1)
	{
		pt=ph;
		system("cls");
		Disp(ph,n);
		printf("*************************************子菜单********************************\n");
		printf("*      1 按编号升序排序                   2 按种类升序排序                *\n");
		printf("*      3 按名称升序排序                   4 按价格升序排序                *\n");
		printf("*      5 按商品数量升序排序               6 按出售数量升序排序            *\n");
		printf("*      7 按总额升序排序                   0 退出                          *\n");
		printf("***************************************************************************\n");
		printf("     请输入选项编号[0~7]:");
		scanf("%s",select1);
		for(i=0;i<strlen(select1);i++)
			if(select1[i]>'9'||select1[i]<'0')
				break;
		if(i==strlen(select1))
			select=atoi(select1);
		else
			select=100;
		if(select==1)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(strcmp(ptt->num,pmin->num)==-1)  
					{	
						chang(pmin,ptt);
					}
					ptt=ptt->next;
				}
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==2)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(strcmp(ptt->type,pmin->type)==-1)  
					{	
						chang(pmin,ptt);
					}
					ptt=ptt->next;
				}	
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==3)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(strcmp(ptt->name,pmin->name)==-1)  
					{	
						chang(pmin,ptt);
					}
					ptt=ptt->next;
				}	
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==4)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(ptt->price-pmin->price<0)  
					{	
						chang(pmin,ptt);
					}
					ptt=ptt->next;
				}
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==5)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(ptt->amount-pmin->amount<0)  
					{	
						chang(pmin,ptt);
					}
					ptt=ptt->next;
				}
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==6)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
					
					if(ptt->sold-pmin->sold<0)  
					{	
						chang(pmin,ptt);
					}	
					ptt=ptt->next;
				}
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==7)
		{
			for(i=0;i<n-1;i++)
			{
				pmin=pt;
				for(j=i+1,ptt=pt->next;j<n;j++)
				{
				
					if(ptt->total-pmin->total<0)  
					{	
						chang(pmin,ptt);
					}	
					ptt=ptt->next;
				}
				pt=pt->next;
			}
			Disp(ph,n);
			saveflag=1;
			printf("\n    =====>完成排序!\n");
			getch();
		}
		else if(select==0)
			break;
		else
			Wrong();
	}
}


void Qur(COMMDITY* ph,int n)
{	int select=100,max,min,t=0,i;
	COMMDITY *p1,*p2,*pht,*pt=ph;
	double max1,min1;
	char name[255],select1[255];
	if(n<=0)
	{
		system("cls");
		printf("\n=====>尚无记录!\n");
		getch();
		return ;
	}
	while(1)
	{
	system("cls");
	Disp(ph,n);
	printf("    *********************************子菜单********************************\n");
	printf("    *      1 按精确编号            2 按模糊编号             3 按精确名称  *\n");
	printf("    *      4 按模糊名称            5 按精确种类             6 按模糊种类  *\n");
	printf("    *      7 按商品价格            8 按商品数量             9 按出售数量  *\n");
	printf("    *      10 按商品总额           0 退出                                 *\n");
	printf("    ***********************************************************************\n");
	printf("     请输入选项编号[0~10]:");
	scanf("%s",select1);
	for(i=0;i<strlen(select1);i++)
		if(select1[i]>'9'||select1[i]<'0')
			break;
	if(i==strlen(select1))
		select=atoi(select1);
	else
		select=100;
	 if(select==1)
	{	
		t=0;
		pt=ph;
		sprintf(name,"") ;
		printf("请输入编号:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->num,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->num,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==2)
	{	
		t=0;
		pt=ph;
		sprintf(name,"") ;
		printf("请输入编号:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->num,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->num,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==3)
	{	
		t=0;
		pt=ph;
		printf("请输入名字:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->name,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->name,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
    else if(select==4)
	{	
		t=0;
		pt=ph;
		printf("请输入名字:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->name,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->name,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==5)
	{
		t=0;
		pt=ph;
		printf("请输入类别:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->type,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->type,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==6)
	{
		t=0;
		pt=ph;
		printf("请输入类别:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->type,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->type,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==7)
	{
		t=0;
		pt=ph;
		while(1)
		{
			doubleinput(&min1,100000,"请输入最小的价格:");
			doubleinput(&max1,100000,"请输入最大的价格:");
			if(max1<min1)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->price>=min1&&pt->price<=max1)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->price>=min1&&pt->price<=max1)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==8)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,100000,"请输入最小的数量:");
			numinput(&max,100000,"请输入最大的数量:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->amount>=min&&pt->amount<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->amount>=min&&pt->amount<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==9)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,100000,"请输入最小的出售数量:");
			numinput(&max,100000,"请输入最大的出售数量:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->sold>=min&&pt->sold<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->sold>=min&&pt->sold<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==10)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,100000,"请输入最小的总额:");
			numinput(&max,100000,"请输入最大的总额:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->total>=min&&pt->total<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->total>=min&&pt->total<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			getch();
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==0)
		return;
	else
	{
		Wrong();
	}
	}
}


void Count(COMMDITY* ph,int n)
{	int select,t=0,i,size,isfind,j,max,min;
	COMMDITY *p1,*p2,*pht,*pt=ph,*ptt;
	char name[255],select1[255];
	double min1,max1;
	if(n<=0)
	{
		system("cls");
		printf("\n=====>尚无记录!\n");
		getch();
		return ;
	}
	while(1)
	{
	system("cls");
	Disp(ph,n);
	printf("    *********************************子菜单********************************\n");
	printf("    *      1 按精确编号            2 按模糊编号             3 按精确名称  *\n");
	printf("    *      4 按模糊名称            5 按精确种类             6 按模糊种类  *\n");
	printf("    *      7 按商品价格            8 按商品数量             9 按出售数量  *\n");
	printf("    *      10 按商品总额           11不同种类数量           0 退出        *\n");
	printf("    ***********************************************************************\n");
	printf("     请输入选项编号[0~11]:");
	scanf("%s",select1);
	for(i=0;i<strlen(select1);i++)
		if(select1[i]>'9'||select1[i]<'0')
			break;
	if(i==strlen(select1))
		select=atoi(select1);
	else
		select=100;
	 if(select==1)
	{	
		t=0;
		pt=ph;
		printf("请输入编号:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->num,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->num,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\aaa.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==2)
	{	
		t=0;
		pt=ph;
		printf("请输入编号:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->num,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->num,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\bbb.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==3)
	{	
		t=0;
		pt=ph;
		printf("请输入名字:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->name,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->name,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\ccc.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
    else if(select==4)
	{	
		t=0;
		pt=ph;
		printf("请输入名字:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->name,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->name,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\ddd.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==5)
	{
		t=0;
		pt=ph;
		printf("请输入类别:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strcmp(pt->type,name)==0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strcmp(pt->type,name)==0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\eee.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==6)
	{
		t=0;
		pt=ph;
		printf("请输入类别:");
		scanf("%s",name);
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(strstr(pt->type,name)!=0)
				{
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(strstr(pt->type,name)!=0)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\fff.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==7)
	{
		t=0;
		pt=ph;
		while(1)
		{
			doubleinput(&min1,100000,"请输入最小的价格:");
			doubleinput(&max1,100000,"请输入最大的价格:");
			if(max1<min1)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->price>=min1&&pt->price<=max1)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->price>=min1&&pt->price<=max1)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\ggg.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==8)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,1000000,"请输入最小的数量:");
			numinput(&max,1000000,"请输入最大的数量:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->amount>=min&&pt->amount<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->amount>=min&&pt->amount<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\hhh.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==9)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,1000000,"请输入最小的出售数量:");
			numinput(&max,1000000,"请输入最大的出售数量:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->sold>=min&&pt->sold<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->sold>=min&&pt->sold<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\iii.txt");
		}
		else
		{
			printf("没有记录\n");
			getch();
		}
	}
	else if(select==10)
	{
		t=0;
		pt=ph;
		while(1)
		{
			numinput(&min,100000000,"请输入最小的总额:");
			numinput(&max,100000000,"请输入最大的总额:");
			if(max<min)
				printf("输入有误!请重新输入\n");
			else
				break;
		}
		for(i=0;i<n;i++)
		{
			if(t==0)
			{	if(pt->total>=min&&pt->total<=max)
				{	
					p2=p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
					p1->next=NULL;
					p2=p1;
					pht=p1;
				}
				else;
			}
			else
			{
				if(pt->total>=min&&pt->total<=max)
				{
					p1=(COMMDITY*)malloc(sizeof(COMMDITY));
					p1->next=NULL;
					p2->next=p1;
					p2=p1;
					strcpy(p1->num,pt->num);
					strcpy(p1->name,pt->name);
					strcpy(p1->type,pt->type);
					p1->price=pt->price;
					p1->amount=pt->amount;
					p1->sold=pt->sold;
					p1->total=pt->total;
					t++;
				}
			}
			pt=pt->next;
		}
		if(t)
		{
			printf("\n\n\n该信息共有%d\n\n",t);
			Disp(pht,t);
			Save1(pht,t,"d:\\jjj.txt");
		}
		else
		{
			Nofind();
			getch();
		}
	}
	else if(select==0)
		break;
	else if(select==11)
	{
		isfind=0;
		size=0;
		t=0;
		pt=ph;
		for(i=0;i<n;i++)
		{
			ptt=ph;
			for(j=0;j<i;j++)
			{	if(strcmp(ptt->type,pt->type)==0)
				{
					isfind=1;
					break;
				}
				ptt=ptt->next;
			}
			if(isfind==1)
			{
				++size;
				isfind=0;
			}
			pt=pt->next;
		}
		printf("\n总有%d种\n",n-size);
		getch();
	}
	else
		Wrong();
	}
}





void Save(COMMDITY *pt,int n)   //保存
{	
	FILE*fp;
	int i=0;
	fp=fopen("d:\\com.txt","w");
	if(fp==NULL)
	{
		printf("\n=====>打开文件失败!\n");
		getch();
	}
	for(i=0;i<n;i++)
	{
		if(fwrite(pt,sizeof(COMMDITY),1,fp)==1)
		{
			pt=pt->next;
			continue;
		}
		else break;
	}
	if(i>0)
	{
		getchar();
		printf("\n\n=====>完成文件保存，全部保存的记录有:%d条\n",i);
		getchar();
		saveflag=0;
	}
	else
	{
		system("cls");
		printf("无记录被新保存!\n");
		getch();
	}
	fclose(fp);
}

int time30()
{
	struct tm *p;
	int ti,t3;
	time_t t = time(0);
	p=localtime(&t);
	ti=p->tm_sec;
	t3=30;
	system("cls");
	printf("请等%d秒后重试",t3);
	while(1)
	{	time_t t = time(0);
		p=localtime(&t);
		if(ti!=p->tm_sec)
		{
			system("cls");
			printf("请等%d秒后重试",--t3);
			ti=p->tm_sec;
		}
		if(t3==0)
		{	
			system("cls");
			return 0;
		}
	}
}

void Savet(int k)
{
	FILE* fp;
	fp=fopen("d:\\time.txt","w");
	fwrite(&k,sizeof(int),1,fp);
	fclose(fp);
}

int mima()   //密码
{	FILE*fp;
	int i=0,j=0,k=0;
	char mi[255],ma[255],shen[255],fen[255];
	fp=fopen("d:\\mima.txt","a+");
	while(!feof(fp))
		if(fread(&mi[i],sizeof(char),1,fp)==1)	
		{	i++;}
	fclose(fp);
	fp=fopen("d:\\shenfen.txt","a+");
	while(!feof(fp))
		if(fread(&shen[j],sizeof(char),1,fp)==1)	j++;
	fclose(fp);
	if(i==0)  
	{
		printf("第一次使用，请设置密码(多于6位):");
		while(1)
		{
			scanf("%s",mi);
			if(strlen(mi)<6)
				printf("少于6位,请重新输入:");
			else break;	
		}
		fp=fopen("d:\\mima.txt","w");
		for(i=0;i<=(int)strlen(mi);i++)
		{
			if(fwrite(&mi[i],sizeof(char),1,fp)==1)
				 continue;
			else break;
		}
		fclose(fp);
		printf("输入身份证:");
		scanf("%s",shen);
		fp=fopen("d:\\shenfen.txt","w");
		for(i=0;i<=(int)strlen(shen);i++)
		{
			if(fwrite(&shen[i],sizeof(char),1,fp)==1) 	
			 continue;
			else break;
		}
		fclose(fp);
	}
	else
	{
		fp=fopen("d:\\time.txt","a+");
		fread(&k,sizeof(int),1,fp);
		fclose(fp);
		while(1)
		{
			if(k==5)
			{
				k=time30();
				Savet(k);
			}
			printf("请输入密码:(输入0重置)");
			i=0;
			while((ma[i]=getch())!='\r')
			{
				if(ma[i]=='\b')
				{
					if(i!=0)
					{
					printf("\b \b");
					i--;
					}
				}
				else
				{
					printf("*");
					i++;
				}
			}
			ma[i]='\0';
			if(strcmp(ma,"0")==0)
			{	
				printf("\n请输入身份证:");
				i=0;
				while((fen[i]=getch())!='\r')
				{
					if(fen[i]=='\b')
					{
						if(i!=0)
						{
					printf("\b \b");
						i--;
						}
					}
					else
					{
						printf("*");
						i++;
					}
				}
				fen[i]='\0';
				if(strcmp(shen,fen)==0)
				{
					printf("\n请输入新密码");
					while(1)
					{
						scanf("%s",mi);
						if(strlen(mi)<6)
						printf("少于6位,请重新输入:");
						else break;	
					}
					fp=fopen("d:\\mima.txt","w");
					for(i=0;i<=(int)strlen(mi);i++)
						{
							if(fwrite(&mi[i],sizeof(char),1,fp)==1)
								continue;
							else break;
						}
					fclose(fp);
					break;
				}
				else
				{
					printf("\n身份证错误");
					getch();
					system("cls");
				}
			}	
			else if(strcmp(mi,ma)==0)
				break;
			else
			{
				printf("\n密码错误\n");
				k++;
				if(k<5)
				{
					printf("你还有%d次机会",5-k);
					getch();
				}
				if(k==5)
				{	
					Savet(k);
					k=time30();
					Savet(k);
				}
				system("cls");
			}
		}
	}
	fclose(fp);
	return k;
}


main()
{
	COMMDITY *phead,*p1,*p2;
	FILE *fp;
	int select;
	char ch[255],select1[255];
	int n=0,k,i;
	k=mima();
	if(k!=5)
	{
		fp=fopen("d:\\com.txt","a+");
		if(fp==NULL)
		{
			printf("\n===>can not open file!\n");
			exit(0);
		}
		p1=p2=(COMMDITY *)malloc(sizeof(COMMDITY));
		phead=(COMMDITY *)malloc(sizeof(COMMDITY));
		phead->next=NULL;
		if(fread(phead,sizeof(COMMDITY),1,fp)==1)
		{
				n++;
				phead->next=NULL;
				p2=phead;
		}
		while(!feof(fp))
		{	
			p1->next=NULL;
			p2->next=p1;
			p2=p1;
			if(fread(p1,sizeof(COMMDITY),1,fp)==1) 
				n++;
			p1=(COMMDITY *)malloc(sizeof(COMMDITY));
		}
		free(p1);
		fclose(fp);
		printf("\n上次记录有%d条信息\n(敲任意键继续)\n",n);
		getch();
		system("cls");
		menu();
		while(1)
		{
			system("cls");
			menu();
			printf("\n            请输入你的选择(0~9:)");
			scanf("%s",select1);
			for(i=0;i<strlen(select1);i++)
				if(select1[i]>'9'||select1[i]<'0')
					break;
			if(i==strlen(select1))
				select=atoi(select1);
			else
				select=100;
			if(select==0)
			{	
				if(saveflag==1)
				{
					getchar();
					printf("\n==>是否保存已经修改的记录到文件?(y/n):");
					while(1)
					{
						scanf("%s",ch);
						if(strlen(ch)>1)
							printf("请输入y/n\n");
						else if(ch[0]=='y'||ch[0]=='Y')
						{
							Save(phead,n);
							break;
						}
						else if(ch[0]=='n'||ch[0]=='N')
							break;
						else
							printf("请输入y/n\n");
					}
				}
				printf("\n=====>谢谢你使用本系统!\n");
				getch();
				break;
			}	
			switch(select)
			{
				case 1:n=Add(phead,n);break;
				case 2:system("cls");
					Disp(phead,n);getch();break;
				case 3:n=Del(phead,n);break;
				case 4:Qur(phead,n);break;
				case 5:Modify(phead,n);break;
				case 6:n=Insert(phead,n);break;
				case 7:SelectSort(phead,n);break;
				case 8:Count(phead,n);break;
				case 9:Save(phead,n);break;
				default:Wrong();getchar();break;
			}
		}
	}
}