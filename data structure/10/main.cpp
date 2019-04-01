#include <stdio.h>

/*
鞍点问题：
若矩阵A中的某一元素A[i,j]是第i行中的最小值，
而又是第j列中的最大值，则称A[i,j]是矩阵A中的一个鞍点。
写出一个可以确定鞍点位置的程序。
*/

int a[10][10];											//初始化矩阵的最大值

int judge(int x, int y,int length,int width)			//鞍点判断函数
{
	int i, j;
	for (i = 0; i<length; i++)							//扫描行
	{
		if (a[x][y]<a[i][y])							//若存在更大值则返回0
			return 0;
	}
	for (j = 0; j<width; j++)							//扫描列
	{
		if (a[x][y]>a[x][j])							//若存在更小值则返回0
			return 0;
	}
	return 1;											//全部扫描完成后如还未返回则该店确定为鞍点，返回1
}

int main()
{
	int i, j;
	int length, width;
	printf("输入矩阵行、列：");
	scanf("%d%d",&length,&width);						//输入矩阵长宽

	printf("输入矩阵值：");
	for (i = 0; i<length; i++)							//输入矩阵值
		for (j = 0; j<width; j++)
			scanf("%d",&a[i][j]);
	
	for (i = 0; i<length; i++)							//输出鞍点
		for (j = 0; j<width; j++)
			if (judge(i, j,length,width) == 1)
				printf("\n鞍点：%d行 %d列\n", i+1, j+1);
	printf("鞍点输出结束");
	return 0;
}