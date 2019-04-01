#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Լɪ��Josephus�������⣺
���Ϊ1,2,3,��,n��n���˰�˳ʱ�뷽��Χ��һȦ��ÿ�˳���һ�����루����������
һ��ʼ��ѡһ����������Ϊ����������ֵm���ӵ�һ���˿�ʼ��˳ʱ�뷽����1��ʼ˳����,����mʱֹͣ��
��m���˳��У�������������Ϊ�µ�mֵ��������˳ʱ�뷽���ϵ���һ�˿�ʼ���´�1������
�����ȥ��ֱ��������ȫ������Ϊֹ��
����n���˵ĵ�ѭ������洢�ṹ�����н�����������γ��ӵ��˵���š�
*/

typedef struct LNode
{
	int data;
	int num;
	struct LNode *next;
}LNode, *linkList;

void createList(linkList &L, int n)  //������ѭ���б�¼������
{
	int x = 0;
	linkList p;
	linkList q;
	L = (linkList)malloc(sizeof(LNode));
	L->next = NULL;
	printf("����ÿ�����е����룺\n");

	for(int i = n; i > 0; --i)
	{
		p = (linkList)malloc(sizeof(LNode));
		if(x == 0)
			q = p;
		x = 1;
		printf("��%d����:",i);
		p->num = i;
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
	q->next = L->next;
}

int Delete(linkList &L,int i)	//ɾ���ֵ�����
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

int printList(linkList L)	//��ӡ����ʣ���˵���Ϣ
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
	printf("������������\n");
	scanf("%d",&len);
	int *numberOfOut;
	numberOfOut = (int*)malloc(sizeof(int)*len);

	createList(A,len);	//�����б�
	p = A->next;	//pָ���б����һ��

	int l;
	printf("������ȡ�ڼ����˵�������Ϊ��ʼ����ֵ��");
	scanf("%d",&l);

	for(int i = 1; i < l; i++)
		p = p->next;
	int m = p->data;
	printf("��ʼ����ֵmΪ%d\n",m);
	
	p = A->next; 
	int j = 1;
	int counting = 0;

	while(1)	//���뱨��ѭ��
	{

		printf("��ţ�%d ����: %d\n",p->num,p->data);
		if(j == m)	//��ӡ��ǰ���е�ѭ��
		{	

			m = p->data;
			printf("��������Ϊ%d,���Ϊ%d�����˳�\n",m,p->num);
			numberOfOut[counting] = p->num; 

			for(int T = 0; T < len-1; T++)  //�ҵ�ǰһԪ��
			{
				p = p->next;
			}

			q = p->next;
			p->next = q->next;
			free(q);	//pָ���һλ

			p = p->next;
			len--;
			j = 1;
			counting++;
			continue;
		}

		if(p == p->next)	//���б�Ϊ��ʱ��ѭ��������
		{
			printf("��������Ϊ%d,���Ϊ%d�����˳�\n",p->data,p->num);
			printf("data: %d\n",p->data);
			printf("�����˾��˳�\n");
			numberOfOut[counting] = p->num;
			counting++;
			free(p);
			break;
		}

		p = p->next;
		j++;

	}

	printf("�˳�˳���ǣ�");
	for(int z = 0; z < counting; z++)
		printf("%d ",numberOfOut[z]);
	printf("\n");
	return 0;
}
