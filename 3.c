#include <stdio.h>
int main()
{
 float a,b,c;
i_i:
 printf("�������֣����ŷָ񣬰��س�����\t����0,0�˳�\n");
 scanf("%f,%f",&a,&b);
 if(a == 0 && b == 0){
	 goto i_ii;
 
 }
 else if(b == 0)
 { 
	 printf("�Ƿ�����\n\n");
 }
 else{
	 printf("����%0.2f\n\n",c = a / b);
 }
 goto i_i;

i_ii:
 return 0;
}
