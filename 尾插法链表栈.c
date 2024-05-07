#include <stdio.h>   //2024-5-7
#include <stdlib.h>

struct Stack
{
    int element;
    struct Stack *next;
    struct Stack *last;
};
typedef struct 
{
    struct Stack *head;
    struct Stack *end;
    int StackTop;
}Root;

void initialize(Root *root);      // 初始化
struct Stack *PackNode(int Tem);  // 打包节点
void InStack(Root *root,int Tem); // 入栈
void Pop(Root *root);             // 出栈
void PStackTop(Root *root);       // 打印栈顶
void FreeNode(Root *root);        // 释放节点
void AllStack(Root *root);        // 显示整个栈元素

void initialize(Root *root)
{
    root->head = NULL;
    root->end = NULL;
    root->StackTop = -1;
}
struct Stack *PackNode(int Tem)
{
    struct Stack *StackTem = NULL;

    if (!(StackTem = (struct Stack *)malloc(sizeof(struct Stack))))
        return NULL;

    StackTem->element = Tem;
    StackTem->next = NULL;
    StackTem -> last = NULL;

    return StackTem;
}
void InStack(Root *root,int Tem)
{
    struct Stack *TemStack = PackNode(Tem);

    if (!TemStack)
    {
        printf("节点申请失败");
        return;
    }

    if (!root->head)
    {
        root->head = TemStack;
        root->end = root->head;
    }
    else
    {
        root->end->next = TemStack;
        TemStack -> last = root -> end;
        root->end = root->end->next;
    }

    root->StackTop++;

    TemStack = NULL;
}

void Pop(Root *root)
{

    if(!root -> head)
    {
        return;
    }

    //打印
    PStackTop(root);

    FreeNode(root);

}
void PStackTop(Root *root)
{
    
    if(!root -> head)
    {
        return;
    }

    printf("%d ",root -> end -> element);

}
void FreeNode(Root *root)
{

    struct Stack *Tem;

    Tem = root -> end;
    Tem -> element = 0;
    
    root -> end = root -> end -> last;
   	
    if(!root -> end)
        root -> head = NULL;
    else
        root -> end -> next = NULL;
        
    root -> StackTop--;

    free(Tem);

}
void AllStack(Root *root)
{
    
    if (!root -> head)
    {
        return;       
    }
    
    struct Stack *Tem = root -> head;

    while (Tem)
    {
        printf("%d ",Tem -> element);
        Tem = Tem -> next;
    }
    
}
int main()
{
    Root tem;
    tem.head = NULL;

    initialize(&tem);

    InStack(&tem,1);
    InStack(&tem,2);
    InStack(&tem,3);

    Pop(&tem);
    Pop(&tem);
    Pop(&tem);
    printf("\n%#X ",tem.end);
    printf("\n%#X ",tem.head);
    
    InStack(&tem,3);
    InStack(&tem,1);
    InStack(&tem,2);
    Pop(&tem);
    Pop(&tem);
    Pop(&tem);

    printf("\n%d ",tem.StackTop);
    printf("\n%#X ",tem.end);
    printf("\n%#X ",tem.head);

    InStack(&tem,1);
    InStack(&tem,2);

    Pop(&tem);

    printf("\n%d ",tem.StackTop);

    printf("\n%#X ",tem.end);
    printf("\n%#X ",tem.head);

    PStackTop(&tem);

    InStack(&tem,1);
    PStackTop(&tem);
    InStack(&tem,2);
    PStackTop(&tem);

    printf("\n");

    AllStack(&tem);

    printf("\n%#X ",tem.end);
    printf("\n%#X ",tem.head);
}
