#include <stdio.h>
#include <stdlib.h>

/*
��������Ҫ��ͳһ��һ�������������
25.�۰��������
26.ð������
27.��������  
28.��ѡ������                 
29.�鲢����
30.������
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

void BInsertSort(SqList &L)  //�۰��������
{
	int low, high,m;
	for (int i = 2; i <= L.num; ++i)
	{
		L.a[0] = L.a[i];   //�ݴ浽a[0]
		low = 1; high = i - 1;
		while (low <= high)
		{
			m = (low + high) / 2;
			if (L.a[0].key < L.a[m].key)  //�۰����
				high = m - 1;  //�Ͱ�������
			else
				low = m + 1;   //�߰�������
		}
		for (int j = i - 1; j >= high + 1; --j)
			L.a[j + 1] = L.a[j];  //��¼����ƶ�
		L.a[high + 1] = L.a[0];  //��ɲ������
	}
}

void BubbleSort(SqList &L, int n)  //ð������
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

void SelectSort(SqList &L)  //��ѡ������
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
		//ѡ��i-L.length����С��
		if (i != j)
		{
			tmp = L.a[j].key;
			L.a[j].key = L.a[i].key;
			L.a[i].key = tmp;
		}
	}
}

int Partition(SqList &L, int low, int high)					//��������
{
	L.a[0].key = L.a[low].key;
	int pivotkey = L.a[low].key;							//��¼�ؼ���
	while (low<high)										//���˽������м�ɨ��
	{
		while (low < high&&L.a[high].key >= pivotkey)		//�Ƶ��Ͷ�
			--high;
		L.a[low].key = L.a[high].key;
		while (low < high&&L.a[low].key <= pivotkey)		//�߶�
			++low;
		L.a[high].key = L.a[low].key;
	}
	L.a[low].key = L.a[0].key;								//�����¼
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

void Merge(Node a[], int low, int mid, int high)		//�鲢����
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

void HeapAdjust(SqList &H, int s, int m)			//������
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
	for (i = H.num / 2; i > 0; --i)					//�����󶥶�
		HeapAdjust(H,i,H.num);
	for (i = H.num; i > 1; --i)						//�����ѽṹ�������Ѷ�Ԫ����ĩβԪ��
	{
		tmp.key = H.a[1].key;						//�Ѷ�Ԫ�غ�ĩβԪ�ؽ��н���
		H.a[1].key = H.a[i].key;
		H.a[i].key = tmp.key;
		HeapAdjust(H,1,i-1);						//���¶Զѽ��е���
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
	printf("���������С��");
	scanf("%d", &num);
//	int emp[] = { 49,36,13,25,74,38,95,3 };
	int *emp;
	int i = 0;
	emp = (int *)malloc(num * sizeof(int));
	printf("�������飺");
	for (i = 0; i < num; i++)
		scanf("%d",&emp[i]);
	SqList L;
	L.num = num;

	L.a = (Node*)malloc((L.num+1)*sizeof(Node));
	for (i = 0; i < L.num; i++)
		L.a[i+1].key = emp[i];
	printf("����Ϊ��");
	printList(L);

	printf("\n�۰��������");
	BInsertSort(L);
	printList(L);
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];

	printf("ð������");
	BubbleSort(L, L.num);
	printList(L);
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];

	printf("��ѡ������");
	SelectSort(L);
	printList(L);

	printf("��������");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	QuickSort(L);
	printList(L);

	printf("�鲢����");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	MergeSort(L);
	printList(L);

	printf("������");
	for (i = 0; i < L.num; i++)
		L.a[i + 1].key = emp[i];
	HeapSort(L);
	printList(L);
    return 0;
}

