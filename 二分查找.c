#include <stdio.h>
int a();
int main() 
{
	printf("%d",a());
}
int a()
{
	int a[] = {1,2,3,5,6,8,10};
	int b = 0,c = 7 - 1;
	while(b <= c)
	{
		int p = (c + b) / 2;
		if(a[p] == 10)
			return p;
		if(a[p] < 10)
			b = p + 1;
		else
			c = p - 1;
	}
	return -1;
}
