#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
约瑟夫（Josephus）环问题：
编号为1,2,3,…,n的n个人按顺时针方向围坐一圈，每人持有一个密码（正整数）。
一开始任选一个正整数作为报数的上限值m，从第一个人开始按顺时针方向自1开始顺序报数,报到m时停止。
报m的人出列，将他的密码作为新的m值，从他在顺时针方向上的下一人开始重新从1报数，
如此下去，直到所有人全部出列为止。
建立n个人的单循环链表存储结构，运行结束后，输出依次出队的人的序号。
*/

typedef struct LNode
{
	int data;
	int num;
	struct LNode *next;
}LNode, *linkList;

void createList(linkList &L, int n)  //创建单循环列表，录入密码
{
	int x = 0;
	linkList p;
	linkList q;
	L = (linkList)malloc(sizeof(LNode));
	L->next = NULL;
	printf("输入每人手中的密码：\n");

	for(int i = n; i > 0; --i)
	{
		p = (linkList)malloc(sizeof(LNode));
		if(x == 0)
			q = p;
		x = 1;
		printf("第%d个人:",i);
		p->num = i;
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
	q->next = L->next;
}

int Delete(linkList &L,int i)	//删除轮到的人
{
	int j = 0;
	linkList p,q;
	p = L;
	while((p->next) && (j < i - 1))
	{
		p = p->next;
		j++;
	}

	if(!(p->next) || j > i - 1)
		return 0;
	q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

int printList(linkList L)	//打印表中剩余人的信息
{
	linkList p = L -> next;
	for(int i = 0; i < 5; i++)
	{
		printf(" %d",p->data);
		p=p->next;
	}
	printf("\n");
	return 9;
}

int main()
{ 	
	linkList A;
	linkList p,q;

	int len;
	printf("输入总人数：\n");
	scanf("%d",&len);
	int *numberOfOut;
	numberOfOut = (int*)malloc(sizeof(int)*len);

	createList(A,len);	//创建列表
	p = A->next;	//p指向列表的下一项

	int l;
	printf("请输入取第几个人的密码作为初始上限值：");
	scanf("%d",&l);

	for(int i = 1; i < l; i++)
		p = p->next;
	int m = p->data;
	printf("初始上限值m为%d\n",m);
	
	p = A->next; 
	int j = 1;
	int counting = 0;

	while(1)	//进入报数循环
	{

		printf("序号：%d 密码: %d\n",p->num,p->data);
		if(j == m)	//打印当前进行的循环
		{	

			m = p->data;
			printf("手中密码为%d,序号为%d的人退出\n",m,p->num);
			numberOfOut[counting] = p->num; 

			for(int T = 0; T < len-1; T++)  //找到前一元素
			{
				p = p->next;
			}

			q = p->next;
			p->next = q->next;
			free(q);	//p指向后一位

			p = p->next;
			len--;
			j = 1;
			counting++;
			continue;
		}

		if(p == p->next)	//当列表为空时从循环中跳出
		{
			printf("手中密码为%d,序号为%d的人退出\n",p->data,p->num);
			printf("data: %d\n",p->data);
			printf("所有人均退出\n");
			numberOfOut[counting] = p->num;
			counting++;
			free(p);
			break;
		}

		p = p->next;
		j++;

	}

	printf("退出顺序是：");
	for(int z = 0; z < counting; z++)
		printf("%d ",numberOfOut[z]);
	printf("\n");
	return 0;
}
