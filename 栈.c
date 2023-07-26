#include<stdio.h>
#include<stdlib.h>
typedef struct zhan
{
	int *a;
	int tom;
	int sou;	
}zhan;
void chu(zhan *p)
{
	if(p == NULL)
	{
		printf("无效地址");return; 
	}
 	p -> a = (int*)malloc(sizeof(int) * 4);
 	p -> tom = -1;
 	p -> sou = 4;
}
void xiao(zhan *p)
{
	if(p == NULL)
	{
		printf("无效地址");return; 
	}
	free(p -> a);
	p -> a = NULL;
	p -> tom = p -> sou = 0;
}
void ru(zhan *p,int x)
{
	if(p -> tom == p -> sou) 
	{
		printf("栈满了");return; 
	}
	(p -> a)[++(p -> tom)] = x;
}
void chuz(zhan *p)
{
	if(p -> tom == -1)
	{
		printf("栈是空的");return; 
	}
	printf("%d",(p -> a)[(p -> tom)--]);
}
int main()
{
	zhan *p = (zhan*)malloc(sizeof(struct zhan));
	chu(p);
	ru(p,1);
	ru(p,2);
	ru(p,3);
	ru(p,4);
	ru(p,5);
	chuz(p);
	printf("出栈\n");
	ru(p,6);
	chuz(p);
	chuz(p);
	printf("出栈\n");
	ru(p,7);
	ru(p,8);
	ru(p,8);
	chuz(p);
	chuz(p);
	chuz(p);
	chuz(p);
	chuz(p);
	chuz(p);
	printf("出栈\n");
	xiao(p);
//	while(p -> tom != -1)
//	{
//		chuz(p);
//	}
 } 
  
