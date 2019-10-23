/*

设计一个算法求出单链表的倒数第m个结点，要求不得求出链表长度，不得对链表进行逆转，如果找到这样的结点就返回它的地址，如果没有就返回NULL。

*/
#include <iostream>
using namespace std;

/**********************链表结构******************************/
template<typename DataType>class ListNode;

template<typename DataType>class LinkList
{
public:
	LinkList()
	{
		head = new ListNode<DataType>(777);
	}

	LinkList(ListNode<DataType>* firstNode)
	{
		head = firstNode;
	}

	//析构函数 
	~LinkList()
	{
		delete head;
	}

	bool insertNode(int index, DataType newData);
	bool insertNode(DataType newData);
	bool removeNode(ListNode<DataType>* q);
	ListNode<DataType>* findNode(DataType value);
	void cleanLink();
	DataType getNodeData(const int index);
	int getLength();
	ListNode<DataType>* getNode(int i);


private:
	ListNode<DataType>* head;
};

/*****************定义链表结点***********************/
template<typename DataType> class ListNode
{
public:
	ListNode()
	{
		next = NULL;
	}

	ListNode(const DataType item, ListNode<DataType>*nodeNext = NULL)
	{
		data = item;
		next = nodeNext;
	}

	~ListNode()
	{
		next = NULL;
	}

	DataType getData()
	{
		return data;
	}

	ListNode<DataType>* getNext()
	{
		return next;
	}

private:
	friend class LinkList<DataType>;
	ListNode<DataType>* next;
	DataType data;
};


template<typename DataType>
bool LinkList<DataType>::insertNode(int index, DataType newData)
{
	ListNode<DataType>* p = head;
	int j;
	for (j = 1; j <= i - 1; j++)
	{
		p = p->next;
		if (NULL == p)
		{
			break;//如果指针为空，则不存在该结点或已到达表尾
		}
	}
	if (NULL == p && j < (i - 1))
	{
		std::cout << "插入位置无效" << std::endl;
		return false;
	}
	ListNode<DataType>* node = new ListNode<DataType>(newData);
	node->next = p->next;
	p->next = node;
	return true;
}

//链表表尾添加元素
template<typename DataType>bool LinkList<DataType>::insertNode(DataType newData)
{
	ListNode<DataType>* p = head;
	ListNode<DataType>* node = new ListNode<DataType>(newData);
	if (NULL == node)
	{
		return false;
	}
	while (NULL != p->next)
	{
		p = p->next;//遍历单链表，找到表尾
	}

	p->next = node;
	return true;
}

template<typename DataType>
bool LinkList<DataType>::removeNode(ListNode<DataType>* q)
{
	if (NULL == q)
	{
		std::cout << "待删除结点不存在！" << std::endl;
		return false;
	}
	ListNode<DataType>* tempPointer = head;
	while (tempPointer->next != q)
	{
		tempPointer = tempPointer->next;
	}

	tempPointer->next = q->next;
	delete q;
	return true;
}

template<typename DataType>
ListNode<DataType>* LinkList<DataType>::findNode(DataType value)
{
	ListNode<DataType>* currentPointer = head;
	//判定游标指针结点的值是否与value相等
	while (NULL != currentPointer && value != currentPointer->next)
	{
		currentPointer = currentPointer->next;
	}
	if (NULL == currentPointer)
	{
		std::cout << "没有找到该结点！程序退出。" << std::endl;
		exit(1);
	}
	else
	{
		return currentPointer;//返回所找到的结点的指针
	}
}

template<typename DataType>
void LinkList<DataType>::cleanLink()
{
	ListNode<DataType>* current = head;
	while (NULL != head->next)
	{
		current = head->next;
		head->next = current->next;
		delete current;
	}
}

template<typename DataType>
DataType LinkList<DataType>::getNodeData(int index)
{
	int linkLength = getLength();
	if (index<1 || index > linkLength)
	{
		std::cout << "结点不存在！" << std::endl;
		return false;
	}
	else
	{
		ListNode<DataType>* pmove = head->next;
		for (int i = 1; i < index && NULL!=pmove; i++)
		{
			pmove = pmove->next;
		}
		return pmove->getData();
	}
}

template<typename DataType>
int LinkList<DataType>::getLength()
{
	int count = 0;
	ListNode<DataType>* p = head->next;
	while (NULL != p)
	{
		p = p->next;
		count++;
	}
	return count;
}

template<typename DataType>
ListNode<DataType>* LinkList<DataType>::getNode(int i)
{
	ListNode<DataType>* p = head->next;
	int j;
	if (i<1 || i>getLength() - 1)
	{
		return false;
	}
	for (j = 1; j < i; j++)
	{
		p = p->next;
		if (NULL == p)
		{
			break;
		}
	}
	if (NULL == p && j < i - 1)
	{
		return false;
	}
	return p;
}


//查找倒数第m个结点
ListNode<int>* searchNodeM(LinkList<int>* link, int m)
{
	ListNode<int>* p = link->getNode(1);
	if (NULL != p && m>0)
	{
		for (int i = 1; i < m; i++)
		{
			p = p->getNext();
			if (NULL == p)
			{
				std::cout << "该链表没有倒数第m个结点" << std::endl;
				return NULL;
			}
		}
	}

	ListNode<int>* q = link->getNode(1);
	while (p->getNext() != NULL)
	{
		p = p->getNext();
		q = q->getNext();
	}

	return q;
}


int main()
{
	LinkList<int>* head = new LinkList<int>();
	int m;
	for (int i = 1; i <= 10; i++)
	{
		head->insertNode(i * 3);
	}
	
	cout << "请输入m的值：";
	cin >> m;

	ListNode<int>* p = searchNodeM(head, m);
	for (int i = 1; i <= 10; i++)
	{
		cout << head->getNodeData(i) << " ,";
	}
	cout << endl;

	cout << "倒数第" << m << "个结点：" << p->getData() << endl;

	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}


/******

注意 LinkList 里面都是 ListNode<DataType> 的形式。

*****/
