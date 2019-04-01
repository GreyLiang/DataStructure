#include <stdio.h>
#include <stdlib.h>

/*
用头尾链表存储表示法
建立广义表，
输出广义表，
求广义表的表头、
广义表的表尾
和广义表的深度。
*/

typedef enum {
	ATOM, LIST 
}ElemTag;

typedef struct GLNode
{
	ElemTag tag;  //标志位
	union 
	{
		char atom;
		struct 
		{ 
			struct GLNode *hp, *tp;
		}ptr;  //表头 表尾
	};
}*GList;

int creat(GList &T)						//建表
{
	T = NULL;
	if (!(T = (GList)malloc(sizeof(GLNode))))
		exit(0);
	printf("建立原子、广义表、空表？（0代表原子、1代表广义表、2代表空表)");
	scanf("%d",&T->tag);
	getchar(); 
	if (T->tag == 2)					//判定输入情况
	{
		T->ptr.hp = NULL;
		T->ptr.tp = NULL;
	}
	else
		if(T->tag == ATOM)
		{
			printf("输入原子：");
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

int printList(GList L)			//最终调用的输出函数
{
	printf("(");
	printlist(L);
	printf(")\n");
	return 1;
}

GList getHead(GList L)			//获取表头元素
{
	if (L->ptr.hp == NULL)
		printf("该表无表头\n");
	else
		if (L->ptr.hp->tag == ATOM)
			printf("%c\n", L->ptr.hp->atom);
		else printList(L->ptr.hp);
	return L->ptr.hp;
}

GList getTail(GList L)			//获取表尾元素
{
	if (L->ptr.tp == NULL)
		printf("该表无表尾\n");
	else
		printList(L->ptr.tp);
	return L->ptr.tp;
}

int Depth(GList L)				//求广义表深度  
{
	int max = 0, dep;
	GList p = L;
	if (L==NULL)
		return 1;				//空表深度为1
	if (L->tag == ATOM) 
		return 0;				//原子深度为零  
	
	for (; p; p = p->ptr.tp)	//遍历列表  
	{
		dep = Depth(p->ptr.hp);	//递归求深度
		if (dep>max)			//更新max  
			max = dep;
	}
	return max + 1;
}

int main()
{
	GList T;
	creat(T);
	printf("广义表为：\n");
	printList(T);
	printf("深度为：%d\n",Depth(T)-1);
	printf("表头为：\n");
	getHead(T);
	printf("表尾为：\n");
	getTail(T);
	return 0;
}