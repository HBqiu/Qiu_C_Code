#include <stdio.h>
int main()
{
 float a,b,c;
i_i:
 printf("输入数字，逗号分格，按回车结束\t输入0,0退出\n");
 scanf("%f,%f",&a,&b);
 if(a == 0 && b == 0){
	 goto i_ii;
 
 }
 else if(b == 0)
 { 
	 printf("非法输入\n\n");
 }
 else{
	 printf("等于%0.2f\n\n",c = a / b);
 }
 goto i_i;

i_ii:
 return 0;
}
