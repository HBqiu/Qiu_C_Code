#include <stdio.h>
void mao();  //ð 
void xuan(); //ѡ 
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
 		b = i;    //��ǰ��С���±� 
 		for(int y = i + 1; y < 5; y++)
		 {
		 	if(a[y] < a[b]) //��������ѭ���Ƚ���û�бȵ�ǰ��С��ҪС�� 
		 	{
		 		b = y;     //���ٵ�ǰ��С���±� 
			}
		  } 
			if(i != b)  //û�бȵ�ǰѭ����ҪС������������ͬ�����±������ֵ����� 
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
