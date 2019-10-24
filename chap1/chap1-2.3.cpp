/*

【循环】链表

*/
#include <iostream>
using namespace std;

template<typename Datatype>class CircularList;
/**********************【循环】链表 结点定义******************************/
template<typename DataType> class CircularListNode
{

//public:
private:
	friend class CircularList<DataType>;
	CircularListNode()
	{
		m_pnext = NULL;
	}

	CircularListNode(DataType data, CircularListNode* nextOne = NULL)
	{
		m_data = data;
		m_pnext = nextOne;
	}
	~CircularListNode()
	{
		m_pnext = NULL;
	}

public:
	DataType getData();


public:
	DataType m_data; //数据域
	CircularListNode<DataType>* m_pnext;//指向后继结点的指针域

};

//获取结点中的数据
template<typename DataType>
DataType CircularListNode<DataType>::getData()
{
	return this->m_data;
}


/*******************循环链表定义***********************/
template<typename DataType> class CircularList
{
public:
	CircularList()
	{
		head = new CircularListNode<DataType>();// 前面声明了友元类，所以这里访问是合法的
		head->m_pnext = head; ////【循环链表】为空的时候，head的next是指向自己的  *****
	}

	~CircularList()
	{
		cleanUp();
		delete head;
	}

public:
	void cleanUp();
	int getLength();

	CircularListNode<DataType>* findNode(int i,DataType value);
	//在链表尾部插入元素
	bool insertNode(DataType item);
	//删除具有value值的所有元素
	bool deleteNode(DataType value);
	//获取指定元素的值
	DataType getValue(CircularListNode<DataType>* node);
	void printLink();

private:
	CircularListNode<DataType>* head;//头指针
};

/******************************清空链表***********************************/
template<typename DataType>
void CircularList<DataType>::cleanUp()
{
	CircularListNode<DataType>* p;//设置指示删除结点的指针	
	while (head->m_pnext != head)
	{
		p = head->m_pnext;//初始化指示指针
		head->m_pnext = p->m_pnext;//将头指针指向下一个结点的下一个结点
		delete p;//回收空间
	}
}

template<typename DataType>
int CircularList<DataType>::getLength()
{
	int length = 0;
	CircularListNode<DataType>* p= head;//设置游标指针
	while (p->m_pnext != head)//游走指针，直到指向头指针时结束.
	{
		p = p->m_pnext;
		length++;
	}
	return length;
}

template<typename DataType>
CircularListNode<DataType>* CircularList<DataType>::findNode(int i,DataType value)
{
	int count = 0;
	CircularListNode<DataType>* p = head;
	while (cout != i)
	{
		//遍历链表，寻找值与value相等的结点
		p = p->m_pnext;
		if (p->m_data == value)
		{
			count++;//记录这是第几个符合条件的结点
		}
		if (p == head)
		{
			return NULL;//链表中没有满足条件的结点
		}
	}
	return p;
}

//在链表尾部插入结点
template<typename DataType>
bool CircularList<DataType>::insertNode(DataType item)
{
	//创建新结点，设置游标
	CircularListNode<DataType>* newNode = new CircularListNode<DataType>(item);
	CircularListNode<DataType>* pmove = head;//游标指针

	if (NULL == newNode)
	{
		cout << "内存分配失败，新结点无法创建" << endl;
		return false;
	}

	//寻找尾结点
	while (pmove->m_pnext != head)
	{
		pmove = pmove->m_pnext;
	}


	/*******************************************循环链表【插入结点】*****************************************************/
	newNode->m_pnext = pmove->m_pnext;	//新结点的next指向head
	pmove->m_pnext = newNode;  //插入新结点
	/*******************************************循环链表【插入结点】*****************************************************/



	return true;
}


template<typename DataType>
bool CircularList<DataType>::deleteNode(DataType value)
{
	int count = 0;
	CircularListNode<DataType>* pmove = head;
	CircularListNode<DataType>* pdel = head->m_pnext;

	/**********************************循环链表【删除结点】*********************************/
	while (pdel != head)//遍历链表
	{
		if (pdel->m_data == value)
		{
			pmove->m_pnext = pdel->m_pnext;
			delete pdel;

			count++;
			pdel = pdel->m_pnext;
		}
		else
		{
			pmove = pdel;//结点不符合，直接移动指针
			pdel = pdel->m_pnext;
		}
	}
	/**********************************循环链表【删除结点】*********************************/

	//如果删除结点数为0，说明没有符合条件的结点
	if (0 == count)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<typename DataType>
DataType CircularList<DataType>::getValue(CircularListNode<DataType>* node)
{	
	return node->m_data;
}


template<typename DataType>
void CircularList<DataType>::printLink()
{
	cout << "printCircularList:" << endl;
	CircularListNode<DataType>* pmove = head->m_pnext;
	while (pmove != head)
	{
		cout << getValue(pmove) << " ,";
		pmove = pmove->m_pnext;
	}
	cout << endl;
}


int main()
{
	CircularList<int>* m_pCircularLinkList = new CircularList<int>();

	for (int i = 1; i <= 10; i++)
	{
		m_pCircularLinkList->insertNode(i * 3);
	}

	m_pCircularLinkList->printLink();

	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}


/******



*****/
