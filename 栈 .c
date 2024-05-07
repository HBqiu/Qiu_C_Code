#include <stdio.h>   //2024-5-7

#define Max 20

static int StackTop; //栈顶

void Initialize(int *Stack);        // 初始化
void InStack(int *Stack,int Tem);   // 入栈
void Pop(int *Stack);              // 出栈
void AllStack(int *Stack);          // 打印栈所有元素
void PStackTop(int *Stack);         // 打印栈顶元素

void Initialize(int *Stack)
{

    for (int i = 0; i < Max; i++)
    {
        Stack[i] = 0;
    }
    
    StackTop = -1;
    
}
void InStack(int *Stack,int Tem)
{

    if(StackTop >= Max - 1)
    {
        printf("ERREO\n");
        return;
    }

    Stack[++StackTop] = Tem;

}
void Pop(int *Stack)
{

    if (StackTop < 0)
    {
        printf("ERREO\n");
        return;
    }

    PStackTop(Stack);
    
    Stack[StackTop--] = 0;
    
}
void AllStack(int *Stack)
{

    for (int i = 0; i <= StackTop; i++)
    {
        printf("%d ",Stack[i]);
    }

    printf("\n");
    
}
void PStackTop(int *Stack)
{

    if(StackTop < 0)
    {
        printf("ERROR\n");
        return;
    }

    printf("%d \n",Stack[StackTop]);

}
int main()
{
    int Stack[Max];
    Initialize(Stack);

    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    InStack(Stack,1);
    InStack(Stack,2);
    InStack(Stack,3);
    

    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    Pop(Stack);
    for (int i = 0; i < Max; i++)
    {
        /* code */printf("%d ",Stack[i]);
    }
    printf("\n%d\n",StackTop);
    
    AllStack(Stack);

    PStackTop(Stack);

    Pop(Stack);
    
    AllStack(Stack);
    
    return 0;
}