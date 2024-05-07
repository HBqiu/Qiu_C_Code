#include <stdio.h>  //2024-5-6
#include <stdlib.h>

struct Queueing
{
    int element;
    struct Queueing *next;
};

typedef struct
{
    struct Queueing *head;
    struct Queueing *end;
    int QueueingSize;
} Root;

void initialize(Root *root);        // 初始化
struct Queueing *PackNode(int Tem); // 打包节点
void Enqueue(Root *root, int Tem);  // 入队
void PQueueing(Root *root);         // 打印第一个元素
void FreeNode(Root *root);          // 释放节点
void dequeue(Root *root);           // 出队
void error();                       // 错误消息
void AllQueueing(Root *root);       // 打印整个队列

void initialize(Root *root)
{
    root->head = NULL;
    root->end = NULL;
    root->QueueingSize = 0;
}
struct Queueing *PackNode(int Tem)
{
    struct Queueing *QueueingTem = NULL;

    if (!(QueueingTem = (struct Queueing *)malloc(sizeof(struct Queueing))))
        return NULL;

    QueueingTem->element = Tem;
    QueueingTem->next = NULL;

    return QueueingTem;
}
void Enqueue(Root *root, int Tem)
{
    struct Queueing *TemQueueing = PackNode(Tem);

    if (!TemQueueing)
    {
        printf("节点申请失败");
        return;
    }

    if (!root->head)
    {
        root->head = TemQueueing;
        root->end = root->head;
    }
    else
    {
        root->end->next = TemQueueing;
        root->end = root->end->next;
    }

    root->QueueingSize++;

    TemQueueing = NULL;
}
void PQueueing(Root *root)
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

    struct Queueing *Tem = root->head;
    root->head = root->head->next;

    if (!root->head)
        root->end = NULL;

    Tem->next = NULL;

    free(Tem);
}

void dequeue(Root *root)
{
    if (!root->head)
    {
        error();
        return;
    }
    PQueueing(root);
    // 释放节点
    FreeNode(root);

    root->QueueingSize--;
}
void error()
{
    printf("空队列");
}
void AllQueueing(Root *root)
{

    if(!root -> head)
    {
        error();
        return;
    }

    struct Queueing *Tem = root -> head;

    while (Tem)
    {
        /* code */ printf("%d ", Tem->element);
        Tem = Tem->next;
    }
}
int main()
{
    Root tem;
    initialize(&tem);
    for (int i = 0; i < 5; i++)
    {
        /* code */ Enqueue(&tem, i);
    }

    dequeue(&tem);
    dequeue(&tem);
    dequeue(&tem);
    dequeue(&tem);
    dequeue(&tem);
    dequeue(&tem);

    Enqueue(&tem, 1);
    Enqueue(&tem, 2);
    Enqueue(&tem, 3);

    dequeue(&tem);
    //dequeue(&tem);
    //dequeue(&tem);
    //dequeue(&tem);

    struct Queueing *Tema = tem.head;
    while (Tema)
    {
        /* code */ printf("%d ", Tema->element);
        Tema = Tema->next;
    }
    printf("\n%d\n", tem.QueueingSize);

    printf("%#X ", tem.end);
    printf("%#X \n", tem.head);

    AllQueueing(&tem);

    return 0;
}
