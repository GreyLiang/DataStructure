#include <stdio.h>
#include <stdlib.h>

/*
13.按先序遍历的扩展序列建立二叉树的存储结构
14.二叉树先序、中序、后序遍历的递归算法
15.二叉树中序遍历的非递归算法
16.二叉树层次遍历的非递归算法
17.求二叉树的深度(后序遍历)
18.建立树的存储结构
19.求树的深度
*/

#define MAX_SIZE 100
#define stacksize 100
#define MAX_TREE_SIZE 100

typedef struct BiTNode  //二叉树
{
	int data;
	struct BiTNode *lchild, *rchild;  //左右孩子指针
}BiTNode, *BiTree;

typedef struct
{
	BiTNode *base;
	BiTNode *top;
	int size;
}Stack;

Stack S;

int InitStack(Stack &S)
{
	S.base = (BiTNode*)malloc(stacksize * sizeof(BiTNode));
	if (!S.base)exit(0);
	S.top = S.base;
	S.size = stacksize;
	return 1;
}

int Push(Stack &S, BiTree e)   //简化的压栈操作
{
	*S.top++ = *e;
	return 1;
}

int Pop(Stack &S, BiTree &e)  //出栈
{
	if (S.top == S.base)
		return 0;
	e = --S.top;
	return 1;
}

int StackEmpty(Stack S)
{
	if (S.base == S.top)
		return 1;
	return 0;
}

int CreatBiTree(BiTree &T)   //先序建立二叉树
{
	int ch;
	printf("输入数据：（0为空）\n");
	scanf("%d", &ch);
	if (ch == 0)
		T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(0);
		T->data = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
	return 1;
}

int Visit(int e)
{
	printf("%d ", e);
	return 1;
}

int PreOrderTraverse(BiTree T, int(*Visit)(int e))  //先序遍历
{
	if (T)
	{
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit))
					return 1;
		return 0;
	}
	else
		return 1;
}

int InOrderTraverse(BiTree T, int(*Visit)(int e))  //中序遍历
{
	if (T)
	{
		if (InOrderTraverse(T->lchild, Visit))
			if (Visit(T->data))
				if (InOrderTraverse(T->rchild, Visit))
					return 1;
		return 0;
	}
	else
		return 1;
}

int PostOrderTraverse(BiTree T, int(*Visit)(int e))  //后序遍历
{
	if (T)
	{
		if (PostOrderTraverse(T->lchild, Visit))
			if (PostOrderTraverse(T->rchild, Visit))
				if (Visit(T->data))
					return 1;
		return 0;
	}
	else
		return 1;
}

int InOrderTraverse_(BiTree T, int(*Visit)(int e))  //中序遍历  非递归
{
	Stack S;
	InitStack(S);
	BiTree p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			if (!Visit(p->data))
				return 0;
			p = p->rchild;
		}
	}
	return 1;
}

int LevelTraverse(BiTree T, int level) //层序
{
	if (!T || level < 0)
		return 0;
	if (level == 0)
	{
		printf("%d ", T->data);
		return 1;
	}
	return LevelTraverse(T->lchild, level - 1) + LevelTraverse(T->rchild, level - 1);
}

void Level(BiTree T)
{
	int i = 0;
	for (i = 0; ; i++)
		if (!LevelTraverse(T, i))
			break;
}

int Depth(BiTree T)						//深度
{
	int depth;
	int depth_l, depth_r;
	if (!T)             //如果二叉树根节点为空，则深度为0  
		depth = 0;
	else
	{
		depth_l = Depth(T->lchild);					//左子树的深度  
		depth_r = Depth(T->rchild);					//右子树的深度  
		depth = 1 + (depth_l>depth_r ? depth_l : depth_r);		//根=max（左，右）+1
	}
	return depth;
}

typedef struct CSNode						
{
	int data;
	struct CSNode * firstchild, *nextsibling;
}CSNode, *CSTree;

typedef struct
{
	CSTree *elem;
	int front;
	int rear;
}LinkQueue;

void InitQueue(LinkQueue &Q)
{
	Q.elem = ((CSTree*)malloc(MAX_SIZE * sizeof(CSNode)));
	Q.front = Q.rear = 0;
}

CSTree EnQueue(LinkQueue &Q, CSNode *p)
{
	if (Q.front == Q.rear)
		Q.elem[Q.front] = p;
	Q.rear++;
	Q.elem[Q.rear] = p;
	return p;
}

CSTree DeQueue(LinkQueue &Q, CSNode *p)
{
	p = Q.elem[Q.front];
	Q.front++;
	return p;
}

CSTree GetHead(LinkQueue Q, CSNode *p)
{
	if (Q.rear != Q.front)
		p = (Q.elem[Q.front]);
	else
		p = NULL;
	return p;
}

int DepthCSTree(CSNode *T)			//树深度
{
	if (!T)
		return 0;
	else
		return (DepthCSTree(T->firstchild) + 1) > DepthCSTree(T->nextsibling) ? DepthCSTree(T->firstchild) + 1 : DepthCSTree(T->nextsibling);

}

CSTree GetTreeNode(int c)			//创建根节点
{
	CSTree C;
	C = (CSTree)malloc(sizeof(CSNode));
	C->data = c;
	C->firstchild = NULL;
	C->nextsibling = NULL;
	return C;
}

CSTree CreateTree(CSTree &T)		//树的存储结构
{
	int ch, fa;
	LinkQueue Q;
	InitQueue(Q);
	CSTree p, r, s;
	p = (CSTree)malloc(sizeof(CSNode));
	r = (CSTree)malloc(sizeof(CSNode));
	s = (CSTree)malloc(sizeof(CSNode));
	printf("输入树：(父母 孩子) -1为空\n");
	scanf("%d %d", &fa, &ch);
	while (ch != -1)
	{
		p = GetTreeNode(ch);    //创建结点
		p = EnQueue(Q, p);      //入队
		if (fa == -1)
			T = p;           //若双亲为空，则所建为根节点
		else
		{
			s = GetHead(Q, s); //取队头
			while (s->data != fa)    //循环遍历，找到双亲节点
			{
				s = DeQueue(Q, s);
				s = GetHead(Q, s);
			}
			if (!(s->firstchild))    //若没有孩子，放在此处
			{
				s->firstchild = p;
				r = p;
			}
			else                      //有孩子，放在兄弟处
			{
				r->nextsibling = p;
				r = p;
			}
		}
		getchar();
		printf("输入树：(父母 孩子) -1为空\n");
		scanf("%d %d", &fa, &ch);
	}
	return T;
}

void Preorder(CSTree T) //先序遍历
{
	if (T)
	{
		printf("%d ", T->data);
		Preorder(T->firstchild);
		Preorder(T->nextsibling);
	}
}

int main()
{
	BiTree T;
	printf("创建二叉树：\n");
	CreatBiTree(T);
	printf("\n先序遍历：\n");
	PreOrderTraverse(T, Visit);
	printf("\n中序遍历：\n");
	InOrderTraverse(T, Visit);
	printf("\n后序遍历：\n");
	PostOrderTraverse(T, Visit);
	printf("\n非递归中序遍历：\n");
	InOrderTraverse_(T, Visit);
	printf("\n层序遍历：\n");
	Level(T);
	printf("\n二叉树深度为：%d\n",Depth(T));

	CSTree TT;
	printf("\n创建树：\n");
	CreateTree(TT);
	printf("\n显示树（先序遍历）：\n");
	Preorder(TT);
	printf("\n树的深度为：%d\n",DepthCSTree(TT));
	
	return 0;
}