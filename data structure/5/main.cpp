#include <stdlib.h>
#include <stdio.h>

/*
4阶斐波那契序列：
f[0] = f[1] = f[2] = 0, f[3] = 1, …, f[i] = f[i-1] + f[i-2] + f[i-3] + f[i-4]，
利用容量为 k = 4 的循环队列，
构造序列的前 n + 1 项（f0, f1 , f2 ,… fn ），
要求满足 f[n] <= 200 而 f[n+1] > 200。
*/

#define MAXQSIZE 6

typedef struct									//构建队列内部元素
{
    int *base;
    int front;
    int rear;
}sqQuene;

int InitQuene(sqQuene &Q)						//构建循环队列
{
	Q.base = (int*)malloc(MAXQSIZE*sizeof(int));
	if(!Q.base)
		exit(0);
	Q.front = 0;
	Q.rear = 0;
	return 1;
}

int queneLenth(sqQuene Q)						//计算队列长度
{
	return (Q.rear - Q.front + MAXQSIZE)%MAXQSIZE;
}

int enQuene(sqQuene &Q,int e)					//向队列中填充元素
{
	if((Q.rear + 1) % MAXQSIZE == Q.front)		//判定队列是否填满
		return 0;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return 1;
}

int deQuene(sqQuene &Q)	
{						//验证队列
	if(Q.front == Q.rear) 
		return 0;
	Q.front = (Q.front + 1) % MAXQSIZE;
	return 1;
}

void printQuene(sqQuene Q)						//打印队列
{
	int i = Q.front;
	int x = 0;
	while(1)									//在窗口打印输出
	{
		printf(" %d ",Q.base[i % MAXQSIZE]);
		x++;
		i++;
		if(x == (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE)
			break;
	}
	printf("\n");
}

int Getnumber(sqQuene &Q,int i)					//指向数组某个给定的元素
{
	return Q.base[i];
}

int main(int argc, char* argv[])
{
	sqQuene Q;
	InitQuene(Q);

	enQuene(Q,0);
	enQuene(Q,0);
	enQuene(Q,0);
	enQuene(Q,1);								//手动填入前4个元素开始数列
	printQuene(Q);

	int number;
	int i = 0;
	while(number < 200)							//定义循环结束条件并开始循环
	{
		number = Getnumber(Q, i % MAXQSIZE) + Getnumber(Q, (i+1) % MAXQSIZE) + Getnumber(Q, (i+2) % MAXQSIZE) + Getnumber(Q, (i+3) % MAXQSIZE);
		deQuene(Q);
		enQuene(Q,number);
		printQuene(Q);
		i++;
	}
	return 0;
}