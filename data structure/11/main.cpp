#include <stdio.h>

/*
ϡ�����ת�ã�
����ϡ�������ÿ��Ԫ�ص��кš��кš�ֵ��
����ϡ��������Ԫ��洢�ṹ��
�����˾���ת�ã���ʾת��ǰ�����Ԫ��ṹ��
*/

typedef struct		//������Ԫ�����кš��кš�ֵ
{
	int i, j;
	int e;
}Triple;

typedef struct		//���佨������Ϊ101�Ĵ洢�ռ䣬�洢��������е������Ϣ
{
	Triple data[101];
	int numLine, numRow, numEle;
}TSMatrix;
 
int FastTransposeSMatrix(TSMatrix M, TSMatrix &T)		//ת�ú���
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

	printf("����ϡ������������");
	scanf("%d", &A.numLine);
	printf("����ϡ������������");
	scanf("%d", &A.numRow);
	printf("����ϡ������Ԫ������");
	scanf("%d", &A.numEle);
	for (int i = 1; i <= A.numEle; i++)
	{
		printf("����Ԫ�ص��С��С�ֵ��");
		scanf("%d", &A.data[i].i);				//��
		scanf("%d", &A.data[i].j);				//��
		scanf("%d", &A.data[i].e);				//ֵ
	}
	for (i = 1; i <= A.numEle; i++)
	{
		printf("ת��ǰ��%d�� %d�� %dֵ\n", A.data[i].i, A.data[i].j, A.data[i].e);
	}
	FastTransposeSMatrix(A, B);
	for (i = 1; i <= B.numEle; i++)
	{
		printf("ת�ú�%d�� %d�� %dֵ\n", B.data[i].i, B.data[i].j, B.data[i].e);
	}
	return 0;
}