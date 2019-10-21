/*

用C++实现一个顺序表，使其可以存储10个整型数据，并可以实现插入、修改元素、删除元素和输出整个顺序表的功能。

*/

#include <iostream>
using namespace std;

/**************线性表数据结构******************/
template <typename DataType> class SeqList
{
public:
	//构造函数
	SeqList(int size = defaultSize)
	{
		//检查赋予的顺序表大小，如果合法则分配相应大小的内存
		if (size > 0)
		{
			maxSize = size;
			length = 0;
			elements = new DataType[maxSize];// 分配内存大小
			for (int i = 0; i < maxSize; i++)
			{
				elements[i] = NULL;
			}
		}
	}
	//析构函数
	~SeqList()
	{
		delete[] elements;//回收内存空间
	}
	bool insertElement(DataType data);//向表尾插入新元素
	bool deleteElement(int location);//删除指定位置的元素
	DataType getElement(int location);//返回指定位置的元素
	bool changeElement(int location, DataType newData);//修改指定位置的元素值
	//获取顺序表长度
	int getLength()
	{
		return length;
	}
	

private:
	static const int defaultSize = 10;
	DataType* elements;
	int maxSize;//顺序表最大大小
	int length;//顺序表的有效长度
};



/*********************顺序表插入操作***********************/
template<typename DataType>bool SeqList<DataType>::insertElement(DataType data)
{
	int currentIndex = length;//记录新元素的插入位置
	if (length >= maxSize)//判断顺序表是否已满
	{
		return false;
	}
	else
	{
		elements[currentIndex] = data;//将新元素插入顺序表表尾
		length++;//顺序表有效长度加1
		return true;
	}
}


/*********************获取指定位置的元素*******************************/
template<typename DataType>DataType SeqList<DataType>::getElement(int location)
{
	if (location<0 || location>length)
	{
		std::cout << "参数非法" << std::endl;
		return 0;
	}
	else
	{
		return elements[location];//返回指定位置的元素
	}
}


/***********************删除指定位置元素*****************************/
template<typename DataType>bool SeqList<DataType>::deleteElement(int location)
{
	if (location < 0 || location >= length)//验证位置索引参数是否有效
	{
		return false;
	}
	else
	{
		for (int i = location; i < length; i++)
		{
			elements[i] = elements[i + 1];//将指定位置之后的元素依次往前移动覆盖前一个元素
		}
		length--;//顺序表长度减1
		return true;
	}
}


/*********************修改指定位置的元素值*******************************/
template<typename DataType>bool SeqList<DataType>::changeElement(int location, DataType newData)
{
	if (location < 0 || location >= length)//验证位置索引参数是否有效
	{
		return false;
	}
	else
	{
		elements[location] = newData;//将指定位置赋给新元素
		return true;
	}
}



/****************************************************/




int main()
{
	SeqList<int> list(10);//建立顺序表
	for (int i = 0; i < 10; i++)
	{
		list.insertElement(i * 10);//插入数据实现初始化
	}

	cout << "初始化后的顺序表：" << endl;
	//输出初始化后的顺序表
	for (int i = 0; i < list.getLength(); i++)
	{
		cout << list.getElement(i) << " ,";
	}
	cout << endl;


	cout << "删除索引为3的元素后的顺序表：" << endl;
	//删除索引为3的元素
	list.deleteElement(3);
	//输出删除元素后的顺序表
	for (int i = 0; i < list.getLength(); i++)
	{
		cout << list.getElement(i) << " ,";
	}
	cout << endl;


	cout << "输出修改后的顺序表：" << endl;
	//将顺序表索引为5的元素值修改为44
	list.changeElement(5, 44);
	//输出修改后的顺序表
	for (int i = 0; i < list.getLength(); i++)
	{
		cout << list.getElement(i) << " ,";
	}
	cout << endl;


	cout << "Hello World C++ Algorithm." << endl;
	system("pause");
	return 0;
}

