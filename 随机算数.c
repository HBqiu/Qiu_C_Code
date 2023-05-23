#include <stdio.h>
#include <stdlib.h>
int peinr(int a,int b,int c);
int main()
{
	int a,b,c,d,g,j; //a提数，b错误次数，c，d随机数，g符号代号 
	char k; 
	printf("请输入题数(1~10)");
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
					case 1: printf("请输入%d + %d =____的答案\n ",c,d);k = '+';break;
					case 2: printf("请输入%d - %d =____的答案\n ",c,d);k = '-';break;
					case 3: printf("请输入%d * %d =____的答案\n ",c,d);k = '*';break;
					case 4: printf("请输入%d / %d =____的答案\n ",c,d);k = '/';break;
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
					if(b != 1) printf("请从新输入\n"); 
					b --;
					if(b == 0)
					{
						 printf("\n错误多次\%d %c %d正确答案是\"%d\"\n",c,k,d,peinr(c,d,g));
					}
				}
			}	 
		}
	}
	else
	printf("输入有误");
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
