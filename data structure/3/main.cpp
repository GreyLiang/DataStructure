#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <winbase.h>

/*
某商场有一个100个车位的停车场，
当车位未满时，等待的车辆可以进入并计时；
当车位已满时，必须有车辆离开，等待的车辆才能进入；
当车辆离开时计算停留的的时间，并且按照每小时1元收费。
汽车的输入信息格式可以是（进入/离开，车牌号，进入/离开时间），
要求可以随时显示停车场内的车辆信息以及收费历史记录。
*/

typedef struct Car
{
    bool enter;  //进入/离开
    int number;  //车牌号
    int time;  //停车时间（1s=1h）
    int startmin,startsec;  //进入时间
    int leavemin,leavesec;  //离开时间
    struct Car *next;
}Car,*CarPtr;

typedef struct 
{
    CarPtr front;  //队头指针
    CarPtr rear;  //队尾指针
}CarQuene;

void creatCar(Car &A)	//插入第一辆车
{
    printf("新车开始排队；\n");
    A.enter=0;
    printf("输入汽车号码：");
    scanf("%d",&A.number);
}

int initQuene(CarQuene &Q)	//建立车队列
{
    Q.front = (CarPtr) malloc (sizeof(Car));
    Q.rear = Q.front;
    if(!Q.front)
		exit(0);
    Q.front->next = NULL;
    return 1;
}

int destoryQuene(CarQuene &Q)	//销毁车队列
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

int EnQuene(CarQuene &Q, Car e)  //新车排队
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

int DeQuene(CarQuene &Q,Car &e)  //旧车出队
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

void getintoparking(Car &A,Car &parking, Car &Record)	//车准备进入停车场
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

void getoutofparking(Car &A,Car &parking,Car &Record)	//车离开停车场
{
    if(parking.enter != 1) 
        printf("该车位没有车辆停放\n");
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

        printf("该车离开停车场，停放了%d秒\n",A.time);
    }
}
void printparking(Car a[])	//打印车辆信息
{
    int i;
    int x=0;
    for(i = 0; i < 100; i++)
        if(a[i].enter == 1)
        {
            x++;
            printf("车辆信息： 车牌号： %05d 进入时刻： %d分%d秒\n",a[i].number,a[i].startmin,a[i].startsec);
        }
        if(x == 0)
            printf("停车场内暂无汽车存放\n");
}

void printrecord(Car *r)	//打印历史停放记录
{
    int i;
    int x = 0;
    for(i = 0; i < 100; i++)
        if(r[i].leavesec >= 0)
        {
            x++;
            printf("车辆信息： 车牌号： %05d 进入时刻： %d分%d秒 离开时刻： %d分%d秒 停靠时间： %d秒 收费： %d元 （实际一秒 = 一小时）\n",r[i].number,r[i].startmin,r[i].startsec,r[i].leavemin,r[i].leavesec,r[i].time,r[i].time);
        }
        if(x==0)
            printf("停车场内无汽车离开,无历史记录\n");
}

int main(int argc, char* argv[])
{    
    Car parking[100];  //停车场
    
    Car *Record;  //历史记录
    Record = (Car *) malloc (200*sizeof(Car));

    CarQuene Q; //构造排队车列
    initQuene(Q);
    Car A;

    int i = 0;

    while(1)
    {
        int judge;
        printf("创造新车排队（0）/车辆进入停车场（1）/车辆离开停车场（2）/停车场现阶段信息（3）/历史记录（4）/退出系统（5）");
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
                printf("没有车在排队\n");
				printf("\n");
			}
            else
			{
                for(i = 0; i < 100; i++)
                {
                    if(parking[i].enter!=1) //停车场有空位
                    {
                        DeQuene(Q,A);
                        getintoparking(A,parking[i],Record[i]);
                        break;
                    }
                    if(i==99)
                        printf("车位已满，请等待\n");
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
                    printf("停车场内无车\n");
            }
            printf("选择让（0~99）的车辆移出停车场？");
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
