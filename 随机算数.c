#include <stdio.h>
#include <stdlib.h>
int peinr(int a,int b,int c);
int main()
{
	int a,b,c,d,g,j; //a������b���������c��d�������g���Ŵ��� 
	char k; 
	printf("����������(1~10)");
	scanf("%d",&a); 
	if(a > 0 && a <= 10)
	{
		for(;a>0;a--)
		{
			b = 3;
			g = rand() % (4 - 1) + 1; 
			c = rand() % 100 + 1;
			d = rand() % 10 + 1;
			switch(g)
				{
					case 1: printf("������%d + %d =____�Ĵ�\n ",c,d);k = '+';break;
					case 2: printf("������%d - %d =____�Ĵ�\n ",c,d);k = '-';break;
					case 3: printf("������%d * %d =____�Ĵ�\n ",c,d);k = '*';break;
					case 4: printf("������%d / %d =____�Ĵ�\n ",c,d);k = '/';break;
				}
			while(b)
			{
				scanf("%d",&j);
				if(j == peinr(c,d,g))
				{
					printf("yes\n");break;
				}	
				else
				{
					printf("no\n");
					if(b != 1) printf("���������\n"); 
					b --;
					if(b == 0)
					{
						 printf("\n������\%d %c %d��ȷ����\"%d\"\n",c,k,d,peinr(c,d,g));
					}
				}
			}	 
		}
	}
	else
	printf("��������");
 } 
int peinr(int a,int b,int c)
{
	int ui;
	
	switch(c)
	{
		case 1: ui = a + b;break;
		case 2: ui = a - b;break;
		case 3: ui = a * b;break;
		case 4: ui = a / b;break;
	}
	
	return ui;
}
