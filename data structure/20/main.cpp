#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

/*
20.输入任意的一个网，用普里姆(Prim)算法构造最小生成树。
*/

#define max 20
int arcs[max][max];
/*
int arcs[6][6] =
{
	0,  6,  1,  5, -1, -1,
	6,  0,  5, -1,  3, -1,
	1,  5,  0,  5,  6,  4,
	5, -1,  5,  0, -1,  2,
	-1, 3,  6, -1,  0,  6,
	-1, -1, 4,  2,  6,  0
};*/

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
}VNode, AdjList[max];  //最大顶点数

typedef struct
{
	AdjList vertices;  //顶点数组
	int vexnum, arcnum;  //顶点数和边数
	int kind;  //图的种类
}Graph;

struct CLOSEDGE
{
	int adjvex;
	int lowcost;
}closedge[max];


int creat(Graph &G)
{
	int i, j, k;
	ArcNode *s;

		printf("输入图的顶点数 边数：\n");
		scanf("%d%d",&G.vexnum,&G.arcnum);
		printf("输入矩阵：\n");
		for (i = 0; i < G.vexnum; i++)
			for (j = 0; j < G.vexnum; j++)
				scanf("%d",&arcs[i][j]);
	
		for (i = 0; i < G.vexnum; i++)
		{
			G.vertices[i].data = i;  //确定顶点编号
			G.vertices[i].firstarc = NULL;
		}

		for (j = 0; j < G.vexnum; j++)
			for (k = 0; k < j; k++)
				if (arcs[k][j] != -1)
				{
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

int minimum(CLOSEDGE a[])  //求最小代价
{
	int min = INT_MAX;
	int u = -1;
	for (int i = 0; i < max; i++)
	{
		if (a[i].lowcost > 0 && a[i].lowcost < min)
		{			
			min = a[i].lowcost;
			u = i;
		}
	}
	if(u==-1)
		printf("error");
	return u;
}

void PRIM(Graph G,int u) 
{
	int k = u;  //以u为起点，之后记录代价最小的边
	for (int j = 0; j < G.vexnum; j++)
		if (j != k)
		{
			closedge[j].lowcost = arcs[k][j];  //进行辅助数组的初始化
			closedge[j].adjvex = u;
		}
	closedge[k].lowcost = 0;  //初始，U={u}
	for (int i = 1; i < G.vexnum; i++)
	{
		k = minimum(closedge);
		printf("输出边：%d ~ %d  \n",closedge[k].adjvex,G.vertices[k].data);
//		for(int b=0;b<G.vexnum;b++)
//			printf(" %d",closedge[b].lowcost);
		
		closedge[k].lowcost = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			if(arcs[k][j]>0)
			if (closedge[j].lowcost == -1||arcs[k][j] < closedge[j].lowcost) //新顶点加入后重新选择最小边
			{
				closedge[j].adjvex = G.vertices[k].data;
				closedge[j].lowcost = arcs[k][j];
			}
		}
	}
}

int main()
{
	Graph G;
	creat(G);
	PRIM(G,0);
    return 0;
}