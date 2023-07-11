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
	if(P == NULL)
		return 0;
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
struct li *shan(struct li *P,int i)  //删除 
{
	if(P == NULL) return 0;
	struct li *pp = P,*q = P -> next;
	while(1)
	{
		if(q -> a == i)
		{
			printf("\n已删掉第%d节点数据\n",q -> a);
			P -> next = q -> next;
			free(q);
			break;		
		}
		P = P -> next;
		q = P -> next;
	 } 
	 return pp;
}
struct li *cha(struct li *P,int i)   //插入 
{
	if(P == NULL) return 0;
	struct li *pp = P;
	struct li *c;
	while(1)
	{
		if(P -> a == i)
		{
			printf("\n在第%d节点插入数据\n",P -> a + 1);
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
	int i;
	struct li *p,*v,*s,*c;
	p = hap();
	c = v = s = p;
	while(p != NULL)
	{
		printf("学号：%d,名字：%s",p -> a,p -> b);
		p = p -> next;
	}
	printf("\n末尾添加\n");
	v = tian(v);
		while(v != NULL)
	{
		printf("学号：%d,名字：%s",v -> a,v -> b);
		v = v -> next;
	}
	printf("\n请输入要删除的学号");
	scanf("%d",&i); 
	s = shan(s,i);
		while(s != NULL)
	{
		printf("学号：%d,名字：%s",s -> a,s -> b);
		s = s -> next;
	}
	printf("\n请输入要添加的学号");
	scanf("%d",&i); 
	c = cha(c,i - 1);
	while(c != NULL)
	{
		printf("学号：%d,名字：%s",c -> a,c -> b);
		c = c -> next;
	}
}
