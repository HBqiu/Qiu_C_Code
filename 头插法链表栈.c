#include <stdio.h>  //2024-5-7
#include <stdlib.h>

struct Stack
{
    int element;
    struct Stack *next;
};

typedef struct
{
    struct Stack *head;
    int StackTop;
} Root;

void initialize(Root *root);        // 初始化
struct Stack *PackNode(int Tem);    // 打包节点
void InStack(Root *root, int Tem);  // 入栈
void PStack(Root *root);            // 打印第一个元素
void FreeNode(Root *root);          // 释放节点
void Pop(Root *root);               // 出队
void error();                       // 错误消息
void AllStack(Root *root);          // 打印整个队列

void initialize(Root *root)
{
    root->head = NULL;
    root->StackTop = -1;
}
struct Stack *PackNode(int Tem)
{
    struct Stack *StackTem = NULL;

    if (!(StackTem = (struct Stack *)malloc(sizeof(struct Stack))))
        return NULL;

    StackTem->element = Tem;
    StackTem->next = NULL;

    return StackTem;
}
void InStack(Root *root, int Tem)
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
    }
    else
    {
        TemStack -> next = root -> head;
        root -> head = TemStack;
    }

    root->StackTop++;

    TemStack = NULL;
}
void PStack(Root *root)
{

    if (!root->head)
    {
        error();
        return;
    }

    printf("\n\n%d\n\n", root->head->element);
}
void FreeNode(Root *root)
{

    if (!root->head)
    {
        error();
        return;
    }

    struct Stack *Tem = root->head;
    root->head = root->head->next;

    Tem->next = NULL;

    free(Tem);
}

void Pop(Root *root)
{
    if (!root->head)
    {
        error();
        return;
    }
    PStack(root);
    // 释放节点
    FreeNode(root);

    root->StackTop--;
}
void error()
{
    printf("空");
}
void AllStack(Root *root)
{

    if(!root -> head)
    {
        error();
        return;
    }

    struct Stack *Tem = root -> head;

    while (Tem)
    {
        /* code */ printf("%d ", Tem->element);
        Tem = Tem->next;
    }
}
int main()
{
    Root tem;
    tem.head = NULL;

    InStack(&tem,1);
    InStack(&tem,2);
    InStack(&tem,3);
    
    Pop(&tem);
    Pop(&tem);
    Pop(&tem);

    InStack(&tem,1);
    InStack(&tem,2);
    InStack(&tem,3);
    Pop(&tem);
    Pop(&tem);
    Pop(&tem);
    Pop(&tem);


    printf("\n");

    AllStack(&tem);
    return 0;
}
