#include <stdio.h>
#include <stdlib.h>

/*
13.�������������չ���н����������Ĵ洢�ṹ
14.�������������򡢺�������ĵݹ��㷨
15.��������������ķǵݹ��㷨
16.��������α����ķǵݹ��㷨
17.������������(�������)
18.�������Ĵ洢�ṹ
19.���������
*/

#define MAX_SIZE 100
#define stacksize 100
#define MAX_TREE_SIZE 100

typedef struct BiTNode  //������
{
	int data;
	struct BiTNode *lchild, *rchild;  //���Һ���ָ��
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

int Push(Stack &S, BiTree e)   //�򻯵�ѹջ����
{
	*S.top++ = *e;
	return 1;
}

int Pop(Stack &S, BiTree &e)  //��ջ
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

int CreatBiTree(BiTree &T)   //������������
{
	int ch;
	printf("�������ݣ���0Ϊ�գ�\n");
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

int PreOrderTraverse(BiTree T, int(*Visit)(int e))  //�������
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

int InOrderTraverse(BiTree T, int(*Visit)(int e))  //�������
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

int PostOrderTraverse(BiTree T, int(*Visit)(int e))  //�������
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

int InOrderTraverse_(BiTree T, int(*Visit)(int e))  //�������  �ǵݹ�
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

int LevelTraverse(BiTree T, int level) //����
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

int Depth(BiTree T)						//���
{
	int depth;
	int depth_l, depth_r;
	if (!T)             //������������ڵ�Ϊ�գ������Ϊ0  
		depth = 0;
	else
	{
		depth_l = Depth(T->lchild);					//�����������  
		depth_r = Depth(T->rchild);					//�����������  
		depth = 1 + (depth_l>depth_r ? depth_l : depth_r);		//��=max�����ң�+1
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

int DepthCSTree(CSNode *T)			//�����
{
	if (!T)
		return 0;
	else
		return (DepthCSTree(T->firstchild) + 1) > DepthCSTree(T->nextsibling) ? DepthCSTree(T->firstchild) + 1 : DepthCSTree(T->nextsibling);

}

CSTree GetTreeNode(int c)			//�������ڵ�
{
	CSTree C;
	C = (CSTree)malloc(sizeof(CSNode));
	C->data = c;
	C->firstchild = NULL;
	C->nextsibling = NULL;
	return C;
}

CSTree CreateTree(CSTree &T)		//���Ĵ洢�ṹ
{
	int ch, fa;
	LinkQueue Q;
	InitQueue(Q);
	CSTree p, r, s;
	p = (CSTree)malloc(sizeof(CSNode));
	r = (CSTree)malloc(sizeof(CSNode));
	s = (CSTree)malloc(sizeof(CSNode));
	printf("��������(��ĸ ����) -1Ϊ��\n");
	scanf("%d %d", &fa, &ch);
	while (ch != -1)
	{
		p = GetTreeNode(ch);    //�������
		p = EnQueue(Q, p);      //���
		if (fa == -1)
			T = p;           //��˫��Ϊ�գ�������Ϊ���ڵ�
		else
		{
			s = GetHead(Q, s); //ȡ��ͷ
			while (s->data != fa)    //ѭ���������ҵ�˫�׽ڵ�
			{
				s = DeQueue(Q, s);
				s = GetHead(Q, s);
			}
			if (!(s->firstchild))    //��û�к��ӣ����ڴ˴�
			{
				s->firstchild = p;
				r = p;
			}
			else                      //�к��ӣ������ֵܴ�
			{
				r->nextsibling = p;
				r = p;
			}
		}
		getchar();
		printf("��������(��ĸ ����) -1Ϊ��\n");
		scanf("%d %d", &fa, &ch);
	}
	return T;
}

void Preorder(CSTree T) //�������
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
	printf("������������\n");
	CreatBiTree(T);
	printf("\n���������\n");
	PreOrderTraverse(T, Visit);
	printf("\n���������\n");
	InOrderTraverse(T, Visit);
	printf("\n���������\n");
	PostOrderTraverse(T, Visit);
	printf("\n�ǵݹ����������\n");
	InOrderTraverse_(T, Visit);
	printf("\n���������\n");
	Level(T);
	printf("\n���������Ϊ��%d\n",Depth(T));

	CSTree TT;
	printf("\n��������\n");
	CreateTree(TT);
	printf("\n��ʾ���������������\n");
	Preorder(TT);
	printf("\n�������Ϊ��%d\n",DepthCSTree(TT));
	
	return 0;
}