#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
ĳ�����˾��Լ��30��Ա����
ÿ��Ա�������������š�ְ������ԣ�
ÿ�궼��Ա����ְ����ְ��
������Ա������˳��洢�ṹ����һ�����Ա�
������ְ����ְ������
����Ա����ְ����ְʱ���޸����Ա����Ҵ�ӡ���µ�Ա��������
*/

typedef struct	//����Ա��
{
	char name[10];	//����
	int number;  //����
	char position[10];  //ְ��

} stuff;

typedef struct
{
	stuff *a;
	int listsize;
	int num;  //��ǰ����
} STFList;

void init(STFList &p)  //��ʼ����Ա��
{
	p.a = (stuff*)malloc(5 * sizeof(stuff));
	p.listsize = 5;
	p.num = 1;
	printf("����Ա����Ϣ������ӵ�һ��Ա����\n");
	printf("����Ա��������");
	scanf("%s",&p.a[0].name);
	printf("����Ա�����ţ�");
	scanf("%d",&p.a[0].number);
	printf("����Ա��ְ��");
	scanf("%s",&p.a[0].position);
}

int insertStuff(STFList &p,int i)	//����Ա����Ϣ
{
	if(i < 1 || i > p.num + 1) 
		return 0;
	
	if(p.num >= p.listsize)
	{
		stuff *newbase;
		newbase = (stuff*)realloc(p.a,(p.listsize + 5)*sizeof(stuff));
		if(!newbase) 
			exit(0);
		p.a = newbase;
		p.listsize += 5;
	}

	stuff *x;
	stuff *y;
	x = &p.a[i - 1];
	for(y = &p.a[p.num - 1]; y >= x; y--)
		*(y + 1) = *(y);

	printf("����Ա����Ϣ��\n");
	printf("����Ա��������");
	scanf("%s",&p.a[i].name);
	printf("����Ա�����ţ�");
	scanf("%d",&p.a[i].number);
	printf("����Ա��ְ��");
	scanf("%s",&p.a[i].position);
	p.num++;
	return 1;
}


int deleteStuff(STFList &p,int i)	//ɾ��Ա����Ϣ
{
	stuff *x,*y;
	if( (i < 1) || (i > p.num) ) 
		return 0;
	x = &(p.a[i - 1]);
	y = p.a+p.num-1;  //��βԪ�ص�λ��
	for(++x; x <= y; x++)
		*(x-1) = *(x);
	p.num--;
	return 1;
}

void printList(STFList p)
{
	printf("Ա����Ϣ��");
	for(int i = 0; i < p.num; i++)
	{
		printf("\n");
		printf(" %s",p.a[i].name);
		printf(" %d",p.a[i].number);
		printf(" %s",p.a[i].position);
	}
}

int main()
{	
	STFList A;
	init(A);

	int judge;
	int element;
	while(judge != 4)
	{
		printf("��ѡ��Ҫ���еĲ�����\n");
		printf("���Ա������1��\n");
		printf("ɾ��Ա������2��\n");
		printf("��ӡԱ������3��\n");
		printf("�˳�ϵͳ����4��\n");
		scanf("%d",&judge);
		switch(judge)
		{
			case 1:
				printf("���������λ�ã�\n");
				scanf("%d",&element);
				insertStuff(A,element);
				printList(A);
				printf("\n");
				break;
			case 2:
				printf("������ɾ��λ�ã�\n");
				scanf("%d",&element);
				deleteStuff(A,element);
				printList(A);
				printf("\n");
				break;
			case 3:
				printList(A);
				printf("\n");
				break;
			default:
				break;
		}
	}
	
	return 0;
}
