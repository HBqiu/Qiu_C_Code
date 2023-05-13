#include <stdio.h>
#include <string.h>  //strcmp比较两个字符串的头文件 
#include <stdlib.h>  //malloc动态分配内存头文件 

struct ip
{
	int i;
	char c[30];
	struct ip *next;
};

int lon,cls = 0,els;  //lon成员总数,cls超过5清屏,els超过5清屏 

struct ip *ch()
{
	char l[10],s[10];
	struct ip *phead = NULL;       //头指针 
	struct ip *pend,*pnew;         //尾结点 新结点 
	lon = 0;
	
	pend = pnew = (struct ip*)malloc(sizeof(struct ip));
	printf("请输入名字，学号\n"); 
	scanf("%s%d",&pnew -> c,&pnew -> i);
	
	while(pnew ->i != 0)
	{
		lon ++;
		cls ++;
		if(lon == 1)
		{
			pnew -> next = NULL;
			phead = pend = pnew; 
		}
		else
		{
			pend -> next = pnew;
			pend = pnew;			
		}
		
		pnew = (struct ip*)malloc(sizeof(struct ip));
		
		printf("退出(exit),按回车继续");
		gets(s);                               //接受缓存区的回车字符，去掉下条语句会直接跳过 
		gets(l);
		if(strcmp(l,"exit") == 0 || strcmp(l,"EXIT") == 0){ system("cls"); break; } 
	  
	//	pnew = (struct ip*)malloc(sizeof(struct ip));   break退出后这条语句未执行没有申请新的空间给pnew，所以下面free不消除新的空间而消除了最后一次输入的结点 
		
		if(cls == 5)
		{
			system("cls");
			cls = 0;
		}
		
		printf("请输入名字，学号\n"); 
		scanf("%s%d",&pnew -> c,&pnew -> i);	
	}
	
	pend -> next = NULL; 
	free(pnew);      //free没有返回值，消除的是malloc最后一次返回的内存地址 
	return phead;
}
void print(struct ip *phead)
{
	struct ip *pinf;
	int malo = 1;
	
	printf("---有%d个成员---\n\n",lon);
	pinf = phead;
	
	while(pinf != NULL)
	{
		printf("   成员NO %d\n",malo);
		printf("学号 %d\n姓名 %s\n\n",pinf -> i,pinf -> c);
		pinf = pinf -> next;
		malo ++;
	}
	printf("需要保存数据吗?\t回车键继续"); 
	getchar();
	
}
int main()
{
	
	struct ip *pnww;        
	pnww = ch();
	print(pnww);
	system("cls");
	printf("是否保存数据(Y\\N)");
	while(1)
	{
		 char po,pp[100]; 
	     po = getchar();
		
		 if(po == 'y' || po == 'Y')
		 { 
			FILE *p;
			int i = 0,d = 0;
			char a[] = "NULL",b[10];//,c[] = "----------成员",cc[] = "----------",dd[] = "学号",pd[] = "姓名";
			char ds[] = "E:\\",ad[] = ".txt";//链接字符使用
			
			system("cls");
			printf("请输入文件绝对地址或新建文件名:"); 
			scanf("%s",a);
			
			p = fopen(a,"r+");
			
			if(p == NULL)  //判断文件是否存在，如果不存在创建文件 
			{
				strcat(ds,a);              //链接字符串 
				strcat(a,ad);
				strcat(ds,ad);
				p = fopen(ds,"w+");
				
			}
			else
			{
				
				i++;                             //如果有文件i++ 
				printf("保存成功\n");
					
			}
			if(p != NULL)
			{
				
				if(i == 0)printf("\n\n文件创建成功，文件名:\"%s\" 文件路径:\"%s\"",a,ds);   //i不等于0输出 i=0表示文件刚创建 
				
				while(pnww != NULL)
				{
					d++; 	
					fprintf(p,"---------成员%d------------\n",d);
					//fprintf(p,"%s","\n");
					//fprintf(p,"%s","  ");
					//fprintf(p,"%s",dd);
					//fprintf(p,"%s"," ");
					fprintf(p," 学号 %d \t ",pnww -> i);
					//fprintf(p,"%s","\t ");
					//fprintf(p,"%s",pd);
					//fprintf(p,"%s"," ");
					fprintf(p,"姓名 %s\n\n",pnww -> c);
					//fprintf(p,"%s","\n\n");
					pnww = pnww -> next;
				
				}	
					
				rewind(p);
				
			}
			
			fclose(p); break;        //关闭文件 
		 }
		 
		 else if(po == 'n' || po == 'N')
		 {
			printf("未保存"); break;
		 }
		
		else
		{
			while(po != '\n')     //避免用户多输入字符留在缓存区 
			{
				gets(pp);
				break;	
			}
			if(els == 5)
			{
				system("cls");
				els = 0;
			}
			printf("请选择是否保存数据(Y\\N)");
			
			els ++;
			
			continue;
		}
	}

	return 0;	
	
}
