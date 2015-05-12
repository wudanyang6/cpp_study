#ifndef _MPRIORITYQUEUE_H_
#define _MPRIORITYQUEUE_H_
#include "MPNode.h"
#include <fstream>

template <class T>
class MPQueue
{
public:
	MPQueue(int maxsize)
	{
		heap = new MPNode<T>[maxsize+1]; 
		heap[0].setKey(1<<31); 
		this->MaxSize = maxsize; 
		this->CurrentSize = 0; 
		cout<<"creat the heap[] is ok"<<endl;
	};
	~MPQueue()
	{
		delete []heap; 
		cout<<"delete the heap[] is ok"<<endl;
	};


	void MaxHeapify(int i);
	void Output();
	void Insert(MPNode<T> insertData);
	MPNode<T> MaxValue();
	MPNode<T> ExtractMax();
	void IncreaseKey(int x, int key);			//将x的键增大，并且最少要增大到比现在大或等于现在的键，即：newK >= oldK
	void exchange(int A, int B);				//调换堆中的两个元素位置
	int getCurrentSize();

private:
	int CurrentSize, MaxSize;					//当前大小、最大容量
	MPNode<T> *heap;							//指向数据
};

template <class T>
int MPQueue<T>::getCurrentSize()
{
	return CurrentSize;
}


template <class T>
void MPQueue<T>::Insert(MPNode<T> insertData)
{
	if(CurrentSize == MaxSize)
	{ 
		cout<<"The heap[] is full."<<endl; 
		return;
	}

	int x = ++CurrentSize;
	heap[x].setKey(-1);
	if (insertData.getKey() >= heap[x].getKey())
	{
		//while (x > 1 && heap[x/2].getKey() < insertData.getKey())
		//{
		//	exchange(x, x/2);
		//	x = x/2;
		//}
		//heap[x] = insertData;
		for (; x > 1 && heap[x/2].getKey() < insertData.getKey(); x /= 2)
		{
			heap[x] = heap[x/2];
		}
		heap[x] = insertData;
	}
	else
	{
		cout << "new key is smaller than current key." << endl;
	}

	//this->IncreaseKey(++CurrentSize, insertData.getKey());
}



template <class T>
MPNode<T> MPQueue<T>::MaxValue()
{
	if (CurrentSize == 0)
	{
		throw exception("no element");
	}
	return heap[1];
}

template <class T>
void MPQueue<T>::IncreaseKey(int x, int key)
{
	if (x <= CurrentSize)
	{
		if (key >= heap[x].getKey())
		{
			heap[x].setKey(key);
			while (x > 1 && heap[x/2].getKey() < key)
			{
				exchange(x, x/2);
				x = x/2;
			}
		}
		else
		{
			cout << "new key is smaller than current key." << endl;
		}
	}
	else
	{
		cout << "out of bound." << endl;
	}
}

template <class T>
void MPQueue<T>::MaxHeapify(int i)
{
	int L, R, largest;
	L = 2*i;
	R = L+1;

	if (L <= CurrentSize && heap[L].getKey() > heap[i].getKey())
	{
		largest = L;
	}
	else
	{
		largest = i;
	}
	if (R <= CurrentSize && heap[R].getKey() > heap[largest].getKey())
	{
		largest = R;
	}


	if (largest != i)
	{
		exchange(i, largest);
		MaxHeapify(largest);
	}


}


template <class T>
MPNode<T> MPQueue<T>::ExtractMax()
{
	MPNode<T> max;//键值最大的键
	if (CurrentSize == 0)
	{
		throw exception("no element");
	}
	max = heap[1];
	heap[1] = heap[CurrentSize--];//将最后一个元素放到根节点，并且当前大小减一

	MaxHeapify(1);

	return max;
}

//交换两个元素
template <class T>
void MPQueue<T>::exchange(int A, int B)
{
	MPNode<T> temp;

	temp = heap[A];
	heap[A] = heap[B];
	heap[B] = temp;
}


//输出优先队列
template<class T>
void MPQueue<T>::Output()
{
	MPNode<T> max;
	std::ofstream out;
	out.open("priorityQueue.txt");

	while (CurrentSize)
	{
		max = ExtractMax();
		out << "key:" << max.getKey() << "\tvalue:" << max.getValue() << endl;
	}
	cout << "导出成功！查看priorityQueue.txt。" << endl;
}

#endif