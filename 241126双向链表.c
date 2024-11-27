#include <stdio.h>
#include <stdlib.h>
struct list
{
    int data;
    struct list *next;
    struct list *up;
};
typedef struct
{
    /* data */
    struct list *root;
    struct list *exit;
}ROOT;
void init(ROOT *R)
{
    R -> root = NULL;
    R -> exit = NULL; 
}
struct list *node(int R)
{
    struct list *Tem = NULL;
    if(!(Tem = (struct list*)malloc(sizeof(struct list))))
    {
        return NULL;
    }
    Tem -> data = R;
    Tem -> next = NULL;
    Tem -> up = NULL;

    return Tem;
}
void danode(int num,ROOT *R)
{
    struct list *newtem = node(num); 
    if (!newtem)
        return ;
    
    if(!R -> root)
    {
        R -> root = newtem;
        R -> exit = R -> root;
        return ;
    }

    R -> exit -> next = newtem;
    newtem -> up = R -> exit;
    R -> exit = newtem;
    return ;
}
int main()
{
    ROOT Temlist;
    init(&Temlist);
    for (size_t i = 0; i < 10; i++)
    {
        danode(i,&Temlist);
        /* code */
    }
    struct list *tem = Temlist.root;
    printf("root:%p\texit:%p\n",Temlist.root,Temlist.exit);
    while (tem)
    {
        /* code */
        printf("数字：%d\t上个地址：%16p\t地址：%p\n",tem -> data,tem -> up,tem);
        tem = tem ->next;
    }
    
    
    return 0;
}
