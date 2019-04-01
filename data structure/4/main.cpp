#include <stdio.h>
#include <stdlib.h>

/*
某银行营业厅共有6个营业窗口，设有排队系统广播叫号，
该银行的业务分为公积金、银行卡、理财卡等三种。
公积金业务指定1号窗口，银行卡业务指定2、3、4号窗口，理财卡业务指定5、6号窗口。
但如果5、6号窗口全忙，而2、3、4号窗口有空闲时，
理财卡业务也可以在空闲的2、3、4号窗口之一办理。
客户领号、业务完成可以作为输入信息，要求可以随时显示6个营业窗口的状态。
*/

typedef struct
{
    int number;  //客户领号
    char event;  //办理事务类型
    char over;  //是否结束
    char window_;  //所在窗口
}Customer;

typedef struct Qnode
{
    Customer customer;
    struct Qnode *next;
}Qnode, *QuenePtr;

typedef struct 
{
    QuenePtr front;  //队头指针
    QuenePtr rear;  //队尾指针
}LinkQuene;

int InitQuene(LinkQuene &Q)		//入队
{
    Q.front = (QuenePtr) malloc (sizeof(Qnode));
    Q.rear = Q.front;
    if(!Q.front) exit(0);
    Q.front->next = NULL;
    return 1;
}

int DestoryQuene(LinkQuene &Q)	//销毁队列
{
    while(Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return 1;
}

int EnQuene(LinkQuene &Q, Customer e)  //插入队尾元素
{
    QuenePtr p;
    p = (QuenePtr)malloc(sizeof(Qnode));
    if(!p) exit(0);
    p->customer.event = e.event; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}

int DeQuene(LinkQuene &Q,Customer &e)
{
    if(Q.front == Q.rear)    return 0;
    QuenePtr p;
    p = Q.front->next;
    e.event=p->customer.event;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return 1;
}

int QueneEmpty(LinkQuene Q)		//判定队空
{
    if(Q.front==Q.rear)
        return 1;
    return 0;
}

void carry(Customer &A,Customer B)	//B入A
{
    A.event = B.event;
    A.number = B.number;
    A.window_ = B.window_;
    A.over = B.over;
}

void PrintWindow(Customer A)
{
    if(A.over==0)
    {
        printf("%c窗口顾客号为%05d，进行的业务是：",A.window_,A.number);    
        switch(A.event)
        {
            case'a':printf("公积金\n");break;
            case'b':printf("银行卡\n");break;
            case'c':printf("理财卡\n");break;
        }
    }
    else 
        printf("%c窗口无顾客办理业务\n",A.window_);
}

void GetIntoWindow(Customer &a,Customer &Window)	//进入窗口办理
{
    a.window_ = Window.window_;
    Window.event = a.event;
    a.over = 0;
    Window.over = 0;
    Window.number = a.number;
    printf("%05d客户进入%c窗口办理",a.number,a.window_);
    switch(a.event)
    {
        case'a':printf("公积金\n");break;
        case'b':printf("银行卡\n");break;
        case'c':printf("理财卡\n");break;
    }
}

int GetOutofWindow(Customer &a,Customer &Window)	//离开窗口
{
    if(Window.number>0)
    {
        carry(a,Window);
        Window.over=1;
        Window.number=NULL;
        printf("编号为%05d的顾客离开%c窗口，该窗口空闲\n",a.number,a.window_);  
        return 1;
    }
    return 0;
}

int main()
{
	//银行总队列
    LinkQuene BankQuene,pubFunds,financialCard,bankCard,Window_avalible_1,Window_avalible_2,Window_avalible_3;

	//三种理财项目排队队列
    InitQuene(BankQuene);			

	//创建三种空闲窗口队列
    InitQuene(pubFunds);			//公积金
	InitQuene(bankCard);			//银行卡
    InitQuene(financialCard);		//理财卡



	//窗口命名
    Customer A,B,C,D,E,F;  

	//创建六个窗口
    A.window_='A';
    B.window_='B';
    C.window_='C';
    D.window_='D';
    E.window_='E';
    F.window_='F';

	//创建三种客户等待队列
	InitQuene(Window_avalible_1);  //A
    InitQuene(Window_avalible_2);  //B C D
    InitQuene(Window_avalible_3);  //E F
	//加入空闲窗口队列
    EnQuene(Window_avalible_1,A);
    EnQuene(Window_avalible_2,B);
    EnQuene(Window_avalible_2,C);
    EnQuene(Window_avalible_2,D);
    EnQuene(Window_avalible_3,E);
    EnQuene(Window_avalible_3,F);

    int judge;
    char leave;
    int j;
    Customer a,b;
    while(1)
    {

        printf("选择操作：添加顾客(0)/顾客进入(1)/顾客离开(2)/显示窗口状态(3)/离开系统(4)");
        scanf("%d",&judge);
        getchar();

        if(judge == 0)		//添加等待顾客
        {
            printf("输入客户信息：\n");
            printf("客户领号：\n");
            scanf("%d",&a.number);
            getchar();
            printf("选择客户业务：公积金(a)/理财卡(b)/银行卡(c)\n");
            scanf("%c",&a.event);

            a.over = -1;
            getchar();
            printf("顾客进入队列\n");
            EnQuene(BankQuene,a);
        }

        if(judge==1)		//顾客进入队列
        {
            j=0;  //判断是否可以进入窗口
            DeQuene(BankQuene,a);
            switch(a.event)
            {
                case'a':
                    EnQuene(pubFunds,a);
                    if(QueneEmpty(Window_avalible_1)==0)
                    {
                        j=1;
                        DeQuene(pubFunds,a);
                        DeQuene(Window_avalible_1,A);
                        GetIntoWindow(a,A);
                    }
                    else 
                        printf("A窗口无空闲，请等待\n");
                    break;

                case'b':
                    EnQuene(financialCard,a);
                    if(QueneEmpty(Window_avalible_2)==0)
                    {
                        j=1;
                        DeQuene(financialCard,a);
                        if(B.event!='b'||B.event!='c')
                        {
                            DeQuene(Window_avalible_2,B);
                            GetIntoWindow(a,B);
                        }
                        else 
                            if(C.event!='b'||C.event!='c')
                            {
                                DeQuene(Window_avalible_2,C);
                                GetIntoWindow(a,C);
                            }
                            else if(D.event!='b'||D.event!='c')
                            {
                                DeQuene(Window_avalible_2,D);
                                GetIntoWindow(a,D);
                            }
                    
                    }
                    else
                        printf("B C D窗口无空闲，请等待\n");
                    break;

                case'c':
                    EnQuene(bankCard,a);
                    if(QueneEmpty(Window_avalible_3)==0)
                    {
                        j=1;
                        DeQuene(bankCard,a);
                        if(E.event!='c')
                        {
                            DeQuene(Window_avalible_3,E);
                            GetIntoWindow(a,E);
                        }
                        else if(F.event!='c')
                        {
                            DeQuene(Window_avalible_3,F);
                            GetIntoWindow(a,F);
                        }
                    }
                    else 
                    {
                        printf("E F窗口无空闲，请等待\n");

                        if(QueneEmpty(Window_avalible_2)==0)
                        {
                            j=1;
                            if(B.event!='b'||B.event!='c')
                            {
                                DeQuene(Window_avalible_2,B);
                                GetIntoWindow(a,B);
                            }
                            else 
                                if(C.event!='b'||C.event!='c')
                                {
                                    DeQuene(Window_avalible_2,C);
                                    GetIntoWindow(a,C);
                                }
                                else if(D.event!='b'||D.event!='c')
                                {
                                    DeQuene(Window_avalible_2,D);
                                    GetIntoWindow(a,D);
                                }
                        }
                        else
                            printf("B C D窗口无空闲，请等待\n");
                    }
                    break;

                default:break;
            }
            if(j==0)
                EnQuene(BankQuene,a);
        }

        if(judge==2)
        {
            printf("选择让哪一窗口的顾客完成业务，离开银行？(A~E)\n");
            scanf("%c",&leave);    

            switch(leave)
            {
                case'A':
					if(GetOutofWindow(b,A))
                        EnQuene(Window_avalible_1,A);
					else 
				        printf("A窗口无人\n");
					break;
                case'B':
					if(GetOutofWindow(b,B))
						EnQuene(Window_avalible_2,B);
					else 
						printf("B窗口无人\n");
					break;
                case'C':
					if(GetOutofWindow(b,C))
						EnQuene(Window_avalible_2,C);
					else 
						printf("C窗口无人\n");
					break;
                case'D':
					if(GetOutofWindow(b,D))
						EnQuene(Window_avalible_2,D);
					else 
						printf("D窗口无人\n");
					break;
                case'E':
					if(GetOutofWindow(b,E))
						EnQuene(Window_avalible_3,E);
					else 
						printf("E窗口无人\n");
					break;
                case'F':
					if(GetOutofWindow(b,F))
						EnQuene(Window_avalible_3,F);
					else 
						printf("F窗口无人\n");
					break;

                default:break;
            }        
        }

        if(judge==3)
        {
            PrintWindow(A);
            PrintWindow(B);
            PrintWindow(C);
            PrintWindow(D);
            PrintWindow(E);
            PrintWindow(F);
        }

        if(judge==4) 
            break;
    }
    return 0;
}
