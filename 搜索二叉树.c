#include <stdio.h>
#include <stdlib.h>

struct tree
{

    int element;

    struct tree *left;
    struct tree *right;

};
typedef struct
{

    struct tree *TreeRoot;

}Root;             

struct tree *PackNode(int Tem);                         // 打包节点
void AddNode(Root *root,int Tem);                       // 添加节点
void Judge(Root *root,struct tree *Tem);                // 插入节点
void PTree(struct tree *Tem);                           // 前序打印
struct tree *DeleteNode(struct tree *Node,int Tem);     // 删除节点
 
struct tree *PackNode(int Tem)
{

    struct tree *TemTreeNode;

    if (!(TemTreeNode = (struct tree *)malloc(sizeof(struct tree))))
        return NULL;
    
    TemTreeNode -> element = Tem;
    TemTreeNode -> left = NULL;
    TemTreeNode -> right = NULL;

    return TemTreeNode;
    
}
void AddNode(Root *root,int Tem)
{
    struct tree *TemTreeNode = PackNode(Tem);

    if(!TemTreeNode)
    {
        return;
    }

    if (!root -> TreeRoot)
    {
        root -> TreeRoot = TemTreeNode;
    }
    else
    {
        //判断插入
        Judge(root,TemTreeNode);
    }

}
void Judge(Root *root,struct tree *Tem)
{

    struct tree *TemTree = root -> TreeRoot;

    while (TemTree)
    {

       if (Tem -> element > TemTree -> element)
       {

            if (!TemTree -> right)
            {
                TemTree -> right = Tem;
                return;
            }
            else
                TemTree = TemTree -> right;
        
       }
       else if(Tem -> element < TemTree -> element)
       {

            if (!TemTree -> left)
            {
                TemTree -> left = Tem;
                return;
            }
            else
                TemTree = TemTree -> left;
        
       }
       
    }

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
struct tree *DeleteNode(struct tree *Node,int Tem)
{

    if (!Node)
    {
        return NULL;
    }

    if (Node -> element < Tem)
    {
        Node -> right = DeleteNode(Node -> right,Tem);
        return Node;
    }
    else if (Node -> element > Tem)
    {
        Node -> left = DeleteNode(Node -> left,Tem);
        return Node;
    }
    else if (Node -> element == Tem)
    {
        //左右都为空时
        if (!Node -> left && !Node -> right)
        {

            struct tree *Temp = Node;
            free(Node);
            Temp = NULL;
            return Temp;

        }
        else if (!Node -> left) //左为空时
        {

            struct tree *Temp = Node -> right;
            free(Node);
            return Temp;

        }
        else if (!Node -> right) //右为空时
        {

            struct tree *Temp = Node -> left;
            free(Node);
            return Temp;

        }
        else if (Node -> right && Node -> left)  //左右都有孩子时 方法一右边节点插入到左边最大的节点上 左边节点代替删除节点
        {
            struct tree *Temp = Node -> left;

            while (Temp -> right)
            {
                Temp = Temp -> right;
            }
            
            Temp -> right = Node -> right;

            struct tree *T = Node -> left;
            Node -> right = NULL;

            free(Node);

            return T;
        }
        /* else if (Node -> right && Node -> left)  //左右都有孩子时 方法二左边节点插入到右边最小的节点上 右边节点代替删除节点
        {
            struct tree *Temp = Node -> right;

            while (Temp -> left)
            {
                Temp = Temp -> left;
            }
            
            Temp -> left = Node -> left;

            struct tree *T = Node -> right;
            Node -> left = NULL;

            free(Node);

            return T;
        } */
    }

    return Node;

}
int main()
{
    Root tem;
    tem.TreeRoot = NULL;
    AddNode(&tem,10);
    AddNode(&tem,9);
    AddNode(&tem,6);
    AddNode(&tem,7);
    AddNode(&tem,1);
    AddNode(&tem,12);
    AddNode(&tem,3);
    AddNode(&tem,4);
    AddNode(&tem,100);
    AddNode(&tem,19);

    tem.TreeRoot = DeleteNode(tem.TreeRoot,6); //删除第一个元素与要更新头节点

    PTree(tem.TreeRoot);
    return 0;

}