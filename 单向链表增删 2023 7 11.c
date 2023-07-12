#include <stdio.h>
#include <stdlib.h>
struct li
{
	int a;
	char b[10];
	struct li *next;
};
struct li *hap()
{
	struct li *t;
	struct li *x,*m;
	m = t = x = (struct li*)malloc(sizeof(struct li));
	t -> next = NULL;
	printf("请输入学号\n");
	scanf("%d",&t -> a);
	printf("学号:%d的名字\n",t -> a);
	scanf("%s",&t -> b);
	while(1)
	{
		t = (struct li*)malloc(sizeof(struct li));
		printf("请输入学号\n");
		scanf("%d",&t -> a);
		if(t -> a <= 0) break;
		printf("请输入学号:%d学生名字\n",t -> a);
		scanf("%s",&t -> b);
		t -> next = NULL;
		m -> next = t;
		m = t;
	}
	free(t);
	m -> next = NULL;
	return x;
}
struct li *tian(struct li* P)   //添加 
{
	if(P == NULL){	printf("空链表");	return 0;	}
	struct li *x,*k;
	k = P;
	while(1)
	{
		P = P-> next;
		if(P -> next == NULL) break;
	}
		while(1)
	{
		x = (struct li*)malloc(sizeof(struct li));
		printf("请输入学号\n");
		scanf("%d",&x -> a);
		if(x -> a <= 0) break;
		printf("请输入学号:%d学生名字\n",x -> a);
		scanf("%s",&x -> b);
		x -> next = NULL;
		P -> next = x;
		P = x;
	}
	free(x);
	P -> next = NULL;
	return k;
	
}
struct li *shan(struct li *P)  //删除 
{
	if(P == NULL){	printf("空链表");	return 0;	}
	int i;
	printf("请输入要删除的学号"); 
	scanf("%d",&i);
	struct li *pp = P,*q = P -> next;
	if(1 == i)
	{
		printf("\n已删掉第%d学号数据\n",1);
		pp = P -> next;
		free(P);
		return pp;
	}
	while(1)
	{
		if(q != NULL)
		{
			if(q -> a == i)
			{
			printf("\n已删掉第%d学号数据\n",q -> a);
			P -> next = q -> next;
			free(q); return pp;		
			}
		}
		P = P -> next;
		q = P -> next;
	 } 	
	printf("没有该学号\n");
}
struct li *cha(struct li *P)   //插入 
{
	if(P == NULL){	printf("空链表");	return 0;	}
	int i;
	printf("插入第几学号数据");
	scanf("%d",&i); 
	struct li *pp = P;
	struct li *c;
	if(i == 1)
	{
		printf("\n插入在第%d数据\n",1);
		c = (struct li*)malloc(sizeof(struct li));
		printf("请输入学号\n");
		scanf("%d",&c -> a);
		printf("请输入学号:%d学生名字\n",c -> a);
		scanf("%s",&c -> b);
		c -> next = pp; 
		pp = c;
		return pp;
	}
	while(1)
	{
		if(P -> a + 1 == i)
		{
			printf("\n插入在第%d数据\n",P -> a + 1);
			c = (struct li*)malloc(sizeof(struct li));
			printf("请输入学号\n");
			scanf("%d",&c -> a);
			printf("请输入学号:%d学生名字\n",c -> a);
			scanf("%s",&c -> b);
			c -> next = P -> next;	
			P -> next = c;
			break;		
		}
		P = P -> next;
	 } 
	 return pp;
}
int main()
{
	struct li *p = NULL,*P; int a;
	printf(" 1.创建链表信息 2.添加链表信息\n 3.删除链表信息 4.插入链表信息\n"); 
	do
	{
		printf("\n请输入编号 0退出\n");
		scanf("%d",&a);
		switch(a) 
		{
			case 0: return 0; 
			case 1: p = hap(); break;
			case 2: p = tian(p); break;
			case 3: p = shan(p); break;
			case 4: p = cha(p); break; 
			default : printf("编号非法 重新输入"); 
		}
		if(a >= 1 && a <= 4)
		{
			P = p;
			while(P != NULL)
			{
				printf("学号：%d  名字：%s  ",P -> a,P -> b);
				P = P -> next;
			}
		}	
		
	}while(1);	
}
