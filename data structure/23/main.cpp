
#include <stdio.h>
#include <stdlib.h>

/*
23.
���һ������һ����������һ�Ŷ����������ĳ���
�Ӷ�����������ɾ��һ����㣬
ʹ�ö������Ա��ֶ��������������ԡ�
*/

typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;  //���Һ���ָ��
}BiTNode, *BiTree;

int SearchBST(BiTree T, int key, BiTree f, BiTree &p)
{
//	printf("���ʣ�%d,chazhao:%d", T->data,key);
	if (T == NULL)
	{
		p = f;
		return false;
	}
	else
		if (key == T->data)
		{
			p = T;
			return true;
		}
		else
			if (key < T->data)
				return SearchBST(T->lchild, key, T, p);  //�������м�������
			else 
				return SearchBST(T->rchild, key, T, p);  //�������м�������
}

int Visit(int e)
{
	printf("%d ", e);
	return 1;
}

int PreOrderTraverse(BiTree T, int(*Visit)(int e))
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

int InsertBST(BiTree &T, int e)
{
	BiTree p = (BiTree)malloc(sizeof(BiTNode));
	if (!SearchBST(T, e, NULL, p))  //���Ҳ��ɹ�
	{
		printf("���룺%d\n", e);
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = NULL;
		s->rchild = NULL;

		if (p==NULL)
			T = s;
		else 
			if (e < p->data)
			{
				printf("insert to %d left:%d\n",p->data,e);
				p->lchild = s;
			}
			else
			{
				printf("insert to %d right:%d\n", p->data, e);
				p->rchild = s;
			}return true;
	}
	else 
		printf("�Ѵ���:%d\n",e);
	return false;
}

bool Delete(BiTree &p) {
	BiTree q, s;
	q = (BiTree)malloc(sizeof(BiTNode));
	s = (BiTree)malloc(sizeof(BiTNode));
	if (!q || !s)
		exit(0);
	if (!p->lchild) {
		q = p;
		p = p->rchild;
		free(q);
	}
	else if (!p->rchild) {
		q = p;
		p = p->lchild;
		free(q);
	}
	else {
		q = p;
		s = p->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;
		}
		p->data = s->data;
		if (q != p)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		delete s;
	}
	return true;
}

int DeleteBST(BiTree &T, int key) {
	if (!T)
		return false;
	else {
		if (key == T->data)
			return Delete(T);
		if (key < T->data)
			return DeleteBST(T->lchild, key);
		if (key >= T->data)
			return DeleteBST(T->rchild, key);
	}
}

int main()
{
	BiTree T = (BiTree)malloc(sizeof(BiTNode));
	T = NULL;
//	int a[] = {9,2,7,4,5,6,3,8,9};

	int a[100];
	printf("�������鳤�ȣ�\n");
	int len;
	scanf("%d",&len);
	for (int i = 0;i<len; i++)
		scanf("%d", &a[i]);
	
	for (int j = 0; j < len; j++)
		InsertBST(T,a[j]);
	
	printf("����");
	PreOrderTraverse(T,Visit);
	
	int key;
	while(1)
	{
		if(T == NULL)
		{
			printf("��Ϊ��");
			return 0;
		}
		printf("\n������Ҫɾ���Ľ��\n");
		scanf("%d", &key);
		if(key == NULL)
			return 0;
		DeleteBST(T, key);
		printf("\n����");
		PreOrderTraverse(T, Visit);	
	}
	return 0;
}