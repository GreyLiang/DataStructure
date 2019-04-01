#include <stdio.h>

/*
八皇后问题：
设8皇后问题的解为 (x1, x2, x3, x4, x5, x6, x7, x8)的形式, 
约束条件为：
在8x8的棋盘上，
其中任意两个xi 和xj不能位于棋盘的同行、同列及同对角线。
要求用一位数组进行存储，输出所有可能的排列。
*/

int n, i, q, num, hang[8];

void queen(int i){  
    int q,k;
    if(i == 8)								//计数达到8，意为放置达到第八名皇后，组数加一，打印结果，函数结束
    {
		num++;
		if(num < 10)						//输出结果1-9的序列多打印一位空格以对齐
		{
			printf("%d    ",num);
			for(q = 0; q < 8; q++)  
				printf("%d ", hang[q] + 1);
			printf("\n");
		}
		else
		{
			printf("%d   ",num);
			for(q = 0; q < 8; q++)  
				printf("%d ", hang[q] + 1);
			printf("\n");
		}
        return;
	}

    for(q = 0; q < 8; q++)					//将当前皇后q逐一尝试放置在不同的列
	{
        for(k = 0; k < i; k++)				//逐一判定q与前面的皇后是否冲突，若冲突则跳出循环改变皇后位置进行下一次判定  
            if( hang[k] == q || (k - i)==(hang[k] - q) || (i - k)==(hang[k] - q) )		//判定当前q所在位置是否和其他皇后同行或对角线
				break;
			if(k == i)						//如果满足题目要求，放置q，尝试第q+1个皇后
			{
				hang[i] = q;
				queen(i + 1);
			}
    }
}

void main()
{
    num = 0;
    queen(0);
}
