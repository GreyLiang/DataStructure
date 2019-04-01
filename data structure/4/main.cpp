#include <stdio.h>
#include <stdlib.h>

/*
ĳ����Ӫҵ������6��Ӫҵ���ڣ������Ŷ�ϵͳ�㲥�кţ�
�����е�ҵ���Ϊ���������п�����ƿ������֡�
������ҵ��ָ��1�Ŵ��ڣ����п�ҵ��ָ��2��3��4�Ŵ��ڣ���ƿ�ҵ��ָ��5��6�Ŵ��ڡ�
�����5��6�Ŵ���ȫæ����2��3��4�Ŵ����п���ʱ��
��ƿ�ҵ��Ҳ�����ڿ��е�2��3��4�Ŵ���֮һ����
�ͻ���š�ҵ����ɿ�����Ϊ������Ϣ��Ҫ�������ʱ��ʾ6��Ӫҵ���ڵ�״̬��
*/

typedef struct
{
    int number;  //�ͻ����
    char event;  //������������
    char over;  //�Ƿ����
    char window_;  //���ڴ���
}Customer;

typedef struct Qnode
{
    Customer customer;
    struct Qnode *next;
}Qnode, *QuenePtr;

typedef struct 
{
    QuenePtr front;  //��ͷָ��
    QuenePtr rear;  //��βָ��
}LinkQuene;

int InitQuene(LinkQuene &Q)		//���
{
    Q.front = (QuenePtr) malloc (sizeof(Qnode));
    Q.rear = Q.front;
    if(!Q.front) exit(0);
    Q.front->next = NULL;
    return 1;
}

int DestoryQuene(LinkQuene &Q)	//���ٶ���
{
    while(Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return 1;
}

int EnQuene(LinkQuene &Q, Customer e)  //�����βԪ��
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

int QueneEmpty(LinkQuene Q)		//�ж��ӿ�
{
    if(Q.front==Q.rear)
        return 1;
    return 0;
}

void carry(Customer &A,Customer B)	//B��A
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
        printf("%c���ڹ˿ͺ�Ϊ%05d�����е�ҵ���ǣ�",A.window_,A.number);    
        switch(A.event)
        {
            case'a':printf("������\n");break;
            case'b':printf("���п�\n");break;
            case'c':printf("��ƿ�\n");break;
        }
    }
    else 
        printf("%c�����޹˿Ͱ���ҵ��\n",A.window_);
}

void GetIntoWindow(Customer &a,Customer &Window)	//���봰�ڰ���
{
    a.window_ = Window.window_;
    Window.event = a.event;
    a.over = 0;
    Window.over = 0;
    Window.number = a.number;
    printf("%05d�ͻ�����%c���ڰ���",a.number,a.window_);
    switch(a.event)
    {
        case'a':printf("������\n");break;
        case'b':printf("���п�\n");break;
        case'c':printf("��ƿ�\n");break;
    }
}

int GetOutofWindow(Customer &a,Customer &Window)	//�뿪����
{
    if(Window.number>0)
    {
        carry(a,Window);
        Window.over=1;
        Window.number=NULL;
        printf("���Ϊ%05d�Ĺ˿��뿪%c���ڣ��ô��ڿ���\n",a.number,a.window_);  
        return 1;
    }
    return 0;
}

int main()
{
	//�����ܶ���
    LinkQuene BankQuene,pubFunds,financialCard,bankCard,Window_avalible_1,Window_avalible_2,Window_avalible_3;

	//���������Ŀ�ŶӶ���
    InitQuene(BankQuene);			

	//�������ֿ��д��ڶ���
    InitQuene(pubFunds);			//������
	InitQuene(bankCard);			//���п�
    InitQuene(financialCard);		//��ƿ�



	//��������
    Customer A,B,C,D,E,F;  

	//������������
    A.window_='A';
    B.window_='B';
    C.window_='C';
    D.window_='D';
    E.window_='E';
    F.window_='F';

	//�������ֿͻ��ȴ�����
	InitQuene(Window_avalible_1);  //A
    InitQuene(Window_avalible_2);  //B C D
    InitQuene(Window_avalible_3);  //E F
	//������д��ڶ���
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

        printf("ѡ���������ӹ˿�(0)/�˿ͽ���(1)/�˿��뿪(2)/��ʾ����״̬(3)/�뿪ϵͳ(4)");
        scanf("%d",&judge);
        getchar();

        if(judge == 0)		//��ӵȴ��˿�
        {
            printf("����ͻ���Ϣ��\n");
            printf("�ͻ���ţ�\n");
            scanf("%d",&a.number);
            getchar();
            printf("ѡ��ͻ�ҵ�񣺹�����(a)/��ƿ�(b)/���п�(c)\n");
            scanf("%c",&a.event);

            a.over = -1;
            getchar();
            printf("�˿ͽ������\n");
            EnQuene(BankQuene,a);
        }

        if(judge==1)		//�˿ͽ������
        {
            j=0;  //�ж��Ƿ���Խ��봰��
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
                        printf("A�����޿��У���ȴ�\n");
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
                        printf("B C D�����޿��У���ȴ�\n");
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
                        printf("E F�����޿��У���ȴ�\n");

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
                            printf("B C D�����޿��У���ȴ�\n");
                    }
                    break;

                default:break;
            }
            if(j==0)
                EnQuene(BankQuene,a);
        }

        if(judge==2)
        {
            printf("ѡ������һ���ڵĹ˿����ҵ���뿪���У�(A~E)\n");
            scanf("%c",&leave);    

            switch(leave)
            {
                case'A':
					if(GetOutofWindow(b,A))
                        EnQuene(Window_avalible_1,A);
					else 
				        printf("A��������\n");
					break;
                case'B':
					if(GetOutofWindow(b,B))
						EnQuene(Window_avalible_2,B);
					else 
						printf("B��������\n");
					break;
                case'C':
					if(GetOutofWindow(b,C))
						EnQuene(Window_avalible_2,C);
					else 
						printf("C��������\n");
					break;
                case'D':
					if(GetOutofWindow(b,D))
						EnQuene(Window_avalible_2,D);
					else 
						printf("D��������\n");
					break;
                case'E':
					if(GetOutofWindow(b,E))
						EnQuene(Window_avalible_3,E);
					else 
						printf("E��������\n");
					break;
                case'F':
					if(GetOutofWindow(b,F))
						EnQuene(Window_avalible_3,F);
					else 
						printf("F��������\n");
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
