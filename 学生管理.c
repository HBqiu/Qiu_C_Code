// 粗稿学生管理系统 完成于2024-1-12 李家祥  
/* 这个C语言程序是一个简单的学生管理系统，具有基本的增、删、改、查、保存等功能。下面是对每个函数的审计和功能分析：

struct lian 和 struct lianid 结构体用于存储学生信息和临时链表中满足条件的学生信息。这些结构体定义了学生的年级、班级、学号、姓名等信息，并使用链表将学生信息组织在一起。

jieID 函数用于创建并初始化一个 LianID 结构体，将传入的 Lian 指针打包成一个临时节点。

jie 函数用于创建并初始化一个 Lian 结构体，将传入的学生信息打包成一个节点。

shenID 函数用于将满足条件的学生信息节点添加到临时链表 LianrID 中。

deltitleID 函数用于删除临时链表 LianrID 中的节点，释放内存。

deltitle 函数用于删除链表中的节点，释放内存。

shen 函数用于将学生信息节点添加到链表 Lianr 中。

print 函数用于打印链表中的学生信息。

wen 函数用于将链表中的学生信息保存到文件。

fileprint 函数用于从文件中读取学生信息，并将其存储在临时链表中。

addtitle 函数用于向链表中添加学生信息，可以一次添加多个学生。

titleUI 和 xiutitleT 函数用于显示和处理修改学生信息的界面和过程。

xiutitle 函数用于修改临时链表中的学生信息。

bansut 函数用于筛选出满足条件的班级学生，并存储在临时链表中。

printsut 函数用于打印满足条件的班级学生信息。

xiusut 函数用于修改满足条件的班级学生信息。

ui 函数用于显示主界面，提供用户选择不同功能的选项。

main 函数是程序的入口，包含一个无限循环，根据用户的选择执行相应的功能。

难易程度：

代码整体比较简单，主要是对学生信息的管理和存取，没有复杂的算法和数据结构。
难点可能在于学生信息的筛选、修改和保存操作，需要一些基本的编程技巧。
程序结构清晰，函数模块化设计，使得代码容易理解和维护。
总体来说，这个程序难度适中，适合初学者练习和学习基本的链表操作和文件处理。*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct lian //年纪 ，班级 ，学号 
{
	int nian;
	int ban;
	char i[10];
	char name[10];
	char num[10];
	struct lian *next;
}Lian;
typedef struct  //链表的头节点 
{
	Lian *head;
	Lian *we; 
}Lianr; 
typedef struct lianid  //存放链表筛选后满足条件的节点地址 
{
	Lian *id;
	struct lianid *next;
}LianID;
typedef struct  //LianID的头节点 
{
	LianID *head;
	LianID *we; 
}LianrID;
LianID* jieID(Lian *P)    //打包LianId节点 
{
	LianID *tem = (LianID*)malloc(sizeof(LianID));
	if(tem != NULL)
	{
		tem -> id = P;
		tem -> next = NULL;
		return tem;
	}
	else
		return NULL;
}
Lian* jie(int nian,int ban,char *i,char *name,char *num)  //打包节点 
{
	Lian *tem = (Lian*)malloc(sizeof(Lian));
	if(tem != NULL)
	{
		tem -> nian = nian;
		tem -> ban = ban;
		strcpy(tem -> i,i);
		strcpy(tem -> name,name);
		strcpy(tem -> num,num);
		tem -> next = NULL;
		return tem;
	}
	else
		return NULL;
	
}
void shenID(LianrID *p,Lian *LP)  //申请LianID节点 
{
	LianID *tem = jieID(LP);
	if(p -> head == NULL)
	{
		p -> head = tem;
		p -> we = tem;
	}
	else
	{
		p -> we -> next = tem;
		p -> we = tem;
	}
}
int deltitleID(LianrID *P)   //删除LianID节点 
 {
 	LianID *tem = P -> head;
 	LianID *tem1 = NULL;
	while(tem)
	{
		tem -> id = NULL;
		tem1 = tem;
		tem = tem -> next;
		free(tem1);
	 } 
	 P -> head = NULL;
	 P -> we = NULL;
	 return 0;
  } 
int deltitle(Lianr *P)   //删除链表函数 
 {
 	Lian *tem = P -> head;
 	Lian *tem1 = NULL;
	while(tem)
	{
		tem1 = tem;
		tem = tem -> next;
		free(tem1);
	 } 
	 P -> head = NULL;
	 P -> we = NULL;
	 return 0;
  } 
void shen(Lianr *p,int nian,int ban,char *i,char *name,char *num) //申请链表 
{
	Lian *tem = jie(nian,ban,i,name,num);
	if(p -> head == NULL)
	{
		p -> head = tem;
		p -> we = tem;
	}
	else
	{
		p -> we -> next = tem;
		p -> we = tem;
	}
}
void print(Lianr *p) //打印链表 
{
	Lian *tem = p -> head;
	if(tem == NULL)
	{
		printf("\n\n空");
		return; 
	}
	while(tem)
	{
		printf("%d,%d,%s,%s,%s\n",tem -> nian,tem -> ban,tem -> i,tem -> name,tem -> num);
		tem = tem -> next;
	}
}
int wen(Lianr *P,char *a) //保存到文件 
{
	if(P -> head == NULL)
	{
		return 1;
	}
	FILE *pfile = fopen("E:\\sut.txt",a);
	if(pfile == NULL)
	{
		return 2;
	}
	Lian *tem = P -> head;
	while(tem)
	{
		fprintf(pfile,"%d %d %s %s %s\n",tem -> nian,tem -> ban,tem -> i,tem -> name,tem -> num);
		tem = tem -> next;
	}
	fclose(pfile);
	deltitle(P); 
	return 0;
}
int fileprint(Lianr *P) //文件内容存放到临时链表 
{
	FILE *pfile = fopen("E:\\sut.txt","r");
	if(pfile == NULL)
	{
		return 1;
	}
	char a[10] = "0",
		 b[10] = "0",
		 c[10] = "0";
	int d,e;
	while(fscanf(pfile,"%d %d %s %s %s",&d,&e,a,b,c) != EOF)
	{
		shen(P,d,e,a,b,c);
	}
	fclose(pfile);
}
int addtitle(Lianr *P)  //链表添加函数 
{
	int p;
	printf("请输入添加人数");
	scanf("%d",&p) ;
	char a[10] = "0",
		 b[10] = "0",
		 c[10] = "0";
	int d,e;
	if(p > 0)
		printf("请输入%d个人资料",p); 
	for(int i = 0; i < p; i++)
	{
		scanf("%d%d%s%s%s",&d,&e,a,b,c);
		shen(P,d,e,a,b,c);
	}
 } 
void titleUI()  
{
	printf("\t -----------------------\n");
	printf("\t|    请选择修改类型\t|\n");
	printf("\t| 1.年纪\t2.班级\t|\n");
	printf("\t| 3.姓名\t4.系别\t|\n");
	printf("\t| 5.学分\t6.全部\t|\n");
	printf("\t -----------------------\n");
 } 
void xiutitleT(Lian *P,LianrID *tem);
void xiutitle(Lianr *P)  //修改临时链表信息 
{
	if(P -> head == NULL)
	{
		printf("空");
		return;	
	}
	char i[10];
	printf("请输入学生名字");
	scanf("%s",i);	
	Lian *tem = P -> head; 
	int temtitlenum = 0;
	LianrID teml;
	teml.head = NULL;
	while(tem)
	{
		if(strcmp(tem -> name,i) == 0)
		{
			temtitlenum++;
			printf("序号%d %d %d %s %s %s\n",temtitlenum,tem -> nian,tem -> ban,tem -> i,tem -> name,tem -> num);
			shenID(&teml,tem);
		}
		tem = tem -> next;
	}
	if(temtitlenum == 0)
	{
		printf("没有该学生");return;
	}	
	if(temtitlenum == 1)
	{
		titleUI();
		xiutitleT(teml.head -> id,&teml);
		//printf("\t\t\n%s\n\n",teml.head -> id -> name);
	 } 
	 else
	 {
	 	int temnum; 
	 	printf("请选择修改序号");
		scanf("%d",&temnum);
		 if(temnum > temtitlenum || temnum < 1)
		 {
		 	printf("有误");
			return; 
		  } 
		  LianID *temT = teml.head;
		  for(int i = 1;i < temnum; i++)
		  {
		  	temT = temT -> next;
		  }
		titleUI();
		xiutitleT(temT -> id,&teml); 
	 }
} 
void xiutitleT(Lian *P,LianrID *tem)  //修改过程 
{	
		short int i;
		scanf("%d",&i);
		int tem1,tem2;char tem3[10],tem4[10],tem5[10]; 
		switch(i)
		{
			case 1:
				printf("请输入修改后年纪");
				scanf("%d",&tem1); 
				P -> nian = tem1;
				break;
			case 2:
				 
				printf("请输入修改后班级");
				scanf("%d",&tem2);
				P -> ban = tem2;
				break;
			case 3:
				
				printf("请输入修改后姓名");
				scanf("%s",tem3);
				strcpy(P -> name,tem3); 
				break;
			case 4:
				printf("请输入修改后系别");
				scanf("%s",tem4);
				strcpy(P -> i,tem4); 
				break;
			case 5:
				printf("请输入修改后学分");
				scanf("%s",tem5);
				strcpy(P -> num,tem5); 
				break;
			case 6:
				printf("请输入全部信息");
				scanf("%d%d%s%s%s",&tem1,&tem2,tem3,tem4,tem5);
				P -> nian = tem1,
				P -> ban = tem2,
				strcpy(P -> i,tem3);
				strcpy(P -> name,tem4);
				strcpy(P -> num,tem5); 
				break;
			default :
				printf("参数有误");
				break; 
		}	
		deltitleID(tem); //该函数结束后返回到调用函数后teml就变成无法访问地址
						//只能传进来地址在此函数里释放(未搞明白，可能此函数结束后会自动释放) 
//		if(tem -> head == NULL)
//		{
//			printf("\n\ndeltitleID");
//		}	  	
 } 
int bansut(Lianr *P,LianrID *temtitle)
{
	if(P == NULL)
	{
		printf("空");
		return 0;
	}
	short i,k,titlenum = 0;
	printf("请输入年纪班级");
	scanf("%d%d",&k,&i); 
	Lian *tem = P -> head;
	while(tem)
	{
		if(tem -> nian == k && tem -> ban == i)
		{
			shenID(temtitle,tem);
			titlenum++;
		}
		tem = tem -> next;
	}
	return titlenum;
}
void printsut(int titlenum,LianrID *temtitle)
{
	if(titlenum == 0)
	{
		printf("没有学生");
		return; 
	}
	else
	{
		printf("该班级一共有%d位学生\n",titlenum);
		LianID *temID = temtitle -> head;
		while(temID)
		{
			printf("%d %d %s %s %s\n",temID -> id -> nian,temID -> id -> ban,temID -> id -> i,temID -> id -> name,temID -> id -> num);
			temID = temID -> next;
		}
	}
	deltitleID(temtitle); 
}
void xiusut(Lianr *P)
{
	if(P -> head == NULL)
	{
		printf("空");
		return;
	}
	Lian *tem = P -> head;	
} 
void ui()
{
	printf("\t-----------------------------------------\n");
	printf("\t|\t\t学生管理系统\t\t|\n");
	printf("\t| 1.录入临时信息\t2.查看临时信息\t|\n");
	printf("\t| 3.修改临时信息\t4.保存临时信息\t|\n");
	printf("\t| 5.查看全部学生\t6.查看班级学生\t|\n");
	printf("\t| 7.修改以存学生\t8.退出管理系统\t|\n");
	printf("\t-----------------------------------------\n"); 
}
int main()
{
	Lianr title;
	title.head = NULL; //链表 
	Lianr filetitle;
	filetitle.head = NULL;//文件读取链表 
	LianrID temtitle;
	temtitle.head = NULL;//存放符合班级学生条件链表 
//	addtitle(&title);
//	print(&title);
//	wen(&title);
//	fileprint(&filetitle);
//	deltitle(&title);
//	print(&title);
//	deltitle(&filetitle);
ui();
//xiutitle(&title);
//print(&title);

while(1)
{
	short Maini = 8;
	scanf("%d",&Maini);
	switch(Maini)
{
	case 1:
		addtitle(&title);break;
	case 2:
		print(&title);break;
	case 3:
		xiutitle(&title);break;
	case 4:
		wen(&title,"a");break;
	case 5:
		fileprint(&filetitle);
		print(&filetitle);
		deltitle(&filetitle);
		break;
	case 6:
		fileprint(&filetitle);
		printsut(bansut(&filetitle,&temtitle),&temtitle);
		deltitle(&filetitle);
		break;
	case 7:
		//修改班级学生
		fileprint(&filetitle);
		xiutitle(&filetitle);
		wen(&filetitle,"w");
		deltitle(&filetitle);
		break;
	case 8:
		return 0; 
}
}
}
