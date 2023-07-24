#include<stdio.h>
#include<stdlib.h>
void i();
struct suang *w();
void f();
int ID = 0;
void data(struct suang *p,int i);
int cha();
void shuju();
struct suang
{
	int id;
	int data;
	struct suang *next;
	struct suang *shang;
};
struct suang *pn()
{
	struct suang*p,*n,*w;
	p = n = w = (struct suang*)malloc(sizeof(struct suang));
	n -> id = ID,n -> data = 0;
	n -> next = NULL,n -> shang = NULL;
	w -> shang = NULL;
	while(1){
		w = n;
		n = (struct suang*)malloc(sizeof(struct suang));
		w -> next = n,n -> shang = w;
		n -> next = NULL;
		printf("请写入编号%d的数据",++ID); 
		n -> id = ID;
		scanf("%d",&n -> data);
		if(n -> data == 0) break;	
	}
	free(n);
	w -> next = NULL;
	return p;
}
int main()
{
	struct suang *o;
	o = pn();
	i(o);
	f(w(o));
//	printf("%d",ID);
	data(o,cha());
	shuju(o,cha());
	return 0;
}
void i(struct suang *p)
{
	//struct suang *pp = p;
	p = p -> next;
	printf("正序\n"); 
	while(p != NULL)
	{
		printf("编号%d的数据是%d\n",p -> id,p -> data);
		p = p -> next; 	
	}
//	while(pp -> next != NULL)
//	{
//		pp = pp -> next;
//	}
//	while(pp -> id) 
//	{
//		printf("编号%d的数据是%d\n",pp -> id,pp -> data);
//		pp = pp -> shang;
//	}
}
struct suang *w(struct suang *pp)
{
	while(pp -> next != NULL)
	{
		pp = pp -> next;
	}
	return pp;
}
void f(struct suang *pp)
{
	printf("反序\n"); 
		while(pp -> id) 
	{
		printf("编号%d的数据是%d\n",pp -> id,pp -> data);
		pp = pp -> shang;
	}
}
void data(struct suang *p,int i)
{
	if(i >= ID || i < 1)
	{
		printf("没有该节点\n"); return;
	}
	struct suang *l = p -> next;
	struct suang *o = w(p);
	while(l != NULL && o != NULL)
	{
		if(l -> id == i)
		{
			printf("该节点数据是%d\n",l -> data);return;
		}
		if(o -> id == i)
		{
			printf("该节点数据是%d\n",o -> data);return;
		}
		l = l -> next;o = o -> shang;
	}
}
int cha()
{
	int a;
	printf("请输入要查找的节点"); 
	scanf("%d",&a);
	return a; 
}
void shuju(struct suang *p,int i)
{
	struct suang *l = p -> next;
	struct suang *o = w(p);
	while(l != NULL && o != NULL)
	{
		if(l -> data == i)
		{
			printf("该数据节点是%d\n",l -> id);return;
		}
		if(o -> data == i)
		{
			printf("该数据节点是%d\n",o -> id);return;
		}
		l = l -> next;o = o -> shang;
	}
	printf("没有该数据\n"); 
	return;
 } 
