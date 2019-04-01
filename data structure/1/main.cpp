#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
某软件公司大约有30名员工，
每名员工有姓名、工号、职务等属性，
每年都有员工离职和入职。
把所有员工按照顺序存储结构建立一个线性表，
建立离职和入职函数，
当有员工离职或入职时，修改线性表，并且打印最新的员工名单。
*/

typedef struct	//单个员工
{
	char name[10];	//姓名
	int number;  //工号
	char position[10];  //职务

} stuff;

typedef struct
{
	stuff *a;
	int listsize;
	int num;  //当前人数
} STFList;

void init(STFList &p)  //初始单个员工
{
	p.a = (stuff*)malloc(5 * sizeof(stuff));
	p.listsize = 5;
	p.num = 1;
	printf("输入员工信息：（添加第一名员工）\n");
	printf("输入员工姓名：");
	scanf("%s",&p.a[0].name);
	printf("输入员工工号：");
	scanf("%d",&p.a[0].number);
	printf("输入员工职务：");
	scanf("%s",&p.a[0].position);
}

int insertStuff(STFList &p,int i)	//插入员工信息
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

	printf("输入员工信息：\n");
	printf("输入员工姓名：");
	scanf("%s",&p.a[i].name);
	printf("输入员工工号：");
	scanf("%d",&p.a[i].number);
	printf("输入员工职务：");
	scanf("%s",&p.a[i].position);
	p.num++;
	return 1;
}


int deleteStuff(STFList &p,int i)	//删除员工信息
{
	stuff *x,*y;
	if( (i < 1) || (i > p.num) ) 
		return 0;
	x = &(p.a[i - 1]);
	y = p.a+p.num-1;  //表尾元素的位置
	for(++x; x <= y; x++)
		*(x-1) = *(x);
	p.num--;
	return 1;
}

void printList(STFList p)
{
	printf("员工信息：");
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
		printf("请选择要进行的操作：\n");
		printf("添加员工：（1）\n");
		printf("删除员工：（2）\n");
		printf("打印员工：（3）\n");
		printf("退出系统：（4）\n");
		scanf("%d",&judge);
		switch(judge)
		{
			case 1:
				printf("请输入插入位置：\n");
				scanf("%d",&element);
				insertStuff(A,element);
				printList(A);
				printf("\n");
				break;
			case 2:
				printf("请输入删除位置：\n");
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
