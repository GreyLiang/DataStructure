#include <stdio.h>

/*
稀疏矩阵转置：
输入稀疏矩阵中每个元素的行号、列号、值，
建立稀疏矩阵的三元组存储结构，
并将此矩阵转置，显示转置前后的三元组结构。
*/

typedef struct		//建立三元组存放行号、列号、值
{
	int i, j;
	int e;
}Triple;

typedef struct		//分配建立长度为101的存储空间，存储矩阵的行列等相关信息
{
	Triple data[101];
	int numLine, numRow, numEle;
}TSMatrix;
 
int FastTransposeSMatrix(TSMatrix M, TSMatrix &T)		//转置函数
{
	int col, t, p, q;
	int numRowm[100];
	int cpot[100];
	T.numLine = M.numRow;
	T.numRow = M.numLine;
	T.numEle = M.numEle;

	if (T.numEle)
	{
		for (col = 1; col <= M.numRow; ++col)
			numRowm[col] = 0;
		for (t = 1; t <= M.numEle; ++t)
			++numRowm[M.data[t].j];

		cpot[1] = 1;

		for (col = 2; col <= M.numRow; ++col)
			cpot[col] = cpot[col - 1] + numRowm[col - 1];
		for (p = 1; p <= M.numEle; ++p)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	return 1;
}

int main()
{
	TSMatrix A, B;

	printf("输入稀疏矩阵的行数：");
	scanf("%d", &A.numLine);
	printf("输入稀疏矩阵的列数：");
	scanf("%d", &A.numRow);
	printf("输入稀疏矩阵的元素数：");
	scanf("%d", &A.numEle);
	for (int i = 1; i <= A.numEle; i++)
	{
		printf("输入元素的行、列、值：");
		scanf("%d", &A.data[i].i);				//行
		scanf("%d", &A.data[i].j);				//列
		scanf("%d", &A.data[i].e);				//值
	}
	for (i = 1; i <= A.numEle; i++)
	{
		printf("转置前：%d行 %d列 %d值\n", A.data[i].i, A.data[i].j, A.data[i].e);
	}
	FastTransposeSMatrix(A, B);
	for (i = 1; i <= B.numEle; i++)
	{
		printf("转置后：%d行 %d列 %d值\n", B.data[i].i, B.data[i].j, B.data[i].e);
	}
	return 0;
}