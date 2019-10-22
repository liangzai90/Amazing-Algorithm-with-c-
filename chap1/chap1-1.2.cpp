/*

用C++实现一个链表表,并可以实现插入、修改元素、删除元素和输出整个链表表的功能。

*/
#include <iostream>
using namespace std;

/**********************链表结构******************************/

template<typename DataType>class ListNode;

template<typename DataType>class LinkList
{
public:
	//无参数构造函数
	LinkList()
	{
		head = new ListNode<DataType>(666);
	}
	//有参数构造函数
	LinkList(ListNode<DataType>* node)
	{
		head = node;
	}
	~LinkList()
	{
		delete head;
	}

	bool insertNode(int index, DataType newData);//插入结点
	bool removeNode(ListNode<DataType>* q);//删除结点
	ListNode<DataType>* findNode(DataType value);//查找指定值的结点并返回地址
	void cleanLink();//清空链表
	DataType getNodeData(const int index);//获取结点数据
	void printNode();//输出所有的结点
private:
	ListNode<DataType>* head;//头结点
};


/**********************定义链表结点******************************/
template<typename DataType>class ListNode
{
public:
	ListNode()
	{
		next = NULL;
	}
	ListNode(DataType item, ListNode<DataType>*nextNode = NULL)
	{
		data = item;
		next = nextNode;
	}
	~ListNode()
	{
		next = NULL;
	}

	//获取结点内的数据
	DataType getData()
	{
		return data;
	}

	//获取指针域
	ListNode* getNext()
	{
		return next;
	}

private:
	friend class LinkList<DataType>;//将LinkList设为友元类，方便其对node的成员数据和方法的访问
	ListNode<DataType>* next;//指向下一个结点的指针
	DataType data;
};



/*********************在链表的第i个结点后插入新结点*******************************/
template<typename DataType>bool LinkList<DataType>::insertNode(int i, DataType newData)
{
	ListNode<DataType>* p = head;//设置游标指针，初始化为头结点地址
	int j;
	for (j = 1; j <= i - 1; j++)
	{
		p = p->next;
		if (NULL == p)//如果指针为空，则不存在该结点，或已到表尾
		{
			break;
		}
	}
	//指针为空且没有到第i个位置，说明不存在第i个结点
	if (NULL == p && j < (i - 1))
	{
		std::cout << "插入位置无效！" << endl;
		return false;
	}

	//简历新结点node
	ListNode<DataType>* node = new ListNode<DataType>(newData);
	//将node的next指针赋值为p的后继结点地址
	node->next = p->next;
	//p的后继指针指向node
	p->next = node;
	return true;
}


///*********************在单链表表尾添加新结点*******************************/
//template<typename DataType>bool LinkList<DataType>::insertNode(DataType newData)
//{
//	ListNode<DataType>* p = head;
//	ListNode<DataType>* node = new ListNode<DataType>(newData);//创建新节点
//	//如果新结点内存分配失败，则返回false
//	if (NULL == node)
//	{
//		return false;
//	}
//	//遍历单链表，找到尾结点
//	while (NULL != p->next)
//	{
//		p = p->next;
//	}
//	p->next = node;//将尾结点next指针指向新结点
//	return true;
//}

/********************删除指定结点********************************/
template<typename DataType>bool LinkList<DataType>::removeNode(ListNode<DataType>* q)
{
	if (NULL == q)//判断待删除结点是否存在
	{
		std::cout << "待删除结点不存在！" << std::endl;
		return false;
	}
	ListNode<DataType>* tempPointer = head;//设置游标，初始化为头结点
	while (tempPointer->next != q)
	{
		tempPointer = tempPointer->next;
	}
	tempPointer->next = q->next;//将q结点的后继结点地址赋值给其前驱结点的next指针
	delete q;//回收结点q的空间
	return true;
}

/***********************查找指定值的结点*****************************/
template<typename DataType>ListNode<DataType>* LinkList<DataType>::findNode(DataType value)
{
	ListNode<DataType>* currentPointer = head;//设置游标指针
	//判定游标指针所指结点的值是否与value相等
	while (currentPointer != NULL && currentPointer->data != value)
	{
		currentPointer = currentPointer->next;
	}
	if (NULL == currentPointer)
	{
		std::cout << "没有找到该结点！程序异常退出！" << std::endl;
		exit(1);
	}
	else
	{
		return currentPointer;//返回所找到的结点的指针
	}
}

/**********************清空链表******************************/
template<typename DataType>void LinkList<DataType>::cleanLink()
{
	ListNode<DataType>* current = head;//设置游标指针
	while (head->next != NULL) //判定head的后继结点是否为NULL
	{
		current = head->next;//将current指向head的后继结点
		head->next = current->next;//将current的后继地址赋值给head的next域
		delete current;//回收current结点所占的空间
	}
}


/************************获取结点数据****************************/
template<typename DataType>DataType LinkList<DataType>::getNodeData(int index)
{
	ListNode<DataType>* currentPointer = head;//设置游标指针
	int iTempIndex = 0;
	//判定游标指针所指结点的值是否与value相等
	while (currentPointer != NULL)
	{
		currentPointer = currentPointer->next;
		if (index == iTempIndex)
		{
			break;
		}
		iTempIndex++;
	}
	if (NULL == currentPointer)
	{
		std::cout << "没有找到该结点！程序异常退出！" << std::endl;
		exit(1);
	}
	else
	{
		return currentPointer->data;//返回所找到的结点的值
	}
}

//void printNode();//
/**********************输出所有的结点******************************/
template<typename DataType>void LinkList<DataType>::printNode()
{
	cout << "printNode:" << endl;
	ListNode<DataType>* currentPointer = head;//设置游标指针
	//判定游标指针所指结点的值是否与value相等
	while (currentPointer != NULL )
	{
		cout << currentPointer->data << " ,";
		currentPointer = currentPointer->next;
	}
	cout << endl;
}



int main()
{
	LinkList<int>* head = new LinkList<int>();

	for (int i = 1; i <= 10; i++)
	{
		head->insertNode(i,i);
	}

	head->printNode();


	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}




/******

注意 LinkList 里面都是 ListNode<DataType> 的形式。

*****/
