#include <stdlib.h>
#include <stdio.h>

/*
4��쳲��������У�
f[0] = f[1] = f[2] = 0, f[3] = 1, ��, f[i] = f[i-1] + f[i-2] + f[i-3] + f[i-4]��
��������Ϊ k = 4 ��ѭ�����У�
�������е�ǰ n + 1 �f0, f1 , f2 ,�� fn ����
Ҫ������ f[n] <= 200 �� f[n+1] > 200��
*/

#define MAXQSIZE 6

typedef struct									//���������ڲ�Ԫ��
{
    int *base;
    int front;
    int rear;
}sqQuene;

int InitQuene(sqQuene &Q)						//����ѭ������
{
	Q.base = (int*)malloc(MAXQSIZE*sizeof(int));
	if(!Q.base)
		exit(0);
	Q.front = 0;
	Q.rear = 0;
	return 1;
}

int queneLenth(sqQuene Q)						//������г���
{
	return (Q.rear - Q.front + MAXQSIZE)%MAXQSIZE;
}

int enQuene(sqQuene &Q,int e)					//����������Ԫ��
{
	if((Q.rear + 1) % MAXQSIZE == Q.front)		//�ж������Ƿ�����
		return 0;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return 1;
}

int deQuene(sqQuene &Q)	
{						//��֤����
	if(Q.front == Q.rear) 
		return 0;
	Q.front = (Q.front + 1) % MAXQSIZE;
	return 1;
}

void printQuene(sqQuene Q)						//��ӡ����
{
	int i = Q.front;
	int x = 0;
	while(1)									//�ڴ��ڴ�ӡ���
	{
		printf(" %d ",Q.base[i % MAXQSIZE]);
		x++;
		i++;
		if(x == (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE)
			break;
	}
	printf("\n");
}

int Getnumber(sqQuene &Q,int i)					//ָ������ĳ��������Ԫ��
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
	enQuene(Q,1);								//�ֶ�����ǰ4��Ԫ�ؿ�ʼ����
	printQuene(Q);

	int number;
	int i = 0;
	while(number < 200)							//����ѭ��������������ʼѭ��
	{
		number = Getnumber(Q, i % MAXQSIZE) + Getnumber(Q, (i+1) % MAXQSIZE) + Getnumber(Q, (i+2) % MAXQSIZE) + Getnumber(Q, (i+3) % MAXQSIZE);
		deQuene(Q);
		enQuene(Q,number);
		printQuene(Q);
		i++;
	}
	return 0;
}