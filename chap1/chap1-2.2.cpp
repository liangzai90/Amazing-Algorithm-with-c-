/*

双向链表

*/
#include <iostream>
using namespace std;


template<typename DataType> class DoubleList;
/**********************双向链表结点定义******************************/
template<typename DataType> class DoubleListNode
{

//public:
private:
	friend class DoubleList<DataType>; ////定义了友元类，所以【DoubleList类】可以访问private里面的声明的构造函数
	//无参构造函数
	DoubleListNode() :m_pprior(NULL), m_pnext(NULL){};
	//带参数构造函数 初始化数据域和指针域
	DoubleListNode(const DataType item, DoubleListNode<DataType>* prior = NULL, DoubleListNode<DataType>*next = NULL) :m_data(item), m_pprior(prior), m_pnext(next){};
	//析构函数
	~DoubleListNode(){
		m_pprior = NULL;
		m_pnext = NULL;
	}

public:
	DataType getData();

private:
	DataType m_data; //数据域
	DoubleListNode<DataType>* m_pprior;//指向前去结点的指针域
	DoubleListNode<DataType>* m_pnext;//指向后继结点的指针域

};

//获取结点中的数据
template<typename DataType>
DataType DoubleListNode<DataType>::getData()
{
	return this->m_data;
}


/*******************双向链表定义***********************/
template<typename DataType> class DoubleList
{
public:
	DoubleList()
	{
		head = new DoubleListNode<DataType>();// 前面声明了友元类，所以这里访问是合法的
	}

	~DoubleList()
	{
		cleanDoubleLink();
		delete head;
	}

public:
	void cleanDoubleLink();
	int getLength();
	DoubleListNode<DataType>* findNode(int i = 0);
	DoubleListNode<DataType>* findData(DataType item);//寻找具有给定值数据的结点
	bool insertNode(DataType item, int i = 0);
	bool removeNode(int i = 0);
	DataType getData(int i = 0);
	void printLink();

private:
	DoubleListNode<DataType>* head;//头指针
};

/******************************清空链表***********************************/
template<typename DataType>
void DoubleList<DataType>::cleanDoubleLink()
{
	DoubleListNode<DataType>* pmove = head->m_pnext;
	DoubleListNode<DataType>* pdel;
	//遍历链表，计算结点数
	while (NULL != pmove)
	{
		pdel = pmove->m_pnext;
		pmove = pdel->m_pnext;
		delete pdel;
	}
	head->m_pnext = NULL;
}

template<typename DataType>
int DoubleList<DataType>::getLength()
{
	int count = 0;
	DoubleListNode<DataType>* pmove = head->m_pnext;
	while (NULL != pmove)
	{
		pmove = pmove->m_pnext;
		count++;
	}
	return count;
}

template<typename DataType>
DoubleListNode<DataType>* DoubleList<DataType>::findNode(int n)
{
	if (n < 1)
	{
		cout << "非有效位置" << endl;
		return NULL;
	}
	DoubleListNode<DataType>* pmove = head->m_pnext;
	for (int i = 1; i < n; i++)
	{
		pmove = pmove->m_pnext;
		if (NULL == pmove)
		{
			cout << "不存在指定结点" << endl;
			return NULL;
		}
	}
	return pmove;  //pmove就是第n个结点
}

template<typename DataType>
bool DoubleList<DataType>::insertNode(DataType item, int n /* = 0 */)
{
	int i;
	if (n < 1)
	{
		cout << "插入位置无效" << endl;
		return 0;
	}

	//创建新结点，设置游标
	DoubleListNode<DataType>* newNode = new DoubleListNode<DataType>(item);
	DoubleListNode<DataType>* pmove = head;

	if (NULL == newNode)
	{
		cout << "内存分配失败，新结点无法创建" << endl;
		exit(1);
	}
	for (i = 1; i < n; i++)
	{
		pmove = pmove->m_pnext;
		if (NULL == pmove)
		{
			cout << "超出链表长度" << endl;
			return 0;
		}
	}



	/*******************************************双向链表【插入结点】*****************************************************/
	//插入新结点
	newNode->m_pnext = pmove->m_pnext;
	if (NULL != pmove->m_pnext) ///判断是否在链表尾部添加结点
	{
		pmove->m_pnext->m_pprior = newNode;
	}

	pmove->m_pnext = newNode;
	newNode->m_pprior = pmove;
	/*******************************************双向链表【插入结点】*****************************************************/



	return 1;
}


template<typename DataType>
bool DoubleList<DataType>::removeNode(int n)
{
	if (n<1 || n>getLength())
	{
		cout << "位置不合法" << endl;
		return false;
	}
	DoubleListNode<DataType>* pmove = head->m_pnext;
	DoubleListNode<DataType>* pdel;
	for (int i = 1; i < n; i++)
	{
		pmove = pmove->m_pnext;
		if (NULL == pmove)
		{
			cout << "超出了链表范围" << endl;
			return false;
		}
	}

	/**********************************双向链表【删除结点】*********************************/
	//删除结点
	pdel = pmove;

	if (NULL != pmove->m_pnext)
	{
		pmove->m_pnext->m_pprior = pdel->m_pprior;//判断是否在链表尾部删除
	}
	pmove->m_pprior->m_pnext = pdel->m_pnext;
	delete pdel;
	/**********************************双向链表【删除结点】*********************************/

	return true;
}

template<typename DataType>
DataType DoubleList<DataType>::getData(int n)
{
	if (n<1 || n>getLength())
	{
		cout << "指定位置无效" << endl;
		exit(1);
	}
	DoubleListNode<DataType>* pmove = head->m_pnext;
	for (int i = 1; i < n; i++)
	{
		pmove = pmove->m_pnext;
		if (NULL == pmove)
		{
			cout << "指定结点不存在！" << endl;
			exit(1);
		}
	}
	if (NULL == pmove)
	{
		cout << "结点不存在" << endl;
		return NULL;
	}
	return pmove->m_data;
}

//获取具有指定值数据的结点
template<typename DataType>
DoubleListNode<DataType>* DoubleList<DataType>::findData(DataType item)
{
	DoubleListNode<DataType>* pmove = head->m_pnext;
	if (NULL == pmove)
	{
		cout << "链表是空表！" << endl;
		exit(1);
	}
	while (item != pmove->getData())
	{
		pmove = pmove->m_pnext;
		if (NULL == pmove)
		{
			cout << "没有所查找的结点" << endl;
			exit(1);
		}
	}
	return pmove;
}

template<typename DataType>
void DoubleList<DataType>::printLink()
{
	cout << "printDoubleList:" << endl;
	DoubleListNode<DataType>* pmove = head->m_pnext;
	while (NULL != pmove)
	{
		cout << pmove->getData() << " ,";
		pmove = pmove->m_pnext;
	}
	cout << endl;
}


int main()
{
	DoubleList<int>* m_pLinkList = new DoubleList<int>();

	for (int i = 1; i <= 10; i++)
	{
		m_pLinkList->insertNode(i * 3, i);
	}

	m_pLinkList->printLink();

	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}


/******



*****/
