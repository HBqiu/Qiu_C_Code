#include <stdio.h>
void fang();//����
void san();//���� 
void san_();//������ 
void xing();//�����Ǻ� 
void you();//���� 
void xing_();//�����Ǻ� 
void zuo();//���� 
int main()
{
//	fang();
//	san();
//	san_();
//	xing();
//	you();
//	xing_();
//	zuo();
} 
 
void fang()
{
	for(int a = 1; a <= 9; a++)
	{
		for(int b = 1;b <= 9; b++)
			printf("%d * %d = %2d  ",a,b,a * b);
		printf("\n");
	}
}
void san()
{
	for(int a = 1; a <= 9; a++)
	{
		for(int b = 1; b <= a; b++)
			printf("%d * %d = %2d  ",a,b,a * b);
		printf("\n");
	}
}
void san_() 
{
	for(int a = 1; a <= 9; a++)
	{
		for(int b = a; b <= 9; b++)
			printf("%d * %d = %2d  ",a,b,a * b);
		printf("\n");
	}	
}
void xing() 
{
	for(int a = 1; a <= 9; a++)
	{
		for(int b = a; b < 9; b++)
			printf(" ");
		for(int c = 1; c <= a; c++)
			printf("*");
		printf("\n");
	}
}
void you()
{
	for(int a = 1; a <= 9; a++)
	{
		for(int b = a; b < 9; b++)
			printf("            ");
		for(int c = 1; c <= a; c++)
			printf("%d * %d = %2d  ",a,c,a * c);
		printf("\n");
	}	
}
void xing_()
{
	for(int a = 1;a <= 9; a++)
	{
		for(int b = 1; b < a; b++)
			printf(" ");
		for(int c = a; c <= 9 ;c++)
			printf("*");
		printf("\n");
	}
 } 
 void zuo()
 {
 	for(int a = 1; a <= 9; a++)
 	{
 		for(int b = 1; b < a; b++)
		 	printf("            ");
		for(int c = a; c <= 9; c++) 
			printf("%d * %d = %2d  ",a,c,a * c);
		printf("\n");
	 }
  } 
