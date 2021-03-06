// 真上机报告.cpp: 定义控制台应用程序的入口点。
//
//本程序使用带有头结点单链表的存储数据类型。

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	double coefficient;
	int index;
	struct node *next;
}Node;
//定义了链表的结点数据类型

void creatPolynomial(Node * &y);
void polynomialMultiply(Node *y1, Node *y2, Node*&y3);
void dealPolynomial(Node *&y);
void printPolynomial(Node *y);

int main()
{
	system("color f0");//修改控制台的界面颜色使其成为白色背景黑色字体
	Node * y1 = NULL, *y2 = NULL, *y3 = NULL;//此处定义了三个头指针分别代表两个多项式和相乘之后的多项式

	puts("即将进行第一个多项式的输入！");
	creatPolynomial(y1);//读入第一个多项式	
	puts("即将进行第二个多项式的输入！");
	creatPolynomial(y2); //读入第二个多项式
	
	printPolynomial(y1);//将第一个多项式以标准格式打印出来
	printPolynomial(y2);//将第二个多项式以标准格式打印出来


	puts("\n\n\n两个多项式相乘后的结果\n");
	polynomialMultiply(y1, y2, y3);//将两个多项式相乘的结果保存为第三个多项式。
	printPolynomial(y3);//将第三个多项式以标准格式打印出来

	system("pause");
	return 0;
}


/*********************************************************
*creatPolynomial:此函数用来创建一个带有头节点的多项式的，*
*头结点y->nodeNum用来存储多项式的个数，然后依次采用尾插法*
*正序创建单链表											 *
**********************************************************/
void creatPolynomial(Node * &y)
{
	//我们采用尾插法来创建带有头结点的单链表
	puts("\n欢迎开始多项式输入输入！！");
	puts("请按(a b)的格式输入，不同项之间使用一个空格隔开，以$表示结束输入\n");

	y = (Node *)malloc(sizeof(Node));
	y->next = NULL;//定义了头结点

	Node *p, *tail = y;//指针p用来生成新的结点，指针tail用来指向结点的尾部
	p = (Node *)malloc(sizeof(Node));//p申请内存


	while (scanf_s("(%lf%d)", &p->coefficient, &p->index) == 2)//读入输入的项的数据，并判断是否输入正确
	{
		getchar();//吸收掉两个不同的项之前的空格

		tail->next = p;
		tail = tail->next;
		tail->next = NULL;
		//以上三条是将新结点尾插入本单链表
		p = (Node *)malloc(sizeof(Node));
	}
	free(p);//释放掉最后一个循环多申请的一个无用的内存

	char a[100];
	gets_s(a);
	//吸收掉输入者可能在$之后多输入的无用的东西，清空缓冲区
}

/*********************************************************
*polynomialMultiply:此函数将两个多项式链表相乘得到一个多 *
*项式单链表，并不修改y1,y2,仅仅修改y3。					 *
**********************************************************/
void polynomialMultiply(Node *y1, Node *y2, Node*&y3)
{
	y3 = (Node *)malloc(sizeof(Node));	//给y3创建头结点

	Node *p1 = y1->next, *p2 = y2->next, *p3 = NULL, *y3Tail = y3;
	//p1用来遍历y1，p2用来遍历y2，p3用来创建新的结点，y3tail用来指向y3的尾部
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			p3 = (Node *)malloc(sizeof(Node));
			p3->coefficient = p1->coefficient * p2->coefficient;
			p3->index = p1->index + p2->index;
			//创建一个新的结点，产生系数相乘，指数相加的结果。
			y3Tail->next = p3;
			y3Tail = y3Tail->next;
			y3Tail->next = NULL;
			//尾插入y3
			p2 = p2->next;
		}

		p2 = y2->next;//扫描一边后使p2复位开始后一轮的扫描
		p1 = p1->next;
	}

	dealPolynomial(y3);//将乘积之后混乱的单链表进行标准化处理
}

/**********************************************************
*dealPolynomial:此函数用来将相乘得来的混乱多项式进行处理  *
**********************************************************/
void dealPolynomial(Node *&y)
{
	Node *p1 = y->next, *p2 = y->next, *pre = p1;
	//p2用来指向首元结点，然后使寻找插入的恰当位置。p1与pre一前一后去寻找位置错乱的结点的位置
 	if (p1 == NULL || p1->next == NULL || p1->next->next == NULL);//如果除去头结点的结点的个数小于等于2的话，不必进行处理
	else
	{
		//将凌乱的数据进行从指数从大到小的排序
		p1 = p1->next;
		pre = p1;
		p1 = p1->next;
		//将pre指向第二个的有元素的结点，p1指向第三个有元素的结点
		while (p1 != NULL)
		{
			if (p1->index > pre->index)//找到顺序不符合的元素
			{
				while (p2->next->index > p1->index)
					p2=p2->next;
				//找到应该插入的位置
				pre->next = p1->next;
				p1->next = p2->next;
				p2->next = p1;
				p1 = pre->next;
				p2 = y->next;
				//进行移位操作
			}
			else
			{
				pre = p1;
				p1 = p1->next;
				//如果顺序都正确的话就继续搜寻
			}

		}

		//将指数相同的项进行合并
		
		while (p2 != NULL && p2->next != NULL)
		{
			if (p2->index == p2->next->index)
			{
				p2->coefficient += p2->next->coefficient;
				p1 = p2->next;//p1为临时借来的，因为他在上面的作用已经没有了，拿来借用一下。
				p2->next = p1->next;
				free(p1);
			}
			else
				p2 = p2->next;
		}

		//将系数为0的项删除
		p2 = y;
		while (p2->next != NULL)
		{
			if (fabs(p2->next->coefficient - 0)<0.000001)//判断是否接近为0
			{
				p1 = p2->next;//p1为临时借来的，因为他在上面的作用已经没有了，拿来借用一下。
				p2->next = p1->next;
				free(p1);
			}
			else
				p2 = p2->next;
		}
	}

}

/**********************************************************
*printPolynomial:此函数用来将传递来的单链表进行格式化的输出*
***********************************************************/
void printPolynomial(Node *y)
{
	Node *p = y->next;

	printf("y= ");//输出函数经典开头
	if (p != NULL)
	{
		//首先进行第一个项的输出

		if (fabs(p->coefficient - 1)<0.000001 && p->index != 0 && p->index != 1)
			printf("X^%d", p->index);
		//输出系数为1，但是指数不是1或0的项，比如X^2
		else if(fabs(p->coefficient - 1) < 0.000001 && p->index == 1)
			printf("X");
		//输出系数为1并且指数为1的数，只有X
		else if (p->coefficient == -1 && p->index != 0 && p->index != 1)
			printf("-X^%d", p->index);
		//输出系数为-1，但是指数不是1或0的项，比如-X^2
		else if (fabs(p->coefficient + 1)<0.000001 && p->index == 1)
			printf("-X");
		//输出系数为-1并且指数为1的数，只有-X
		else if (p->index == 1)
			printf("%gX", p->coefficient);
		//输出系数为1但是指数不是1的数，例如5X
		else if (p->index == 0)
			printf("%g", p->coefficient);
		//输出常数，比如3.1
		else
			printf("%gX^%d", p->coefficient, p->index);
		//输出普通的数,比如3.1X^2
		p = p->next;

		//进行之后的输出
		while (p != NULL)
		{
			if ((p->coefficient - 0)>0.000001)
				printf("+");
			//判断时候是正数
			if (fabs(p->coefficient - 1) < 0.000001 && p->index != 0 && p->index != 1)
				printf("X^%d", p->index);
			//输出系数为1，但是指数不是1或0的项，比如X^2
			else if (fabs(p->coefficient - 1) < 0.000001 && p->index == 1)
				printf("X");
			//输出系数为1并且指数为1的数，只有X
			else if (p->coefficient == -1 && p->index != 0 && p->index != 1)
				printf("-X^%d", p->index);
			//输出系数为-1，但是指数不是1或0的项，比如-X^2
			else if (fabs(p->coefficient + 1) < 0.000001 && p->index == 1)
				printf("-X");
			//输出系数为-1并且指数为1的数，只有-X
			else if (p->index == 1)
				printf("%gX", p->coefficient);
			//输出系数为1但是指数不是1的数，例如5X
			else if (p->index == 0)
				printf("%g", p->coefficient);
			//输出常数，比如3.1
			else
				printf("%gX^%d", p->coefficient, p->index);
			//输出普通的数,比如3.1X^2
			p = p->next;
		}
	}
	else
		printf("0");
	//如果是空链表的话就输出0
	
	puts("");
}
