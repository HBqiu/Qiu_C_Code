#include <stdio.h>
#define N 6
void scan(int a[],int b);
void print(int a[],int b);
void pai(int a[],int b);
void zi(int *a,int *b);
int main()
{	 
    //int N = 0; 
	int a[N];
	//printf("请输入有多少元素");
	//scanf("%d",&N);
	printf("请输入%d个元素\n",N); 
	scan(a,N);
	printf("排序前\n");
	print(a,N);
	pai(a,N);
	printf("排序后\n");
	print(a,N);
	
 } 
void scan(int a[],int b)
 {
 	for(int i = 0;i < b; i++)
 	{
 		scanf("%d",&a[i]);
	 }
 }
void print(int a[],int b)
{
	for(int i = 0; i < b; i++)
	{
		printf("%d  ",a[i]);
	}
	printf("\n");
}
void pai(int a[],int b)
{
	for(int i = 1; i < b; i++)
	{
		for(int c = 0; c < b - i; c++)
		{
			if(a[c] > a[c + 1])
			{
				zi(&a[c],&a[c + 1]);
			}
		}
	}
	
}
void zi(int *a,int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
