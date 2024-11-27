#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 4
typedef struct
{
    char *cmd;
    void (*p)(int i, int y);

} CMD;

void XQADD(int i, int y);
void XQSUB(int i, int y);
void XQMUL(int i, int y);
void XQDIV(int i, int y);
void Print();
CMD cmds[MAX] = {
    {
        "ADD",
        XQADD
    },
    {
        "SUB",
        XQSUB  //如何这个函数返回值为int类型，可以强制转化为（void (*)(int, int)）类型。调用时再强制转为（int (*)(int, int)）
    },
    {
        "MUL",
        XQMUL
    },
    {
        "DIV",
        XQDIV
    }};
int main(int argc, char *argv[], char *argg[])
{
    /* int c = 0;
    while (argg[c])
    {
         printf("%s\n",argg[c++]);

    } */
    
    if (argc != 4)
    {
        Print();
    }
    else
    {

        for (int i = 0; i < MAX; i++)
        {
            
            if (!strcmp(strupr(argv[1]), cmds[i].cmd))
            {
                cmds[i].p(atoi(argv[2]), atoi(argv[3]));
                return 0;
            }

        }

        printf("命令不存在");
    }

    return 0;
}
void XQADD(int i, int y)
{
    printf("%d + %d = %d", i, y, i + y);
}
void XQSUB(int i, int y)
{
    printf("%d - %d = %d", i, y, i - y);
}
void XQMUL(int i, int y)
{
    printf("%d * %d = %d", i, y, i * y);
}
void XQDIV(int i, int y)
{
    printf("%d / %d = %d", i, y, i / y);
}
void Print()
{
    printf("XQ ADD <num> <mum>\n");
    printf("XQ SUB <num> <mum>\n");
    printf("XQ NUL <num> <mum>\n");
    printf("XQ DIV <num> <mum>");
}
