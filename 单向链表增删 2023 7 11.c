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
	printf("������ѧ��\n");
	scanf("%d",&t -> a);
	printf("ѧ��:%d������\n",t -> a);
	scanf("%s",&t -> b);
	while(1)
	{
		t = (struct li*)malloc(sizeof(struct li));
		printf("������ѧ��\n");
		scanf("%d",&t -> a);
		if(t -> a <= 0) break;
		printf("������ѧ��:%dѧ������\n",t -> a);
		scanf("%s",&t -> b);
		t -> next = NULL;
		m -> next = t;
		m = t;
	}
	free(t);
	m -> next = NULL;
	return x;
}
struct li *tian(struct li* P)   //��� 
{
	if(P == NULL){	printf("������");	return 0;	}
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
		printf("������ѧ��\n");
		scanf("%d",&x -> a);
		if(x -> a <= 0) break;
		printf("������ѧ��:%dѧ������\n",x -> a);
		scanf("%s",&x -> b);
		x -> next = NULL;
		P -> next = x;
		P = x;
	}
	free(x);
	P -> next = NULL;
	return k;
	
}
struct li *shan(struct li *P)  //ɾ�� 
{
	if(P == NULL){	printf("������");	return 0;	}
	int i;
	printf("������Ҫɾ����ѧ��"); 
	scanf("%d",&i);
	struct li *pp = P,*q = P -> next;
	if(1 == i)
	{
		printf("\n��ɾ����%dѧ������\n",1);
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
			printf("\n��ɾ����%dѧ������\n",q -> a);
			P -> next = q -> next;
			free(q); return pp;		
			}
		}
		P = P -> next;
		q = P -> next;
	 } 	
	printf("û�и�ѧ��\n");
}
struct li *cha(struct li *P)   //���� 
{
	if(P == NULL){	printf("������");	return 0;	}
	int i;
	printf("����ڼ�ѧ������");
	scanf("%d",&i); 
	struct li *pp = P;
	struct li *c;
	if(i == 1)
	{
		printf("\n�����ڵ�%d����\n",1);
		c = (struct li*)malloc(sizeof(struct li));
		printf("������ѧ��\n");
		scanf("%d",&c -> a);
		printf("������ѧ��:%dѧ������\n",c -> a);
		scanf("%s",&c -> b);
		c -> next = pp; 
		pp = c;
		return pp;
	}
	while(1)
	{
		if(P -> a + 1 == i)
		{
			printf("\n�����ڵ�%d����\n",P -> a + 1);
			c = (struct li*)malloc(sizeof(struct li));
			printf("������ѧ��\n");
			scanf("%d",&c -> a);
			printf("������ѧ��:%dѧ������\n",c -> a);
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
	printf(" 1.����������Ϣ 2.���������Ϣ\n 3.ɾ��������Ϣ 4.����������Ϣ\n"); 
	do
	{
		printf("\n�������� 0�˳�\n");
		scanf("%d",&a);
		switch(a) 
		{
			case 0: return 0; 
			case 1: p = hap(); break;
			case 2: p = tian(p); break;
			case 3: p = shan(p); break;
			case 4: p = cha(p); break; 
			default : printf("��ŷǷ� ��������"); 
		}
		if(a >= 1 && a <= 4)
		{
			P = p;
			while(P != NULL)
			{
				printf("ѧ�ţ�%d  ���֣�%s  ",P -> a,P -> b);
				P = P -> next;
			}
		}	
		
	}while(1);	
}
