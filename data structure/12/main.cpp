#include <stdio.h>
#include <stdlib.h>

/*
��ͷβ����洢��ʾ��
���������
��������
������ı�ͷ��
�����ı�β
�͹�������ȡ�
*/

typedef enum {
	ATOM, LIST 
}ElemTag;

typedef struct GLNode
{
	ElemTag tag;  //��־λ
	union 
	{
		char atom;
		struct 
		{ 
			struct GLNode *hp, *tp;
		}ptr;  //��ͷ ��β
	};
}*GList;

int creat(GList &T)						//����
{
	T = NULL;
	if (!(T = (GList)malloc(sizeof(GLNode))))
		exit(0);
	printf("����ԭ�ӡ�������ձ���0����ԭ�ӡ�1��������2����ձ�)");
	scanf("%d",&T->tag);
	getchar(); 
	if (T->tag == 2)					//�ж��������
	{
		T->ptr.hp = NULL;
		T->ptr.tp = NULL;
	}
	else
		if(T->tag == ATOM)
		{
			printf("����ԭ�ӣ�");
			scanf("%c", &T->atom);
		}
		else
		{
			creat(T->ptr.hp);
			creat(T->ptr.tp);
		}
	return 1;
}

int printlist(GList L)
{
	if (L == NULL||L->tag==2);
	else
		if (L->ptr.hp->tag == ATOM)
		{
			printf("%c", L->ptr.hp->atom);
			printlist(L->ptr.tp);
		}
		else if (L->tag == LIST)
		{
			printf("(");
			printlist(L->ptr.hp);
			printf(")");
			printlist(L->ptr.tp);
		} 
	return 1;
}

int printList(GList L)			//���յ��õ��������
{
	printf("(");
	printlist(L);
	printf(")\n");
	return 1;
}

GList getHead(GList L)			//��ȡ��ͷԪ��
{
	if (L->ptr.hp == NULL)
		printf("�ñ��ޱ�ͷ\n");
	else
		if (L->ptr.hp->tag == ATOM)
			printf("%c\n", L->ptr.hp->atom);
		else printList(L->ptr.hp);
	return L->ptr.hp;
}

GList getTail(GList L)			//��ȡ��βԪ��
{
	if (L->ptr.tp == NULL)
		printf("�ñ��ޱ�β\n");
	else
		printList(L->ptr.tp);
	return L->ptr.tp;
}

int Depth(GList L)				//���������  
{
	int max = 0, dep;
	GList p = L;
	if (L==NULL)
		return 1;				//�ձ����Ϊ1
	if (L->tag == ATOM) 
		return 0;				//ԭ�����Ϊ��  
	
	for (; p; p = p->ptr.tp)	//�����б�  
	{
		dep = Depth(p->ptr.hp);	//�ݹ������
		if (dep>max)			//����max  
			max = dep;
	}
	return max + 1;
}

int main()
{
	GList T;
	creat(T);
	printf("�����Ϊ��\n");
	printList(T);
	printf("���Ϊ��%d\n",Depth(T)-1);
	printf("��ͷΪ��\n");
	getHead(T);
	printf("��βΪ��\n");
	getTail(T);
	return 0;
}