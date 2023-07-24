#include <stdio.h>
void mao();  //冒 
void xuan(); //选 
int main()
{
//mao();
xuan();
} 

 void xuan()
 {
 	int a[] = {5,4,58,6,1},b;
 	for(int i = 0; i < 5 - 1; i++)
 	{
 		b = i;    //当前最小数下标 
 		for(int y = i + 1; y < 5; y++)
		 {
		 	if(a[y] < a[b]) //继续后续循环比较有没有比当前最小还要小的 
		 	{
		 		b = y;     //跟踪当前最小数下标 
			}
		  } 
			if(i != b)  //没有比当前循环还要小的跳过交换，同样的下标异或数值会出错 
			{
				a[i] = a[i] ^ a[b];
		  		a[b] = a[i] ^ a[b];
		 		a[i] = a[i] ^ a[b];
			} 
	 }
 	for(int i = 0; i < 5; i++)
	 	printf("%d",a[i]);	
 }
 void mao()
 {
 		int a[] = {5,4,3,2,1};
	for(int i = 1; i < 5; i++)
	{
		for(int y = 0; y < 5 - i; y++ )
		{
			if(a[y] > a[y + 1])
			{
				a[y] = a[y] ^ a[y + 1];
				a[y + 1] = a[y] ^ a[y + 1]; 
				a[y] = a[y] ^ a[y + 1];
			}
		}
	 } 
	 for(int i = 0; i < 5 ; i++)
	 	printf("%d",a[i]);
 }
