#include <stdio.h>
#include <stdlib.h>
#include "prompt.h"
#include "operation.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	float a,b = 0;
	char q,t;
	int w,we,m;
	i:
	printf("\t请选择数字\n1 计算器\n2 退出\n");
	scanf("%d",&we);
	switch(we){
		case 1:{
					printf("\t\t\t正在加载"); 
					system("cls");
					printf("\t\t两位数运算\n");
					ii:
					printf("输入数字和符号如(1+1)输入0,0返回菜单，按回车结束\n");
					w = scanf("%f%c%f",&a,&q,&b);
					//printf("%d\n",w);
					//printf("%d\n",q); 
							 if(a == 0 && b == 0){
									goto i;
								}
								
								else if(w != 3){
							   	tishi_3();
							   	while(getchar() != '\n'){        //避免出现死循环，输入非数字时，字符会停留在缓存区，下次调用scanf会直接从缓存区里输入从而进入死循环 
								   }
							   	goto ii; 
								}
								
									else{
										 switch(q){
											 
										 	case 47:{
												yunsuan_1(a,b);
												goto ii; 
											 	break;
												}
												
											case 42:{
												yunsuan_2(a,b);
												goto ii;
												break;
											}
											case 37:{
												yunsuan_5((int)a,(int)b);
												goto ii;
												break;
											}
											case 43:{
												yunsuan_3(a,b);	
												goto ii; 
											 	break;
												}
											case 45:{
												yunsuan_4(a,b);
												goto ii; 
											 	break;
												}
											default:{
												tishi_1();
												goto ii;
												break;
											}
									 	}
											 	
										}
								break;
									}
	
			case 2:{
			printf("\t\t已退出\n"); 
			break;
		}
								}			
					return 0;
					
}

						
		    

