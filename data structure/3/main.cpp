#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <winbase.h>

/*
ĳ�̳���һ��100����λ��ͣ������
����λδ��ʱ���ȴ��ĳ������Խ��벢��ʱ��
����λ����ʱ�������г����뿪���ȴ��ĳ������ܽ��룻
�������뿪ʱ����ͣ���ĵ�ʱ�䣬���Ұ���ÿСʱ1Ԫ�շѡ�
������������Ϣ��ʽ�����ǣ�����/�뿪�����ƺţ�����/�뿪ʱ�䣩��
Ҫ�������ʱ��ʾͣ�����ڵĳ�����Ϣ�Լ��շ���ʷ��¼��
*/

typedef struct Car
{
    bool enter;  //����/�뿪
    int number;  //���ƺ�
    int time;  //ͣ��ʱ�䣨1s=1h��
    int startmin,startsec;  //����ʱ��
    int leavemin,leavesec;  //�뿪ʱ��
    struct Car *next;
}Car,*CarPtr;

typedef struct 
{
    CarPtr front;  //��ͷָ��
    CarPtr rear;  //��βָ��
}CarQuene;

void creatCar(Car &A)	//�����һ����
{
    printf("�³���ʼ�Ŷӣ�\n");
    A.enter=0;
    printf("�����������룺");
    scanf("%d",&A.number);
}

int initQuene(CarQuene &Q)	//����������
{
    Q.front = (CarPtr) malloc (sizeof(Car));
    Q.rear = Q.front;
    if(!Q.front)
		exit(0);
    Q.front->next = NULL;
    return 1;
}

int destoryQuene(CarQuene &Q)	//���ٳ�����
{
    while(Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return 1;
}

void carryA(Car *A,Car B)
{
    A->enter = B.enter;
    A->leavemin = B.leavemin;
    A->leavesec = B.leavesec;
    A->number = B.number;
    A->startmin = B.startmin;
    A->startsec = B.startsec;
    A->time = B.time;
}

void carryB(Car *A,Car &B)
{
    B.enter = A->enter;
    B.leavemin = A->leavemin;
    B.leavesec = A->leavesec;
    B.number = A->number;
    B.startmin = A->startmin;
    B.startsec = A->startsec;
    B.time = A->time;
}

int EnQuene(CarQuene &Q, Car e)  //�³��Ŷ�
{
    CarPtr p;
    p = (CarPtr) malloc (sizeof(Car));
    if(!p) 
		exit(0);
    carryA(p,e);
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}

int DeQuene(CarQuene &Q,Car &e)  //�ɳ�����
{
    if(Q.front == Q.rear)    return 0;
    CarPtr p;
    p = Q.front->next;
    carryB(p,e);
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return 1;
}

void getintoparking(Car &A,Car &parking, Car &Record)	//��׼������ͣ����
{
    parking.enter = 1;
    A.enter = 1;
    parking.number = A.number;

    SYSTEMTIME ptime;
    GetLocalTime(&ptime);

    parking.startsec = ptime.wSecond;
    parking.startmin = ptime.wMinute;
    Record.startsec = parking.startsec;
    Record.startmin = parking.startmin;
    Record.number = parking.number;
 }

void getoutofparking(Car &A,Car &parking,Car &Record)	//���뿪ͣ����
{
    if(parking.enter != 1) 
        printf("�ó�λû�г���ͣ��\n");
    else
    {
        parking.enter = 0;
        A.enter = 0;
        parking.number = NULL;
        parking.time = NULL;
        
        SYSTEMTIME ptime;
        GetLocalTime(&ptime);
        parking.leavesec = ptime.wSecond;
        parking.leavemin = ptime.wMinute;
        A.time = (parking.leavemin-parking.startmin)*60+(parking.leavesec-parking.startsec);

        Record.leavemin = parking.leavemin;
        Record.leavesec = parking.leavesec;
        Record.time = A.time;

        printf("�ó��뿪ͣ������ͣ����%d��\n",A.time);
    }
}
void printparking(Car a[])	//��ӡ������Ϣ
{
    int i;
    int x=0;
    for(i = 0; i < 100; i++)
        if(a[i].enter == 1)
        {
            x++;
            printf("������Ϣ�� ���ƺţ� %05d ����ʱ�̣� %d��%d��\n",a[i].number,a[i].startmin,a[i].startsec);
        }
        if(x == 0)
            printf("ͣ�����������������\n");
}

void printrecord(Car *r)	//��ӡ��ʷͣ�ż�¼
{
    int i;
    int x = 0;
    for(i = 0; i < 100; i++)
        if(r[i].leavesec >= 0)
        {
            x++;
            printf("������Ϣ�� ���ƺţ� %05d ����ʱ�̣� %d��%d�� �뿪ʱ�̣� %d��%d�� ͣ��ʱ�䣺 %d�� �շѣ� %dԪ ��ʵ��һ�� = һСʱ��\n",r[i].number,r[i].startmin,r[i].startsec,r[i].leavemin,r[i].leavesec,r[i].time,r[i].time);
        }
        if(x==0)
            printf("ͣ�������������뿪,����ʷ��¼\n");
}

int main(int argc, char* argv[])
{    
    Car parking[100];  //ͣ����
    
    Car *Record;  //��ʷ��¼
    Record = (Car *) malloc (200*sizeof(Car));

    CarQuene Q; //�����Ŷӳ���
    initQuene(Q);
    Car A;

    int i = 0;

    while(1)
    {
        int judge;
        printf("�����³��Ŷӣ�0��/��������ͣ������1��/�����뿪ͣ������2��/ͣ�����ֽ׶���Ϣ��3��/��ʷ��¼��4��/�˳�ϵͳ��5��");
        scanf("%d",&judge);
        
        if(judge == 0)
        {
            creatCar(A);
            EnQuene(Q,A);
        }

        if(judge ==1 )
        {
            if(Q.front == Q.rear)
			{
                printf("û�г����Ŷ�\n");
				printf("\n");
			}
            else
			{
                for(i = 0; i < 100; i++)
                {
                    if(parking[i].enter!=1) //ͣ�����п�λ
                    {
                        DeQuene(Q,A);
                        getintoparking(A,parking[i],Record[i]);
                        break;
                    }
                    if(i==99)
                        printf("��λ��������ȴ�\n");
                }
			}
			printf("\n");
        }
        
        if(judge==2)
        {
            for(i = 0; i < 100; i++)
            {
                if(parking[i].enter == 1)
                    break;
                if(i == 99)
                    printf("ͣ�������޳�\n");
            }
            printf("ѡ���ã�0~99���ĳ����Ƴ�ͣ������");
            scanf("%d",&i);
            getoutofparking(A,parking[i],Record[i]);
			printf("\n");
        }

        if(judge == 3)
		{
            printparking(parking);
			printf("\n");
		}

        if(judge == 4)
		{
            printrecord(Record);
			printf("\n");
		}

        if(judge == 5)
            break;
    }    
    return 0;
}
