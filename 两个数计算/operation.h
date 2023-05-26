int yunsuan_1(float aq,float dq)//除法 
{

 float a = aq ,b = dq ;
 	    
		 if(b == 0) { 
			 printf("\t不能除于0\n\n");
			// printf("a=%.2f\tb=%.2f",a,b);
			putchar('\n');
		 	}
		 else{
			printf("\t等于%0.2f\n\n",a / b);
		//	printf("a=%.2f\tb=%.2f",a,b);
			putchar('\n');
			}
 return 0;
}

int yunsuan_2(float aq,float dq)//乘法 
{

 float a = aq ,b = dq ;
	    
	printf("\t等于%0.2f\n\n",a * b);
	//printf("a=%.2f\tb=%.2f",a,b);
	putchar('\n');

 return 0;
}

int yunsuan_3(float aq,float dq)//加法 
{

 float a = aq ,b = dq ;
	    
	printf("\t等于%0.2f\n\n",a + b);
	//printf("a=%.2f\tb=%.2f",a,b);
	putchar('\n');

 return 0;
}

int yunsuan_4(float aq,float dq)//减法 
{

 float a = aq ,b = dq ;
	    
	printf("\t等于%0.2f\n\n",a - b);
	//printf("a=%.2f\tb=%.2f",a,b);
	putchar('\n');

 return 0;
}

int yunsuan_5(int aq,int dq)//取余 
{

 int a = aq ,b = dq ;
	    
	printf("\t等于%d\n\n",a % b);
//	printf("a=%d\tb=%d",a,b);
	putchar('\n');

 return 0;
}




