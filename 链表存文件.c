#include <stdio.h>
#include <string.h>  //strcmp�Ƚ������ַ�����ͷ�ļ� 
#include <stdlib.h>  //malloc��̬�����ڴ�ͷ�ļ� 

struct ip
{
	int i;
	char c[30];
	struct ip *next;
};

int lon,cls = 0,els;  //lon��Ա����,cls����5����,els����5���� 

struct ip *ch()
{
	char l[10],s[10];
	struct ip *phead = NULL;       //ͷָ�� 
	struct ip *pend,*pnew;         //β��� �½�� 
	lon = 0;
	
	pend = pnew = (struct ip*)malloc(sizeof(struct ip));
	printf("���������֣�ѧ��\n"); 
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
		
		printf("�˳�(exit),���س�����");
		gets(s);                               //���ܻ������Ļس��ַ���ȥ����������ֱ������ 
		gets(l);
		if(strcmp(l,"exit") == 0 || strcmp(l,"EXIT") == 0){ system("cls"); break; } 
	  
	//	pnew = (struct ip*)malloc(sizeof(struct ip));   break�˳����������δִ��û�������µĿռ��pnew����������free�������µĿռ�����������һ������Ľ�� 
		
		if(cls == 5)
		{
			system("cls");
			cls = 0;
		}
		
		printf("���������֣�ѧ��\n"); 
		scanf("%s%d",&pnew -> c,&pnew -> i);	
	}
	
	pend -> next = NULL; 
	free(pnew);      //freeû�з���ֵ����������malloc���һ�η��ص��ڴ��ַ 
	return phead;
}
void print(struct ip *phead)
{
	struct ip *pinf;
	int malo = 1;
	
	printf("---��%d����Ա---\n\n",lon);
	pinf = phead;
	
	while(pinf != NULL)
	{
		printf("   ��ԱNO %d\n",malo);
		printf("ѧ�� %d\n���� %s\n\n",pinf -> i,pinf -> c);
		pinf = pinf -> next;
		malo ++;
	}
	printf("��Ҫ����������?\t�س�������"); 
	getchar();
	
}
int main()
{
	
	struct ip *pnww;        
	pnww = ch();
	print(pnww);
	system("cls");
	printf("�Ƿ񱣴�����(Y\\N)");
	while(1)
	{
		 char po,pp[100]; 
	     po = getchar();
		
		 if(po == 'y' || po == 'Y')
		 { 
			FILE *p;
			int i = 0,d = 0;
			char a[] = "NULL",b[10];//,c[] = "----------��Ա",cc[] = "----------",dd[] = "ѧ��",pd[] = "����";
			char ds[] = "E:\\",ad[] = ".txt";//�����ַ�ʹ��
			
			system("cls");
			printf("�������ļ����Ե�ַ���½��ļ���:"); 
			scanf("%s",a);
			
			p = fopen(a,"r+");
			
			if(p == NULL)  //�ж��ļ��Ƿ���ڣ���������ڴ����ļ� 
			{
				strcat(ds,a);              //�����ַ��� 
				strcat(a,ad);
				strcat(ds,ad);
				p = fopen(ds,"w+");
				
			}
			else
			{
				
				i++;                             //������ļ�i++ 
				printf("����ɹ�\n");
					
			}
			if(p != NULL)
			{
				
				if(i == 0)printf("\n\n�ļ������ɹ����ļ���:\"%s\" �ļ�·��:\"%s\"",a,ds);   //i������0��� i=0��ʾ�ļ��մ��� 
				
				while(pnww != NULL)
				{
					d++; 	
					fprintf(p,"---------��Ա%d------------\n",d);
					//fprintf(p,"%s","\n");
					//fprintf(p,"%s","  ");
					//fprintf(p,"%s",dd);
					//fprintf(p,"%s"," ");
					fprintf(p," ѧ�� %d \t ",pnww -> i);
					//fprintf(p,"%s","\t ");
					//fprintf(p,"%s",pd);
					//fprintf(p,"%s"," ");
					fprintf(p,"���� %s\n\n",pnww -> c);
					//fprintf(p,"%s","\n\n");
					pnww = pnww -> next;
				
				}	
					
				rewind(p);
				
			}
			
			fclose(p); break;        //�ر��ļ� 
		 }
		 
		 else if(po == 'n' || po == 'N')
		 {
			printf("δ����"); break;
		 }
		
		else
		{
			while(po != '\n')     //�����û��������ַ����ڻ����� 
			{
				gets(pp);
				break;	
			}
			if(els == 5)
			{
				system("cls");
				els = 0;
			}
			printf("��ѡ���Ƿ񱣴�����(Y\\N)");
			
			els ++;
			
			continue;
		}
	}

	return 0;	
	
}
