#pragma warning(disable:4996)  //注意此行代码如果不添加，vs2019编译不过
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct NODE
{
	//char Name[20];
	int no;
	int score;
	struct NODE *pNext;  //装着下一块空间的地址
}Node;

Node *pHead = NULL;  //指向链表的头节点
Node* pTail = NULL;  //指向链表的尾节点


void CreateList(int no,int score)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->no = no;//(*tmp).no = no;两种写法等效
	tmp->score = score;
	tmp->pNext = NULL;  //至此一块空间已经被创建好了

	//二：连接链表
	if (pHead == NULL)  //可以判断这个链表是第一个节点
	{
		pHead = tmp;  //把tmp值拿出来放在pHead里面
	}
	else
	{
		pTail->pNext = tmp;
	}
	pTail = tmp;
}

void FindNode()
{
	int findno = 0;
	scanf("%d", &findno);
	Node* t = pHead;
	while (t != NULL)
	{
		if (t->no == findno)
		{
			printf("要查找的学号的成绩为 %d\n", t->score);
			break;
		}
		t = t->pNext;
	}
}

void DeletePrint(int no)
{
	Node *t = pHead;
	Node *pre = NULL;
	while (t != NULL)
	{
		if (t->no == no)
		{
			if (t == pHead)
			{ 
				pHead = pHead->pNext;
			}
			else if (t == pTail)
			{
				pTail = pre;
				pTail->pNext = NULL;
			}
			else
			{
				pre->pNext = t->pNext;
				free(t);
			}
			break;
		}
		pre = t;
		t = t->pNext;
	}
}

void PrintList()
{
	Node *t = pHead;
	while (t)
	{
		printf("学号 %d 的成绩为 %d \n", t->no, t->score);
		t = t->pNext;
	}
}

void FreeList()
{
	Node *t = pHead;
	Node *next = NULL;
	while (t)
	{
		next = t->pNext;
		free(t);
		t = next;
		if (t == NULL)
		{
			break;
		}
	}
	pHead = NULL;
	pTail = NULL;
}

void InsetNode()
{
	printf("请输入要插入哪个节点前:\n");
	int no = 0;
	scanf("%d", &no);
	printf("请输入要插入的节点数据:\n");
	int number = 0;
	int score = 0;
	scanf("%d %d", &number, &score);

	//先找到要插入的为止
	Node *t = pHead;
	Node *pre = NULL;
	while (t != NULL)
	{
		if (t->no == no)
		{
			//添加一个节点
			Node* p = malloc(sizeof(Node));
			p->no = number;
			p->score = score;
			p->pNext = NULL;
			if (t == pHead)
			{
				p->pNext = pHead;
				pHead = p;
			}
	/*		else if (t == pTail)
			{
				pTail = pre;
				pTail->pNext = NULL;
			}*/
			else
			{
				pre->pNext = p;
				p->pNext = t;
			}
			return;
		}
		pre = t;
		t = t->pNext;
	}
	CreateList(number, score);
}

int main()
{
	printf("请输入学生信息:\n");
	int no;
	int score;

	while (1)
	{
		scanf(" %d %d", &no, &score);
		if (no < 0)
		{
			printf("学生信息输入完毕:\n");
			break;
		}
		//一：要想存储数据，需要有地方去存储
		CreateList(no, score);
	}

	//链表的查找功能
	FindNode();
	
	//打印整个链表
	PrintList();

	//删除指定节点
	printf("请输入要删除的学号:");
	scanf("%d", &no);
	DeletePrint(no);

	PrintList();
	
	//在指定节点前增加一条数据
	InsetNode();
	PrintList();
	//释放节点
	FreeList();

	return 0;
}

