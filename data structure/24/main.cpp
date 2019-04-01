
/*
24.
�趨��ϣ���� H(key) = key MOD 11 ( ��=11 )��
����һ��ؼ������У�
��������̽����ɢ�н����ͻ�ķ���������ϣ��Ĵ洢�ṹ��
��ʾ��ϣ��
��������ؼ��֣�
�ж��Ƿ��ڹ�ϣ���С�
*/

#include <stdio.h>
#include <stdlib.h>


#define size 11

typedef struct {
	int *elem;
	int count;
	int sizeindex;
}HashTable;

int Hash(int i)
{
	int j;
	j = i % size;
	return j;
}

int SearchHash(HashTable H, int k, int &p, int &c)			//����
{
	p = Hash(k);
	while ((H.elem[p] != -1) && (k != H.elem[p]))
	{
		p = Hash(k + c);
		c++;
		if (c > size ||H.elem[p]==-1)
		{
			printf("���Ҳ��ɹ�\n");
			return 0;
		}

		if (H.elem[p] == k)
		{
			printf("���ҳɹ� %d: %d \n",p,H.elem[p]);
			return 1;
		}
	}
	if (H.elem[p] == k)
	{
		printf("���ҳɹ� %d: %d \n", p, H.elem[p]);
		return 1;
	}
	return 0;
}

int InsertHash(HashTable &H, int e)		//����
{
	int c = 0;
	int p = Hash(e);
	if (SearchHash(H, e, p, c))
		return 0;
	else 
	{
		H.elem[p] = e; 
		++H.count;
		return 1;
	}
}

int CreatHash(HashTable &H)				//������ϣ��
{
	if (H.elem = (int *)malloc(size * sizeof(int))) {
		for (int i = 0; i < size; i++)
			H.elem[i] = -1;
		return 1;
	}
	return 0;
}

int printHash(HashTable H)
{
	for (int i = 0; i < size; i++)
		printf("%d: %d ",i,H.elem[i]);
	return 1;
}

int main()
{
//	int a[] = { 1,12,11,0,14,25,9 };
	int *a;
	int num;
	printf("�����С��\n");
	scanf("%d",&num);
	a = (int*)malloc(num*sizeof(int));
	printf("�����������У�\n");
	for (int i = 0; i < num; i++)
		scanf("%d",&a[i]);
	int c = 0, p = 0;
	HashTable H;
	CreatHash(H);
	for (i = 0; i < num; i++)
		InsertHash(H,a[i]);
	printHash(H); 
	int s;
	printf("\n��������Ҫ���ҵ����֣�");
	scanf("%d",&s);
	SearchHash(H,s,p,c);
	return 0;
}

