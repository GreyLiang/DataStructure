#include <stdio.h>
#include <stdlib.h>

/*
以下问题要求统一在一个大程序里解决。
25.折半插入排序
26.冒泡排序
27.快速排序  
28.简单选择排序                 
29.归并排序
30.堆排序
*/

typedef struct  
{
	int key;
}Node;

typedef struct
{
	Node *a;
	int listsize;
	int num;  
} SqList;

void BInsertSort(SqList &L)  //折半插入排序
{
	int low, high,m;
	for (int i = 2; i <= L.num; ++i)
	{
		L.a[0] = L.a[i];   //暂存到a[0]
		low = 1; high = i - 1;
		while (low <= high)
		{
			m = (low + high) / 2;
			if (L.a[0].key < L.a[m].key)  //折半查找
				high = m - 1;  //低半区插入
			else
				low = m + 1;   //高半区插入
		}
		for (int j = i - 1; j >= high + 1; --j)
			L.a[j + 1] = L.a[j];  //记录向后移动
		L.a[high + 1] = L.a[0];  //完成插入操作
	}
}

void BubbleSort(SqList &L, int n)  //冒泡排序
{
	int tmp;
	for (int i = n, change = true; i >= 1 && change; --i)
	{
		change = false;
		for(int j = 1; j < i; j++)
		{
			if (L.a[j].key > L.a[j+1].key)
			{
				tmp = L.a[j].key;
				L.a[j].key = L.a[j+1].key;
				L.a[j+1].key = tmp;
				change = true;
			}
		}
	}
}

void SelectSort(SqList &L)  //简单选择排序
{
	int i,j,tmp,k,min;
	for (i = 1; i < L.num; i++)
	{
		min = L.a[i].key; 
		j = i;
		for (k = i; k <= L.num; k++)
		{
			if (L.a[k].key < L.a[j].key)
				j = k;
		}
		//选择i-L.length中最小的
		if (i != j)
		{
			tmp = L.a[j].key;
			L.a[j].key = L.a[i].key;
			L.a[i].key = tmp;
		}
	}
}

int Partition(SqList &L, int low, int high)					//快速排序
{
	L.a[0].key = L.a[low].key;
	int pivotkey = L.a[low].key;							//记录关键字
	while (low<high)										//两端交替向中间扫描
	{
		while (low < high&&L.a[high].key >= pivotkey)		//移到低端
			--high;
		L.a[low].key = L.a[high].key;
		while (low < high&&L.a[low].key <= pivotkey)		//高端
			++low;
		L.a[high].key = L.a[low].key;
	}
	L.a[low].key = L.a[0].key;								//枢轴记录
	return low;
}

void QSort(SqList &L, int low, int high)
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc);
		QSort(L, pivotloc + 1, high);
	}
}

void QuickSort(SqList &L)
{
	QSort(L,1,L.num);
}

void Merge(Node a[], int low, int mid, int high)		//归并排序
{
	int i = low, j = mid + 1;
	int k = 1;
	Node *b = (Node*)malloc(sizeof(Node) * (high - low + 1));
	while (i <= mid && j <= high)
	{
		if (a[i].key < a[j].key)
			b[k++].key = a[i++].key;
		else
			b[k++].key = a[j++].key;
	}
	while (i <= mid)
		b[k++].key = a[i++].key;
	while (j <= high)
		b[k++].key = a[j++].key;
	for (i = low, k = 1; i <= high; i++, k++)
		a[i].key = b[k].key;
}

void MSort(Node a[], int low, int high)
{
	if (low < high)
	{
		int m = (low + high) / 2;
		MSort(a, low, m);
		MSort(a, m + 1, high);
		Merge(a, low, m, high);
	}
}

void MergeSort(SqList &L)
{
	MSort(L.a, 1, L.num);
}

void HeapAdjust(SqList &H, int s, int m)			//堆排序
{
	Node rc;
	rc.key = H.a[s].key;
	for (int j = 2 * s; j <= m; j *= 2)
	{
		if (j < m&&H.a[j].key < H.a[j + 1].key)
			++j;
		if (!(rc.key < H.a[j].key))
			break;
		H.a[s].key = H.a[j].key;
		s = j;
	}
	H.a[s].key = rc.key;
}

void HeapSort(SqList &H)
{
	int i;
	Node tmp;
	for (i = H.num / 2; i > 0; --i)					//构建大顶堆
		HeapAdjust(H,i,H.num);
	for (i = H.num; i > 1; --i)						//调整堆结构、交换堆顶元素与末尾元素
	{
		tmp.key = H.a[1].key;						//堆顶元素和末尾元素进行交换
		H.a[1].key = H.a[i].key;
		H.a[i].key = tmp.key;
		HeapAdjust(H,1,i-1);						//重新对堆进行调整
	}
}

void printList(SqList L)
{
	for (int i = 1; i <= L.num; i++)
		printf("%d ", L.a[i].key);
	printf("\n");
}

int main()
{
	int num;
	printf("输入数组大小：");
	scanf("%d", &num);
//	int emp[] = { 49,36,13,25,74,38,95,3 };
	int *emp;
	int i = 0;
	emp = (int *)malloc(num * sizeof(int));
	printf("输入数组：");
	for (i = 0; i < num; i++)
		scanf("%d",&emp[i]);
	SqList L;
	L.num = num;

	L.a = (Node*)malloc((L.num+1)*sizeof(Node));
	for (i = 0; i < L.num; i++)
		L.a[i+1].key = emp[i];
	printf("数列为：");
	printList(L);

	printf("\n折半插入排序：");
	BInsertSort(L);
	printList(L);
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];

	printf("冒泡排序：");
	BubbleSort(L, L.num);
	printList(L);
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];

	printf("简单选择排序：");
	SelectSort(L);
	printList(L);

	printf("快速排序：");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	QuickSort(L);
	printList(L);

	printf("归并排序：");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	MergeSort(L);
	printList(L);

	printf("堆排序：");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	HeapSort(L);
	printList(L);
    return 0;
}

