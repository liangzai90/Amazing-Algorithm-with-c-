/*

判断单链表里面是否有环，求出环的位置

设置2个指针，指针p每次走1步，指针q每次走2步。
等到他们相遇的时候，已经走过了S步。

假设链表长度是L,
链表起点到环起点距离是a,
环长度是r,
假设p,q指针相遇的时候，慢(p)指针已经在环内走了X步，总共走了S步，
那么快(q)指针总走了2S步

再相遇的时候，快指针一定已经走了n圈环形路线了，所以有 ：2S = S + nr , 所以有 S = nr 
走了的路S由2部分构成，a+X,所以  S = a + X 

所以 a + X = nr = (n-1)r + r = (n-1) + L - a 
a = (n-1)r + L-a - X    (公式4)

由于 (n-1)r + L-a 表示的是相遇点的位置，且 L-a 等于环长度r,那么 L-a - X表示相遇点继续前进到达环起始位置的距离。
公式4提现的意思就是链表起点到环的起点长度a，与快慢指针相遇点到环的起始位置的长度相等。这个结论是我们解决这道题目的理论基础。


因此，相遇之后，再走a步就可以到达环起点。

*/
#include <iostream>
using namespace std;


#include <iostream>

/**************链表结构***************/
template<typename DataType> class ListNode;
template <typename DataType> class LinkList
{
public:

	LinkList()
	{
		head = new ListNode<DataType>();
	}

	LinkList(ListNode<DataType> *firstNode)
	{
		head = firstNode;
	}

	//析构函数
	~LinkList()
	{

		delete head;
	}

	//在第i个结点后插入结点
	bool insertNode(int index, DataType newData);
	//在表尾添加新结点
	bool insertNode(DataType newData);
	bool insertNode(ListNode<DataType>* node);
	//删除结点
	bool removeNode(ListNode<DataType> *q);
	//查找指定值的结点并返回地址
	ListNode<DataType>* findNode(DataType value);
	//清空链表
	void cleanLink();
	//获取第i个结点中的数据
	DataType getNodeData(const int index);
	//获取链表长度
	int getLength();
	//查找链表第i个元素
	ListNode<DataType>* getNode(int i);
	void printLinkList();
	
private:
	ListNode<DataType> *head;              //头结点
};

/*************定义链表结点****************/
template <typename DataType> class ListNode
{
public:
	ListNode()
	{
		next = NULL;
	}
	ListNode(const DataType item, ListNode<DataType> *nodeNext = NULL)
	{
		data = item;
		next = nodeNext;
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
	//修改指针域
	void setNext(ListNode* next){
		this->next = next;
	}

public:
	friend class LinkList<DataType>;      //将LinkList设为友元类，方便其对node的成员数据和方法的访问
	ListNode<DataType> *next;             //指向下一个结点的指针
	DataType data;                        //节点中的数据
};

/*************在链表的第i个结点后插入新结点***************/
template<typename DataType> bool LinkList<DataType>::insertNode(int i, DataType newData)
{
	ListNode<DataType> *p = head;                //设置游标指针，初始化为头结点地址
	int j;
	for (j = 1; j <= i - 1; j++)                       //查找第i个结点，指针需要移动i-1次
	{
		p = p->next;
		if (p == NULL)                          //如果指针为空，则不存在该结点，或已到表尾
		{

			break;
		}

	}
	if (p == NULL && j < (i - 1))                      //指针为空且没有到第i个位置，说明不存在第i个结点
	{
		std::cout << "插入位置无效！" << endl;
		return false;
	}
	ListNode<DataType> *node = new ListNode<DataType>(newData);     //建立新结点node      
	node->next = p->next;                                           //将node的next指针赋值为p的后继结点地址
	p->next = node;                                                 //p的后继指针指向node
	return true;
}

/***********************在单链表表尾添加新结点*****************************/
template<typename DataType> bool LinkList<DataType>::insertNode(DataType newData)
{
	ListNode<DataType> *p = head;                               //设置游标指针
	ListNode<DataType> *node = new ListNode<DataType>(newData); //创建新结点
	if (node == NULL)                                            //如果新结点内存分配失败，返回false
	{
		return false;
	}
	while (p->next != NULL)                                 //遍历单链表，找到尾结点
	{
		p = p->next;
	}
	p->next = node;                                        //将尾结点next指针指向新结点
	return true;
}

template<typename DataType> 
bool LinkList<DataType>::insertNode(ListNode<DataType>* node)
{
	ListNode<DataType>* pHead = head;
	if (NULL == node)
	{
		return false;
	}
	while (NULL != pHead->next)
	{
		pHead = pHead->next;
	}
	pHead->next = node;
	return true;
}


/*******************删除指定结点*******************/
template<typename DataType> bool LinkList<DataType>::removeNode(ListNode<DataType> *q)
{
	if (q == NULL)                                       //判断待删除结点是否存在
	{
		std::cout << "待删除结点不存在！" << std::endl;
		return false;
	}
	ListNode<DataType> *tempPointer = head;            //设置游标指针，初始化为头结点
	while (tempPointer->next != q)                      //遍历单链表，找到q所指向的结点的前驱结点
	{
		tempPointer = tempPointer->next;
	}
	tempPointer->next = q->next;                       //将q结点的后继结点地址赋值给其前驱结点的next指针
	delete q;                                          //回收结点q的空间
	return true;
}

/*********************查找指定值的结点***************/
template<typename DataType> ListNode<DataType>* LinkList<DataType>::findNode(DataType value)
{
	ListNode<DataType> *currentPointer = head;               //设置游标指针
	//判定游标指针所指结点的值是否与value相等
	while (currentPointer != NULL && currentPointer->data != value)
	{
		currentPointer = currentPointer->next;
	}
	if (currentPointer == NULL)                              //判定所找结点是否存在
	{
		std::cout << "没有找到该结点！程序退出！" << endl;
		exit(1);
	}
	else
	{
		return currentPointer;                             //返回所找到的结点的指针
	}
}
/********************清空链表***********************/
template<typename DataType> void LinkList<DataType>::cleanLink()
{
	ListNode<DataType> *current = head;                   //设置游标指针
	while (head->next != NULL)                             //判断head的后继结点是否为NULL
	{
		current = head->next;                             //将current指向head的后继结点
		head->next = current->next;                       //将current的后继地址赋值给head的next域
		delete current;                                   //回收current结点所占的空间
	}
}
/*********************获取结点数据******************/
template<typename DataType> DataType LinkList<DataType>::getNodeData(int index)
{
	int linkLength = getLength();
	if (index < 1 || index > linkLength)
	{
		std::cout << "结点不存在！" << std::endl;
		return false;
	}
	else
	{
		ListNode<DataType> *pmove = head->next;
		for (int i = 1; i < index&&pmove; i++)
		{
			pmove = pmove->next;
		}
		return pmove->getData();
	}
}
/******************获取链表长度********************/
template<typename DataType> int LinkList<DataType>::getLength()
{
	int count = 0;
	ListNode<DataType> *p = head->next;
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}

/********************查找链表第i个元素********************/
template<typename DataType> ListNode<DataType>* LinkList<DataType>::getNode(int i)
{
	ListNode<DataType> *p = head->next;
	int j;
	if (i<1 || i>getLength() - 1)                //带头结点所以实际节点数需减1
	{
		return false;
	}
	for (j = 1; j < i; j++)
	{
		p = p->next;
		if (p == NULL)
		{
			break;
		}
	}
	if (p == NULL && j < i - 1)
	{
		return false;
	}
	return p;
}


template<typename DataType>
void LinkList<DataType>::printLinkList()
{
	cout << "printLinkList:" << endl;
	ListNode<DataType> *p = head->next;
	while (NULL != p)
	{
		cout << p->getData() << ",";
		p = p->next;
	}
	cout << endl;
}




bool isCircleLink(ListNode<int>* head)
{
	if (NULL == head)
	{
		return false;//如果头结点为NULl，返回false
	}
	ListNode<int>* p;
	ListNode<int>* q;
	p = q = head;//初始化头指针head
	while (NULL != p && NULL != q && NULL != q->next)
	{
		p = p->next;//p每次移动1步
		q = q->next->next;//q每次移动2步
		if (p == q)
		{
			cout << "p:" << p->getData() << endl;
			cout << "q:" << q->getData() << endl;
			break;
		}
	}
	if (p == q && NULL != p)
	{
		return true;//相遇，且不为NULL则有环
	}
	else
	{
		return false;//无环
	}
}


ListNode<int>* circleStart(ListNode<int>* head)
{
	if (NULL == head)
	{
		return false;//如果头结点为NULl，返回false
	}
	//设置跑步指针
	ListNode<int>* p;
	ListNode<int>* q;
	p = q = head;//初始化指针为head 
	while (NULL != q && NULL != q->next)
	{
		p = p->next;//p每次走1步
		q = q->next->next;//q每次走2步
		if (p == q)
		{
			break;
		}
	}

	//相遇且不为NULL，则有环
	if (p == q && NULL != p)
	{
		//快指针重新赋值
		q = head;
		while (p != q)
		{
			//继续移动，直到相遇
			p = p->next;
			q = q->next;
		}
		return p;//返回相遇结点，即为环起始位置
	}
	else
	{
		return NULL;//否则无环
	}
}


int main()
{
	LinkList<int>* list = new LinkList<int>();
	ListNode<int>* head = new ListNode<int>(666, NULL);//设置头结点
	list->insertNode(head);//添加头结点
	for (int i = 1; i <= 10; i++)
	{
		list->insertNode(i * 3);//添加链表，此时链表无环
	}

	//输出单链表
	list->printLinkList();
 	if (isCircleLink(list->getNode(1)))
 	{
 		cout << "该链表有环" << endl;
 	}
 	else
 	{
 		cout << "该链表无环" << endl;
 	}





	//构造有环链表
	ListNode<int>* q = new ListNode<int>(777, list->getNode(5));
	list->insertNode(q);
	
	cout << "------------------------start" << endl;
	ListNode<int>* p = head;
	int iCount = 0;
	while (NULL != p)
	{
		cout << p->getData() << ",";
		p = p->next;
		iCount++;
		if (iCount > 30)
		{
			break;
		}
	}
	cout << endl<<"------------------------end" << endl;

	//慎用getNode，因为在调用getLength的时候，如果有环，会造成死循环
	if (isCircleLink(head))
	{
		cout << "该链表有环" << endl;
		cout << "circleStart:" << circleStart(head)->getData() << endl;
	}
	else
	{
		cout << "该链表无环" << endl;
	}


	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}


/******



*****/
