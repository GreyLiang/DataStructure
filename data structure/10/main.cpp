#include <stdio.h>

/*
�������⣺
������A�е�ĳһԪ��A[i,j]�ǵ�i���е���Сֵ��
�����ǵ�j���е����ֵ�����A[i,j]�Ǿ���A�е�һ�����㡣
д��һ������ȷ������λ�õĳ���
*/

int a[10][10];											//��ʼ����������ֵ

int judge(int x, int y,int length,int width)			//�����жϺ���
{
	int i, j;
	for (i = 0; i<length; i++)							//ɨ����
	{
		if (a[x][y]<a[i][y])							//�����ڸ���ֵ�򷵻�0
			return 0;
	}
	for (j = 0; j<width; j++)							//ɨ����
	{
		if (a[x][y]>a[x][j])							//�����ڸ�Сֵ�򷵻�0
			return 0;
	}
	return 1;											//ȫ��ɨ����ɺ��绹δ������õ�ȷ��Ϊ���㣬����1
}

int main()
{
	int i, j;
	int length, width;
	printf("��������С��У�");
	scanf("%d%d",&length,&width);						//������󳤿�

	printf("�������ֵ��");
	for (i = 0; i<length; i++)							//�������ֵ
		for (j = 0; j<width; j++)
			scanf("%d",&a[i][j]);
	
	for (i = 0; i<length; i++)							//�������
		for (j = 0; j<width; j++)
			if (judge(i, j,length,width) == 1)
				printf("\n���㣺%d�� %d��\n", i+1, j+1);
	printf("�����������");
	return 0;
}