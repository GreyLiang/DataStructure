/*
21.要求建立图的存储结构（邻接表或邻接矩阵），
输入任意的一个图，
显示图的深度优先搜索遍历边。

22.要求建立图的存储结构（邻接表或邻接矩阵），
输入任意的一个图，
显示图的广度优先搜索遍历边。
*/

#include <stdlib.h>
#include <stdio.h>

#define max 20

typedef struct Qnode
{
	int num;
	struct Qnode *next;
}Qnode, *QuenePtr;

typedef struct
{
	QuenePtr front;  //队头指针
	QuenePtr rear;  //队尾指针
}LinkQuene;

int InitQuene(LinkQuene &Q)
{
	Q.front = (QuenePtr)malloc(sizeof(Qnode));
	Q.rear = Q.front;
	if (!Q.front) 
		exit(0);
	Q.front->next = NULL;
	return 1;
}

int EnQuene(LinkQuene &Q, int e)  //插入队尾元素
{
	QuenePtr p;
	p = (QuenePtr)malloc(sizeof(Qnode));
	if (!p) exit(0);
	p->num = e; 
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQuene(LinkQuene &Q, int &e)
{
	if (Q.front == Q.rear)	return 0;
	QuenePtr p;
	p = Q.front->next;
	e = p->num;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return 0;
}

int QueneEmpty(LinkQuene Q)
{
	if (Q.front == Q.rear)
		return 1;
	return 0;
}


typedef struct ArcNode
{
	int adjvex;  //该边指向的顶点的位置
	struct ArcNode *nextarc;  //指向下一条边的指针
	int *info;  //该边相关信息的指针
}ArcNode;

typedef struct VNode
{
	int data;  //顶点信息
	ArcNode *firstarc;  //指向第一条依附该顶点的边的指针
}VNode,AdjList[max];

typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;  //顶点数和边数
	int kind;  //图的种类
}Graph;

int creat(Graph &G)
{
	int i, j, k;
	int a, b;
	ArcNode *s;
	printf("输入顶点数和边数：");
	scanf("%d%d",&G.vexnum,&G.arcnum);

	for (i = 0; i < G.vexnum; i++)
	{
		G.vertices[i].data = i;  //确定顶点编号
		G.vertices[i].firstarc = NULL;
	}

	for (i = 0; i < G.arcnum; i++)
	{
		printf("输入边：");
		scanf("%d%d",&j,&k);
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = j;
		s->nextarc = G.vertices[k].firstarc;
		G.vertices[k].firstarc = s;

		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = k;
		s->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = s;
	}

	return 1;
}

bool visited[max];
//int(*VisitFunc)(int v);

int Visit(int e)
{
	printf("%d",e);
	return 1;
}

int FirstAdjvex(Graph G, int v)  //返回边指向的第一个顶点
{
	if(G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	return -1;
}

int NextAdjvex(Graph G, int v, int w)
{
	ArcNode* p;
	p = G.vertices[v].firstarc;
	
	while (p)
	{
		if (p->nextarc==NULL)
			return -1;
		if (p->adjvex == w)
			return p->nextarc->adjvex;

		p = p->nextarc;
	}
		return -1;
}

int(*VisitFunc)(int v);

void DFS(Graph &G, int v)
{
	int w;
	visited[v] = true;
	Visit(v);
	for (w = FirstAdjvex(G, v); w >= 0; w = NextAdjvex(G, v, w))
		if (!visited[w])
			DFS(G, w);
}


void DFSTraverse(Graph G, int(*VisitFunc)(int v))
{
	int v;
	VisitFunc = Visit;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false;
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v])
			DFS(G,v);
}

void BFSTraverse(Graph G, int(*VisitFunc)(int v))
{
	LinkQuene Q;
	int v,u,w;
//	VisitFunc = Visit;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = false;
	InitQuene(Q);
	for (v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v]) 
		{
			visited[v] = true; 
			Visit(v);
			EnQuene(Q,v);
			while (!QueneEmpty(Q))
			{
				DeQuene(Q,u);
				for (w = FirstAdjvex(G, u); w >= 0; w = NextAdjvex(G, u, w))
				{
					if (!visited[w])
					{
						visited[w] = true;
						Visit(w);
						EnQuene(Q, w);
					}
				}
			}
		}
	}
}

int main()
{
	Graph G;
	creat(G); 
	printf("\nBFS:");
	BFSTraverse(G,Visit);
	printf("\nDFS:");
	DFSTraverse(G,Visit);
	return 0;
}

