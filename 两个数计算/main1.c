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
	printf("\t��ѡ������\n1 ������\n2 �˳�\n");
	scanf("%d",&we);
	switch(we){
		case 1:{
					printf("\t\t\t���ڼ���"); 
					system("cls");
					printf("\t\t��λ������\n");
					ii:
					printf("�������ֺͷ�����(1+1)����0,0���ز˵������س�����\n");
					w = scanf("%f%c%f",&a,&q,&b);
					//printf("%d\n",w);
					//printf("%d\n",q); 
							 if(a == 0 && b == 0){
									goto i;
								}
								
								else if(w != 3){
							   	tishi_3();
							   	while(getchar() != '\n'){        //���������ѭ�������������ʱ���ַ���ͣ���ڻ��������´ε���scanf��ֱ�Ӵӻ�����������Ӷ�������ѭ�� 
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
			printf("\t\t���˳�\n"); 
			break;
		}
								}			
					return 0;
					
}

						
		    

