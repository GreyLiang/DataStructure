#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

/*
20.���������һ������������ķ(Prim)�㷨������С��������
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
	int adjvex;  //�ñ�ָ��Ķ����λ��
	struct ArcNode *nextarc;  //ָ����һ���ߵ�ָ��
	int *info;  //�ñ������Ϣ��ָ��
}ArcNode;

typedef struct VNode
{
	int data;  //������Ϣ
	ArcNode *firstarc;  //ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[max];  //��󶥵���

typedef struct
{
	AdjList vertices;  //��������
	int vexnum, arcnum;  //�������ͱ���
	int kind;  //ͼ������
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

		printf("����ͼ�Ķ����� ������\n");
		scanf("%d%d",&G.vexnum,&G.arcnum);
		printf("�������\n");
		for (i = 0; i < G.vexnum; i++)
			for (j = 0; j < G.vexnum; j++)
				scanf("%d",&arcs[i][j]);
	
		for (i = 0; i < G.vexnum; i++)
		{
			G.vertices[i].data = i;  //ȷ��������
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

int minimum(CLOSEDGE a[])  //����С����
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
	int k = u;  //��uΪ��㣬֮���¼������С�ı�
	for (int j = 0; j < G.vexnum; j++)
		if (j != k)
		{
			closedge[j].lowcost = arcs[k][j];  //���и�������ĳ�ʼ��
			closedge[j].adjvex = u;
		}
	closedge[k].lowcost = 0;  //��ʼ��U={u}
	for (int i = 1; i < G.vexnum; i++)
	{
		k = minimum(closedge);
		printf("����ߣ�%d ~ %d  \n",closedge[k].adjvex,G.vertices[k].data);
//		for(int b=0;b<G.vexnum;b++)
//			printf(" %d",closedge[b].lowcost);
		
		closedge[k].lowcost = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			if(arcs[k][j]>0)
			if (closedge[j].lowcost == -1||arcs[k][j] < closedge[j].lowcost) //�¶�����������ѡ����С��
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