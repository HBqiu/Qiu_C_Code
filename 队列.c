#include <stdio.h>  //2024-5-6

void initialize(int *Queueing);        //初始化
int Enqueue(int *Queueing,int Tem);    //入队
int PQueueing(int *Queueing);          //打印当前第一个元素
int dequeue(int *Queueing);            //出队
void forward(int *Queueing);           //前移
int AllQueueing(int *Queueing);        //打印整个队列

#define Max 20           //队列最大长度
#define Psubscript 0     //第一个元素

static int QueueingSize; //队列最后一个元素下标

void initialize(int *Queueing) 
{

    for (int i = 0; i < Max; i++)
    {
        Queueing[i] = 0;
    }

    QueueingSize = 0;

}
int Enqueue(int *Queueing,int Tem)
{

    if (QueueingSize >= Max)
        return 401; //统一标识符 队列已满
    
    Queueing[QueueingSize] = Tem;
    QueueingSize++;

    return 0;
}
int PQueueing(int *Queueing)
{
    if(QueueingSize == 0)
        return 402; //队列为空

    printf("%d",Queueing[Psubscript]);
    
    return 0;

}
int dequeue(int *Queueing)
{

    if(QueueingSize == 0)
        return 402; 

    PQueueing(Queueing);
    
    forward(Queueing);

    QueueingSize--;
	
	return 0;

}
void forward(int *Queueing)
{
    for (int i = 0; i < QueueingSize; i++)
    {
        Queueing[i] = Queueing[i + 1];
    }
}
void Plog(int i)
{
    switch (i)
    {
    case 0:
        printf("成功");
        break;
    case 401:
        printf("队列已满");
        break;
    case 402:
        printf("队列为空");
        break;
    }
}
int AllQueueing(int *Queueing)
{

    if (!QueueingSize)
        return 402;

    for (int i = 0; i < QueueingSize; i++)
    {
        printf("%d ",Queueing[i]);
    }
    
    return 0;
    
}
int main()
{
    int Queueing[Max];
    initialize(Queueing);
    for (int i = 0; i < Max; i++)
    {
     /* code */printf("%d",Queueing[i]) ;
    }
    printf("\n");

    Enqueue(Queueing,1);
    Enqueue(Queueing,2);
    Enqueue(Queueing,3);
    Enqueue(Queueing,4);
    Enqueue(Queueing,5);
    Enqueue(Queueing,6);
    Enqueue(Queueing,7);
    Enqueue(Queueing,8);
    Enqueue(Queueing,9);
    Enqueue(Queueing,10);
    Enqueue(Queueing,11);
    Enqueue(Queueing,12);
    Enqueue(Queueing,13);
    Enqueue(Queueing,14);
    Enqueue(Queueing,15);
    Enqueue(Queueing,16);
    Enqueue(Queueing,17);
    Enqueue(Queueing,18);
    Enqueue(Queueing,19);
    Enqueue(Queueing,20);
    Enqueue(Queueing,21);
    Enqueue(Queueing,22);
    Enqueue(Queueing,23);
    Plog(Enqueue(Queueing,4));
    
    for (int i = 0; i < Max; i++)
    {
     /* code */printf("%d ",Queueing[i]) ;
    }
    printf("\n");
    
    printf("%d\n",QueueingSize);
    
    Plog(dequeue(Queueing));
    dequeue(Queueing);
    dequeue(Queueing);
    dequeue(Queueing);
    Plog(dequeue(Queueing));

	Enqueue(Queueing,2);
    Enqueue(Queueing,22);
    Enqueue(Queueing,23);
    
    printf("\n");
    
    for (int i = 0; i < Max; i++)
    {
     /* code */printf("%d ",Queueing[i]) ;
    }
    printf("\n");   

    AllQueueing(Queueing);

    return 0;
}
