
/*
24.
设定哈希函数 H(key) = key MOD 11 ( 表长=11 )，
输入一组关键字序列，
根据线性探测再散列解决冲突的方法建立哈希表的存储结构，
显示哈希表，
任意输入关键字，
判断是否在哈希表中。
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

int SearchHash(HashTable H, int k, int &p, int &c)			//查找
{
	p = Hash(k);
	while ((H.elem[p] != -1) && (k != H.elem[p]))
	{
		p = Hash(k + c);
		c++;
		if (c > size ||H.elem[p]==-1)
		{
			printf("查找不成功\n");
			return 0;
		}

		if (H.elem[p] == k)
		{
			printf("查找成功 %d: %d \n",p,H.elem[p]);
			return 1;
		}
	}
	if (H.elem[p] == k)
	{
		printf("查找成功 %d: %d \n", p, H.elem[p]);
		return 1;
	}
	return 0;
}

int InsertHash(HashTable &H, int e)		//插入
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

int CreatHash(HashTable &H)				//创建哈希表
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
	printf("输入大小：\n");
	scanf("%d",&num);
	a = (int*)malloc(num*sizeof(int));
	printf("输入数字序列：\n");
	for (int i = 0; i < num; i++)
		scanf("%d",&a[i]);
	int c = 0, p = 0;
	HashTable H;
	CreatHash(H);
	for (i = 0; i < num; i++)
		InsertHash(H,a[i]);
	printHash(H); 
	int s;
	printf("\n请输入需要查找的数字：");
	scanf("%d",&s);
	SearchHash(H,s,p,c);
	return 0;
}

