#include <stdio.h>
#include <string.h>
int main() 
{
	char aa[1000];
	int b[26] = {};
	scanf("%s",aa);
	int aaa = strlen(aa);
	for( int a = 0; a < aaa; a++)
	{
		b[aa[a] - 'a']++;
	}
	int bb = 0;
	for(int a = 1; a < 26; a++)
	{
		if(b[a] > b[bb])
		bb = a;
	}	
	printf("�����ַ�������\"%c\" ���ִ��� \"%d\"",bb + 'a',b[bb]);
}
