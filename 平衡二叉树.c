#include <stdio.h>
#include <stdlib.h>

#define true	1
#define false	0

struct tree
{

    int element;
    int treeHigh;

    struct tree *left;
    struct tree *right;

};
typedef struct
{

    struct tree *TreeRoot;

}Root;             

struct tree *PackNode(int Tem);                         // 打包节点
struct tree *AddNode(struct tree *root,int Tem);        // 添加节点
void PTree(struct tree *Tem);                           // 前序打印
void FindVal(Root *root,int val);                       // 查找元素
int Find(Root *root,int val);                           // 查找实现
int Max(int a,int b);                                   // 返回最大值
int getHigh(struct tree *Node);                         // 得到树高
int getBalance(struct tree *Tem);                       // 得到平衡因子
struct tree *leftRotate(struct tree *Tem);              // 右旋
struct tree *rightRotate(struct tree *Tem);             // 左旋
void middleTree(struct tree *Tem);                      // 中序打印
struct tree *DeleteNode(struct tree *root,int val);     // 删除节点

struct tree *PackNode(int Tem)
{

    struct tree *TemTreeNode;

    if (!(TemTreeNode = (struct tree *)malloc(sizeof(struct tree))))
        return NULL;
    
    TemTreeNode -> element = Tem;
    TemTreeNode -> treeHigh = 1;
    TemTreeNode -> left = NULL;
    TemTreeNode -> right = NULL;

    return TemTreeNode;
    
}
struct tree *AddNode(struct tree *root,int Tem)
{
    if (!root)
        return PackNode(Tem);


    if (Tem > root -> element)
    {
        root -> right = AddNode(root -> right,Tem);
    }
    else if (Tem < root -> element)
    {
        root -> left = AddNode(root -> left,Tem);
    }
    else
        return root;

    //更新树高
    root -> treeHigh = Max(getHigh(root -> left),getHigh(root -> right)) + 1;
    
    //获取平衡因子
    int balance = getBalance(root);
    
    //LL失衡
    if (balance == 2 && getBalance(root -> left) == 1)
        return rightRotate(root);

    //LR失衡
    if (balance == 2 && getBalance(root -> left) == -1)
    {
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    
    //RR失衡
    if (balance == -2 && getBalance(root -> right) == -1)
    {
        return leftRotate(root);
    }
    
    //RL失衡
    if (balance == -2 && getBalance(root -> right) == 1)
    {
        root -> right = rightRotate(root ->right);
        return leftRotate(root);
    }
    
    return root;
}
void PTree(struct tree *Tem)
{
    if (!Tem)
    {
        return;
    }
    
    printf("%d ",Tem -> element); 
    PTree(Tem -> left);
    PTree(Tem -> right);

}
void middleTree(struct tree *Tem)
{
    if (!Tem)
    {
        return;
    }
    
    middleTree(Tem -> left);
    printf("%d ",Tem -> element); 
    middleTree(Tem -> right);

}
int Find(Root *root,int val)
{

    struct tree *Tem = root -> TreeRoot;

    while (Tem)
    {

        if (Tem -> element == val)
        {
            return true;
        }
        else if (Tem -> element > val)
        {
            Tem = Tem -> left;
        }
        else 
            Tem = Tem -> right;
    
    }
    
    return false;

}
void FindVal(Root *root,int val)
{
    if (!root -> TreeRoot)
    {
        return ;
    }

    if (Find(root,val))
    {
        printf("1 ");
    }
    else 
        printf("0 ");

    return ;
    
}
int Max(int a,int b)
{
    return a > b ? a : b;
}
int getHigh(struct tree *Node)
{
    return Node ? Node -> treeHigh : 0;
}
struct tree *leftRotate(struct tree *Tem)
{

    struct tree *NewNode = Tem -> right;
    Tem -> right = NewNode -> left;
    NewNode -> left = Tem;

    //更新树高
    NewNode -> treeHigh = Max(getHigh(NewNode -> left),getHigh(NewNode -> right)) + 1;
    Tem -> treeHigh = Max(getHigh(Tem -> left),getHigh(Tem -> right)) + 1;
    
    return NewNode;
}
struct tree *rightRotate(struct tree *Tem)
{

    struct tree *NewNode = Tem -> left;
    Tem -> left = NewNode -> right;
    NewNode -> right = Tem;

    //更新树高
    NewNode -> treeHigh = Max(getHigh(NewNode -> left),getHigh(NewNode -> right)) + 1;
    Tem -> treeHigh = Max(getHigh(Tem -> left),getHigh(Tem -> right)) + 1;
    
    return NewNode;
}
int getBalance(struct tree *Tem)
{
    return getHigh(Tem -> left) - getHigh(Tem -> right);
}
struct tree *DeleteNode(struct tree *root,int val)
{

    //删除逻辑普通搜索树的删除
    if (!root)
        return root;

    if (root -> element > val)
    {
        root -> left = DeleteNode(root -> left,val);   
    }
    else if (root -> element < val)
    {
        root -> right = DeleteNode(root -> right,val);
    }
    else if (root -> element == val)
    {
        //左右都没有孩子
        if (!root -> left && !root -> right)
        {
            struct tree *Tem = root;
            root = NULL;
            free(Tem);
        }
        //有一个孩子 左
        else if (!root -> left)
        {
            struct tree *Tem = root;
            root = root -> left;
            free(Tem);
        }
        //有一个还在 右
        else if (!root -> right)
        {
            struct tree *Tem = root;
            root = root -> right;
            free(Tem);
        }
        //左右都有孩子
        else
        {
           /*  struct tree *Tem = root -> right;

            while (Tem -> left)
            {
                Tem = Tem -> left;
            }

            root -> element = Tem -> element;

            root -> right = DeleteNode(root -> right,Tem -> element);  */

            struct tree *Tem = root -> left;
            while (Tem -> right)
            {
                Tem = Tem -> right;
            }
            Tem -> right = root -> right;

            root = root -> left;
        }
    }

        if (!root)
        {
            return root;
        }
        //更新树高
        root -> treeHigh = Max(getHigh(root -> left),getHigh(root -> right)) + 1;
        
        //获取平衡因子
        int balance = getBalance(root);
        
        //LL失衡   和插入唯一不同的就是LL RR失衡的子树的平衡因子有可能等于0
        if (balance > 1 && getBalance(root -> left) >= 0)
            return rightRotate(root);

        //LR失衡
        if (balance > 1 && getBalance(root -> left) < 0)
        {
            root -> left = leftRotate(root -> left);
            return rightRotate(root);
        }
        
        //RR失衡
        if (balance < -1 && getBalance(root -> right) <= 0)
        {
            return leftRotate(root);
        }
        
        //RL失衡
        if (balance < -1 && getBalance(root -> right) > 0)
        {
            root -> right = rightRotate(root ->right);
            return leftRotate(root);
        }
        
        return root;
}
int main()
{
    Root tem;
    tem.TreeRoot = NULL;

    for (int i = 1; i < 8; i++)
    {
        tem.TreeRoot = AddNode(tem.TreeRoot,i * 10);
    }

    printf("-------------前序打印----------------\n");
    PTree(tem.TreeRoot);
    printf("\n-------------中序打印----------------\n");
    middleTree(tem.TreeRoot);
    printf("\n");
    
    tem.TreeRoot = DeleteNode(tem.TreeRoot,10);
    tem.TreeRoot = DeleteNode(tem.TreeRoot,20);
    tem.TreeRoot = DeleteNode(tem.TreeRoot,30);

    printf("-------------前序打印----------------\n");
    PTree(tem.TreeRoot);
    printf("\n-------------中序打印----------------\n");
    middleTree(tem.TreeRoot);
    printf("\n");
    /* for (int i = 0; i < 10; i++)
    {
        FindVal(&tem,i);
    }
    printf("\n");
    
    printf("treeHigh:%d \n",getHigh(tem.TreeRoot)); //根节点的树高就是这个树的深度
    
    printf("treeHigh:%d \n",tem.TreeRoot -> treeHigh); //直接查看根节点树高
 */
    return 0;

}